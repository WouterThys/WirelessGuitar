/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif
#endif

#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <delay.h>         /* Includes delay functions                        */
#include "dsp.h"           /* Includes dsp functions                          */
#include "../../common_files/system.h"              /* System funct/params, like osc/peripheral config */
#include "../../common_files/common_defs&vars.h"    /* Common defines for all the PICs */
#include "wl_module.h"           /* Functions of the NORDIC */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "interrupts.h"    /* Interrupts functions                            */



/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
void SerialAnswer(void);

struct SerialStruct SerialTx;

// Finit state machine variables
anouchka_fsm_state fsm_new_state, fsm_old_state = aINIT;
#define STATE_NEW_STATE(new_state){\
fsm_new_state = new_state;\
}
/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {
    /* Disable the interrupts */
    DisableInterrupts();
    /* Configure the oscillator for the device */
    PLLset();
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    InitPwm1(); // Init Pwm, NO enable included
    InitUart1(); // Init UART2, NO enable included
    InitTmr4(); // Init Timer4, NO enable included
    InitTmr3(); // Init Timer3, NO enable included

    InitInterrupts(); // Init the interrupts
    EnableInterrupts(); // Enable interrupts

    /* Initialise variables */
    SerialTx.TransmitAddress = ANOUCHKA; // Always the same

    while (1) {

        // Check inputs: these are the commands from LCD
        if (U2SoftFlag) {
            if (SerialRx.TransmitAddress == LCD) { // Check address, should always be LCD
                switch (SerialRx.Command) {
                    case lSEARCH_A:
                        STATE_NEW_STATE(aSEARCH_A);
                        break;

                    case lSEARCH_HW:
                        _INT1IE = 1;
                        nrf_init(); // Init the SPI and Hardware ports
                        nrf_tx_config(nrf_TX_NR_0, nrf_ENAA_P0); // Init the nRF module as TX , Pipe0 - AutoAck
                        Delay_ms(5);
                        payload[PL_COMMAND] = (ANOUCHKA + aSEARCH_HW);
                        STATE_NEW_STATE(aSEARCH_HW);
                        break;

                    case lWAIT:
                        STATE_NEW_STATE(aPREPARE);
                        break;

                    case lTRANSMIT:
                        T3CONbits.TON = 1; // Timer 3 is enabled on sample frequency
                        PTCONbits.PTEN = 1; // Enable pwm signal                       
                        STATE_NEW_STATE(aTRANSMIT);
                        break;

                    case lMENU:
                        if (SerialRx.Dat1 == mmMETRONOOM) {
                            T4CONbits.TON = 1;
                            PTCONbits.PTEN = 1;
                            tmp_cnt = sine_cnt = tempo_cnt = tone_cnt = freq_cnt = 0;
                            STATE_NEW_STATE(aMETRONOOM);
                        } else {
                            T4CONbits.TON = 0;
                            PTCONbits.PTEN = 0;
                            STATE_NEW_STATE(aIDLE);
                        }
                        break;

                    default:
                        break;
                }
            } else { // If TransmitAddress is wrong, the receiver packet is wrong, delay and wait until sended again
                Delay_ms(2);
                uart_block_count = 0;
            }
            U2SoftFlag = 0;
        }


        switch(fsm_old_state) {
            case aINIT:
                PTCONbits.PTEN = 0;
                T3CONbits.TON = 0;
                _INT1IE = 0;
                STATE_NEW_STATE(aIDLE);
                break;

            case aSEARCH_A:
                _INT1IE = 0;
                PTCONbits.PTEN = 0;
                T3CONbits.TON = 0;
                SerialTx.Command = aSEARCH_A;
                SerialTx.Hardware = (0x00 + HW_A);
                SerialAnswer();
                STATE_NEW_STATE(aIDLE);
                break;

            case aSEARCH_HW:
                if(!nrf_find_rx(nrf_TX_NR_0)) { // Wait until the other nRF is found
                    Delay_ms(50);
                } else {
                    SerialTx.Command = aSEARCH_HW;
                    SerialTx.Hardware = (HW_P + HW_Pnrf + HW_A + HW_Anrf);
                    SerialAnswer();
                    STATE_NEW_STATE(aIDLE);
                }
                break;

            case aPREPARE:
                payload[PL_COMMAND] = (ANOUCHKA + aPREPARE);
                nrf_send_array(payload, PL_LENGTH);
                Delay_ms(5);
                nrf_rx_config(RX_PW_P0,nrf_ENAA_P0); // Init the nRF module as RX, Pipe0 - AutoAck
                Delay_ms(5);
                nrf_CE_H;           // Listening for pakets
                STATE_NEW_STATE(aIDLE);
                break;

            case aTRANSMIT:
//                if(fsm_new_state != aTRANSMIT) {
//                    nrf_CE_L;   // Disable receiving
//                    Delay_ms(10);
//                    nrf_tx_config(nrf_TX_NR_0, nrf_ENAA_P0); // Configure as transmitter again
//                    Delay_ms(5);
//                }
                break;

            case aMETRONOOM:
                metronoom(SerialRx.Dat2, (SerialRx.Dat3 << 8)+(SerialRx.Dat4));
                break;

            case aIDLE:
                break;

            default:
                break;
        }
        
        fsm_old_state = fsm_new_state;
    }
}

/*******************************************************************************
 *              Uart write/read one block
 *              -------------------------
 *
 * Writes one block of data to the uart
 *******************************************************************************/
void SerialAnswer() {
    U1TXREG = SerialTx.TransmitAddress + SerialTx.Command;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Hardware;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Dat1;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Dat2;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Dat3;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Dat4;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Dat5;
    while (U1STAbits.TRMT == 0) {
    }
    U1TXREG = SerialTx.Dat6;
    while (U1STAbits.TRMT == 0) {
    }
}