/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#include <xc.h>
#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
     //////////////////////////////////////////////////
    ////        PORTS
    ////
    ////   Analog pins : both ANSEL + Tristate must be set !!!!!
    ////
    ////
    //////////////////////////////////////////////////

    PORTA = 0x0000 ;
                        //   RA0 : OpAmp MUST be declared as INPUT sigh sigh sigh
    TRISA = 0x0000 ;    //    RA0 :  digital OUT
                        //    RA1 :  digital OUT
                        //    RA2 :  OSC_IN
                        //    RA3 :  OSC_OUT
                        //    RA4 :  digital OUT
                        //             ana_out Vref20  MUST BE declared as INPUT
                        //                  sigh sigh sigh ...

    ANSELA =0x0000 ;     //  All digital

    PORTB = 0x0020 ;     //  RB0 :  digital OUT
                         //  RB1 :  digital OUT
                         //  RB2 :  digital OUT
                         //  RB3 :  digital OUT

                         //  RB4 :  digital OUT
                         //  RB5 :  uart_rx
                         //  RB6 :  debug/program PGEC2
                         //  RB7 :  

                         //  RB8 :  UART_TX
                         //  RB9 :  digital OUT
                         //  RB10 : PWM3_H out
                         //  RB11 : PWM3_L out

                         //  RB12 : PWM2_H out
                         //  RB13 : PWM2_L out
                         //  RB14 : PWM_1_H out    Pin_25
                         //  RB15 : PWM_1_L out    Pin_26


    TRISB = 0x0020 ;      //   all pins are output   except
                          //   RB5 = RX UART (input)

    PORTBbits.RB6 = 1;      // TX when not controlled by UART : high !!!
    ANSELB = 0x0000  ;      // All digital

}

