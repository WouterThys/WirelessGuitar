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
void bananen(void);
uint8_t count;

/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {
    /* Disable the interrupts */
    DisableInterrupts();
    /* Configure the oscillator for the device */
    PLLset();
    ConfigureOscillator();

    Delay_ms(1);

    /* Initialize IO ports and peripherals */
    InitApp();
    InitDma0();       // Init DMA0 with ADC, enable included
    InitAdc1();       // Init ADC1 with DMA0, enable included
    InitTmr3();         // Init Timer3 for Adc sample frequency, NO enable included

    nrf_init();       // Init the SPI and Hardware ports
    nrf_rx_config(RX_PW_P0,nrf_ENAA_P0); // Init the nRF module, Pipe0 - AutoAck
    Delay_ms(5);

    InitInterrupts();   // Init the interrupts
    EnableInterrupts(); // Enable interrupts
    nrf_CE_H;           // Listening for pakets


    while (1) {
        if(nrf_int_status & NRF_INT_MASK) {
            if(payload[PL_COMMAND] == (ANOUCHKA + aSEARCH_HW)){
//                _LATB14 = 1;
            } else {
            }

            if(payload[PL_COMMAND] == (ANOUCHKA + aPREPARE)){
//                _LATB13 = 1;
                nrf_tx_config(nrf_TX_NR_0, nrf_ENAA_P0); // Init the nRF module as TX , Pipe0 - AutoAck
                Delay_ms(50);
                T3CONbits.TON = 1;
            } else {
            }
        }

        if(fail) {
            fail = 0;
            DisableInterrupts();
            nrf_rx_config(RX_PW_P0,nrf_ENAA_P0); // Init the nRF module, Pipe0 - AutoAck
            Delay_ms(5);
            EnableInterrupts(); // Enable interrupts
            nrf_CE_H;           // Listening for pakets

        }

    }
}


