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
#ifndef CPU_H
#define CPU_H


/****************************************************************************/
/*              S Y S T E M   I N C L U D E   F I L E S                     */
/****************************************************************************/

// _16F505
// _12F519
// _16F684
// _16F57


#include <pic.h>
//#include "pic16f72x.h"
/****************************************************************************/
/*               L O C A L   I N C L U D E   F I L E S                      */
/****************************************************************************/

/****************************************************************************/
/*                 M A C R O   D E F I N I T I O N S                        */
/****************************************************************************/
#define CCS_PORT
#define ENABLE_INTS     GIE = 1
#define DISABLE_INTS    GIE = 0


#ifdef CCS_PORT
#define Output_High(p)    (p=1)
#define Output_Low(p)    (p=0)

#define input(x)    ( x==1 )
#endif
//#define _delay_2uS() asm("goto $+1")
//#define _delay_2uS() asm(" goto $+1"); asm ("goto $+1");asm ("goto $+1");asm ("goto $+1");asm ("goto $+1");asm ("goto $+1");asm ("goto $+1");asm ("goto $+1")
#define _delay_2uS() asm("nop"); asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");//asm("nop");asm("nop")
//#define _delay_2uS() asm("nop")
//#define delay_us(1) asm("nop")
//#define _delay_2uS() delay_us(0)
#define _nop() asm("nop")

//#define NORDIC_TRANSPORT_I_2_C
#define NORDIC_TRANSPORT_SPI
//#define INTERNAL_OSC
#define OSC_SPEED       (8000000.0)
#define CPU_SPEED       (OSC_SPEED/4.0)

/****************************************************************************/
/*                  T Y P E   D E F I N I T I O N S                         */
/****************************************************************************/

/****************************************************************************/
/*        A P P L I C A T I O N   S C O P E   D E C L A R A T I O N S       */
/****************************************************************************/


/****************************************************************************/
/*                          F U N C T I O N S                               */
/****************************************************************************/


#endif // ndef CPU_H

