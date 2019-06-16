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

/**
 * U1 for computer interface
 */
void InitUart1(void) {
    /* UART TRIS SELECT */
    TRISBbits.TRISB5 = 1; // RX
    TRISBbits.TRISB6 = 0; // TX
    PORTBbits.RB6 = 1; // TX when not controlled by UART : high !!!

    /* SELELCT OUTPUT PORTS */
    RPINR18bits.U1RXR = 37; // Select Pin14 (= RP37) to RXUART1
    RPOR2bits.RP38R = 1; // Select Pin15 (= RP38) to TXUART1, RP38 tied to UART1 Transmit

        // U2MODE Register settings
    U1MODEbits.UARTEN = 0; // Disable UART
    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-baud disabled


    // Baud rate setting
    U1BRG = 78;

    // U2STA Register settings
    U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U1STAbits.UTXISEL1 = 0;
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received

    // Enabling
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART TX
}

// void putch(uint8_t byte) {
//     U1TXREG = byte;
//     while(U1STAbits.TRMT == 0) {}
// }


 /**
 * U2 for pic interface
 */
void InitUart2(void) {
    /* UART TRIS SELECT */
    TRISBbits.TRISB4 = 1; // RX
    TRISAbits.TRISA4 = 0; // TX

    /* SELELCT OUTPUT PORTS */
    RPINR19bits.U2RXR = 36; // Select Pin11 (= RP36) to RXUART2
    RPOR0bits.RP20R = 0b000011; // Select Pin22 (= RP43) to TXUART2, RP43 tied to UART2 Transmit
    
    // U2MODE Register settings
    U2MODEbits.UARTEN = 0; // Disable UART
    U2MODEbits.STSEL = 0; // 1-stop bit
    U2MODEbits.PDSEL = 0; // No parity, 8-data bits
    U2MODEbits.ABAUD = 0; // Auto-baud disabled


    // Baud rate setting
    U2BRG = 78;

    // U2STA Register settings
    U2STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
    U2STAbits.UTXISEL1 = 0;
    U2STAbits.URXISEL = 0; // Interrupt after one RX character is received

    // Enabling
    U2MODEbits.UARTEN = 1; // Enable UART
    U2STAbits.UTXEN = 1; // Enable UART TX
}

uint8_t U2Buffer[UART_LENGTH];

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

void InitTmr4(void) {
   TMR4 = 0x0000;
   PR4 = (SAMPPRD);
   T4CONbits.TCKPS = 0b00;
}

