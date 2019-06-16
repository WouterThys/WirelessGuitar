/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif
#endif

#include <delay.h>
#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include "dsp.h"
#include "../../common_files/system.h"
#include "../../common_files/common_defs&vars.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void) {
    // Setup analog functionality and port direction 
    TRISA = 0x0000;
    ANSELA = 0x0000;
    PORTA = 0x0000;

    TRISB = 0x0000;
    ANSELB = 0x0000;
    PORTB = 0x0000;
}


/*******************************************************************************/
/*******************************************************************************/
/**    **    **    *****     ******     ********                               */
/**    **    **   **   **    **   **    ********                               */
/**    **    **   **   **    ******        **                                  */
/**     **  **    *******    **  **        **                                  */
/**       **      **   **    **   **       **                                  */
/*******************************************************************************/
/*******************************************************************************/
void InitUart1(void) {
     /* UART TRIS SELECT */
    TRISBbits.TRISB5 = 1; // RX
    TRISBbits.TRISB6 = 0; // TX
    PORTBbits.RB6 = 1; // TX when not controlled by UART : high !!!

    /* SELELCT OUTPUT PORTS */
    RPINR18bits.U1RXR = 37; // Select Pin14 (= RP37) to RXUART1
    RPOR2bits.RP38R = 0b000001; // Select Pin15 (= RP38) to TXUART1, RP38 tied to UART1 Transmit

    // U1MODE Register Settings
    U1MODEbits.UARTEN = 0; //UARTx is disabled; all UARTx pins are controlled by PORT latches; UARTx power consumption minimal
    U1MODEbits.USIDL = 0; //Continue module operation in Idle mode
    U1MODEbits.IREN = 0; //IrDA encoder and decoder disabled
    U1MODEbits.UEN = 0b00; //UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLKx pins controlled by PORT latches
    U1MODEbits.LPBACK = 0; //Loopback mode is disabled
    U1MODEbits.ABAUD = 0; //Baud rate measurement disabled or completed
    U1MODEbits.URXINV = 1; //1 = UxRX Idle state is ?0?
    U1MODEbits.BRGH = 0; //BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
    U1MODEbits.PDSEL = 0b00; //8-bit data, no parity
    U1MODEbits.STSEL = 0; //One Stop bit

    // U1STA Register Settings
    U1STAbits.UTXISEL0 = 0; //bit 15,13 UTXISEL<1:0>: Transmission Interrupt Mode Selection bits
    U1STAbits.URXISEL1 = 0; // Interrupt when a character is transferred to the Transmit Shift Register (this implies there is at least one character open in the transmit buffer)
    U1STAbits.UTXINV = 1; //UxTX Idle state is ?0?
    U1STAbits.UTXEN = 0; //Transmit disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled by port.
    U1STAbits.URXISEL = 0b00; //Interrupt is set when any character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more characters
    U1STAbits.ADDEN = 0; //Address Detect mode disabled

    // U1BRG Register Settings
    U1BRG = 455; // 455  --->  Baud = 9600   Fcy = 70 Mhz
}

 void putch(uint8_t byte) {
     U1TXREG = byte;
     while(U1STAbits.TRMT == 0) {}
 }


/*******************************************************************************/
/*******************************************************************************/
/**    *****      *****      **                                                */
/**    **         **   *     **                                                */
/**      **       *****      **                                                */
/**        **     **         **                                                */
/**    ******     **         **                                                */
/*******************************************************************************/
/*******************************************************************************/
void InitSpiMaster(void) {
    /* SPI TRIS SELECT*/
    TRISBbits.TRISB7 = 0; // SCK1 is clock output (Master mode)
    TRISBbits.TRISB8 = 0; // SD01 is data output
    TRISBbits.TRISB9 = 1; // SDI1 is data input

    SPI1BUF = 0; // Clear the buffer

    // SPI1STAT Register Settings
    SPI1STATbits.SPIEN = 0; // Disable SPI module
    SPI1STATbits.SPISIDL = 0; // Continue module operation in Idle mode
    SPI1STATbits.SPIBEC = 0; // Number of SPIx transfers are pending.
    SPI1STATbits.SPIROV = 0; // No Receive Overflow has occurred

    // SPI1CON1 Register Settings
    SPI1CON1bits.DISSCK = 0; // SPIx clock on SCKx pin is enabled
    SPI1CON1bits.DISSDO = 0; // SDOx pin is controlled by the module
    SPI1CON1bits.MODE16 = 0; // Communication is byte-wide (8 bits)
    SPI1CON1bits.SMP = 1; // Input data is sampled at the end of data output time
    SPI1CON1bits.CKE = 1; // Serial output data changes on transition from active clock state to Idle clock state (see bit 6)
    SPI1CON1bits.CKP = 0; // Idle state for clock is a low level; active state is a high level
    SPI1CON1bits.MSTEN = 1; // Master mode enabled
    SPI1CON1bits.SPRE = 0b111; // Secondary prescale 1:1
    SPI1CON1bits.PPRE = 0b00; // Primary prescale 64:1
    
    // SPI1CON2 Register Settings
    SPI1CON2bits.FRMEN = 0; // Framed SPIx support is disabled
    SPI1CON2bits.SPIBEN = 0; // Enhanced buffer is disabled (Legacy mode)
    
    // Enable SPI module
    SPI1STATbits.SPIEN = 1; // Enable SPI module
}

uint8_t WriteSpi_8b(uint8_t data) {
     SPI1BUF = data;
     while(!SPI1STATbits.SPIRBF) {}
     return SPI1BUF;

}