void initUART(void)
{

    RPINR18bits.U1RXR = 0b0100101  ;   // Select Pin14 (= RP37) to RUART1
    RPOR2bits.RP38R =    0b000001  ;   // Select Pin15 (=RP38) to TXUART1

    //////////////////////////////////////////////////
    /////
    ////        UART
    ////
    ////://////////////////////////////////////////////

    U1MODEbits.UARTEN = 0;          //bit 15 UARTEN: UARTx Enable bit
                                        //1 = UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>
                                        //0 = UARTx is disabled; all UARTx pins are controlled by PORT latches; UARTx power consumption minimal
                                    //bit 14 Unimplemented: Read as ?0?
    U1MODEbits.USIDL = 0;           //bit 13 USIDL: Stop in Idle Mode bit
                                        //1 = Discontinue module operation when device enters Idle mode
                                        //0 = Continue module operation in Idle mode
    U1MODEbits.IREN = 0;            //bit 12 IREN: IrDA® Encoder and Decoder Enable bit
                                        //1 = IrDA encoder and decoder enabled
                                        //0 = IrDA encoder and decoder disabled
    //U1MODEbits.RTSMD = 0;         //bit 11 RTSMD: Mode Selection for UxRTS Pin bit
                                        //1 =UxRTS pin in Simplex mode
                                        //0 =UxRTS pin in Flow Control mode
                                    //bit 10 Unimplemented: Read as ?0?
    U1MODEbits.UEN = 0b00;          //bit 9-8 UEN<1:0>: UARTx Pin Enable bits
                                        //11 = UxTX, UxRX and BCLKx pins are enabled and used; UxCTS pin controlled by PORT latches
                                        //10 = UxTX, UxRX, UxCTS and UxRTS pins are enabled and used
                                        //01 = UxTX, UxRX and UxRTS pins are enabled and used; UxCTS pin controlled by PORT latches
                                        //00 = UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/BCLKx pins controlled by PORT latches
    //U1MODEbits.WAKE = 0;            //bit 7 WAKE: Wake-up on Start bit Detect During Sleep Mode Enable bit
                                        //1 = UARTx continues to sample the UxRX pin; interrupt generated on falling edge; bit cleared in hardware on following rising edge
                                        //0 = No wake-up enabled
    U1MODEbits.LPBACK = 0;          //bit 6 LPBACK: UARTx Loopback Mode Select bit
                                        //1 = Enable Loopback mode
                                        //0 = Loopback mode is disabled
    U1MODEbits.ABAUD = 0;           //bit 5 ABAUD: Auto-Baud Enable bit
                                        //1 = Enable baud rate measurement on the next character ? requires reception of a Sync field before other data; cleared in hardware upon completion
                                        //0 = Baud rate measurement disabled or completed
    U1MODEbits.URXINV = 0;          //bit 4 URXINV: Receive Polarity Inversion bit
                                        //1 = UxRX Idle state is ?0?
                                        //0 = UxRX Idle state is ?1?
    U1MODEbits.BRGH = 0;            //bit 3 BRGH: High Baud Rate Enable bit
                                        //1 = BRG generates 4 clocks per bit period (4x baud clock, High-Speed mode)
                                        //0 = BRG generates 16 clocks per bit period (16x baud clock, Standard mode)
    U1MODEbits.PDSEL = 0b00;        //bit 2-1 PDSEL<1:0>: Parity and Data Selection bits
                                        //11 = 9-bit data, no parity
                                        //10 = 8-bit data, odd parity
                                        //01 = 8-bit data, even parity
                                        //00 = 8-bit data, no parity
    U1MODEbits.STSEL = 0;           //bit 0 STSEL: Stop Bit Selection bit
                                        //1 = Two Stop bits
                                        //0 = One Stop bit


    U1STAbits.UTXISEL0 = 0;
    U1STAbits.URXISEL1 = 0;         //bit 15,13 UTXISEL<1:0>: Transmission Interrupt Mode Selection bits
                                        //11 = Reserved; do not use
                                        //10 = Interrupt when a character is transferred to the Transmit Shift Register, and as a result, the
                                        //transmit buffer becomes empty
                                        //01 = Interrupt when the last character is shifted out of the Transmit Shift Register; all transmit
                                        //operations are completed
                                        //00 = Interrupt when a character is transferred to the Transmit Shift Register (this implies there is
                                        // at least one character open in the transmit buffer)
    U1STAbits.UTXINV = 0;           //bit 14 UTXINV: Transmit Polarity Inversion bit
                                        //If IREN = 0:
                                        //1 = UxTX Idle state is ?0?
                                        //0 = UxTX Idle state is ?1?
                                        //If IREN = 1:
                                        //1 = IrDA encoded UxTX Idle state is ?1?
                                        //0 = IrDA encoded UxTX Idle state is ?0?
                                    //bit 12 Unimplemented: Read as ?0?
   //U1STAbits.UTXBRK = 0;          //bit 11 UTXBRK: Transmit Break bit
                                        //1 = Send Sync Break on next transmission ? Start bit, followed by twelve ?0? bits, followed by Stop bit;
                                        //cleared by hardware upon completion
                                        //0 = Sync Break transmission disabled or completed
   U1STAbits.UTXEN = 0;             //bit 10 UTXEN: Transmit Enable bit
                                        //1 = Transmit enabled, UxTX pin controlled by UARTx
                                        //0 = Transmit disabled, any pending transmission is aborted and buffer is reset. UxTX pin controlled by port.
                                    //bit 9 UTXBF: Transmit Buffer Full Status bit (read-only)
                                        //1 = Transmit buffer is full
                                        //0 = Transmit buffer is not full, at least one more character can be written
                                    //bit 8 TRMT: Transmit Shift Register Empty bit (read-only)
                                        //1 = Transmit Shift Register is empty and transmit buffer is empty (the last transmission has completed)
                                        //0 = Transmit Shift Register is not empty, a transmission is in progress or queued
     U1STAbits.URXISEL = 0b00;      //bit 7-6 URXISEL<1:0>: Receive Interrupt Mode Selection bits
                                        //11 = Interrupt is set on UxRSR transfer making the receive buffer full (i.e., has 4 data characters)
                                        //10 = Interrupt is set on UxRSR transfer making the receive buffer 3/4 full (i.e., has 3 data characters)
                                        //0x = Interrupt is set when any character is received and transferred from the UxRSR to the receive
                                        //buffer. Receive buffer has one or more characters.
  U1STAbits.ADDEN = 0;              //    bit 5 ADDEN: Address Character Detect bit (bit 8 of received data = 1)
                                        //1 = Address Detect mode enabled. If 9-bit mode is not selected, this does not take effect.
                                        //0 = Address Detect mode disabled
                                    //bit 4 RIDLE: Receiver Idle bit (read-only)
                                        //1 = Receiver is Idle
                                        //0 = Receiver is active
                                    //bit 3 PERR: Parity Error Status bit (read-only)
                                        //1 = Parity error has been detected for the current character (character at the top of the receive FIFO)
                                        //0 = Parity error has not been detected
                                    //bit 2 FERR: Framing Error Status bit (read-only)
                                        //1 = Framing error has been detected for the current character (character at the top of the receive FIFO)
                                        //0 = Framing error has not been detected
                                    //bit 1 OERR: Receive Buffer Overrun Error Status bit (read/clear only)
                                        //1 = Receive buffer has overflowed
                                        //0 = Receive buffer has not overflowed. Clearing a previously set OERR bit (1 ?0 transition) resets the receiver buffer and the UxRSR to the empty state.
                                    //bit 0 URXDA: Receive Buffer Data Available bit (read-only)
                                        //1 = Receive buffer has data, at least one more character can be read
                                        //0 = Receive buffer is empty


   

    U1BRG = 455  ;                // 455  --->  Baud = 9600   Fcy = 70 Mhz
    //  U1MODEbits.UARTEN = 0 ;       //  LATER ... Enable UART1

    //
    // U1STAbits.UTXEN = 1  ;        // Enable TX pin  ( only after UARTEN = 1)
    //

    return ;
}
    //////////////////////////////////////////////////
    /////
    ////        PWM     Master Time Base  Used for SYNC ???
    ////
    //////////////////////////////////////////////////

