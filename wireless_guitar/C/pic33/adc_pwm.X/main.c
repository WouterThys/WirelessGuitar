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
#include "../common_files/system.h"              /* System funct/params, like osc/peripheral config */
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
    InitApp();          // Init hardware port directions and analog selections
//    InitUart1();        // Init UART11, NO enable included
    InitTmr3();         // Init Timer3, NO enable included (sample frequency)
    InitAdc1();         // Init Adc1 with Dma0, enable included
    InitDma0();         // Init Dma0 with Adc1, enable included

    /* Init and Enable the interrupts */
    InitInterrupts();   // Init the interrupts
    EnableInterrupts(); // Enable interrupts

    /* Start up conditions */
    payload[PL_COMMAND] = (PENNY + 0x01);   // First payload byte
    payload[PL_END] = (PENNY + 0x01);   // First payload byte

    T3CONbits.TON = 1;  // Start AD Conversions
//    U1MODEbits.UARTEN = 1;    // Enable U1 sending
//    U1STAbits.UTXEN = 1;      // Enable U1 receiving
//PTCONbits.PTEN = 1;
    while (1) {
//        if(AdcFlag) {
//            printf("cnt1: %d\n", pwm_count1);
//            printf("cnt2: %d\n", pwm_count2);
//            printf("\n");
//            AdcFlag = 0;
//        }
    }
}

