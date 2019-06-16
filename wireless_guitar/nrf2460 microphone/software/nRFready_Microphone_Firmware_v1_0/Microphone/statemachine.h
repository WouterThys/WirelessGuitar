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

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


void ProcessStateMachine(void);
void IntializeStateMachine(void);
BYTE GetCurrentState(void);


enum States
{
	LINK_CHECK,
	BUTTON_STATE,
	LOAD_NORDIC,
	LOAD_AKM,
    ENTER_SLEEP,
	POWER_DOWN,
	PAIRING

};

#define SLEEP() asm("sleep")



#endif // n

