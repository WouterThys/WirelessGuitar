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

#ifndef PINOUTS_H
#define PINOUTS_H


typedef unsigned char BYTE;

#define N_RESET      RC0 //output low
#define SUSN         RC1 //output Low
#define mSDA         RC2 //Output Low
#define mSCL         RC3 //output low
#define PDN1         RC4 //output low
#define PDN2         RC5 //output low

#define LED1         RA2 
#define LED2         RA4 //output Low
#define SW           RA5 //output low

#define mSDA_Input() TRISC|=0x04;  
#define mSDA_Output() TRISC&=0xFB; 

#define Output_High(p)    (p=1)
#define Output_Low(p)    (p=0)

void delay_us(BYTE);
void delay_ms(BYTE);
BYTE EEpromRead(BYTE);
void EEpromWrite(BYTE,BYTE);



#endif