//    PTCON = 0x0000 ;                  // Clear all bits
//    PTCON2bits.PCLKDIV = 0b010 ;      // Divide Fosc / 4
//
//
//    RGB_PERIOD  = 0x8000 ;                 // 40 kHz  (Clock = 150 Mhz)
//    RED_DUTY = RGB_PERIOD /64 ;
//    GREEN_DUTY = RGB_PERIOD /128 ;
//    BLUE_DUTY = RGB_PERIOD /256 ;
//
//    PTPER = RGB_PERIOD ;
//
//    PHASE1 = RGB_PERIOD ;                // Phase Register ( = period )
//    PDC1   = RED_DUTY ;                // Duty Cycle Register
//
//    PHASE2 = RGB_PERIOD ;                // Phase Register ( = period )
//    PDC2   = GREEN_DUTY ;                // Duty Cycle Register
//
//    PHASE3 = RGB_PERIOD ;                // Phase Register ( = period )
//    PDC3   = BLUE_DUTY ;                // Duty Cycle Register


    //////////////////////////////////////////////////
    /////
    ////        PWM 1    Using Local Time Base and Local Duty Cycle
    ////
    //////////////////////////////////////////////////

//    PWMCON1 = 0x0000 ;                // Clear all bits
//    PWMCON1bits.FLTIEN = 0 ;          // Disable FAULT interrupts
//    PWMCON1bits.CLIEN = 0 ;           // Disable CURRENT LIMIT interrupts
//    PWMCON1bits.TRGIEN = 0 ;          // Trigger will not generate interrupt
//    PWMCON1bits.ITB = 1 ;             // Local Phase defines Period of PWM
//    PWMCON1bits.MDCS = 0 ;            // Local Duty Cycle
//    PWMCON1bits.DTC = 0b10   ;       // disabled USING dead time
//    PWMCON1bits.DTCP = 0  ;          // H is shorter, L is longer
//    PWMCON1bits.MTBS = 0 ;           // n.u.
//    PWMCON1bits.CAM = 1 ;            // CENTER aligned
//    PWMCON1bits.XPRES = 0 ;         // no external inputs
//    PWMCON1bits.IUE = 0 ;           // update at end of cycle
//
//    IOCON1bits.PENH= 1 ;            // PWM1H Output ownership bit
//    IOCON1bits.PENL = 0 ;           // GPIO controls PWM1L
//    IOCON1bits.POLH = 0 ;           // Active high polarity for PWM1H
//    IOCON1bits.POLL = 0 ;           // Active low polarity for PWM1L
//    IOCON1bits.PMOD = 0b00  ;       // Pin pair is Complementary
//    IOCON1bits.OVRENH = 0 ;         // PWM controls PWM_H
//    IOCON1bits.OVRENL = 0 ;         // PWM controls PWM_L
//    IOCON1bits.OVRDAT1 = 0 ;        // When override : PWM_H = 0
//    IOCON1bits.OVRDAT0 = 1 ;        // When override : PWM_L = 1
//    IOCON1bits.OSYNC = 1 ;          // Output overrides are sync with time base

