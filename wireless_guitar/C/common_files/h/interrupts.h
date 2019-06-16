/* 
 * File:   interrupts.h
 * Author: wouter
 *
 * Created on 30 januari 2015, 12:44
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#ifdef	__cplusplus
extern "C" {
#endif
    extern void init_interrupts(void);
    extern void interrupt HighISR(void);
    extern void interrupt low_priority LowISR(void);

    
    //***************************************//
    //************* INTCON ******************//
    //***************************************//
#define GIE     INTCONbits.GIE
#define GIEH    INTCONbits.GIEH //: Global Interrupt Enable bit
// When IPEN = 0:
//  1 = Enables all unmasked interrupts
//  0 = Disables all interrupts
// When IPEN = 1:
//  1 = Enables all high priority interrupts
//  0 = Disables all high priority interrupts
#define PEIE    INTCONbits.PEIE
#define GIEL    INTCONbits.GIEL //: Peripheral Interrupt Enable bit
// When IPEN = 0:
//  1 = Enables all unmasked peripheral interrupts
//  0 = Disables all peripheral interrupts
// When IPEN = 1:
// 1 = Enables all low priority peripheral interrupts
// 0 = Disables all low priority peripheral interrupts
#define TMR0IE  INTCONbits.TMR0IE //: TMR0 Overflow Interrupt Enable bit
// 1 = Enables the TMR0 overflow interrupt
// 0 = Disables the TMR0 overflow interrupt
#define INT0IE  INTCONbits.INT0IE //: INT0 External Interrupt Enable bit
// 1 = Enables the INT0 external interrupt
// 0 = Disables the INT0 external interrupt
#define RBIE    INTCONbits.RBIE //: RB Port Change Interrupt Enable bit
// 1 = Enables the RB port change interrupt
// 0 = Disables the RB port change interrupt
#define TMR0IF  INTCONbits.TMR0IF //: TMR0 Overflow Interrupt Flag bit
//1 = TMR0 register has overflowed (must be cleared in software)
//0 = TMR0 register did not overflow
#define INT0IF  INTCONbits.INT0IF //: INT0 External Interrupt Flag bit
// 1 = The INT0 external interrupt occurred (must be cleared in software)
// 0 = The INT0 external interrupt did not occur
#define RBIF    INTCONbits.RBIF //: RB Port Change Interrupt Flag bit (1)
//1 = At least one of the RB7:RB4 pins changed state (must be cleared in software)
//0 = None of the RB7:RB4 pins have changed state


    //***************************************//
    //************* INTCON2 *****************//
    //***************************************//
#define RBPU    INTCON2bits.RBPU //: PORTB Pull-up Enable bit
// 1 = All PORTB pull-ups are disabled
// 0 = PORTB pull-ups are enabled by individual port latch values
#define INTEDG0 INTCON2bits.INTEDG0 //: External Interrupt 0 Edge Select bit
// 1 = Interrupt on rising edge
// 0 = Interrupt on falling edge
#define INTEDG1 INTCON2bits.INTEDG1 //: External Interrupt 1 Edge Select bit
// 1 = Interrupt on rising edge
// 0 = Interrupt on falling edge
#define INTEDG2 INTCON2bits.INTEDG2 //: External Interrupt 2 Edge Select bit
// 1 = Interrupt on rising edge
// 0 = Interrupt on falling edge
#define TMR0IP  INTCON2bits.TMR0IP //: TMR0 Overflow Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define RBIP    INTCON2bits.RBIP //: RB Port Change Interrupt Priority bit
// 1 = High priority
// 0 = Low priority




    //***************************************//
    //************* INTCON3 *****************//
    //***************************************//
#define INT2IP  INTCON3bits.INT2IP //: INT2 External Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define INT1IP  INTCON3bits.INT1IP //: INT1 External Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define INT2IE  INTCON3bits.INT2IE //: INT2 External Interrupt Enable bit
// 1 = Enables the INT2 external interrupt
// 0 = Disables the INT2 external interrupt
#define INT1IE  INTCON3bits.INT1IE //: INT1 External Interrupt Enable bit
// 1 = Enables the INT1 external interrupt
// 0 = Disables the INT1 external interrupt
#define INT2IF  INTCON3bits.INT2IF //: INT2 External Interrupt Flag bit
// 1 = The INT2 external interrupt occurred (must be cleared in software)
// 0 = The INT2 external interrupt did not occur
#define INT1IF  INTCON3bits.INT1IF //: INT1 External Interrupt Flag bit
// 1 = The INT1 external interrupt occurred (must be cleared in software)
// 0 = The INT1 external interrupt did not occur


    //***************************************//
    //************* PIR1 ********************//
    //***************************************//
#define PIR1    PIR1

