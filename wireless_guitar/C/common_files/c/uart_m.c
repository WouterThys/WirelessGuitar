#include <p18cxxx.h>
#include <stdio.h>
#include "../h/uart_m.h"

char read_data;
char new_data;

void init_uart_m(int baud, char TX_inv, char RX_inv) {
//	FOSC/[64 (n + 1)] (n = value of SPBRGH:SPBRG register pair)
//	For a device with FOSC of 48 MHz, desired baud rate of 9600, Asynchronous mode, 8-bit BRG:
//	Desired Baud Rate = FOSC/(64 ([SPBRGH:SPBRG] + 1))
//	Solving for SPBRGH:SPBRG:
//	X = ((FOSC/Desired Baud Rate)/64) – 1
//	= ((48000000/64*9600)) – 1
//	= [77.125] = 77(0x4D)
	
	SPBRG = baud;    

//transmitter control register TXSTA
        CSRC = 0;             //master mode
	BRGH = 0; 		//low speed
        TXEN = 0;             //wait
	TX9 = 0;              //8bit transmissie
	SYNC = 0; 		//asynchroon

//receiver
        SPEN = 0;             //wait
	RX9 = 0; 		//8bit
	ADDEN = 0; 		//geen addressen		

// baud controle
	TXCKP = TX_inv; //data  inverteren
	RXDTP = RX_inv; //data  inverteren
	BRG16 = 0; 		//8bit BRG
}

void uart_write_m(char data) {
	TXREG = data;
        while(TRMT==0) {}
}

void uart_write_string(char *text) {
  int i;
  for(i=0;text[i]!='\0';i++)
	  uart_write_m(text[i]);
}

char uart_read_m() {
  while(!RCIF);
  return RCREG;
}

void uart_read_string(char *Output, unsigned int length) {
	int i;
	for(i=0;i<length;i++)
		Output[i] = uart_read_m();
}

void enable_uart_m() {
	RX = 1;		//RX pin
	TX = 0;		//TX pin

	TXEN = 1; 		//activate TX
	CREN = 0; 		//activate RX
	SPEN = 1;             // Enable UART
}

void disable_uart_m() {
	TXEN = 0; 		//deactivate TX 
	CREN = 0; 		//deactivate RX
	SPEN = 0;		//disable UART
}


void terminal_write_m(const char string[],signed int value) {
#ifdef SPI
    spi_disable();
#endif
    enable_uart_m();
    printf(string,value);
    disable_uart_m();
#ifdef SPI
    spi_enable();
#endif
}

void putch(unsigned char byte)
{
    uart_write_m(byte);
}


void lcd_write(unsigned char data) {
//    spi_disable();
//    enable_uart_m();
//
//    uart_write_m(data);
//
//    disable_uart_m();
//    spi_enable();
}

/*******************************************************************************
 *              Uart write/read one block
 *              -------------------------
 *
 * Writes/reads one block of data to the uart
 *******************************************************************************/
void uart_write_block(unsigned char *data, unsigned char length) {
    while (length) {
        TXREG = *data;
        while(TRMT==0) {}
        length--;
        data++;
    }
}