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

#include <pic.h>
#include "Types.h"
#include "pinouts.h"
#include "statemachine.h"
#include "timers.h"
#include "adjustableparameters.h"
__CONFIG(0x30D4);

void SetupProcessor(void);

void main(void)
{
    SetupProcessor();
    Timer_Constructor();
	IntializeStateMachine();

	while(1)
    {
		GIE=0;
        ProcessStateMachine();
        GIE=1;
		
	}
}

void SetupProcessor()
{
   OSCCON = 0x71;
   ANSEL = 0;
   CMCON0=7;
   CMCON1=0;
   ADON=0;
   PSA=0;
		
	T0IE=0;INTE=0;RAIE=0;PEIE=0;
	WDTCON=0x17; //2sec WDT
  
   TRISA=0x18;
   PORTA=0x04; 
   
   TRISC=0x04;
   PORTC=0x28;                         
}


extern void TimerSystem_TickIsr(void);
extern void AccBus_ReceiveIsr(void);
extern void SPI_ReceiveDataIsr_FromISR(void);

void interrupt ISR ( void )
{
  //  if ( SSPIF )        { SPI_ReceiveDataIsr_FromISR(); return; }
  //  if ( T0IF && T0IE ) { AccBus_ReceiveIsr(); return;   }
    if ( TMR1IF )       { TimerSystem_TickIsr(); return; }
}
				

