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

#include <pic.h>
#include "pinouts.h"
#include "nordicmanager.h"
#include "adjustableparameters.h"
__CONFIG(0x30D4);

BYTE TransmissionError;

#define input(x)    ( x==1 )
#define _nop() asm("nop")


typedef   bit   int1;
#define   CONST   const

unsigned int i=0, data=0, red_address_changed=0, blue_address_changed=0, timeout=0;


eeprom unsigned char NordicReg1RED[64] =
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
RED_NORDIC_REG_0x0C,     
RED_NORDIC_REG_0x0D,      
RED_NORDIC_REG_0x0E,      
RED_NORDIC_REG_0x0F,      
RED_NORDIC_REG_0x10,      
RED_NORDIC_REG_0x11,      
RED_NORDIC_REG_0x12,      
RED_NORDIC_REG_0x13,      
RED_NORDIC_REG_0x14,      
RED_NORDIC_REG_0x15,      
RED_NORDIC_REG_0x16,      
RED_NORDIC_REG_0x17,      
RED_NORDIC_REG_0x18,      
RED_NORDIC_REG_0x19,      
RED_NORDIC_REG_0x1A,      
RED_NORDIC_REG_0x1B,      
RED_NORDIC_REG_0x1C,      
RED_NORDIC_REG_0x1D,      
RED_NORDIC_REG_0x1E,      
RED_NORDIC_REG_0x1F,      
RED_NORDIC_REG_0x20,     
RED_NORDIC_REG_0x21,      
RED_NORDIC_REG_0x22,      
RED_NORDIC_REG_0x23,      
RED_NORDIC_REG_0x24,      
RED_NORDIC_REG_0x25,      
RED_NORDIC_REG_0x26,      
RED_NORDIC_REG_0x27,      
RED_NORDIC_REG_0x28,      
RED_NORDIC_REG_0x29,      
RED_NORDIC_REG_0x2A,      
RED_NORDIC_REG_0x2B,      
RED_NORDIC_REG_0x2C,      
RED_NORDIC_REG_0x2D,      
RED_NORDIC_REG_0x2E,      
RED_NORDIC_REG_0x2F,      
RED_NORDIC_REG_0x30,      
RED_NORDIC_REG_0x31,      
RED_NORDIC_REG_0x32,      
RED_NORDIC_REG_0x33,      
RED_NORDIC_REG_0x34,     
RED_NORDIC_REG_0x35,      
RED_NORDIC_REG_0x36,      
RED_NORDIC_REG_0x37,      
RED_NORDIC_REG_0x38,     
RED_DEFAULT_ADDRESS_0,  
RED_DEFAULT_ADDRESS_1 , 
RED_DEFAULT_ADDRESS_2 , 
RED_DEFAULT_ADDRESS_3 , 
RED_DEFAULT_ADDRESS_4 , 
0x00, //  3E
0x00, //  3F

};
eeprom  unsigned char NordicReg1REDA[64] =
{
0x00, //  40
0x00, //  41
0x00, //  42
0x00, //  43
0x00, //  44
0x00, //  45   
0x00, //  46
0x00, //  47
0x00, //  48   
0x03, //  49
0x00, //  4A
0x00, //  4B
0x00, //  4C   
0x00, //  4D
0x00, //  4E
0x00, //  4F
0x00, //  50   
0x00, //  51
0x06, //  52
0x00, //  53   
0x00, //  54
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
0x00  //  7F
//0x20,
//0x82
};

eeprom unsigned char NordicReg2BLUE[64] =
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
DEFAULT_ADDRESS_0, //  39    
DEFAULT_ADDRESS_1 , //  3A 
DEFAULT_ADDRESS_2 , //  3B
DEFAULT_ADDRESS_3 , //  3C
DEFAULT_ADDRESS_4 , //  3D
0x00, //  3E
0x00, //  3F

};
eeprom  unsigned char NordicReg2BLUEA[64] =
{
0x00, //  40
0x00, //  41
0x00, //  42
0x00, //  43
0x00, //  44
0x00, //  45   
0x00, //  46
0x00, //  47
0x00, //  48   
0x03, //  49
0x00, //  4A
0x00, //  4B
0x00, //  4C   
0x00, //  4D
0x00, //  4E
0x00, //  4F
0x00, //  50  
0x00, //  51
0x06, //  52 
0x00, //  53   
0x00, //  54
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
0x00  //  7F

};


