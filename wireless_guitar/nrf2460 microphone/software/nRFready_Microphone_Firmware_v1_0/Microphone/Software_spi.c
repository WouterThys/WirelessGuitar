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

#include "Software_spi.h"

void ClockEight ( BYTE  data)
{
     BYTE t;
   for(t=0;t<8;t++)
    {
      if(data & 0x80)
         Output_High(DATAO);
      else
         Output_Low(DATAO);
      _delay_2uS();
      Output_High(CLK);
      _delay_2uS();
      Output_Low(CLK);
      _delay_2uS();
      data = data<<1;
    }
}

// if selected AKMChipSelect this routine selects the AKM instead of the Nordic
void SPI_Send( BYTE  address, BYTE  data8, BYTE Target)
{
   //  BYTE t;
    Output_Low(CLK);
    delay_ms(1);
    if ( Target )
    {
        Output_Low(CSNA);
    }
    else
    {
    Output_Low(CSNW);
    }
    delay_ms(1);
    ClockEight(address);

    delay_ms(1);
    ClockEight(data8);
    

     delay_ms(1);
    if ( Target )
    {
        Output_High(CSNA);
    }
    else
    {
    Output_High(CSNW);
    }
    // Output_High(CSNW);
     delay_ms(1);
}
BYTE Nordic_Read(  BYTE raddress2)
{    
     BYTE t;   BYTE data8;
    Output_Low(CLK);
    _delay_2uS();
    raddress2 = raddress2 | 0x80;  //force read bit
    delay_ms(1);
    Output_Low(CSNW);
    delay_ms(1);
    ClockEight(raddress2);

    delay_ms(1);
    data8 = 0;
    for(t=0;t<8;t++)              // Get data
    {
        data8 = data8<<1;
        _delay_2uS();
        Output_High(CLK);
        _delay_2uS();
        if(input(DATAI))                                   
            data8=data8+1;
        Output_Low(CLK);
     }
     delay_ms(1);
     Output_High(CSNW);
     delay_ms(1);
     //delay_ms(4);
  return(data8);
}

