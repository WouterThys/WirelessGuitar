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

#ifndef TYPES_H
#define TYPES_H



#define STATIC

/****************************************************************************/
/*                  T Y P E   D E F I N I T I O N S                         */
/****************************************************************************/

//
//  For shorthand purposes only, some common types
//
typedef unsigned short  WORD;
typedef unsigned char   BYTE;
typedef unsigned long   DWORD;
typedef unsigned char * STRING;
typedef signed char SBYTE;

//
//  Give us a bool type
//
typedef BYTE bool;
enum {false, true};
enum {FALSE,TRUE};


//
//  A commonly used function pointer type
//
typedef void (*VoidFunction) (void);


/****************************************************************************/
/*        A P P L I C A T I O N   S C O P E   D E C L A R A T I O N S       */
/****************************************************************************/

/****************************************************************************/
/*                          F U N C T I O N S                               */
/****************************************************************************/

#endif

