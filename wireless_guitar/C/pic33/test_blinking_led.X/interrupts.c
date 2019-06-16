/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#include <xc.h>
#include <p33EP64MC502.h>
#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>       /* Includes true/false definition */
#include "user.h"
/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* Refer to the C30 (MPLAB C Compiler for PIC24F MCUs and dsPIC33F DSCs) User */
/* Guide for an up to date list of the available interrupt options.           */
/* Alternately these names can be pulled from the device linker scripts.      */
/*                                                                            */
/* dsPIC33F Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt      _C1Interrupt                                           */
/* _IC1Interrupt       _DMA3Interrupt                                         */
/* _OC1Interrupt       _IC3Interrupt                                          */
/* _T1Interrupt        _IC4Interrupt                                          */
/* _DMA0Interrupt      _IC5Interrupt                                          */
/* _IC2Interrupt       _IC6Interrupt                                          */
/* _OC2Interrupt       _OC5Interrupt                                          */
/* _T2Interrupt        _OC6Interrupt                                          */
/* _T3Interrupt        _OC7Interrupt                                          */
/* _SPI1ErrInterrupt   _OC8Interrupt                                          */
/* _SPI1Interrupt      _DMA4Interrupt                                         */
/* _U1RXInterrupt      _T6Interrupt                                           */
/* _U1TXInterrupt      _T7Interrupt                                           */
/* _ADC1Interrupt      _SI2C2Interrupt                                        */
/* _DMA1Interrupt      _MI2C2Interrupt                                        */
/* _SI2C1Interrupt     _T8Interrupt                                           */
/* _MI2C1Interrupt     _T9Interrupt                                           */
/* _CNInterrupt        _INT3Interrupt                                         */
/* _INT1Interrupt      _INT4Interrupt                                         */
/* _ADC2Interrupt      _C2RxRdyInterrupt                                      */
/* _DMA2Interrupt      _C2Interrupt                                           */
/* _OC3Interrupt       _DCIErrInterrupt                                       */
/* _OC4Interrupt       _DCIInterrupt                                          */
/* _T4Interrupt        _DMA5Interrupt                                         */
/* _T5Interrupt        _U1ErrInterrupt                                        */
/* _INT2Interrupt      _U2ErrInterrupt                                        */
/* _U2RXInterrupt      _DMA6Interrupt                                         */
/* _U2TXInterrupt      _DMA7Interrupt                                         */
/* _SPI2ErrInterrupt   _C1TxReqInterrupt                                      */
/* _SPI2Interrupt      _C2TxReqInterrupt                                      */
/* _C1RxRdyInterrupt                                                          */
/*                                                                            */
/* dsPIC33E Primary Interrupt Vector Names:                                   */
/*                                                                            */
/* _INT0Interrupt     _IC4Interrupt      _U4TXInterrupt                       */
/* _IC1Interrupt      _IC5Interrupt      _SPI3ErrInterrupt                    */
/* _OC1Interrupt      _IC6Interrupt      _SPI3Interrupt                       */
/* _T1Interrupt       _OC5Interrupt      _OC9Interrupt                        */
/* _DMA0Interrupt     _OC6Interrupt      _IC9Interrupt                        */
/* _IC2Interrupt      _OC7Interrupt      _PWM1Interrupt                       */
/* _OC2Interrupt      _OC8Interrupt      _PWM2Interrupt                       */
/* _T2Interrupt       _PMPInterrupt      _PWM3Interrupt                       */
/* _T3Interrupt       _DMA4Interrupt     _PWM4Interrupt                       */
/* _SPI1ErrInterrupt  _T6Interrupt       _PWM5Interrupt                       */
/* _SPI1Interrupt     _T7Interrupt       _PWM6Interrupt                       */
/* _U1RXInterrupt     _SI2C2Interrupt    _PWM7Interrupt                       */
/* _U1TXInterrupt     _MI2C2Interrupt    _DMA8Interrupt                       */
/* _AD1Interrupt      _T8Interrupt       _DMA9Interrupt                       */
/* _DMA1Interrupt     _T9Interrupt       _DMA10Interrupt                      */
/* _NVMInterrupt      _INT3Interrupt     _DMA11Interrupt                      */
/* _SI2C1Interrupt    _INT4Interrupt     _SPI4ErrInterrupt                    */
/* _MI2C1Interrupt    _C2RxRdyInterrupt  _SPI4Interrupt                       */
/* _CM1Interrupt      _C2Interrupt       _OC10Interrupt                       */
/* _CNInterrupt       _QEI1Interrupt     _IC10Interrupt                       */
/* _INT1Interrupt     _DCIEInterrupt     _OC11Interrupt                       */
/* _AD2Interrupt      _DCIInterrupt      _IC11Interrupt                       */
/* _IC7Interrupt      _DMA5Interrupt     _OC12Interrupt                       */
/* _IC8Interrupt      _RTCCInterrupt     _IC12Interrupt                       */
/* _DMA2Interrupt     _U1ErrInterrupt    _DMA12Interrupt                      */
/* _OC3Interrupt      _U2ErrInterrupt    _DMA13Interrupt                      */
/* _OC4Interrupt      _CRCInterrupt      _DMA14Interrupt                      */
/* _T4Interrupt       _DMA6Interrupt     _OC13Interrupt                       */
/* _T5Interrupt       _DMA7Interrupt     _IC13Interrupt                       */
/* _INT2Interrupt     _C1TxReqInterrupt  _OC14Interrupt                       */
/* _U2RXInterrupt     _C2TxReqInterrupt  _IC14Interrupt                       */
/* _U2TXInterrupt     _QEI2Interrupt     _OC15Interrupt                       */
/* _SPI2ErrInterrupt  _U3ErrInterrupt    _IC15Interrupt                       */
/* _SPI2Interrupt     _U3RXInterrupt     _OC16Interrupt                       */
/* _C1RxRdyInterrupt  _U3TXInterrupt     _IC16Interrupt                       */
/* _C1Interrupt       _USB1Interrupt     _ICDInterrupt                        */
/* _DMA3Interrupt     _U4ErrInterrupt    _PWMSpEventMatchInterrupt            */
/* _IC3Interrupt      _U4RXInterrupt     _PWMSecSpEventMatchInterrupt         */
/*                                                                            */
/* For alternate interrupt vector naming, simply add 'Alt' between the prim.  */
/* interrupt vector name '_' and the first character of the primary interrupt */
/* vector name.  There is no Alternate Vector or 'AIVT' for the 33E family.   */
/*                                                                            */
/* For example, the vector name _ADC2Interrupt becomes _AltADC2Interrupt in   */
/* the alternate vector table.                                                */
/*                                                                            */
/* Example Syntax:                                                            */
/*                                                                            */
/* void __attribute__((interrupt,auto_psv)) <Vector Name>(void)               */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more comprehensive interrupt examples refer to the C30 (MPLAB C        */
/* Compiler for PIC24 MCUs and dsPIC DSCs) User Guide in the                  */
/* <C30 compiler instal directory>/doc directory for the latest compiler      */
/* release.  For XC16, refer to the MPLAB XC16 C Compiler User's Guide in the */
/* <XC16 compiler instal directory>/doc folder.                               */
/*                                                                            */
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/
char ReceivedChar;

/* TODO Add interrupt routine code here. */
    void InintInterrupts(void)
    {
        INTCON1 = 0x0000 ;              // Clear all special pending flags
        INTCON3 = 0x0000 ;
        INTCON4 = 0x0000 ;
        INTCON1bits.NSTDIS = 0 ;        // Enable Interrupt Nesting   MUST !!!!

                                    // Settings for UART1
                                    // ---------------------
    IPC2bits.U1RXIP = 3 ;           // Higher priority for RX
    IPC3bits.U1TXIP = 2 ;           // Low priority for TX

    IFS0 = 0x0000    ;              // Clear ALL Flags
    IFS0bits.U1TXIF = 0 ;
    IFS0bits.U1RXIF = 0 ;

    IEC0bits.U1TXIE = 1 ;          // do generate TX interrupt ...
    IEC0bits.U1RXIE = 1 ;          // do generate RX interrupt ...

//                                    // Settings for UART1 Errors
//                                    // --------------------------------
//   IPC16bits.U1EIP = 6 ;           // high priority for Error Flag
//   IFS4bits.U1EIF = 0 ;           // Clear pending Error flag
//   IEC4bits.U1EIE = 1 ;            //Enable Interrupt Error UART
        return;
    }
    void DisableInterrupts (void)
    {
        SRbits.IPL = 0b111 ;          // Set CPU at Level = 7  (DISABLE ALL INTERRUPTS)
        INTCON2bits.GIE = 0;
        return;
    }
    void EnableInterrupts(void)
    {
    SRbits.IPL = 0b000  ;           // Set CPU at Level = 0
    CORCONbits.IPL3 = 0 ;            // Lower priority
    INTCON2bits.GIE = 1 ;           // GIE = 1
    return;
    }

    void __attribute__((__interrupt__, no_auto_psv)) _U1RXInterrupt(void)
{
            IFS0bits.U1RXIF = 0 ;       // Clear RX Interrupt Flag

            ReceivedChar = U1RXREG ;         // Read data

            //PORTB ^= (1 << 1);
            if (ReceivedChar == 0x01)
            {
                PORTBbits.RB1 = 1;
            }
            if (ReceivedChar == 0x00)
            {
                PORTBbits.RB1 = 0;
            }

            if(U1STAbits.FERR == 1) ;   // Check for Receive Errors
                {
                    U1STAbits.FERR = 0 ;
                 }
                            // Check for Overrun Errors  (after reading out all data)
            if(U1STAbits.OERR == 1)
                {
                    U1STAbits.OERR = 0 ;     // Clear error to keep receiving
                }
}


void __attribute__((__interrupt__, no_auto_psv)) _U1TXInterrupt(void)
{
       IFS0bits.U1TXIF = 0 ;               // Clear Interrupt Flag
        U1TXREG = 0x33;
        //IEC0bits.U1TXIE = 0 ;   // disable another TX interrupt

}