uint8_t WriteSpi_16b(uint16_t data) {
     SPI1CON1bits.MODE16 = 1;
     SPI1BUF = data;
     while(!SPI1STATbits.SPIRBF) {}
     return SPI1BUF;
}

uint8_t WriteSpi_array(uint8_t * data, uint8_t length){
    while(length){
        WriteSpi_8b(*data);
        length--;
	data++;
    }
    return 1;
}

void    ReadSpi_array(uint8_t * dataout, uint8_t * datain, uint8_t length){
    while(length){
	SPI1BUF = *dataout;  // Load one byte
	while(!SPI1STATbits.SPIRBF) {}    // Wait for buffer full            // Clear flag
        *datain = SPI1BUF;   // Read out data
        length--;
	dataout++;
        datain++;
    }
}

/*******************************************************************************/
/*******************************************************************************/
/**     *****     *****         ****                                           */
/**    **   **    **   **     **                                               */
/**    **   **    **    **   **                                                */
/**    *******    **   **     **                                               */
/**    **   **    *****         ****                                           */
/*******************************************************************************/
/*******************************************************************************/
uint16_t dmaBuffer = 0;
uint16_t AdcBufferA[NUMSAMP] __attribute__((space(xmemory)));
uint16_t AdcBufferB[NUMSAMP] __attribute__((space(xmemory)));
uint16_t AdcBufferAt[NUMSAMP] __attribute__((space(xmemory)));
uint16_t AdcBufferBt[NUMSAMP] __attribute__((space(xmemory)));

void InitAdc1(void) {
    /* ADC TRIS SELECT*/
    _TRISA0 = 1;
    ANSELA = 0x0001;

    // ADCON1 Register Settings
    AD1CON1bits.ADON = 0; //0 = ADC is off
    AD1CON1bits.ADSIDL = 0; //Continues module operation in Idle mode
    AD1CON1bits.ADDMABM = 1; //DMA buffers are written in the order of conversion; the module provides an address to the DMA channel that is the same as the address used for the non-DMA stand-alone buffer
    AD1CON1bits.AD12B = 0; //10-bit, 4-channel ADC operation
    AD1CON1bits.FORM = 0b00; //Integer (D OUT = 0000 00dd dddd dddd)
    AD1CON1bits.SSRC = 0b010; //Timer3 compare ends sampling and starts conversion
    AD1CON1bits.SSRCG = 0; //Sample Trigger Source Group bit, See SSRC<2:0> for details.
    AD1CON1bits.ASAM = 1; //Sampling begins immediately after the last conversion; SAMP bit is auto-set
    AD1CON1bits.SAMP = 0; //ADC Sample-and-Hold amplifiers are holding

    // AD1CON2 Register Settings
    AD1CON2bits.VCFG = 0b000; //Converter Voltage Reference Configuration bits
    AD1CON2bits.CSCNA = 0; //Does not scan inputs
    AD1CON2bits.CHPS = 0b00; //Converts CH0
    AD1CON2bits.SMPI = 0b0000; //Increments the DMA address after completion of every sample/conversion operation
    AD1CON2bits.BUFM = 0; //Always starts filling the buffer from the start address.
    AD1CON2bits.ALTS = 0; //Always uses channel input selects for Sample MUXA

    // AD1CON3 Register Settings
    AD1CON3bits.ADRC = 1; //Clock derived from system clock
    AD1CON3bits.ADCS = 255;

    // AD1CON4 Register Settings
    AD1CON4bits.ADDMAEN = 1; //Conversion results are stored in the ADC1BUF0 register for transfer to RAM using DMA
    AD1CON4bits.DMABL = 0b000; //Allocates 1 word of buffer to each analog input

    // AD1CHS0 Register Settings
    AD1CHS0bits.CH0NA = 0; //Channel 0 negative input is V REFL
    AD1CHS0bits.CH0SA = 0b00000; //Channel 0 positive input is AN0 (1,3)

    AD1CON1bits.ADON = 1; //bit 15 ADON: ADC1 Operating Mode bit
}

void InitDma0(void) {
    // DMA0CON Register Settings
    DMA0CONbits.CHEN = 0; //Channel is disabled
    DMA0CONbits.SIZE = 0; //Word
    DMA0CONbits.DIR = 0; //Reads from peripheral address, writes to RAM address
    DMA0CONbits.HALF = 0; //Initiates interrupt when all of the data has been moved
    DMA0CONbits.NULLW = 0; //Normal operation
    DMA0CONbits.AMODE = 0b00; //Register Indirect with Post-Increment mode
    DMA0CONbits.MODE = 0b10; //Continuous, Ping-Pong modes are enabled

    // DMA0REQ Register Settings
    DMA0REQbits.FORCE = 0; //Automatic DMA transfer initiation by DMA request
    DMA0REQbits.IRQSEL = 0b00001101; //00001101 = ADC1 ? ADC1 Convert done

    // Primary Start Address bits (source or destination)
    DMA0STAL = (uint16_t) & AdcBufferA;
    DMA0STAH = (uint16_t) & AdcBufferA;

    // Primary Start Address bits (source or destination)
    DMA0STBL = (uint16_t) & AdcBufferB;
    DMA0STBH = (uint16_t) & AdcBufferB;

    // Peripheral Address Register bits
    DMA0PAD = (int16_t) & ADC1BUF0;

    // Peripheral Count Number
    DMA0CNT = (NUMSAMP - 1);

    DMA0CONbits.CHEN = 1; //DMA Channel Enable bit
}

void InitTmr3(void) {
   TMR3 = 0x0000;
   PR3 = SAMPPRD;
   T3CONbits.TCKPS = 0b00;
}