//#define SSPIF   PIR1bits.SPPIF //: Streaming Parallel Port Read/Write Interrupt Flag bit (1)
// 1 = A read or a write operation has taken place (must be cleared in software)
// 0 = No read or write has occurred
#define ADIF    PIR1bits.ADIF //: A/D Converter Interrupt Flag bit
// 1 = An A/D conversion completed (must be cleared in software)
// 0 = The A/D conversion is not complete
#define RCIF    PIR1bits.RCIF //: EUSART Receive Interrupt Flag bit
// 1 = The EUSART receive buffer, RCREG, is full (cleared when RCREG is read)
// 0 = The EUSART receive buffer is empty
#define TXIF    PIR1bits.TXIF //: EUSART Transmit Interrupt Flag bit
// 1 = The EUSART transmit buffer, TXREG, is empty (cleared when TXREG is written)
// 0 = The EUSART transmit buffer is full
#define SSPIF   PIR1bits.SSPIF //: Master Synchronous Serial Port Interrupt Flag bit
// 1 = The transmission/reception is complete (must be cleared in software)
// 0 = Waiting to transmit/receive
#define CCP1IF  PIR1bits.CCP1IF //: CCP1 Interrupt Flag bit
//Capture mode:
// 1 = A TMR1 register capture occurred (must be cleared in software)
// 0 = No TMR1 register capture occurred
//Compare mode:
// 1 = A TMR1 register compare match occurred (must be cleared in software)
// 0 = No TMR1 register compare match occurred
//PWM mode:
// Unused in this mode.
#define TMR2IF  PIR1bits.TMR2IF //: TMR2 to PR2 Match Interrupt Flag bit
// 1 = TMR2 to PR2 match occurred (must be cleared in software)
// 0 = No TMR2 to PR2 match occurred
#define TMR1IF  PIR1bits.TMR1IF //: TMR1 Overflow Interrupt Flag bit
// 1 = TMR1 register overflowed (must be cleared in software)
// 0 = TMR1 register did not overflow


    //***************************************//
    //************* PIE1 ********************//
    //***************************************//
#define PIE1    PIE1

#define SPPIE   PIE1bits.SPPIE //: Streaming Parallel Port Read/Write Interrupt Enable bit (1)
// 1 = Enables the SPP read/write interrupt
// 0 = Disables the SPP read/write interrupt
#define ADIE    PIE1bits.ADIE //: A/D Converter Interrupt Enable bit
// 1 = Enables the A/D interrupt
// 0 = Disables the A/D interrupt
#define RCIE    PIE1bits.RCIE //: EUSART Receive Interrupt Enable bit
// 1 = Enables the EUSART receive interrupt
// 0 = Disables the EUSART receive interrupt
#define TXIE    PIE1bits.TXIE //: EUSART Transmit Interrupt Enable bit
// 1 = Enables the EUSART transmit interrupt
// 0 = Disables the EUSART transmit interrupt
#define SSPIE   PIE1bits.SSPIE //: Master Synchronous Serial Port Interrupt Enable bit
// 1 = Enables the MSSP interrupt
// 0 = Disables the MSSP interrupt
#define CCP1IE  PIE1bits.CCP1IE //: CCP1 Interrupt Enable bit
// 1 = Enables the CCP1 interrupt
// 0 = Disables the CCP1 interrupt
#define TMR2IE  PIE1bits.TMR2IE //: TMR2 to PR2 Match Interrupt Enable bit
// 1 = Enables the TMR2 to PR2 match interrupt
// 0 = Disables the TMR2 to PR2 match interrupt
#define TMR1IE  PIE1bits.TMR1IE //: TMR1 Overflow Interrupt Enable bit
// 1 = Enables the TMR1 overflow interrupt
// 0 = Disables the TMR1 overflow interrupt


    //***************************************//
    //************* IPR1 ********************//
    //***************************************//

#define SPPIP   IPR1bits.SPPIP //: Streaming Parallel Port Read/Write Interrupt Priority bit (1)
// 1 = High priority
// 0 = Low priority
#define ADIP    IPR1bits.ADIP //: A/D Converter Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define RCIP    IPR1bits.RCIP //: EUSART Receive Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define TXIP    IPR1bits.TXIP //: EUSART Transmit Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define SSPIP   IPR1bits.SSPIP //: Master Synchronous Serial Port Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define CCP1IP  IPR1bits.CCP1IP //: CCP1 Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define TMR2IP  IPR1bits.TMR2IP //: TMR2 to PR2 Match Interrupt Priority bit
// 1 = High priority
// 0 = Low priority
#define TMR1IP  IPR1bits.TMR1IP //: TMR1 Overflow Interrupt Priority bit
// 1 = High priority
// 0 = Low priority

    //***************************************//
    //************* RCON ********************//
    //***************************************//
#define IPEN    RCONbits.IPEN //: Interrupt Priority Enable bit
// 1 = Enable priority levels on interrupts
// 0 = Disable priority levels on interrupts (PIC16CXXX Compatibility mode)
#define SBOREN  RCONbits.SBOREN //: BOR Software Enable bit (1)
// For details of bit operation, see Register 4-1.
#define RI      RCONbits.RI //: RESET Instruction Flag bit
// For details of bit operation, see Register 4-1.
#define TO      RCONbits.TO //: Watchdog Time-out Flag bit
// For details of bit operation, see Register 4-1.
#define PD      RCONbits.PD //: Power-Down Detection Flag bit
// For details of bit operation, see Register 4-1.
#define POR     RCONbits.POR //: Power-on Reset Status bit (2)
// For details of bit operation, see Register 4-1.
#define BOR     RCONbits.BOR //: Brown-out Reset Status bit
// For details of bit operation, see Register 4-1.





#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

