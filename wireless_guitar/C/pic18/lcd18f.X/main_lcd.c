#include <xc.h>
#include <stdio.h>
#include "../common_files/h/common_defs&vars.h"
#include "../common_files/h/config2550.h"
#include "../common_files/h/timer0.h"
#include "../common_files/h/uart_m.h"
#include "../common_files/h/interrupts.h"
#include "lcd_hd44780.h"


// Hardware defines
#define BUTTON_DOWN !PORTBbits.RB0
#define BUTTON_BACK !PORTBbits.RB1
#define BUTTON_UP   !PORTBbits.RB2
#define BUTTON_OK   !PORTBbits.RB3

#define INP_B_DOWN  0x01
#define INP_B_UP    0x02
#define INP_B_OK    0x04
#define INP_B_BACK  0x08
#define INP_RX_FLAG 0x10

#define LCD_UPDATE() lcd_update()
#define STATE_NEW_STATE(new_state){\
fsm_new_state = new_state;\
lcd_update();\
}
#define INP_BUTTON_CLEAR() (inputs = inputs & 0x10)
#define INP_UART_CLEAR() (inputs = inputs & 0x0F)



// Functions
unsigned char read_buttons(void);
void lcd_update(void);
void lcd_start_up(void);
void lcd_screensaver(void);
void lcd_connection(void);
void _delay_10ms(int length);

// Variables
unsigned char read_data, new_data, inputs = 0;
unsigned char buttons_new, buttons_old, buttons_change;
unsigned char uart_tx_block[UART_LENGTH];
unsigned char uart_rx_block[UART_LENGTH];
unsigned char uart_block_count = 0;
unsigned char i, j,first, scrs, scrs_cnt, scrs_speed,brightness;


lcd_fsm_state fsm_new_state, fsm_old_state = lINIT;
main_menu_state main_menu = mMENU;
sub_menu_lcd_state sub_menu = smBRIGHTNESS;


void init_pic() {
    TRISA = 0x00;
    TRISB = 0x0F;   // RB7-RB4: brightness, RB3-RB0: buttons
    TRISC = 0x00;

    ADCON1bits.PCFG = 0b1111;
    // Timer 0 init
    init_timer0(TMR0_16_bit,TMR0_PRESC_ON,TMR0_PRESC_4);
    init_uart_m(12, 0, 0); //57600 -- lcd writing

    RCIF = 0;
    RCIE = 1;
    PEIE = 0;

    brightness = 4;
    LCDLedOff();
}

