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

#ifndef TIMERS_H
#define TIMERS_H



//
//  This structure defines a timer and is passed to all functions
//

typedef struct
{
    unsigned int started;
    unsigned int length;
} Timer_t;



//
// Initialise the timer system
//
extern void Timer_Constructor ( void );

//
//  Start the timer running. Will expire in 'length' milliseconds.
//
#define Timer_Start(t,l) _Timer_Start(&(t), (l))
extern void _Timer_Start ( Timer_t *theTimer, unsigned int length );
//
//  Is the specified timer expired and active?
//  A stopped timer will return false.
//
#define Timer_IsExpired(t) _Timer_IsExpired(&(t))
extern unsigned char _Timer_IsExpired ( Timer_t *theTimer );
//
//  Stop the timer. A stopped timer will not report as expired.
//
//extern void Timer_Stop ( Timer_t *theTimer );
#define Timer_Stop(t) (t).length = 0

//
//  Is a timer active? An expired timer will return TRUE.
//
//extern unsigned char Timer_IsActive ( Timer_t *theTimer );
#define Timer_IsActive(t) ((t).length != 0)
#endif // ndef TIMERS_H

