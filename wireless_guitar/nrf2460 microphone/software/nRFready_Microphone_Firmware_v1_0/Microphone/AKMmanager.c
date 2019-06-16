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

#include "adjustableParameters.h"
#include "akm.h"



void AKM_Constructor(void)
{
    BYTE address;
    PDN=1;   
    address=(0x10+0xA0);
    SPI_Send(address,AKM_REG_0x10,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x11,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x12,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x13,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x14,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x15,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x16,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x17,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x18,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x19,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x1A,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x1B,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x1C,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x1D,AKM_TARGET);
    SPI_Send(++address,AKM_REG_0x1E,AKM_TARGET);
}