//#org DEFAULT
void setup_ports(void);


/*************************************************************************/
void main(void)
{  

    setup_ports();
	PDN1=0;
	PDN2=0;

	N_RESET=0; //NORDIC POWERUP
	delay_us(500);
	delay_ms(100);
	delay_ms(100);
 	delay_ms(100);
	delay_ms(100);
	delay_ms(100);
	delay_ms(100);
	delay_ms(100);
	delay_ms(100);//

	N_ADDR=0xD2; //nordic master red
	Nordic_Wakeup(); 
	
	N_ADDR=0x52; //nordic slave blue
	Nordic_Wakeup2();
	
	LED1=0;
	LED2=0;
	
	delay_ms(100);
	
	while(1)
	{	
		N_ADDR=0xD2; //red
		if(!(Nordic_Read(0x03)&0x01))   //flash if not connected
		{
			LED2=1;
			delay_ms(255);
			LED2=0;
			delay_ms(255);
		}
		else                           //solid if connected
		{
			LED2=1;
		}
		

		N_ADDR=0x52; //blue
		if(!(Nordic_Read(0x03)&0x01))    //flash if not connected
		{
			LED1=1;
			delay_ms(255);
			LED1=0;
			delay_ms(255);
		}
		else			//solid if connected
		{
			LED1=1;
		}
		delay_ms(255);


		//pairing button
		if (!SW)
		{
			delay_ms(255);
			delay_ms(255);
			delay_ms(255);
			if (!SW)   //button long enough, start pairing
			{
				PDN1=1;PDN2=1;

				while(!SW)
				{
					LED1=1;
					LED2=1;
					delay_ms(100);
					LED1=0;
					LED2=0;
					delay_ms(100);
				}

				N_ADDR=0xD2;     //address red
				Nordic_Send(0x39, RED_PAIRING_ADDRESS_0); //set to pairing address
				Nordic_Send(0x3A, RED_PAIRING_ADDRESS_1);
				Nordic_Send(0x3B, RED_PAIRING_ADDRESS_2);
				Nordic_Send(0x3C, RED_PAIRING_ADDRESS_3);
				Nordic_Send(0x3D, RED_PAIRING_ADDRESS_4);
				Nordic_Send(0x36, 0x10); //force relink

				N_ADDR=0x52;     //address blue
				Nordic_Send(0x39, PAIRING_ADDRESS_0);
				Nordic_Send(0x3A, PAIRING_ADDRESS_1);
				Nordic_Send(0x3B, PAIRING_ADDRESS_2);
				Nordic_Send(0x3C, PAIRING_ADDRESS_3);
				Nordic_Send(0x3D, PAIRING_ADDRESS_4);
				Nordic_Send(0x36, 0x10); //force relink


				
				while ((red_address_changed == 0) && (blue_address_changed == 0) && (timeout !=1 )) //check for change of address
				{
					N_ADDR=0xD2;
					if (Nordic_Read(0x39)!=RED_PAIRING_ADDRESS_0)
						red_address_changed=1;
					if (Nordic_Read(0x3A)!=RED_PAIRING_ADDRESS_1)
						red_address_changed=1;
					if (Nordic_Read(0x3B)!=RED_PAIRING_ADDRESS_2)
						red_address_changed=1;
					if (Nordic_Read(0x3C)!=RED_PAIRING_ADDRESS_3)
						red_address_changed=1;
					if (Nordic_Read(0x3D)!=RED_PAIRING_ADDRESS_4)
						red_address_changed=1;

					N_ADDR=0x52;
					if (Nordic_Read(0x39)!=PAIRING_ADDRESS_0)
						blue_address_changed=1;
					if (Nordic_Read(0x3A)!=PAIRING_ADDRESS_1)
						blue_address_changed=1;
					if (Nordic_Read(0x3B)!=PAIRING_ADDRESS_2)
						blue_address_changed=1;
					if (Nordic_Read(0x3C)!=PAIRING_ADDRESS_3)
						blue_address_changed=1;
					if (Nordic_Read(0x3D)!=PAIRING_ADDRESS_4)
						blue_address_changed=1;

					i++;
					if (i==60)
					{
						timeout=1;
						i=0;
					}

					LED1=1;
					LED2=1;
					delay_ms(100);
					LED1=0;
					LED2=0;
					delay_ms(100);
				}

				if (timeout != 1) //if timed out, skip 
				{
					for (i=0;i<5;i++)
						delay_ms(255);
					
					for (i=0;i<5;i++) //write address to EEPROM
					{
						N_ADDR=0xD2;	
						delay_ms(10);
						if (red_address_changed==1) //red changed
						{
							data=Nordic_Read(0x39+i);
							EEpromWrite(0x39+i,Nordic_Read(0x39+i));
						}
						else
						{
							data=EEpromRead(0x39+i);
							Nordic_Readback(0x39+i,data);
							
						//	Nordic_Send(0x39+i, EEpromRead(0x39+i));	//0x39
						}
				
						N_ADDR=0x52;	
						delay_ms(10);
						if (blue_address_changed==1)  //blue changed
						{
							data=Nordic_Read(0x39+i);
							EEpromWrite((0x39+128)+i,Nordic_Read(0x39+i));
						}
						else
						{
							data=EEpromRead((0x39+128)+i);							
							Nordic_Readback(0x39+i, data); //57+128
						
						}
	
						delay_ms(50);	
					}
					if (red_address_changed==0)
					{
						N_ADDR=0xD2; //red
						Nordic_Send(0x36, 0x10); //force relink
						N_RESET=0; //NORDIC POWERUP
						
						delay_ms(100);
						delay_ms(100);
					 	delay_ms(100);
					
					
						N_ADDR=0xD2; //nordic master red
						Nordic_Wakeup(); 
					
	
					}
					if (blue_address_changed==0)
					{
						N_ADDR=0x52;        //blue
						Nordic_Send(0x36, 0x10); //force relink
						N_RESET=0; //NORDIC POWERUP
						
						delay_ms(100);
						delay_ms(100);
					 	delay_ms(100);
					
					
						N_ADDR=0x52; //nordic slave blue
						Nordic_Wakeup2();

					}
				}
			/*	else
				{
					for (i=0;i<5;i++) //write address to EEPROM
					{
						N_ADDR=0xD2;	
						delay_ms(10);
						Nordic_Send(0x39+i, EEpromRead(57+i));	
					
						N_ADDR=0x52;	
						delay_ms(10);
						Nordic_Send(0x39+i, EEpromRead(185+i)); //57+128
					
						delay_ms(50);	
					}
				}*/
				
				timeout=0;
				i=0;
				red_address_changed=0;
				blue_address_changed=0;
				PDN1=0;PDN2=0;
				delay_ms(255);
			}
		}	
	}
}        
   