//    FCLCON1 = 0x0000 ;
//    FCLCON1bits.FLTMOD = 0b11 ;     // Disable Fault input pins


    //////////////////////////////////////////////////
    /////
    ////        PWM 2    Using Local Time Base and Local Duty Cycle
    ////
    //////////////////////////////////////////////////

//    PWMCON2 = 0x0000 ;                // Clear all bits
//    PWMCON2bits.FLTIEN = 0 ;          // Disable FAULT interrupts
//    PWMCON2bits.CLIEN = 0 ;           // Disable CURRENT LIMIT interrupts
//    PWMCON2bits.TRGIEN = 0 ;          // Trigger will not generate interrupt
//    PWMCON2bits.ITB = 1 ;             // Local Phase defines Period of PWM
//    PWMCON2bits.MDCS = 0 ;            // Local Duty Cycle
//    PWMCON2bits.DTC = 0b10   ;       // disabled USING dead time
//    PWMCON2bits.DTCP = 0  ;          // H is shorter, L is longer
//    PWMCON2bits.MTBS = 0 ;           // n.u.
//    PWMCON2bits.CAM = 1 ;            // CENTER aligned
//    PWMCON2bits.XPRES = 0 ;         // no external inputs
//    PWMCON2bits.IUE = 0 ;           // update at end of cycle
//
//    IOCON2bits.PENH= 1 ;            // PWM1H Output ownership bit
//    IOCON2bits.PENL = 0 ;           // GPIO controls PWM1L
//    IOCON2bits.POLH = 0 ;           // Active high polarity for PWM1H
//    IOCON2bits.POLL = 0 ;           // Active low polarity for PWM1L
//    IOCON2bits.PMOD = 0b00  ;       // Pin pair is Complementary
//    IOCON2bits.OVRENH = 0 ;         // PWM controls PWM_H
//    IOCON2bits.OVRENL = 0 ;         // PWM controls PWM_L
//    IOCON2bits.OVRDAT1 = 0 ;        // When override : PWM_H = 0
//    IOCON2bits.OVRDAT0 = 1 ;        // When override : PWM_L = 1
//    IOCON2bits.OSYNC = 1 ;          // Output overrides are sync with time base
//
//    FCLCON2 = 0x0000 ;
//    FCLCON2bits.FLTMOD = 0b11 ;     // Disable Fault input pins


    //////////////////////////////////////////////////
    /////
    ////        PWM 3    Using Local Time Base and Local Duty Cycle
    ////
    //////////////////////////////////////////////////

//    PWMCON3 = 0x0000 ;                // Clear all bits
//    PWMCON3bits.FLTIEN = 0 ;          // Disable FAULT interrupts
//    PWMCON3bits.CLIEN = 0 ;           // Disable CURRENT LIMIT interrupts
//    PWMCON3bits.TRGIEN = 0 ;          // Trigger will not generate interrupt
//    PWMCON3bits.ITB = 1 ;             // Local Phase defines Period of PWM
//    PWMCON3bits.MDCS = 0 ;            // Local Duty Cycle
//    PWMCON3bits.DTC = 0b10   ;       // disabled USING dead time
//    PWMCON3bits.DTCP = 0  ;          // H is shorter, L is longer
//    PWMCON3bits.MTBS = 0 ;           // n.u.
//    PWMCON3bits.CAM = 1 ;            // CENTER aligned
//    PWMCON3bits.XPRES = 0 ;         // no external inputs
//    PWMCON3bits.IUE = 0 ;           // update at end of cycle
//
//    IOCON3bits.PENH= 1 ;            // PWM1H Output ownership bit
//    IOCON3bits.PENL = 0 ;           // GPIO controls PWM1L
//    IOCON3bits.POLH = 0 ;           // Active high polarity for PWM1H
//    IOCON3bits.POLL = 0 ;           // Active low polarity for PWM1L
//    IOCON3bits.PMOD = 0b00  ;       // Pin pair is Complementary
//    IOCON3bits.OVRENH = 0 ;         // PWM controls PWM_H
//    IOCON3bits.OVRENL = 0 ;         // PWM controls PWM_L
//    IOCON3bits.OVRDAT1 = 0 ;        // When override : PWM_H = 0
//    IOCON3bits.OVRDAT0 = 1 ;        // When override : PWM_L = 1
//    IOCON3bits.OSYNC = 1 ;          // Output overrides are sync with time base
//
//    FCLCON3 = 0x0000 ;
//    FCLCON3bits.FLTMOD = 0b11 ;     // Disable Fault input pins

    //////////////////////////////////////////////////
    /////
    ////        UART   ---->   handled by DMA !!!!
    ////
    //////////////////////////////////////////////////

