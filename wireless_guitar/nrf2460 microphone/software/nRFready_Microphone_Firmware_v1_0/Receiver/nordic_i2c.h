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

#ifndef NORDIC_I2C_H
#define NORDIC_I2C_H

#include "pinouts.h"

typedef unsigned char BYTE;

BYTE Nordic_Read(  BYTE );

extern BYTE TransmissionError;
void Nordic_Send(  BYTE , BYTE );
BYTE Nordic_Readback ( BYTE  ,  BYTE  );



#endif // ndef NORDIC_H