void delay_us(BYTE time)
{
    while ( time )
    {
        time--;
    }
}
void delay_ms(BYTE time)
{
    BYTE temp=20;
    BYTE temp2=19;

    while ( time )
    {
        while (temp2  )
        {
            while ( temp )
            {
                temp--;
            }
         temp2--;
        temp=20;
        }
        temp2=19;
        time--;
    }
}

BYTE EEpromRead(BYTE address)
{

 //   EEADRH=0;
    EEADR=address;
    RD=1;  //RD=1
    return (EEDAT);

}

void EEpromWrite(BYTE address, BYTE value)
{
     EEADR=address;
	 EEDAT=value;

  	 //EECON1bits.CFGS=0;
     //EECON1bits.EEPGD=0;
     //EEADRH=0;
     //EEADR=address; //ADDRESS_4;
     //EEDATA=value;  //data8;
     WREN=1;
     GIE=0;
     EECON2=0x55;
     EECON2=0xAA;
     WR=1;
     GIE=1;
     WREN=0;
}


//***********************************************************
void setup_ports(void)
{
   OSCCON = 0x71;
   ANSEL = 0;
   CMCON0=7;
   CMCON1=0;
   ADON=0;
  
   TRISA=0x20;
   TRISC=0x02;
   PORTA=0x00;
   PORTC=0x00;

}
/****************************************************************************/