//    U1MODEbits.UEN = 0b00   ;     // RX pin , TX pin used.  Others = I/O
//    U1MODEbits.BRGH = 1  ;        // High Speed Mode
//    U1MODEbits.PDSEL = 0b00 ;     // 8,N,2
//    U1MODEbits.STSEL = 1   ;      //  2 stop bits
//
//                                 // next interrupt activities will be handled by DMA
//
//    IPC2bits.U1RXIP = 2 ;           // Higher priority for RX
//    IPC3bits.U1TXIP = 2 ;           // Low priority for TX
//    IPC16bits.U1EIP = 6 ;           // High Priority for TX RX  Errors
//
//    IFS0bits.U1TXIF = 0 ;           // Clear any pending flag
//    IFS0bits.U1RXIF = 0 ;
//    IFS4bits.U1EIF = 0 ;
//
//    U1STAbits.UTXISEL1= 0 ;      // Interrupt when TX buffer has spare location
//    U1STAbits.UTXISEL0= 0 ;      //  Fastest one ...
//
//    U1STAbits.URXISEL= 0b00 ;      // Interrupt when character received
//
//                                   // Disable Interrupt on UART  ---> DMA mode
//    IEC0bits.U1TXIE = 0 ;          // do NOT yet generate TX interrupt ...
//    IEC0bits.U1RXIE = 0 ;          // do NOT yet generate RX interrupt ...
//    IEC4bits.U1EIE = 1 ;           // Enable Error interrupts
//
//    U1BRG = 80  ;                 //  39  ----> Baud = 460800   Fcy = 75 Mhz
//                                  //  80 --->  Baud = 230400    Fcy = 75 Mhz
//                                  // 162  --->  Baud = 115200    Fcy = 75 Mhz
//                                  // 325  --->  Baud = 57600    Fcy = 75 Mhz
//    U1MODEbits.UARTEN = 1 ;       //  Enable UART1
//
//
//    U1STAbits.UTXEN = 1  ;        // Enable TX pin  ( only after UARTEN = 1)
                                    // Enable TX circuitry  (will also set U1TXIF .... !!!! )
                                    // wait at least one baud before sending first character
//    for (i=0; i<40000; i++)
//       {
//          Nop() ;
//       }


    //////////////////////////////////////////////////
    ////
    /////      Timer 1 ---> used
    ////
    //////////////////////////////////////////////////

//    PR1 = 0x03AA ;              // Count value for TMR1    12.5 uSec
//                                // 75 Mhz clock --->   937.5 --> 0x03AA
//    T1CON = 0x0000  ;           // Reset all bits
//    T1CONbits.TCKPS = 0b00 ;     // Prescaler 1/1
//    T1CONbits.TCS = 0 ;         // Internal Fp  clock  75MHz
//    T1CONbits.TGATE = 0 ;          // IF on Equal  (not gated Timer1)
//    T1CONbits.TON = 1  ;          // Start Timer 1
//




