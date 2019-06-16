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

#include "delay.h"

void delay_ms(BYTE time)
{
    BYTE temp=50;
    BYTE temp2=16;

    while ( time )
    {
        while (temp2  )
        {
            while ( temp )
            {
                temp--;
            }
         temp2--;
        temp=50;
        }
        temp2=8;
        time--;
    }
}

