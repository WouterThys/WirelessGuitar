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

#include "nordicmanager.h"



BYTE    Nordic_LinkPresent(void)
{
    BYTE temp;
    temp=Nordic_Read(0x83);
    temp=temp&0x01;
	    
    return temp;
}


void Nordic_Wakeup(void)
{
    BYTE t;
	BYTE pointer;    
	BYTE data8;  
	BYTE address;    
	BYTE dataR;
	BYTE raddress;

#ifdef _16F684||_16F505
    Output_Low(CLK);
    Output_Low(DATAO);
#endif
    _delay_2uS();
    for(pointer =0; pointer<130; pointer++)     //Looping Send/Readback               
    {
		#asm
			CLRWDT
		#endasm
      	address = pointer;
      	if(pointer == 128)
        	address = 0x4A;                //change for RXmod
      	if(pointer == 129)
        	address = 0x5A;                //change for TXmod
      	raddress = address ;        //Save Read Address
               
      	data8 = NordicRegData[pointer] ;   //Get data from table
      	dataR=data8;

      	if(data8 != 0x00 )                //Only send/read if not zero
      	{
        	SPI_Send( address,data8,NORDIC_TARGET);
      		data8=Nordic_Read( raddress );

            if(data8 != dataR)
            {
            	pointer = pointer -1;               //If data does not match resend
            }
  
      	}
    }
}