//void DMA_UART_RX(void)          // DMA Channel_0
//{
//    DMA0CONbits.CHEN = 0 ;
//    UART_mode = 0  ;              // DMA in RX mode of UART
//    IFS0bits.U1RXIF = 0 ;        // Clear pending UART RX interrupts
//    IFS0bits.U1TXIF = 0 ;        // Clear pending UART TX interrupts
//    SRbits.IPL = 0b001  ;           // Set CPU at Level = 1
//
//    RX_full_flag = 0 ;
//    TX_empty_flag = 0 ;
//
//    DMA0CON = 0x4001 ;            // Byte transfert, READ peripheral, Full Block
//                                 // Register Post Increment, continous no PingPong
//    DMA0REQ = 0x000B ;          // UART1 RX
//
//    DMA0STAL = (volatile unsigned int) &RX_DATA  ;
//    DMA0STAH = 0x0000  ;
//    DMA0PAD = (volatile unsigned int)&U1RXREG;
//    DMA0CNT = 0x003F    ;         // Block = 63 + 1 = 64 Bytes
//    IFS0bits.DMA0IF = 0;        // Clear DMA interrupt
//    IEC0bits.DMA0IE = 1;        // Enable DMA interrupt
//    IPC1bits.DMA0IP = 2 ;       // DMA Priority
//    DMA0CONbits.CHEN = 1 ;
//
//    return ;
//}
//
//
//void DMA_UART_TX(void)          // DMA Channel_0  for 64 Bytes
//{
//    DMA0CONbits.CHEN = 0 ;
//    UART_mode = 1  ;              // DMA in TX mode of UART
//    IFS0bits.U1RXIF = 0 ;        // Clear pending UART RX interrupts
//    IFS0bits.U1TXIF = 0 ;        // Clear pending UART TX interrupts
//    SRbits.IPL = 0b001  ;           // Set CPU at Level = 1
//
//    RX_full_flag = 0 ;
//    TX_empty_flag = 0 ;
//
//    DMA0CON = 0x6001 ;            // Byte transfert, WRITE peripheral, Full Block
//                                 // Register Post Increment, OneShot no PingPong
//    DMA0REQ = 0x000C ;          // UART1 TX    with FORCE BIT
//
//    DMA0STAL = (volatile unsigned int) &TX_DATA ;
//    DMA0STAH = 0x0000 ;
//    DMA0PAD =  (volatile unsigned int) &U1TXREG;
//    DMA0CNT = 0x003F    ;         // Block = 63 + 1 = 64 Bytes
//    IFS0bits.DMA0IF = 0;        // Clear DMA interrupt
//    IPC1bits.DMA0IP = 5 ;       // DMA Priority
//    IEC0bits.DMA0IE = 1;        // Enable DMA interrupt
//    DMA0CONbits.CHEN = 1 ;
//    DMA0REQbits.FORCE = 1 ;
//
//    return ;
//}
//
//void DMA_UART_TX2(void)          // DMA Channel_0  for 128 Bytes
//{
//    DMA0CONbits.CHEN = 0 ;
//    UART_mode = 1  ;              // DMA in TX mode of UART
//    IFS0bits.U1RXIF = 0 ;        // Clear pending UART RX interrupts
//    IFS0bits.U1TXIF = 0 ;        // Clear pending UART TX interrupts
//    SRbits.IPL = 0b001  ;           // Set CPU at Level = 1
//
//    RX_full_flag = 0 ;
//    TX_empty_flag = 0 ;
//
//    DMA0CON = 0x6001 ;            // Byte transfert, WRITE peripheral, Full Block
//                                 // Register Post Increment, OneShot no PingPong
//    DMA0REQ = 0x000C ;          // UART1 TX    with FORCE BIT
//
//    DMA0STAL = (volatile unsigned int) &TX_DATA ;
//    DMA0STAH = 0x0000 ;
//    DMA0PAD =  (volatile unsigned int) &U1TXREG;
//    DMA0CNT = 0x007F    ;         // Block = 127 + 1 = 128 Bytes
//    IFS0bits.DMA0IF = 0;        // Clear DMA interrupt
//    IEC0bits.DMA0IE = 1;        // Enable DMA interrupt
//    IPC1bits.DMA0IP = 5 ;       // DMA Priority
//    DMA0CONbits.CHEN = 1 ;
//    DMA0REQbits.FORCE = 1 ;
//
//    return ;
//}
//
//
//void DMA_CAPTURE(void)           // DMA Channel_1
//{
//    unsigned int dummy ;
//    IC1CON2bits.TRIGSTAT = 0 ;      // STOP Capture Timer
//    IFS0bits.IC1IF = 0  ;           // Clear pending IC1 interrupt flag
//    IEC0bits.IC1IE = 0  ;           // Disable IC1 interrupts for CPU
//                                    //  DMA treated interrupts
//    IPC0bits.IC1IP = 2  ;           // Set IC priority to 2
//
//    SRbits.IPL = 0b001  ;           // Set CPU at Level = 1
//
//    DMA1CON = 0x0000 ;              // Clear all
//    DMA1CONbits.SIZE = 0 ;      // Word transfert
//    DMA1CONbits.DIR = 0 ;       // READ from IC
//    DMA1CONbits.AMODE = 0b00 ;   // Register Indirect Post_Increment
//    DMA1CONbits.MODE = 0b01 ;    // One Shot, no Pingpong
//
//    DMA1REQ = 0x0001 ;          // IC1 = Input Capture 1
//
//    DMA1STAL = (volatile unsigned int) &IC_DATA ;   // Store into 64 word register
//    DMA1STAH = 0x0000 ;
//    DMA1PAD =  (volatile unsigned int) &IC1BUF ;    // IC Capture Register
//    //DMA1CNT = 0x003F    ;         // Block = 63 + 1 = 64 Captured Words
//    DMA1CNT = 0x001F    ;         // Block = 31 + 1 = 32 Captured Words
//                                  // 16 High + 16 Low freqs
//
//    IFS0bits.DMA1IF = 0;        // Clear DMA interrupt
//    IEC0bits.DMA1IE = 1;        // Enable DMA interrupt
//    IPC3bits.DMA1IP = 0b010 ;       // DMA Priority
//
//    while (PORTBbits.RB13 == 0)     // Wait for F_LOW --> F_HIGH trigger
//                                    // RB13 = 1
//    {
//        Nop();
//    }
//
//    while (IC1CON1bits.ICBNE == 1)
//    {
//        dummy = IC1BUF ;          // Empty FIFO
//    }
//
//    IC1CON2bits.TRIGSTAT = 1 ;      // Start Capture Timer
//    DMA1CONbits.CHEN = 1 ;
//
//     return ;
//}
//
//void CAPTURE_TX(void)   // Transfert Capture Words into TX Bytes
//{
//    unsigned int i ;
//    unsigned long TEMP ;
//       for(i=0;i<63;i++)
//        {
//            if(IC_DATA[i]<IC_DATA[i+1])
//                IC_DATA[i] = IC_DATA[i+1]-IC_DATA[i];
//            else
//                {
//                TEMP = IC_DATA[i+1]+65535 - IC_DATA[i] ;
//                IC_DATA[i] = TEMP %65536 ;
//                }
//
//              TX_DATA[2*i] = IC_DATA[i]/256;
//              TX_DATA[(2*i)+1] = IC_DATA[i]%256;
//          }
//
//        TX_DATA[0] = RX_DATA[0];     // check for correct UART loop
//        TX_DATA[1] = RX_DATA[1];     // echo back first value
//
//        TX_DATA[126] = TX_DATA[124] ;   // duplicate last value
//        TX_DATA[127] = TX_DATA[125] ;
//
//         return ;
//}
//
//void DISPLAY_REGS_A(void)
//{
//        unsigned int dummy ;
//
//         TX_DATA[0]= (char)  0xAA ;                     // Start word
//         TX_DATA[1]= (char)  0xAA;
//
//         TX_DATA[2]= (char)  0xCC ;                     // Command REGS_A
//         TX_DATA[3]= (char)  0x0A ;
//
////         dummy = SR ;
////         dummy = dummy >> 8 ;
////         TX_DATA[4]= (char) dummy  & 0x00FF ;
////         TX_DATA[5]= (char) SR     & 0x00FF ;
//
//
//         TX_DATA[4]= RX_DATA[4] ;
//         TX_DATA[5]= RX_DATA[5] ;
//
//
//         dummy = CORCON ;
//         dummy = dummy >> 8 ;
//         TX_DATA[6]= (char) dummy      & 0x00FF ;
//         TX_DATA[7]= (char) CORCON     & 0x00FF ;
//
//         dummy = IFS0 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[8]= (char) dummy    & 0x00FF ;
//         TX_DATA[9]= (char) IFS0     & 0x00FF ;
//
//         dummy = IFS1 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[10]= (char) dummy    & 0x00FF ;
//         TX_DATA[11]= (char) IFS1     & 0x00FF ;
//
//         dummy = IFS2 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[12]= (char) dummy    & 0x00FF ;
//         TX_DATA[13]= (char) IFS2     & 0x00FF ;
//
//         dummy = IFS3 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[14]= (char) dummy    & 0x00FF ;
//         TX_DATA[15]= (char) IFS3     & 0x00FF ;
//
//         dummy = IFS4 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[16]= (char) dummy    & 0x00FF ;
//         TX_DATA[17]= (char) IFS4     & 0x00FF ;
//
//         dummy = IEC0 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[18]= (char) dummy    & 0x00FF ;
//         TX_DATA[19]= (char) IEC0     & 0x00FF ;
//
//         dummy = IEC1 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[20]= (char) dummy    & 0x00FF ;
//         TX_DATA[21]= (char) IEC1     & 0x00FF ;
//
//         dummy = IEC2 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[22]= (char) dummy    & 0x00FF ;
//         TX_DATA[23]= (char) IEC2     & 0x00FF ;
//
//         dummy = IEC3 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[24]= (char) dummy    & 0x00FF ;
//         TX_DATA[25]= (char) IEC3     & 0x00FF ;
//
//         dummy = IEC4 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[26]= (char) dummy    & 0x00FF ;
//         TX_DATA[27]= (char) IEC4     & 0x00FF ;
//
//         dummy = IPC0 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[28]= (char) dummy    & 0x00FF ;
//         TX_DATA[29]= (char) IPC0     & 0x00FF ;
//
//         dummy = IPC1 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[30]= (char) dummy    & 0x00FF ;
//         TX_DATA[31]= (char) IPC1     & 0x00FF ;
//
//         //
//
//         dummy = IPC2 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[32]= (char) dummy    & 0x00FF ;
//         TX_DATA[33]= (char) IPC2     & 0x00FF ;
//
//         dummy = IPC3 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[34]= (char) dummy    & 0x00FF ;
//         TX_DATA[35]= (char) IPC3     & 0x00FF ;
//
//         dummy = IPC4 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[36]= (char) dummy    & 0x00FF ;
//         TX_DATA[37]= (char) IPC4     & 0x00FF ;
//
//         dummy = INTCON1 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[38]= (char) dummy       & 0x00FF ;
//         TX_DATA[39]= (char) INTCON1     & 0x00FF ;
//
//         dummy = INTCON2 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[40]= (char) dummy       & 0x00FF ;
//         TX_DATA[41]= (char) INTCON2     & 0x00FF ;
//
//         dummy = INTCON3 ;
//         dummy = dummy >> 8 ;
//         TX_DATA[42]= (char) dummy       & 0x00FF ;
//         TX_DATA[43]= (char) INTCON3     & 0x00FF ;
//
//         dummy = INTTREG ;
//         dummy = dummy >> 8 ;
//         TX_DATA[44]= (char) dummy       & 0x00FF ;
//         TX_DATA[45]= (char) INTTREG     & 0x00FF ;
//
//         dummy = DMA0CON ;
//         dummy = dummy >> 8 ;
//         TX_DATA[46]= (char) dummy       & 0x00FF ;
//         TX_DATA[47]= (char) DMA0CON     & 0x00FF ;
//
//         dummy = DMA0REQ ;
//         dummy = dummy >> 8 ;
//         TX_DATA[48]= (char) dummy       & 0x00FF ;
//         TX_DATA[49]= (char) DMA0REQ     & 0x00FF ;
//
//         dummy = DMA0STAL ;
//         dummy = dummy >> 8 ;
//         TX_DATA[50]= (char) dummy       & 0x00FF ;
//         TX_DATA[51]= (char) DMA0STAL    & 0x00FF ;
//
//         dummy = DMA0STAH ;
//         dummy = dummy >> 8 ;
//         TX_DATA[52]= (char) dummy       & 0x00FF ;
//         TX_DATA[53]= (char) DMA0STAH    & 0x00FF ;
//
//         dummy = DMA0PAD ;
//         dummy = dummy >> 8 ;
//         TX_DATA[54]= (char) dummy       & 0x00FF ;
//         TX_DATA[55]= (char) DMA0PAD     & 0x00FF ;
//
//         dummy = DMA0CNT ;
//         dummy = dummy >> 8 ;
//         TX_DATA[56]= (char) dummy       & 0x00FF ;
//         TX_DATA[57]= (char) DMA0CNT     & 0x00FF ;
//
//         dummy = U1MODE ;
//         dummy = dummy >> 8 ;
//         TX_DATA[58]= (char) dummy       & 0x00FF ;
//         TX_DATA[59]= (char) U1MODE      & 0x00FF ;
//
//         dummy = U1STA ;
//         dummy = dummy >> 8 ;
//         TX_DATA[60]= (char) dummy       & 0x00FF ;
//         TX_DATA[61]= (char) U1STA       & 0x00FF ;
//
//         TX_DATA[62]= (char) 0x0F ;
//         TX_DATA[63]= (char) 0x0F ;
//
//         return ;
//}