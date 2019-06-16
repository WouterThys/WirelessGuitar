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

    /* UART1 MODE REGISTER */
    U1MODEbits.UARTEN = 0; //bit 15 UARTEN: UARTx Enable bit
    //1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
    //0 = UARTx is disabled; all UARTx pins are controlled by PORT latches; UARTx power consumption minimal
    U1MODEbits.USIDL = 0; //bit 13 USIDL: Stop in Idle Mode bit
    //1 = Discontinue module operation when device enters Idle mode
    //0 = Continue module operation in Idle mode
    U1MODEbits.IREN = 0; //bit 12 IREN: IrDA® Encoder and Decoder Enable bit
    //1 = IrDA encoder and decoder enabled
    //0 = IrDA encoder and decoder disabled
    U1MODEbits.UEN = 0b00; //bit 9-8 UEN<1:0>: UARTx Pin Enable bits
    //11 = UxTX, UxRX and BCLKx pins are enabled and used; UxCTS pin controlled by PORT latches
    //10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
    //01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by PORT latches
    //00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLKx pins controlled by PORT latches
    U1MODEbits.LPBACK = 0; //bit 6 LPBACK: UARTx Loopback Mode Select bit
    //1 = Enable Loopback mode
    //0 = Loopback mode is disabled
    U1MODEbits.ABAUD = 0; //bit 5 ABAUD: Auto-Baud Enable bit
    //1 = Enable baud rate measurement on the next character ? requires reception of a Sync field before other data; cleared in hardware upon completion
    //0 = Baud rate measurement disabled or completed
    U1MODEbits.URXINV = 1; //bit 4 URXINV: Receive Polarity Inversion bit
    //1 = UxRX Idle state is ?0?
    //0 = UxRX Idle state is ?1?
    U1MODEbits.BRGH = 0; //bit 3 BRGH: High Baud Rate Enable bit
    //1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
    //0 = BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
    U1MODEbits.PDSEL = 0b00; //bit 2-1 PDSEL<1:0>: Parity and Data Selection bits
    //11 = 9-bit data, no parity
    //10 = 8-bit data, odd parity
    //01 = 8-bit data, even parity
    //00 = 8-bit data, no parity
    U1MODEbits.STSEL = 0; //bit 0 STSEL: Stop Bit Selection bit
    //1 = Two Stop bits
    //0 = One Stop bit


    /* UART1 STATUS AND CONTROL REGISTER */
    U1STAbits.UTXISEL0 = 0; //bit 15,13 UTXISEL<1:0>: Transmission Interrupt Mode Selection bits
    U1STAbits.URXISEL1 = 0;
    //11 = Reserved; do not use
    //10 = Interrupt when a character is transferred to the Transmit Shift Register, and as a result, the transmit buffer becomes empty
    //01 = Interrupt when the last character is shifted out of the Transmit Shift Register; all transmit operations are completed
    //00 = Interrupt when a character is transferred to the Transmit Shift Register (this implies there is at least one character open in the transmit buffer)
    U1STAbits.UTXINV = 1; //bit 14 UTXINV: Transmit Polarity Inversion bit
    //If IREN = 0:
    // 1 = UxTX Idle state is ?0?
    // 0 = UxTX Idle state is ?1?
    //If IREN = 1:
    // 1 = IrDA encoded UxTX Idle state is ?1?
    // 0 = IrDA encoded UxTX Idle state is ?0?
    U1STAbits.UTXEN = 0; //bit 10 UTXEN: Transmit Enable bit
    //1 = Transmit enabled, UxTX pin controlled by UARTx
    //0 = Transmit disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled by port.
    U1STAbits.URXISEL = 0b00; //bit 7-6 URXISEL<1:0>: Receive Interrupt Mode Selection bits
    //11 = Interrupt is set on UxRSR transfer making the receive buffer full (i.e., has 4 data characters)
    //10 = Interrupt is set on UxRSR transfer making the receive buffer 3/4 full (i.e., has 3 data characters)
    //0x = Interrupt is set when any character is received and transferred from the UxRSR to the receive buffer. Receive buffer has one or more characters.
    U1STAbits.ADDEN = 0; //bit 5 ADDEN: Address Character Detect bit (bit 8 of received data = 1)
    //1 = Address Detect mode enabled. If 9-bit mode is not selected, this does not take effect.
    //0 = Address Detect mode disabled


    U1BRG = 455; // 455  --->  Baud = 9600   Fcy = 70 Mhz
    // U1MODEbits.UARTEN = 0 ;       // LATER ... Enable UART1
    // U1STAbits.UTXEN = 1  ;        // Enable TX pin  ( only after UARTEN = 1)

    return;
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
        *datain = WriteSpi_8b(*dataout);   // Read out data
        length--;
	dataout++;
        datain++;
    }
}



/*******************************************************************************/
/*******************************************************************************/
/**                                */
/**                         */
/**                                  */
/**                               */
/**                                */
/*******************************************************************************/
/*******************************************************************************/
void InitPwm1(void) {
    // PTCON Register Settings
    PTCONbits.PTEN = 0; // PWM module is disabled
    PTCONbits.PTSIDL = 0; // PWM time base runs in CPU Idle mode
    PTCONbits.SEIEN = 0; // Special Event Interrupt is disabled
    PTCONbits.SYNCOEN = 0; // SYNCO output is disabled
    PTCONbits.SYNCEN = 0; // External synchronization of primary time base is disabled

    // PTCON2 Register Settings
    PTCON2bits.PCLKDIV = 0b001; // Divide by 4

    // PWMCON1 Register Settings
    PWMCON1bits.MDCS = 1; // MDC register provides duty cycle information for this PWM generator
    PWMCON1bits.MTBS = 0; // PWM generator uses the primary master time base for synchronization and the clock source for the PWM generation logic
    PWMCON1bits.CAM = 0; // Edge-Aligned mode is enabled
    PWMCON1bits.XPRES = 0; // External pins do not affect PWM time base
    PWMCON1bits.IUE = 0; // Updates to the active MDC/PDCx/SDCx/DTRx/ALTDTRx/PHASEx/SPHASEx registers are immediate
    PWMCON2 = PWMCON3 = 0x0000;

    // IOCON1 Register Settings
    IOCON1bits.PENH = 1; // PWM module controls PWMxH pin
    IOCON1bits.PENL = 0; // GPIO module controls PWMxL pin
    IOCON1bits.POLH = 0; // PWMxH pin is active-high
    IOCON1bits.PMOD = 0b00; // PWM I/O pin pair is in Complementary Output mode
    IOCON2 = IOCON3 = 0x0000;

    // FCLCON Register Settings
    FCLCON1 = FCLCON2 = FCLCON3 = 0x0003; // Fault input is disabled

    // Primary Master Time Base Period Register
    PTPER = 2048;

    // PWM Master Duty Cycle Register
    MDC = 512;

}

void InitTmr3(void) {
   TMR3 = 0x0000;
   PR3 = SAMPPRD;
   T3CONbits.TCKPS = 0b00;
}