void main(void) {
    init_pic();
    TMR0IF = 0;
    TMR0ON = 1;
    GIEH = 1;
    GIEL = 1;
    while (1) {
        if(TMR0IF) {
            if(!(inputs & 0x10))
                inputs = read_buttons();

            // Transition of FSM
            switch (fsm_old_state) {
                case lINIT:
                    STATE_NEW_STATE(lSEARCH_A);
                    break;

                case lSEARCH_A:
                    switch (inputs) {
                        case INP_B_DOWN:
                            break;
                        case INP_B_UP:
                            break;
                        case INP_B_OK:
                            break;
                        case INP_B_BACK:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case INP_RX_FLAG:
                            INP_UART_CLEAR();
                            if ((uart_rx_block[SER_COMMAND] == (ANOUCHKA + lSEARCH_A))) {
                                if((uart_rx_block[SER_HW]) == HW_A) {      // Anouchka is there
                                    STATE_NEW_STATE(lSEARCH_HW);
                                    first = 0;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    break;

                case lSEARCH_HW:
                    switch (inputs) {
                        case INP_B_DOWN:
                            break;
                        case INP_B_UP:
                            break;
                        case INP_B_OK:
                            break;
                        case INP_B_BACK:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case INP_RX_FLAG:
                            INP_UART_CLEAR();
                            if ((uart_rx_block[SER_COMMAND] == (ANOUCHKA + lSEARCH_HW))) {
                                if(uart_rx_block[SER_HW] == (HW_P + HW_Pnrf + HW_A + HW_Anrf)) { // wait until all hardware found
                                    STATE_NEW_STATE(lWAIT);
                                    first = 0;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    break;

                case lWAIT:
                    switch (inputs) {
                        case INP_B_DOWN:
                            break;
                        case INP_B_UP:
                            break;
                        case INP_B_OK:
                            STATE_NEW_STATE(lTRANSMIT);
                            break;
                        case INP_B_BACK:
                            break;
                        case INP_RX_FLAG:
                            break;
                        default:
                            break;
                    }
                    break;

                case lTRANSMIT:
                    switch (inputs) {
                        case INP_B_DOWN:
                            break;
                        case INP_B_UP:
                            break;
                        case INP_B_OK:
                            break;
                        case INP_B_BACK:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case INP_RX_FLAG:
                            INP_UART_CLEAR();
                            break;
                        default:
                            break;
                    }
                    break;

                case lMENU:
                    switch (inputs) {
                        case INP_B_DOWN:
                            STATE_NEW_STATE(lMENU_DOWN);
                            break;
                        case INP_B_UP:
                            STATE_NEW_STATE(lMENU_UP);
                            break;
                        case INP_B_OK:
                            STATE_NEW_STATE(lMENU_OK);
                            break;
                        case INP_B_BACK:
                            STATE_NEW_STATE(lTRANSMIT);
                            break;
                        case INP_RX_FLAG:
                            INP_UART_CLEAR();
                            break;
                        default:
                            break;
                    }
                    break;

                case lMENU_UP:
                    STATE_NEW_STATE(lMENU);
                    break;

                case lMENU_DOWN:
                    STATE_NEW_STATE(lMENU);
                    break;

                case lMENU_OK:
                    switch (main_menu) {
                        case mMENU:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case mRESET:
                            STATE_NEW_STATE(lRESET);
                            break;
                        case mSTEMMEN:
                            STATE_NEW_STATE(lSTEMMEN);
                            break;
                        case mMETRONOOM:
                            STATE_NEW_STATE(lMETRONOOM);
                            break;
                        case mMOPJE:
                            STATE_NEW_STATE(lMOPJE);
                            break;
                        case mTETTEN:
                            STATE_NEW_STATE(lTETTEN);
                            break;
                        case mLCD:
                            STATE_NEW_STATE(lLCD);
                            break;
                        default:
                            break;
                    } 
                    break;

                case lRESET:
                    STATE_NEW_STATE(lINIT);
                    break;

                case lSTEMMEN:
                    STATE_NEW_STATE(lMENU);
                    break;

                case lMETRONOOM:
                    STATE_NEW_STATE(lMENU);
                    break;

                case lMOPJE:
                    STATE_NEW_STATE(lMENU);
                    break;

                case lTETTEN:
                    switch (inputs) {
                        case INP_B_BACK:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case INP_B_UP:
                            if(scrs_speed >= 10){
                                scrs_speed -= 10;
                            }
                            break;
                        case INP_B_DOWN:
                            if(scrs_speed <= 50){
                                scrs_speed += 10;
                            }
                            break;
                        default:
                            STATE_NEW_STATE(lTETTEN);
                            break;
                    }
                    break;

                case lLCD:
                    switch (inputs) {
                        case INP_B_BACK:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case INP_B_OK:
                            STATE_NEW_STATE(lMENU);
                            break;
                        case INP_B_UP:
                            if(brightness < BRIGHTNESS_MAX){
                                brightness++;
                            }
                            STATE_NEW_STATE(lLCD);
                            break;
                        case INP_B_DOWN:
                            if(brightness > BRIGHTNESS_MIN){
                                brightness--;
                            }
                            STATE_NEW_STATE(lLCD);
                            break;
                        default:
                            STATE_NEW_STATE(lLCD);
                            break;
                    }
                    break;

                default:
                    break;
            }

            // Output  FSM ************************************************************************************
            // ------------------------------------------------------------------------------------------------
            // ************************************************************************************************
            switch (fsm_old_state) {
                case lINIT:
                    main_menu = mMENU;
                    scrs_speed = 20;
                    first = 0;
                    enable_uart_m(); // Enable uart
                    uart_block_count = 0;
                    LCDInit(LS_NONE); // Initialize the LCD Module
                    LCDClear(); // Clear the display
                    LCDBrightness(brightness);
                    LCDLedOn();
                    lcd_start_up(); // Write start up string
                    
                    break;

                case lSEARCH_A:
                    uart_tx_block[SER_COMMAND] = (LCD + lSEARCH_A);
                    uart_write_block(uart_tx_block, UART_LENGTH);
                    LCD_UPDATE();
                    break;

               case lSEARCH_HW:
                   if(!first) {
                        uart_tx_block[SER_COMMAND] = (LCD + lSEARCH_HW);
                        uart_write_block(uart_tx_block, UART_LENGTH);
                        LCD_UPDATE();
                        first = 1;
                   }
                    break;

                case lWAIT:
                    if(first) {
                        uart_tx_block[SER_COMMAND] = (LCD + lWAIT);
                        uart_write_block(uart_tx_block, UART_LENGTH);
                        LCD_UPDATE();
                        first = 0;
                    }
                    if(fsm_new_state == lTRANSMIT) {
                        uart_tx_block[SER_COMMAND] = (LCD + lTRANSMIT);
                        uart_write_block(uart_tx_block, UART_LENGTH);
                        LCD_UPDATE();
                    }
                    break;

                case lTRANSMIT:
                    break;

                case lMENU:                   
                    break;

                case lMENU_UP:
                    if (main_menu > MENU_MIN)
                        main_menu--;
                    LCD_UPDATE();
                    break;

                case lMENU_DOWN:
                    if (main_menu < MENU_MAX)
                        main_menu++;
                    LCD_UPDATE();
                    break;

                case lMENU_OK:
                    break;

                case lRESET: 
                    break;

                case lSTEMMEN:
                    break;

                case lMETRONOOM:
                    break;

                case lMOPJE:
                    break;

                case lTETTEN:
                    LCD_UPDATE();
                    break;

                case lLCD:
                    LCDBrightness(brightness);
                    LCD_UPDATE();
                    break;

                default:
                    break;
            }
            fsm_old_state = fsm_new_state;
            TMR0IF = 0;
        }

    }

}

/*******************************************************************************
 *              Interrupt handler
 *              -----------------
 *
 * Uart interrupts: count UART_LENGTH RX interrupts, when UART_LENGT bytes
 * received, set rx flag
 *******************************************************************************/
void interrupt ISR() {
    if (RCIF) {
        uart_rx_block[uart_block_count] = RCREG;
        uart_block_count++;
        if (uart_block_count == UART_LENGTH) {
            uart_block_count = 0;
            inputs = (0xFF & INP_RX_FLAG); // Clear all other inputs, set uart flag
        }
        
    }
}

/*******************************************************************************
 *              Read Buttons
 *              ------------
 *
 * Update the buttons, only when HIGH to LOW
 * Do not update when there is no change
 *******************************************************************************/
unsigned char read_buttons(){
    buttons_change = 0;
    buttons_new = ((BUTTON_BACK<<3) + (BUTTON_OK<<2) + (BUTTON_UP<<1) + (BUTTON_DOWN));
    if((buttons_new != 0) && (buttons_old == 0) && (buttons_old != buttons_new))
        buttons_change = 1;
    else
        buttons_change = 0;

    buttons_old = buttons_new;
    
    if(buttons_change) {
        return buttons_new;
    } else {
        return 0x00;
    }
}


/*******************************************************************************
 *              LCD basic programs
 *              ------------------
 *
 * All the programs the LCD can run in the finite state machine
 * - update: date lcd up
 * - start up screen: roll text over screen
 * - screensaver: bouncing tits
 *******************************************************************************/
void lcd_update(void) {
        switch (fsm_new_state) {
            case lINIT:
                break;
            case lSEARCH_A:
                lcd_connection();
                break;
            case lSEARCH_HW:
                lcd_connection();
                break;
            case lWAIT:
                LCDWriteStringXY(0, 0, "Druk 'OK' om te ");
                LCDWriteStringXY(0, 1, "beginnen        ");
                break;
            case lTRANSMIT:
                LCDWriteStringXY(0, 0, "Transmit        ");
                LCDWriteStringXY(0, 1, "                ");
                break;
            case lMENU:
                LCDWriteStringXY(0, 0, "Menu:  >        ");
                LCDWriteStringXY(0, 1, "                ");
                switch (main_menu) {
                    case mMENU:
                        LCDWriteStringXY(8, 0, "-kies-< ");
                        LCDWriteStringXY(8, 1, "Reset   ");
                        break;
                    case mRESET:
                        LCDWriteStringXY(8, 0, "Reset   ");
                        LCDWriteStringXY(8, 1, "Stemmen ");
                        break;
                    case mSTEMMEN:
                        LCDWriteStringXY(8, 0, "Stemmen ");
                        LCDWriteStringXY(8, 1, "Click   ");
                        break;
                    case mMETRONOOM:
                        LCDWriteStringXY(8, 0, "Click   ");
                        LCDWriteStringXY(8, 1, "Mopje   ");
                        break;
                    case mMOPJE:
                        LCDWriteStringXY(8, 0, "Mopje   ");
                        LCDWriteStringXY(8, 1, "Tetten  ");
                        break;
                    case mTETTEN:
                        LCDWriteStringXY(8, 0, "Tetten  ");
                        LCDWriteStringXY(8, 1, "Bright..");
                        break;
                    case mLCD:
                        LCDWriteStringXY(8, 0, "LCD ins..");
                        LCDWriteStringXY(8, 1, "stelling ");
                        break;
                    default:
                        break;
                }

                break;
            case lMENU_UP:
                break;
            case lMENU_DOWN:
                break;
            case lMENU_OK:
                break;
            case lRESET:
                LCDWriteStringXY(0, 0, "R E S E T       ");
                LCDWriteStringXY(0, 1, "                ");
                _delay_10ms(100);
                break;
            case lSTEMMEN:
                LCDWriteStringXY(0, 0, "S T E M M E N   ");
                LCDWriteStringXY(0, 1, "                ");
                _delay_10ms(100);
                break;
           case lMETRONOOM:
                LCDWriteStringXY(0, 0, "C L I C K       ");
                LCDWriteStringXY(0, 1, "                ");
                _delay_10ms(100);
                break;
           case lMOPJE:
                LCDWriteStringXY(0, 0, "M O P K E       ");
                LCDWriteStringXY(0, 1, "                ");
                _delay_10ms(100);
                break;
            case lTETTEN:
                scrs_cnt++;
                if(scrs_cnt == scrs_speed) {
                    lcd_screensaver();
                    scrs_cnt = 0;
                }
                break;
           case lLCD:
                LCDWriteStringXY(0, 0, "BRIGHTNESS      ");
                LCDWriteIntXY(0,1,brightness,2);
                break;
    }

}

void lcd_start_up() {
    unsigned char busy = 1;
    unsigned char x_pos = 0;
    unsigned char start[] = "Waldo";
    const char *st = start;
    while (busy) {
        LCDClear();
        LCDWriteStringXY(x_pos, 0, st);
        st++;

        if (*st == '\0') {
            busy = 0;
            x_pos = 0;
            LCDClear();
        }
        _delay_10ms(50);
    }
}


void lcd_connection(void) {
    LCDLoadCostum(3);
    // A
    LCDWriteStringXY(0, 0, "%0");
    LCDWriteStringXY(1, 0, "%1");
    LCDWriteStringXY(0, 1, "%4");
    LCDWriteStringXY(2, 1, "%5");
    // P
    LCDWriteStringXY(14, 0, "%2");
    LCDWriteStringXY(15, 0, "%3");
    LCDWriteStringXY(14, 1, "%6");
    LCDWriteStringXY(15, 1, "%7");
    LCDWriteStringXY(13, 1, "%5");

    if(i%4) {
        LCDWriteStringXY(3,0,"Connecting");
    } else {
        LCDWriteStringXY(3,0,"          ");
    }
    if(j) {
        LCDWriteStringXY(2+i, 1,"\176");
        _delay_10ms(20);
    } else {
        LCDWriteStringXY(2+i, 1,"\177");
        _delay_10ms(20);
    }
            
    if (i == 11 || i == 0) {
        j = !j;
    }

    if (j) {
        i++;
    } else {
        i--;
    }
}

void lcd_screensaver(void) {
    if ((i == 0) || (i == 4) || (i == 8)) {
        LCDLoadCostum(2);
    }
    if ((i == 1) || (i == 3) || (i == 5) || (i == 7) || (i == 9)) {
        LCDLoadCostum(1);
    }
    if ((i == 2) || (i == 6) || (i == 10)) {
        LCDLoadCostum(0);
    }

    LCDClear();
    LCDWriteStringXY(i, 0, "%0");
    LCDWriteStringXY(i + 1, 0, "%1");
    LCDWriteStringXY(i + 2, 0, "%2");

    LCDWriteStringXY(i, 1, "%3");
    LCDWriteStringXY(i + 1, 1, "%4");
    LCDWriteStringXY(i + 2, 1, "%5");


    LCDWriteStringXY(i + 3, 0, "%0");
    LCDWriteStringXY(i + 4, 0, "%1");
    LCDWriteStringXY(i + 5, 0, "%2");

    LCDWriteStringXY(i + 3, 1, "%3");
    LCDWriteStringXY(i + 4, 1, "%4");
    LCDWriteStringXY(i + 5, 1, "%5");

    if (i == 10 || i == 0) {
        j = !j;
    }

    if (j) {
        i++;
    } else {
        i--;
    }
}


