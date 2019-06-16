/* Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
*
* The information contained herein is confidential property of Nordic
* Semiconductor ASA.Terms and conditions of usage are described in detail
* in NORDIC SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
*
* Licensees are granted free, non-transferable use of the information. NO
* WARRENTY of ANY KIND is provided. This heading must NOT be removed from
* the file.
*
* 
*/

#include "timers.h"
//#include "pic16f72x.h"
#include <pic.h>

#define OSC_SPEED       (8000000.0)
#define CPU_SPEED       (OSC_SPEED/4.0)

#define TICKS_2MS       (CPU_SPEED/500.0)
#define LATENCY         20
#define TIMER1_RELOAD   ((int)(-(TICKS_2MS-LATENCY)))


unsigned int Timer_SysTime;
unsigned int now;


/****************************************************************************/
/* Function:    Constructor                                                 */
/*                                                                          */
/* Initialises the software timer system                                    */
/*                                                                          */
/****************************************************************************/

void Timer_Constructor ( void )
{
    Timer_SysTime = 0;


    //
    TMR1L = 0;                  // prevent rollover to high byte
    TMR1H = (TIMER1_RELOAD >> 8) & 0xff;
    TMR1L = TIMER1_RELOAD & 0xff;
    T1CON = 0x01;               // Prescale 1:1, Oscillator off, No synch, intrnal clock. timer ON
    TMR1IE = 1;                 // Enable Timer1 Interrupt
    PEIE = 1;                   // Enable peripheral interrupts
    TMR1IF = 0;                 // but dismiss any spurious interrupts

}
/****************************************************************************/
/* Function:    Timer_Start                                                 */
/*                                                                          */
/* Start a timer of the specified length                                    */
/*                                                                          */
/****************************************************************************/

void _Timer_Start ( Timer_t *theTimer, unsigned int length )
{
    TMR1IE = 0;                 // Disble Timer1 Interrupt
    theTimer->started = Timer_SysTime;
    TMR1IE = 1;                 // Enable Timer1 Interrupt

    length++;
    length /= 2;
    if ( 1==length )
    {
        length++;
    }
    theTimer->length = length;
}

/****************************************************************************/
/* Function:    Timer_IsExpired                                             */
/*                                                                          */
/* Returns TRUE if the provided timer has expired.                          */
/*                                                                          */
/****************************************************************************/

unsigned char _Timer_IsExpired ( Timer_t *theTimer )
{
    int length = theTimer->length;

    if ( length != 0 )
    {
        TMR1IE = 0;                 // Disble Timer1 Interrupt
        now = Timer_SysTime;
        TMR1IE = 1;                 // Enable Timer1 Interrupt

        now -= theTimer->started;
        return (now >= length);
    }

    return 0;
}

/****************************************************************************/
/* Function:    Timer_Stop                                                  */
/*                                                                          */
/* Stops a timer, so that it no longer reports as Expired                   */
/*                                                                          */
/****************************************************************************/
#if 0
// Done as macro
void Timer_Stop ( Timer_t *theTimer )
{
    theTimer->length = 0;
}
#endif
/****************************************************************************/
/* Function:    Timer_IsActive                                              */
/*                                                                          */
/* Returns TRUE if the timer is not stopped.                                */
/* An expired timer will report as active.                                  */
/*                                                                          */
/****************************************************************************/
#if 0
// Done as macro
unsigned char Timer_IsActive ( Timer_t *theTimer )
{
    return theTimer->length != 0;
}
#endif

/****************************************************************************/
/***********************INTERRUPT LEVEL ROUTINE******************************/
/****************************************************************************/
/* Function:    TimerSystem::TickIsr                                        */
/*                                                                          */
/* Handle a tick interrupt from the h/w timer                               */
/*                                                                          */
/****************************************************************************/
/***********************INTERRUPT LEVEL ROUTINE******************************/
/****************************************************************************/

void TimerSystem_TickIsr ( void )
{
    TMR1L = 0;                  
    TMR1H = (TIMER1_RELOAD >> 8) & 0xff;
    TMR1L = TIMER1_RELOAD & 0xff;
    TMR1IF = 0; // Re-enable the interrupt

    Timer_SysTime++;
}


