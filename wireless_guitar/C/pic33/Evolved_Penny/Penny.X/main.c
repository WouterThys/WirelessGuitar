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

    /* Initialize IO ports and peripherals */
    InitApp();
//    InitUart1();      // Init UART11, NO enable included
//    InitTimer1();     // Init Timer1, NO enbale included
    InitDma0();       // Init DMA0 with ADC, enable included
    InitAdc1();       // Init ADC1 with DMA0, enable included
    InitTmr3();         // Init Timer3 for Adc sample frequency, NO enable included
    
    InitInterrupts();   // Init the interrupts
    EnableInterrupts(); // Enable interrupts

    nrf_init();       // Init the SPI and Hardware ports
    nrf_tx_config(nrf_TX_NR_0,nrf_ENAA_P0); // Init the nRF module, Pipe0 - AutoAck
    Delay_ms(5);
    payload[PL_COMMAND] = (PENNY | pSEARCH_HW);

    while(!nrf_find_rx(nrf_TX_NR_0)) {   // Wait until the other nRF is found
        Delay_ms(100);
    }

//    nrf_tx_config(nrf_TX_NR_0,nrf_ENAA_NONE); // Init the nRF module, Pipe0 - No Ack
//    Delay_ms(5);
    
    T3CONbits.TON = 1;  // Start the Adc conversions on timer3 frequency

    while (1) {


    }
}

void bananen() {
    printf("CONFIG: %x \n", nrf_read_register(CONFIG));
    printf("EN_AA: %x \n", nrf_read_register(EN_AA));
    printf("RF_SETUP: %x \n", nrf_read_register(RF_SETUP));
    printf("RF_CH: %x \n", nrf_read_register(RF_CH));
    printf("SETUP_RETR: %x \n", nrf_read_register(SETUP_RETR));
    printf("FIFO_STATUS: %x \n", nrf_read_register(FIFO_STATUS));
    printf("STATUS: %x \n *-------PENNY-------* \n", nrf_read_register(STATUS));
}

