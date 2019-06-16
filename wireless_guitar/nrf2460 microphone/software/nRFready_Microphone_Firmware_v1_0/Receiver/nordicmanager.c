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
* $LastChangedRevision: 133 $
*/

#include "nordicmanager.h"

typedef unsigned char BYTE;

signed long pointer;
BYTE data8;
BYTE address;
BYTE N_ADDR=0xD2;

void Nordic_Wakeup()
{
   
    delay_us(30);
    for(pointer =0; pointer<128; pointer++)     //Looping Send/Readback
    {
        delay_us(30);
        address = pointer;
        delay_us(30);
        data8=EEpromRead( address);
			
        if(data8 != 0x00 )                //Only send/read if not zero
	  	{
        	delay_us(30);
			if ( !Nordic_Readback(address,data8) )  //error in Nordic register load
            {
            	pointer = pointer -1;               //data does not match, resend
                LED2=1;
		   		delay_ms(500);  		
        		LED2=0;
				delay_ms(500);
             
            }
        }
    }
	while ( !Nordic_Readback(0x44,0x02) );
	while ( !Nordic_Readback(0x49,0x03) );
	while ( !Nordic_Readback(0x50,0x02) ); 
	while ( !Nordic_Readback(0x53,0x02) ); 
	while ( !Nordic_Readback(0x56,0x03) );
	while ( !Nordic_Readback(0x4A,0x20) );
	while ( !Nordic_Readback(0x5A,0x83) );
}

void Nordic_Wakeup2()
{
    	
    delay_us(30);
    for(pointer =0; pointer<128; pointer++)     //Looping Send/Readback
    {
   		delay_us(30);
        address = pointer;
		delay_us(30);
        data8=EEpromRead( address+128);

	    if(data8 != 0x00 )                
	  	{
        	delay_us(30);
            if ( !Nordic_Readback(address,data8) )
            {
            	pointer = pointer -1;               
                LED1=1;
			 	delay_ms(500);  //changed to 500
             	LED1=0;//LED2=0;
				delay_ms(500);
            }
      	}
    }
    while ( !Nordic_Readback(0x44,0x02) );
	while ( !Nordic_Readback(0x49,0x03) );
    while ( !Nordic_Readback(0x50,0x02) );
    while ( !Nordic_Readback(0x53,0x02) );
    while ( !Nordic_Readback(0x56,0x03) );
    while ( !Nordic_Readback(0x4A,0x20) );
    while ( !Nordic_Readback(0x5A,0x83) );
    
}

