#include "../h/spi_tx.h"
#include "../h/interrupts.h"
#include <p18f2550.h>

unsigned char read = 0;

/*************************************************
            Initialize the SPI Master
 **************************************************/

void spi_init_master() {
    SSPEN  = 0; // disable MMSP

    SMP = 1; // *******Sample bit               - sample at the end
    CKP = 0; // Clock Polarity			- low when idle		**MUST BE SAME ON MASTER AND SLAVE**
    CKE = 1; // Clock Edge Select		- transmit on transition from active clock state to idle
    SSPM = 0b0010; //master mode
    SSPEN = 0; // Wait to enable serial port

    SSPIF = 0;
    SSPIE = 0;
    SSPIP = 0;
}

/*************************************************
            Fast Writing Data
 **************************************************/
unsigned char spi_w(unsigned char data) {
     SSPBUF = data;
     while(!SSPIF){};       // Wait until data is fetched
     SSPIF = 0;             // Clear flag
     return SSPBUF;
     
}

/*************************************************
            Writing Array
 **************************************************/
void spi_w_array(unsigned char * data, unsigned char length){
    unsigned char tmp;
    while(length){
	SSPBUF = *data;     // Load one byte
	while( !SSPIF );    // Wait for buffer full
        SSPIF = 0;          // Clear flag
        tmp = SSPBUF;       // Read out data
        length--;
	data++;
    }
}


/*************************************************
            Writing/Reading Array
 **************************************************/
void spi_rw_array(unsigned char * dataout, unsigned char * datain, unsigned int length){
    while(length){
	SSPBUF = *dataout;  // Load one byte
	while( !SSPIF );    // Wait for buffer full
        SSPIF = 0;          // Clear flag
        *datain = SSPBUF;   // Read out data
        length--;
	dataout++;
        datain++;
    }
}


/*************************************************
            Enable SPI
 **************************************************/
void spi_enable() {
    SDI = 1;   // Serial Data In     	- enable master mode
    SCK = 0;   // Serial Clock          - clear TRISB1 for master
    SDO = 0;   // Serial Data Out       - clear TRISC7
    SSPEN = 1; // Enable serial port
}


/*************************************************
            Disable SPI
 **************************************************/
void spi_disable() {
    SSPEN = 0; // Disable serial port
} 