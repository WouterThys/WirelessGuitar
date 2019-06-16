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

#include "types.h"
#include "table.h"
#include "AdjustableParameters.h"


const unsigned BYTE PairingAddress [SIZE_OF_PAIRING] =
{
PAIRING_ADDRESS_0,
PAIRING_ADDRESS_1,
PAIRING_ADDRESS_2,
PAIRING_ADDRESS_3,
PAIRING_ADDRESS_4,
};

const unsigned  BYTE  NordicRegData [SIZE_OF_TABLE] =
{
                   
0x00, //  00
0x51, //  01
0x00, //  02
0x00, //  03
0x00, //  04
0x00, //  05
0x00, //  06
0x00, //  07
0x00, //  08
0x00, //  09
0x00, //  0A
0x00, //  0B
NORDIC_REG_0x0C,     
NORDIC_REG_0x0D,      
NORDIC_REG_0x0E,      
NORDIC_REG_0x0F,      
NORDIC_REG_0x10,      
NORDIC_REG_0x11,      
NORDIC_REG_0x12,      
NORDIC_REG_0x13,      
NORDIC_REG_0x14,      
NORDIC_REG_0x15,      
NORDIC_REG_0x16,      
NORDIC_REG_0x17,      
NORDIC_REG_0x18,      
NORDIC_REG_0x19,      
NORDIC_REG_0x1A,      
NORDIC_REG_0x1B,      
NORDIC_REG_0x1C,      
NORDIC_REG_0x1D,      
NORDIC_REG_0x1E,      
NORDIC_REG_0x1F,      
NORDIC_REG_0x20,     
NORDIC_REG_0x21,      
NORDIC_REG_0x22,      
NORDIC_REG_0x23,      
NORDIC_REG_0x24,      
NORDIC_REG_0x25,      
NORDIC_REG_0x26,      
NORDIC_REG_0x27,      
NORDIC_REG_0x28,      
NORDIC_REG_0x29,      
NORDIC_REG_0x2A,      
NORDIC_REG_0x2B,      
NORDIC_REG_0x2C,      
NORDIC_REG_0x2D,      
NORDIC_REG_0x2E,      
NORDIC_REG_0x2F,      
NORDIC_REG_0x30,      
NORDIC_REG_0x31,      
NORDIC_REG_0x32,      
NORDIC_REG_0x33,      
NORDIC_REG_0x34,     
NORDIC_REG_0x35,      
NORDIC_REG_0x36,      
NORDIC_REG_0x37,      
NORDIC_REG_0x38,     
DEFAULT_ADDRESS_0,  //  39    
DEFAULT_ADDRESS_1 , //  3A 
DEFAULT_ADDRESS_2 , //  3B
DEFAULT_ADDRESS_3 , //  3C
DEFAULT_ADDRESS_4 , //  3D
0x00, //  3E
0x00, //  3F
0x00, //  40
0x00, //  41
0x00, //  42
0x00, //  43
0x00, //  44
0x00,//0x0C, //  45   //Shutdown 0x00
0x00, //  46
0x00, //  47
0x00,//0x64, //  48   //Shutdown 0x00
0x03, //  49
0x00, //  4A
0x00, //  4B
0x00,//0x0A, //  4C   //Shutdown 0x00
0x00, //  4D
0x00, //  4E
0x00, //  4F
0x00, //  50   
0x00, //  51
0x06, //  52 
0x00,//  53   
0x80, //  54
0x00, //  55
0x03, //  56
0x00, //  57
0x00, //  58
0x00, //  59
0x00, //  5A
0x00, //  5B
0x00, //  5C
0x00, //  5D
0x00, //  5E
0x00, //  5F
0x00, //  60
0x00, //  61
0x00, //  62
0x00, //  63
0x00, //  64
0x00, //  65
0x00, //  66
0x00, //  67
0x00, //  68
0x00, //  69
0x00, //  6A
0x00, //  6B
0x00, //  6C
0x00, //  6D
0x00, //  6E
0x00, //  6F
0x00, //  70  
0x00, //  71
0x00, //  72
0x00, //  73
0x00, //  74
0x00, //  75
0x00, //  76
0x00, //  77
0x00, //  78
0x00, //  79
0x00, //  7A
0x00, //  7B
0x00, //  7C
0x00, //  7D
0x00, //  7E
0x00, //  7F
0x20,
0x83
};


