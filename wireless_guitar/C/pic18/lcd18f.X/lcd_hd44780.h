/* 
 * File:   lcd_hd44780_pic16.h
 * Author: Avinash
 *
 * Created on 6 June, 2013, 11:51 AM
 */

#ifndef LCD_HD44780_H
#define	LCD_HD44780_H

#include <xc.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


/************************************************
	LCD CONNECTIONS
*************************************************/

//LCD Data Port
//Port PA1-PA4 are connected to D4-D7
#define LCD_DATA        A   //Port PA1-PA4 are connected to D4-D7
#define LCD_DATA_POS    1

//Register Select (RS)
//RS is connected to Port C bit 0
#define LCD_RS_PORT     C
#define LCD_RS_POS      0

//Read/Write (RW)
//RW is connected to Port C bit 1
#define LCD_RW_PORT     C
#define LCD_RW_POS      1

//Enable signal (E)
//E is connected to Port C bit 2
#define LCD_E_PORT      C
#define LCD_E_POS       2

#define LCD_BRIGHT_PORT PORTB
#define LCD_LED_PORT    PORTAbits.RA5

/***********************************************

LCD Type Selection
Uncomment Just one of them

************************************************/

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


//************************************************




//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000



/***************************************************
			F U N C T I O N S
****************************************************/



void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteSmartString(const char *msg);
void LCDWriteInt(int val,int8_t field_length);
void LCDWriteBin(char val,char notation);
void LCDWriteHex(char val,char notation);
void LCDGotoXY(uint8_t x,uint8_t y);
void LCDLoadCostum(char select);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();

/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome()  LCDCmd(0b00000010)

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}

#define LCDWriteBinXY(x,y,val,notation) {\
 LCDGotoXY(x,y);\
 LCDWriteBin(val,notation);\
}

#define LCDWriteHexXY(x,y,val,notation) {\
 LCDGotoXY(x,y);\
 LCDWriteHex(val,notation);\
}

const unsigned char __brght [] =
 {
     0b0001, 0b0010, 0b0100, 0b0011, 0b0101, 0b0110, 0b1000,
     0b0111, 0b1001, 0b1010, 0b1100, 0b1011, 0b1101, 0b1110,
     0b1111,
 };
#define BRIGHTNESS_MIN    0
#define BRIGHTNESS_MAX    15

#define LCDBrightness(a) {\
 LCD_BRIGHT_PORT = (__brght[a]<<4);\
}

#define LCDLedOn()    (LCD_LED_PORT = 1)
#define LCDLedOff()   (LCD_LED_PORT = 0)
/***************************************************/




/*_________________________________________________________________________________________*/

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_HD44780_PIC16_H */

