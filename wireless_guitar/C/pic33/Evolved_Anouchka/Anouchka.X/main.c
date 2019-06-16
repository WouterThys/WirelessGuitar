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
    InitPwm1();         // Init Pwm, NO enable included
    InitApp();
//    InitUart1();      // Init UART11, NO enable included
    InitTmr3();
//    InitTimer1();     // Init Timer1, NO enbale included
    

    nrf_init();       // Init the SPI and Hardware ports
    nrf_rx_config(RX_PW_P0,nrf_ENAA_P0); // Init the nRF module, Pipe0 - AutoAck
    Delay_ms(5);

    InitInterrupts();   // Init the interrupts
    EnableInterrupts(); // Enable interrupts
    nrf_CE_H;           // Listening for pakets

    //    U1MODEbits.UARTEN = 1;
    //    U1STAbits.UTXEN = 1;

    while (1) {

    }
}

