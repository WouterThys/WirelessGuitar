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

#include "Types.h"
#include "nordicManager.h"
#include "statemachine.h"
#include "timers.h"
#include "akm.h"
#include "delay.h"


#define  STATE_MACHINE_TICK_RATE    6 //in  ms

static BYTE CurrentState;
static Timer_t  StateMachineTimer;
static BYTE linkcount=255;
static bit  SYSTEM_ON=0;
static long PSwitchCount=0;
static BYTE no_link_count=0,i=0,timeout=0,link=0;


BYTE GetCurrentState(void)
{
    return CurrentState;
}

void IntializeStateMachine(void)
{
    CurrentState=BUTTON_STATE;
    Timer_Start(StateMachineTimer, STATE_MACHINE_TICK_RATE);
}

static void ProcessEnterSleep(void)
{
   	LED=0;
	SYSTEM_ON=0;
	PDN=0;
	link=0;
	//N_RESET=1;
	SPI_Send( 0x5A,0x40,NORDIC_TARGET); //nordic sleep
	delay_ms(500);
	while (PSWITCH)  //not pressed
	{	
		#asm
		CLRWDT
		SLEEP
		#endasm
	}
	CurrentState=LINK_CHECK;
}

static void ProcessButton(void)
{
	if (SYSTEM_ON==1)CurrentState=LINK_CHECK;
	
	if(PSWITCH == 0) //pressed
    {
		PSwitchCount++; 
		if (PSwitchCount>600)PSwitchCount=300; //overflow protection
		if (PSwitchCount>55) //LED alert user to let go
			LED=!link;
		
		if (PSwitchCount > 250) // long press
		{
			if (SYSTEM_ON==0) //although long press-> pairing mode, if system is off should turn on system first
			{
				LED=1;
				SYSTEM_ON=1;
				CurrentState=LOAD_AKM;
			}
			else
			{
				//pairing
				while(PSWITCH == 0)//pressed
				{
					LED=1;
					delay_ms(60);
					LED=0;
					delay_ms(60);
					LED=1;
					delay_ms(60);
					LED=0;
					delay_ms(60);
						#asm
						CLRWDT
						#endasm	
				}
				CurrentState=PAIRING;
				PSwitchCount=0; 
			}
		}
    }
    else //released
	{
		if(PSwitchCount > 70 && PSwitchCount < 300) // >70 = debounce, <300 = ensure short press
        {    
            if (SYSTEM_ON==0)
			{
				LED=1;
				SYSTEM_ON=1;
				CurrentState=LOAD_AKM;
			}
            else if (SYSTEM_ON==1)
				CurrentState=ENTER_SLEEP;
		}
		PSwitchCount=0; 
	}
   
}

static void ProcessPairing(void)
{
	CurrentState=BUTTON_STATE;

	for (i=0;i<5;i++)
		SPI_Send( 0x39+i,PairingAddress[i],NORDIC_TARGET);  //set back to pairing address
	
	SPI_Send( 0x36,0x10,NORDIC_TARGET); //Force Relink

	while (!Nordic_LinkPresent() && timeout<20 )
	{
		no_link_count++;
		timeout++;  //timeout after 20 clicks
		if (no_link_count==10)
		{
		//	SPI_Send( 0x36,0x10,NORDIC_TARGET); //Force Relink
			no_link_count=0;
		}

		if (PSWITCH==0)
		{
			timeout=20;
			CurrentState=ENTER_SLEEP;
		}
		LED=1;
		delay_ms(50);
		LED=0;
		delay_ms(50);
		LED=1;
		delay_ms(50);
		LED=0;
		delay_ms(50);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
		delay_ms(100);delay_ms(100);
			#asm
			CLRWDT
			#endasm
	}
		
	
	if (timeout<20)  //if timed out, skip
	{
		for (i=0;i<5;i++)                        
			SPI_Send( 0x39+i,NordicRegData[0x39+i],NORDIC_TARGET);   //set unique address

		SPI_Send(0x3E, 0x01, NORDIC_TARGET);    //send unique address to ARX
	
		while (Nordic_Read(0x3E)==0x02)     //check if successful
		{
			SPI_Send(0x3E, 0x01, NORDIC_TARGET);   //resend if not successful
			LED=1;
			delay_ms(100);
			LED=0;
			delay_ms(100);
		}
	}

}
static void ProcessAKMBoot(void)
{
	AKM_Constructor();
	CurrentState=LOAD_NORDIC;
}

static void ProcessNordicBoot(void)
{
 	N_RESET=0;
	delay_ms(255);
	delay_ms(255);
	delay_ms(255);
	Nordic_Wakeup();
	CurrentState=LINK_CHECK;
}
static void ProcessLink(void)
{
	if ( linkcount == 0)
	{	
	    linkcount=100;
		if (  Nordic_LinkPresent())
        {
			link=1;
			LED=1;
		}
	    else
		{
	        link=0;
			LED=1;
			delay_ms(200);
			LED=0;
			delay_ms(200);
		}
	}
	else
		linkcount--;

	CurrentState=BUTTON_STATE;
}

void ProcessStateMachine(void)
{
	#asm
	CLRWDT
	#endasm
    if ( Timer_IsExpired(StateMachineTimer) )
    {

        Timer_Start(StateMachineTimer, STATE_MACHINE_TICK_RATE);

        switch ( CurrentState ) {
            case BUTTON_STATE:
                	ProcessButton();
                break;
            case LINK_CHECK:
                    ProcessLink();
                break;
			case LOAD_NORDIC:
					ProcessNordicBoot();	
				break;
            case LOAD_AKM:
                    ProcessAKMBoot();
                break;
            case ENTER_SLEEP:
                    ProcessEnterSleep();
                break;
            case PAIRING:
                    ProcessPairing();
                break;
            
            default  :
                break;
        }
    }

}

