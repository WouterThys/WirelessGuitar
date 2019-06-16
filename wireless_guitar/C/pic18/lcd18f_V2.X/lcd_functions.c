#include <xc.h>
#include <stdio.h>
#include "../common_files/h/common_defs&vars.h"
#include "../common_files/h/config2550.h"
#include "../common_files/h/timer0.h"
#include "../common_files/h/uart_m.h"
#include "../common_files/h/interrupts.h"
#include "lcd_hd44780.h"
#include "myutils.h"

/*******************************************************************************
 *              Lcd menu Finite State Machine
 *              -----------------------------
 *
 * Finite state machine to select menu variables, updates for the lcd and
 * properties of the project
 *******************************************************************************/
unsigned char send = 0;
void lcd_main_menu_fsm(unsigned char mmOld) {
    switch (main_menu_old) {
        case mmMENU:
            switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld);     // Go back to lcd fsm
                    break;
                default:
                    break;
            }
            break;

        case mmRESET:
            switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    STATE_NEW_STATE(lINIT);           // Go to lcd INIT state
                    LCDLedOff();
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld);     // Go back to lcd fsm
                    break;
                default:
                    break;
            }
            break;

        case mmSTEMMEN:
            switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld);     // Go back to lcd fsm
                    break;
                default:
                    break;
            }
            break;

        case mmMETRONOOM:
           switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    mmSTATE_NEW_STATE(mmMETRONOOMsm);
                    send = 1;
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld);     // Go back to lcd fsm
                    break;
                default:
                    break;
            }
            break;

        case mmMOPJE:
            switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld);     // Go back to lcd fsm
                    break;
                default:
                    break;
            }
            break;

        case mmTETTEN:
             switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    mmSTATE_NEW_STATE(mmTETTENsm);
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld); // Go back to lcd fsm
                    break;
                default:
                    break;
            }
             break;

        case mmLCD:
            switch (inputs) {
                case INP_B_UP:
                    if (main_menu_old > mmMENU_MIN)
                        main_menu_new--;
                    LCD_UPDATE();
                    break;
                case INP_B_DOWN:
                    if (main_menu_old < mmMENU_MAX)
                        main_menu_new++;
                    LCD_UPDATE();
                    break;
                case INP_B_OK:
                    mmSTATE_NEW_STATE(mmLCDsm);
                    break;
                case INP_B_BACK:
                    STATE_NEW_STATE(mmOld);     // Go back to lcd fsm
                    break;
                default:
                    break;
            }
            break;

        case mmMETRONOOMsm:
            lcd_sub_menu_metronoom();
            switch (inputs) {
                case INP_B_UP:
                    break;
                case INP_B_DOWN:
                    break;
                case INP_B_OK:
                    break;
                case INP_B_BACK:
                    mmSTATE_NEW_STATE(mmMETRONOOM);
                    SerialTx.Command = lMENU;
                    SerialTx.Dat1 = 0;
                    SerialTransmit();
                    break;
                default:
                    break;
            }
            break;

        case mmTETTENsm:
            lcd_sub_menu_tetten();
            switch (inputs) {
                case INP_B_UP:
                    break;
                case INP_B_DOWN:
                    break;
                case INP_B_OK:
                    mmSTATE_NEW_STATE(mmTETTEN);
                    break;
                case INP_B_BACK:
                    mmSTATE_NEW_STATE(mmTETTEN);
                    break;
                default:
                    break;
            }
            break;

        case mmLCDsm:
            lcd_sub_menu_lcd();
            switch (inputs) {
                case INP_B_UP:
                    break;
                case INP_B_DOWN:
                    break;
                case INP_B_OK:
                    break;
                case INP_B_BACK:
                    mmSTATE_NEW_STATE(mmLCD);
                    break;
                default:
                    break;
            }
            break;
    }
    main_menu_old = main_menu_new;
}

/*******************************************************************************
 *              Lcd sub menu's
 *              --------------
 *
 * Sub menu routines
 * - sub menu metronoom: metronoom met maatsoort en tempo, zend waardes naar Anouchka
 * - sub menu tetten:  borstjes
 * - sub menu lcd: instellingen voor het lcd scherm
 *******************************************************************************/
