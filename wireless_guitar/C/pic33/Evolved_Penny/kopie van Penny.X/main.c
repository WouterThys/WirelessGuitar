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

#include "../../common_files/system.h"              /* System funct/params, like osc/peripheral config */
#include "../../common_files/common_defs&vars.h"    /* Common defines for all the PICs */
#include "../../common_files/wl_module.h"           /* Functions of the NORDIC */
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
    InitUart1();
    InintInterrupts();
    EnableInterrupts();

    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;

    nrf_init();
    nrf_tx_config(nrf_TX_NR_0); // Config Module
    uint8_t k = 0;
    for (k = 0; k < (PL_LENGTH - 1); k++) {
        payload[k] = k;
    }
    while (1) {
        
        nrf_send_array(payload, PL_LENGTH);
        
        Delay_1s;
        
        //bananen();
        

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

