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

#ifndef NORDIC_H
#define NORDIC_H

#include "cpu.h"
#include "types.h"
#include "pinouts.h"
#include "delay.h"
#include "table.h"

#include "software_spi.h"

void Nordic_Wakeup(void);
BYTE Nordic_LinkPresent(void);


#endif // ndef NORDIC_H

