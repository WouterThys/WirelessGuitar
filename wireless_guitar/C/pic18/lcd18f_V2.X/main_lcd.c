#include <xc.h>
#include <stdio.h>
#include "../common_files/h/common_defs&vars.h"
#include "../common_files/h/config2550.h"
#include "../common_files/h/timer0.h"
#include "../common_files/h/uart_m.h"
#include "../common_files/h/interrupts.h"
#include "lcd_hd44780.h"
#include "myutils.h"

// Functions
unsigned char read_buttons(void);
void _delay_10ms(int length);

// Variables
unsigned char i, j, first, scrs, scrs_cnt, scrs_speed, brightness;
unsigned char read_data, new_data, inputs, go_back;
unsigned char buttons_new, buttons_old, buttons_change;
unsigned char uart_tx_block[UART_LENGTH];
unsigned char uart_rx_block[UART_LENGTH];
struct SerialStruct SerialRx, SerialTx;
unsigned char uart_block_count = 0;
unsigned short lSEARCH_Acnt, lSEARCH_HWcnt = 0;


void init_pic() {
    TRISA = 0x00;
    TRISB = 0x0F;   // RB7-RB4: brightness, RB3-RB0: buttons
    TRISC = 0x00;

    ADCON1bits.PCFG = 0b1111;
    init_uart_m(12, 0, 0); //57600 -- lcd writing

    RCIF = 0;
    RCIE = 1;
    PEIE = 0;

    brightness = 1;
    LCDLedOff();
}

void main(void) {
    init_pic();
    scrs_speed = 10;
    LCDInit(LS_NONE); // Initialize the LCD Module
    LCDClear(); // Clear the display
    LCDBrightness(brightness);
    TMR0IF = 0;
    init_timer0(TMR0_16_bit,TMR0_PRESC_ON,TMR0_PRESC_4);
    GIEH = 1;
    GIEL = 1;
    while (1) {
        LCDWriteIntXY(15,1,fsm_old_state,1);
        if(TMR0IF) {
            LATAbits.LA0 = !LATAbits.LA0;
            if(!(inputs & 0x10))
                inputs = read_buttons();

            // TRANSITION  FSM ********************************************************************************
            // ------------------------------------------------------------------------------------------------
            // ************************************************************************************************
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
                            if (SerialRx.Command == lSEARCH_A) {
                                if(SerialRx.Hardware == HW_A) {      // Anouchka is there
                                    STATE_NEW_STATE(lSEARCH_HW);
                                    lSEARCH_Acnt = lSEARCH_HWcnt = first = 0;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    lSEARCH_Acnt++;
                    if(lSEARCH_Acnt >= 1023) {
                        lSEARCH_Acnt = 0;
                        j = i = 0;
                        STATE_NEW_STATE(lTIMEOUT);
                    }
                    go_back = lSEARCH_A;
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
                            if (SerialRx.Command == lSEARCH_HW) {
                                if(SerialRx.Hardware == (HW_P + HW_Pnrf + HW_A + HW_Anrf)) { // wait until all hardware found
                                    STATE_NEW_STATE(lWAIT);
                                    lSEARCH_Acnt = lSEARCH_HWcnt = 0;
                                }
                            }
                            break;
                        default:
                            break;
                    }
                    lSEARCH_HWcnt++;
                    if(lSEARCH_HWcnt >= 1023) {
                        j = i = 0;
                        STATE_NEW_STATE(lTIMEOUT);
                    }
                    go_back = lSEARCH_HW;
                    break;

                case lWAIT:
                    switch (inputs) {
                        case INP_B_DOWN:
                            break;
                        case INP_B_UP:
                            break;
                        case INP_B_OK:
                            STATE_NEW_STATE(lTRANSMIT);     // Show message on lcd, wait untill user is ready
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
                    go_back = lWAIT;
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
                    go_back = lTRANSMIT;
                    break;

                case lMENU:
                    lcd_main_menu_fsm(go_back);
                    INP_UART_CLEAR();
                    break;

                case lTIMEOUT:
                    switch (inputs) {
                        case INP_B_DOWN:
                            break;
                        case INP_B_UP:
                            break;
                        case INP_B_OK:
                            STATE_NEW_STATE(go_back);
                            lSEARCH_HWcnt = lSEARCH_Acnt = scrs_cnt = i = j = 0;
                            LCD_UPDATE();
                            break;
                        case INP_B_BACK:
                            break;
                        case INP_RX_FLAG:
                            INP_UART_CLEAR();
                            break;
                        default:
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
                    main_menu_old = main_menu_new = mmMENU;
                    sub_menu_lcd = smBRIGHTNESS;
                    i = j = scrs_cnt = first = 0;
                    lSEARCH_Acnt = lSEARCH_HWcnt = 0;
                    enable_uart_m(); // Enable uart
                    uart_block_count = 0;
                    SerialTx.TransmitAddress = LCD;
                    LCDLedOn();
                    lcd_start_up(); // Write start up string
                    break;

                /* Keep sending Anouchka messages to check if she is there */
                case lSEARCH_A:
                    SerialTx.Command = lSEARCH_A;
                    SerialTransmit();
                    LCD_UPDATE();
                    break;

               /* Send Anouchka the command to search other nRF module, send only once */
               case lSEARCH_HW:
                   if(!first) {
                        SerialTx.Command = lSEARCH_HW;
                        SerialTransmit();
                        first = 1;
                   }
                   LCD_UPDATE();
                   break;

                case lWAIT:
                    if(first) {
                        SerialTx.Command = lWAIT;
                        SerialTransmit();
                        LCD_UPDATE();
                        first = 0;
                    }
                    if(fsm_new_state == lTRANSMIT) {
                        SerialTx.Command = lTRANSMIT;
                        SerialTransmit();
                        LCD_UPDATE();
                    }
                    break;

                case lTRANSMIT:
                    break;

                case lMENU:                   
                    break;

                case lTIMEOUT:
                    lcd_time_out(go_back);
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
    if (RCIF) { // Uart received, cleared in hardware when buffer is red
        uart_rx_block[uart_block_count] = RCREG;
        uart_block_count++;
        if (uart_block_count == UART_LENGTH) {
            uart_block_count = 0;
            SerialRx.TransmitAddress = (uart_rx_block[SER_COMMAND] & 0xF0);
            SerialRx.Command = (uart_rx_block[SER_COMMAND] & 0x0F);
            SerialRx.Hardware = uart_rx_block[SER_HW];
            SerialRx.Dat1 = uart_rx_block[SER_DAT1];
            SerialRx.Dat2 = uart_rx_block[SER_DAT2];
            SerialRx.Dat3 = uart_rx_block[SER_DAT3];
            SerialRx.Dat4 = uart_rx_block[SER_DAT4];
            SerialRx.Dat5 = uart_rx_block[SER_DAT5];
            SerialRx.Dat6 = uart_rx_block[SER_DAT6];

            if(SerialRx.TransmitAddress == ANOUCHKA)
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




