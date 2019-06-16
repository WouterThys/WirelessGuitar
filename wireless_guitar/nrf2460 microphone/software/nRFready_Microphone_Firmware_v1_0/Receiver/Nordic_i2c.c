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

#include "nordic_i2c.h"
#include "nordicmanager.h"

typedef unsigned char BYTE;

static void ClockEight( BYTE  temp);

static void ClockEight( BYTE  temp)
{
     BYTE t;
	 for(t=0;t<8;t++)
    {

       Output_Low(mSDA);

       if(temp & 0x80)
          Output_High(mSDA);
        delay_us(100);
       Output_High(mSCL);
       delay_us(100);
       Output_Low(mSCL);
       delay_us(100);
       temp = temp<<1;
       Output_Low(mSDA);
    }
}

void Nordic_Send(  BYTE  address, BYTE  data8)
{
    // BYTE t;
     BYTE temp;
    TransmissionError=0;
  //  IssueStartBit();
#if 1
    Output_High(mSCL);
    Output_High(mSDA);
    delay_us(100);
    Output_Low(mSDA);
    delay_us(100);
    Output_Low(mSCL);
    delay_us(100);
#endif
    temp = N_ADDR;
    ClockEight( temp);

#ifdef _12F519
    TRIS=TRIS_I2C_READ;
#endif
    mSDA_Input();
    delay_us(3);
    Output_High(mSCL);
    delay_us(100);
    if(mSDA)//if(mReadSDA)
    {
       TransmissionError |= 1;
    }
    Output_Low(mSCL);


#ifdef _12F519
    TRIS=TRIS_I2C_WRITE;
#endif
    mSDA_Output();

    ClockEight( address);


#ifdef _12F519
    TRIS=TRIS_I2C_READ;
#endif
    mSDA_Input();
    Output_High(mSCL);
    delay_us(100);
    if(mSDA)//if(mReadSDA)
    {
       TransmissionError |= 1;
    }

    Output_Low(mSCL);

#ifdef _12F519
    TRIS=TRIS_I2C_WRITE;
#endif
    mSDA_Output();

    ClockEight( data8);


#ifdef _12F519
    TRIS=TRIS_I2C_READ;
#endif    
    mSDA_Input();
    
    Output_High(mSCL);
    delay_us(100);
    if(mSDA)//if(mReadSDA)
    {
     TransmissionError |= 1;

    }

    Output_Low(mSCL);

#ifdef _12F519
    TRIS=TRIS_I2C_WRITE;
#endif
    mSDA_Output();

    Output_Low(mSDA);  //STOP CONDITION
    delay_us(100);
    Output_High(mSCL);
    delay_us(100);
    Output_High(mSDA);

}
BYTE Nordic_Read(  BYTE raddress)
{
     BYTE t; BYTE  temp;
    TransmissionError=0;
    //IssueStartBit();
#if 1
    Output_High(mSCL);
    Output_High(mSDA);
    delay_us(100);
    Output_Low(mSDA);
    delay_us(100);
    Output_Low(mSCL);
    delay_us(100);
#endif
    temp = N_ADDR;
    ClockEight( temp);


#ifdef _12F519
    TRIS=TRIS_I2C_READ;
#endif
    mSDA_Input();

    Output_High(mSCL);
    delay_us(100);
    if(mSDA)//if(mReadSDA)
    {
       TransmissionError |= 1;
    }
    Output_Low(mSCL);//finish ack


#ifdef _12F519
    TRIS=TRIS_I2C_WRITE;
#endif
    mSDA_Output();


    delay_us(100);
    ClockEight( raddress);



#ifdef _12F519
    TRIS=TRIS_I2C_READ;
#endif
    mSDA_Input();

    Output_High(mSCL);
    delay_us(100);
    if(mSDA)// if(mReadSDA)
    {

       TransmissionError |= 1;

    }

    Output_Low(mSCL);//finish ack

    mSDA_Output();


    Output_High(mSDA);

    delay_us(100);
    Output_High(mSCL);
    delay_us(100);
    Output_Low(mSDA);//restart
    delay_us(100);
    Output_Low(mSCL);
    delay_us(100);

    temp = N_ADDR+1;
    ClockEight( temp);


    mSDA_Input();

    Output_High(mSCL);
    delay_us(100);
    if(mSDA)//if(mReadSDA)
    {
       TransmissionError |= 1;


    }
    Output_Low(mSCL);//finish ack



    temp=30;
    while ( --temp ) ;

    temp = 0;

    for(t=0;t<8;t++)              // Get data
    {
       temp = temp<<1;
       delay_us(100);
       Output_High(mSCL);
       delay_us(100);
       if(mSDA)//if(mReadSDA)
           temp=temp+1;
       Output_Low(mSCL);
    }




    Output_High(mSCL);
    delay_us(100);
    if(!mSDA)//if(!mReadSDA)
    {
       TransmissionError |= 1;

    }
    Output_Low(mSCL);//finish ack
    //
    //delay_us(30);
    //Output_High(mSCL);
    //delay_us(30);
   // Output_Low(mSCL);


    mSDA_Output();

    Output_Low(mSDA);  //STOP CONDITION
    Output_High(mSCL);
    delay_us(100);
    Output_High(mSDA);
    return(temp);
}
#if 1
BYTE Nordic_Readback ( BYTE  address,  BYTE  data8)
{
    BYTE raddress,rdata;
    BYTE temp=250;
    raddress=address;
    rdata=data8;
    Nordic_Send(address,data8);
   while ( --temp );
    data8= Nordic_Read(address);
    return (rdata==data8 );

}
#endif