unsigned char indicator = 0;
unsigned int indicator_cnt;
unsigned char m1 = 4;
unsigned char t1 = 1;
unsigned char t2 = 2;
unsigned char t3 = 0;
unsigned short tempo = 120;
void lcd_sub_menu_metronoom(void) {
    switch (inputs) {
        case INP_B_UP:
            break;
        case INP_B_DOWN:
            break;
        case INP_B_OK:
            if(sub_menu_metronoom < smMENU_METRONOOM_MAX)
                sub_menu_metronoom++;
            else
                sub_menu_metronoom = smM1;
            break;
        case INP_B_BACK:
            break;
        default:
            break;
    }

    switch (sub_menu_metronoom) {
        case smM1:
            LCDWriteStringXY(9, 1 , "^      ");
            switch (inputs) {
                case INP_B_UP:
                    send = 1;
                    if(m1 < 4)
                        m1++;
                    break;
                case INP_B_DOWN:
                    send = 1;
                    if(m1 > 1)
                        m1--;
                    break;
                default:
                    break;
            }
            break;

        case smT1:
            LCDWriteStringXY(9, 1 , "    ^  ");
            switch (inputs) {
                case INP_B_UP:
                    send = 1;
                    if(t1 < 3)
                        t1++;
                    else
                        t1 = 1;
                    break;
                case INP_B_DOWN:
                    send = 1;
                    if(t1 > 1)
                        t1--;
                    else
                        t1 = 3;
                    break;
                default:
                    break;
            }
            break;

        case smT2:
            LCDWriteStringXY(9, 1 , "     ^ ");
            switch (inputs) {
                case INP_B_UP:
                    send = 1;
                    if(t2 < 9)
                        t2++;
                    else
                        t2 = 0;
                    break;
                case INP_B_DOWN:
                    send = 1;
                    if(t2 > 0)
                        t2--;
                    else
                        t2 = 9;
                    break;
                default:
                    break;
            }
            break;

        case smT3:
            LCDWriteStringXY(9, 1 , "      ^");
            switch (inputs) {
                case INP_B_UP:
                    send = 1;
                    if(t3 < 9)
                        t3++;
                    else
                        t3 = 0;
                    break;
                case INP_B_DOWN:
                    send = 1;
                    if(t3 > 0)
                        t3--;
                    else
                        t3 = 9;
                    break;
                default:
                    break;
            }
            break;

        default:
            break;
    }
    LCDWriteIntXY(9, 0, m1, 1);
    LCDWriteStringXY(10, 0 , "/4");
    LCDWriteIntXY(13, 0, t1, 1);
    LCDWriteIntXY(14, 0, t2, 1);
    LCDWriteIntXY(15, 0, t3, 1);
    if(send) {
        tempo = (t1*100 + t2*10 + t3);
        SerialTx.Command = lMENU;
        SerialTx.Dat1 = mmMETRONOOM;
        SerialTx.Dat2 = m1;
        SerialTx.Dat3 = (tempo & 0xFF00)>>8;
        SerialTx.Dat4 = (tempo & 0x00FF);
        SerialTransmit();
        send = 0;
    }

    if(indicator_cnt >= (1200/(tempo<<2))) {
        LCDWriteStringXY(1, 1 , "****");
        indicator_cnt = 0;
    }
    indicator_cnt++;

}

void lcd_sub_menu_tetten() {
    lcd_screensaver();
}

