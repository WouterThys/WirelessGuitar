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

#ifndef SOFTWARE_SPI_H
#define SOFTWARE_SPI_H

#include "cpu.h"
#include "types.h"
#include "pinouts.h"
#include "delay.h"
#include "table.h"

 BYTE Nordic_Read(  BYTE );
//extern bit  AKMChipSelect,TransmissionError;

void SPI_Send(  BYTE , BYTE ,BYTE);
bit Nordic_Readback ( BYTE  ,  BYTE  );

enum TargetTypes
{
    NORDIC_TARGET,
    AKM_TARGET
};



#endif // ndef _H

