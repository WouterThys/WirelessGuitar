#ifndef __SPI_TX_H
#define __SPI_TX_H

/** I N C L U D E S *************************************************/
#include <p18f2550.h>						// Finds correct header for any PIC18
#include <delays.h>                                             // Enables you to add varying amount of NOPs (Delays)
#include <stdlib.h>

/** V A R I A B L E S ***********************************************/

extern unsigned char input;

// Define names for SPI connection pins
#define SDO 		TRISCbits.TRISC7		// Serial Data Out (SDO)	-- Pin that data goes out from
#define SDI 		TRISBbits.TRISB0		// Serial Data In (SDI)		-- Pin that data comes in to
#define SCK 		TRISBbits.TRISB1		// Serial Clock (SCK)		-- Pin that sends clock signal to sync all  SPI devices
#define SMP             SSPSTATbits.SMP			// Sample Bit (SMP)		-- Pin that sets where to sample data
#define CKP		SSPCON1bits.CKP			// Clock Polarity (CKP)		-- Pin that sets where SCK will idle
#define CKE		SSPSTATbits.CKE			// Clock Edge Select (CKE)	-- Pin that sets which transition transmission takes place
#define SSPEN		SSPCON1bits.SSPEN		// Serial Prt Enbl (SSPEN)	-- Pin that will enable serial port and configure SCK, SDO, SDI and SS as serial port pins
#define SSPM            SSPCON1bits.SSPM                // Master/lave mode (SSPM)      -- Choose between master and slave mode
#define WCOL		SSPCON1bits.WCOL		// Write Collision (WCOL)	-- Detect bit
#define BF              SSPSTATbits.BF

#define SPI             0x12


/** P R O T O T Y P E S *********************************************/


/*************************************************
                        Functions for Writing Data
 **************************************************/
void spi_init_master(void);
unsigned char spi_w(unsigned char data);
void spi_w_array(unsigned char * data, unsigned char length);
void spi_rw_array(unsigned char * dataout, unsigned char * datain, unsigned int length);
void spi_enable(void);
void spi_disable(void);

#endif
//EOF----------------------------------------------------------------