void lcd_sub_menu_lcd() {
    switch (inputs) {
        case INP_B_UP:
            break;
        case INP_B_DOWN:
            break;
        case INP_B_OK:
            if(sub_menu_lcd < smMENU_LCD_MAX)
                sub_menu_lcd++;
            else
                sub_menu_lcd = smBRIGHTNESS;
            break;
        case INP_B_BACK:
            break;
        default:
            break;
    }
    switch (sub_menu_lcd) {
        case smBRIGHTNESS:
            LCDWriteStringXY(2, 1, "<");
            LCDWriteStringXY(9, 1, " ");
            LCDWriteStringXY(14, 1, " ");
            switch (inputs) {
                case INP_B_UP:
                    if(brightness < BRIGHTNESS_MAX)
                        brightness++;
                    break;
                case INP_B_DOWN:
                    if(brightness > BRIGHTNESS_MIN)
                        brightness--;
                    break;
                default:
                    break;
            }
            LCDBrightness(brightness);
            LCDWriteIntXY(0, 1,brightness,2);
            LCDWriteIntXY(7, 1,scrs_speed,2);
            LCDWriteStringXY(12, 1, "ON");
            break;

        case smSCRSPEED:
            LCDWriteStringXY(2, 1, " ");
            LCDWriteStringXY(9, 1, "<");
            LCDWriteStringXY(14,1," ");
            switch (inputs) {
                case INP_B_UP:
                    if(scrs_speed < 50)
                        scrs_speed += 5;
                    break;
                case INP_B_DOWN:
                    if(scrs_speed > 10)
                        scrs_speed -= 5;
                    break;
                default:
                    break;
            }
            LCDWriteIntXY(0, 1,brightness,2);
            LCDWriteIntXY(7, 1,scrs_speed,2);
            LCDWriteStringXY(12, 1, "ON");
            break;

        case smLED:
            switch (inputs) {
                case INP_B_UP:
                    PORTAbits.RA5 = !PORTAbits.RA5;
                    break;
                case INP_B_DOWN:
                    PORTAbits.RA5 = !PORTAbits.RA5;
                    break;
                default:
                    break;
            }
            LCDWriteStringXY(2,1," ");
            LCDWriteStringXY(9,1," ");
            LCDWriteStringXY(14,1,"<");
            break;

        default:
            break;
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
 * - time out: kon andere hw niet op tijd vinden
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
                switch (main_menu_new) {
                    case mmMENU:
                        LCDWriteStringXY(8, 0, "-kies-< ");
                        LCDWriteStringXY(8, 1, "Reset   ");
                        break;
                    case mmRESET:
                        LCDWriteStringXY(8, 0, "Reset   ");
                        LCDWriteStringXY(8, 1, "Stemmen ");
                        break;
                    case mmSTEMMEN:
                        LCDWriteStringXY(8, 0, "Stemmen ");
                        LCDWriteStringXY(8, 1, "Click   ");
                        break;
                    case mmMETRONOOM:
                        LCDWriteStringXY(8, 0, "Click   ");
                        LCDWriteStringXY(8, 1, "Mopje   ");
                        break;
                    case mmMOPJE:
                        LCDWriteStringXY(8, 0, "Mopje   ");
                        LCDWriteStringXY(8, 1, "Tetten  ");
                        break;
                    case mmTETTEN:
                        LCDWriteStringXY(8, 0, "Tetten  ");
                        LCDWriteStringXY(8, 1, "Lcd     ");
                        break;
                    case mmLCD:
                        LCDWriteStringXY(8, 0, "Lcd     ");
                        LCDWriteStringXY(0, 1, "                ");
                        break;
                    case mmMETRONOOMsm:
                        LCDWriteStringXY(0, 0, "Metronom");
                        break;
                    case mmLCDsm:
                        LCDWriteStringXY(0, 0, "Hldrh  Spd  Led ");
                        break;
                    default:
                        break;
                }
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
    scrs_cnt++;
    if (scrs_cnt == scrs_speed) {
        LCDLoadCostum(3);
        // A
        LCDWriteStringXY(0, 0, "%0");
        LCDWriteStringXY(1, 0, "%1");
        LCDWriteStringXY(0, 1, "%4");
        LCDWriteStringXY(1, 1, " ");
        LCDWriteStringXY(2, 1, "%5");
        // P
        LCDWriteStringXY(14, 0, "%2");
        LCDWriteStringXY(15, 0, "%3");
        LCDWriteStringXY(14, 1, "%6");
        LCDWriteStringXY(15, 1, "%7");
        LCDWriteStringXY(13, 1, "%5");

        if(i%4) {
            LCDWriteStringXY(2,0," Connecting");
        } else {
            LCDWriteStringXY(3,0,"           ");
        }
        if(j) {
            LCDWriteStringXY(2+i, 1,"\176");
        } else {
            LCDWriteStringXY(2+i, 1,"\177");
        }

        if (i == 11 || i == 0) {
            j = !j;
        }

        if (j) {
            i++;
        } else {
            i--;
        }
        scrs_cnt = 0;
    }
}

void lcd_screensaver(void) {
    scrs_cnt++;
    if (scrs_cnt == scrs_speed) {
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

        scrs_cnt = 0;
    }
}

void lcd_time_out(unsigned char mmOld) {
scrs_cnt++;
    if (scrs_cnt == ((unsigned int)scrs_speed*16)) {
        if(j == 0) {
            LCDWriteStringXY(0, 0, " Kan            ");
            LCDWriteStringXY(0, 1, " niet vinden    ");
            switch(mmOld) {
                case lSEARCH_A:
                    LCDWriteStringXY(5, 0, "Anoucka    ");
                    break;

                case lSEARCH_HW:
                    LCDWriteStringXY(5, 0, "Penny      ");
                    break;

                default:
                    break;
            }
        } else {
            LCDWriteStringXY(0, 0, "Druk OK om weer ");
            LCDWriteStringXY(0, 1, "te zoeken...    ");
        }
        j ^= 1;
        scrs_cnt = 0;
    }
}
