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


//#define RED_MIC   //uncomment this to create .hex file for red mic. Otherwise it will be the blue mic.

#ifdef  RED_MIC
#define     DEFAULT_ADDRESS_0     0x3B
#define     DEFAULT_ADDRESS_1     0xF6
#define     DEFAULT_ADDRESS_2     0xF3
#define     DEFAULT_ADDRESS_3     0x53
#define     DEFAULT_ADDRESS_4     0x17

#define     PAIRING_ADDRESS_0     0x00
#define     PAIRING_ADDRESS_1     0x1A
#define     PAIRING_ADDRESS_2     0x2B
#define     PAIRING_ADDRESS_3     0x3C
#define     PAIRING_ADDRESS_4     0x4D

#else
//blue 
#define     PAIRING_ADDRESS_0     0x5D
#define     PAIRING_ADDRESS_1     0x6C
#define     PAIRING_ADDRESS_2     0x7B
#define     PAIRING_ADDRESS_3     0x8A
#define     PAIRING_ADDRESS_4     0x90

#define     DEFAULT_ADDRESS_0     0xAB
#define     DEFAULT_ADDRESS_1     0x31
#define     DEFAULT_ADDRESS_2     0x3E
#define     DEFAULT_ADDRESS_3     0x3F
#define     DEFAULT_ADDRESS_4     0x3A

#endif

#ifdef RED_MIC
#define     NORDIC_REG_0x0C     0x34
#define     NORDIC_REG_0x0D     0x0A
#define     NORDIC_REG_0x0E     0x42
#define     NORDIC_REG_0x0F     0x4F
#define     NORDIC_REG_0x10     0x18
#define     NORDIC_REG_0x11     0x26
#define     NORDIC_REG_0x12     0x00
#define     NORDIC_REG_0x13     0x00 
#define     NORDIC_REG_0x14     0x00 
#define     NORDIC_REG_0x15     0x00 
#define     NORDIC_REG_0x16     0x00 
#define     NORDIC_REG_0x17     0x00 
#define     NORDIC_REG_0x18     0x00 
#define     NORDIC_REG_0x19     0x00 
#define     NORDIC_REG_0x1A     0x00 
#define     NORDIC_REG_0x1B     0x00 
#define     NORDIC_REG_0x1C     0x00 
#define     NORDIC_REG_0x1D     0x00 
#define     NORDIC_REG_0x1E     0x00 
#define     NORDIC_REG_0x1F     0x00 
#define     NORDIC_REG_0x20     0x00 
#define     NORDIC_REG_0x21     0x00 
#define     NORDIC_REG_0x22     0x00 
#define     NORDIC_REG_0x23     0x00 
#define     NORDIC_REG_0x24     0x00 
#define     NORDIC_REG_0x25     0x00 
#define     NORDIC_REG_0x26     0x00 
#define     NORDIC_REG_0x27     0x00 
#define     NORDIC_REG_0x28     0x00 
#define     NORDIC_REG_0x29     0x00 
#define     NORDIC_REG_0x2A     0x00 
#define     NORDIC_REG_0x2B     0x00 
#define     NORDIC_REG_0x2C     0x00 
#define     NORDIC_REG_0x2D     0x00 
#define     NORDIC_REG_0x2E     0x00 
#define     NORDIC_REG_0x2F     0x00 
#define     NORDIC_REG_0x30     0x00 
#define     NORDIC_REG_0x31     0x00 
#define     NORDIC_REG_0x32     0x00 
#define     NORDIC_REG_0x33     0x02 
#define     NORDIC_REG_0x34     0x06 
#define     NORDIC_REG_0x35     0x03 
#define     NORDIC_REG_0x36     0x00 
#define     NORDIC_REG_0x37     0x00 
#define     NORDIC_REG_0x38     0x00 

#else

//BLUE
#define     NORDIC_REG_0x0C     0x1F
#define     NORDIC_REG_0x0D     0x3B
#define     NORDIC_REG_0x0E     0x11
#define     NORDIC_REG_0x0F     0x04
#define     NORDIC_REG_0x10     0x2D
#define     NORDIC_REG_0x11     0x49
#define     NORDIC_REG_0x12     0x00
#define     NORDIC_REG_0x13     0x00
#define     NORDIC_REG_0x14     0x00
#define     NORDIC_REG_0x15     0x00
#define     NORDIC_REG_0x16     0x00
#define     NORDIC_REG_0x17     0x00
#define     NORDIC_REG_0x18     0x00
#define     NORDIC_REG_0x19     0x00
#define     NORDIC_REG_0x1A     0x00
#define     NORDIC_REG_0x1B     0x00
#define     NORDIC_REG_0x1C     0x00
#define     NORDIC_REG_0x1D     0x00
#define     NORDIC_REG_0x1E     0x00
#define     NORDIC_REG_0x1F     0x00
#define     NORDIC_REG_0x20     0x00
#define     NORDIC_REG_0x21     0x00
#define     NORDIC_REG_0x22     0x00
#define     NORDIC_REG_0x23     0x00
#define     NORDIC_REG_0x24     0x00
#define     NORDIC_REG_0x25     0x00
#define     NORDIC_REG_0x26     0x00
#define     NORDIC_REG_0x27     0x00
#define     NORDIC_REG_0x28     0x00
#define     NORDIC_REG_0x29     0x00
#define     NORDIC_REG_0x2A     0x00
#define     NORDIC_REG_0x2B     0x00
#define     NORDIC_REG_0x2C     0x00
#define     NORDIC_REG_0x2D     0x00
#define     NORDIC_REG_0x2E     0x00
#define     NORDIC_REG_0x2F     0x00
#define     NORDIC_REG_0x30     0x00
#define     NORDIC_REG_0x31     0x00
#define     NORDIC_REG_0x32     0x00
#define     NORDIC_REG_0x33     0x02
#define     NORDIC_REG_0x34     0x06
#define     NORDIC_REG_0x35     0x03
#define     NORDIC_REG_0x36     0x00
#define     NORDIC_REG_0x37     0x00
#define     NORDIC_REG_0x38     0x00
#endif

//AKM AK5700
#define     AKM_REG_0x10     0x07
#define     AKM_REG_0x11     0x26
#define     AKM_REG_0x12     0x14
#define     AKM_REG_0x13     0x01
#define     AKM_REG_0x14     0x23
#define     AKM_REG_0x15     0x90
#define     AKM_REG_0x16     0x00
#define     AKM_REG_0x17     0x00
#define     AKM_REG_0x18     0x91
#define     AKM_REG_0x19     0x00
#define     AKM_REG_0x1A     0x00
#define     AKM_REG_0x1B     0xE1
#define     AKM_REG_0x1C     0x00
#define     AKM_REG_0x1D     0x50
#define     AKM_REG_0x1E     0x02



