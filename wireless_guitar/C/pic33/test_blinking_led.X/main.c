/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#include <xc.h>


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

#include "interrupts.h"
/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
void wait(void);
/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{
    DisableInterrupts ();
    /* Configure the oscillator for the device */
    PLLset();
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();
    initUART();
    InintInterrupts();
    EnableInterrupts();
    
    /* TODO <INSERT USER APPLICATION CODE HERE> */
 U1MODEbits.UARTEN = 1;
  U1STAbits.UTXEN = 1;
    while(1)
    {
//          PORTB ^= (1 << 1);
//          wait();PORTB ^= (1 << 1);
//        PORTBbits.RB1 = 1;
//        wait();
//        PORTBbits.RB1 = 0;
//        wait();
    }


}
 void wait(void){
     int i;
     for (i = 0; i < 20000;i++)
        {
            int j;
            for (j = 0; j < 50;j++)
            {
            }
        }
    return;
    }

 
 