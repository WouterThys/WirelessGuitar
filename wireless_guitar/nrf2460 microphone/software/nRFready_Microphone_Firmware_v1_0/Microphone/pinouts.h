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

#ifndef PINOUTS_H
#define PINOUTS_H


#define N_RESET  RC5  //output
#define CSNW     RC3  //output
#define DATAI    RC2  //Input
#define DATAO    RC1  //Output
#define CLK      RC0  //output

#define CSNA     RA2  //output High
#define PSWITCH  RA3  //Input
#define PDN      RA1  //Output
#define LED      RA0  //Output


#define CPU_CONFIGURATION   0x3094



#endif // ndef PINOUTS_H

