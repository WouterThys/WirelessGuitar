/* 
 * File:   timer0.h
 * Author: wouter
 *
 * Created on 22 december 2014, 20:36
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif

/** I N C L U D E S *************************************************/
#include <p18f2550.h>

#define TMR0_8_BIT     1
#define TMR0_16_bit    0
#define TMR0_PRESC_ON  0
#define TMR0_PRESC_OFF 1
#define TMR0_PRESC_256 0b111
#define TMR0_PRESC_128 0b110
#define TMR0_PRESC_64  0b101
#define TMR0_PRESC_32  0b100
#define TMR0_PRESC_16  0b011
#define TMR0_PRESC_8   0b010
#define TMR0_PRESC_4   0b001
#define TMR0_PRESC_2   0b000

    /** P R O T O T Y P E S *********************************************/

    void init_timer0(unsigned char eight_bit, unsigned char presc, unsigned char presc_val);
    void enable_timer0(char);
    void disable_timer0(void);

/** V A R I A B L E S ***********************************************/
//T0CON
#define T0CON       T0CON

#define TMR0ON      T0CONbits.TMR0ON    // Timer0 On/Off Control bit
//    1 = Enables Timer0
//    0 = Stops Timer0
#define T08BIT      T0CONbits.T08BIT    // Timer0 8-Bit/16-Bit Control bit
//    1 = Timer0 is configured as an 8-bit timer/counter
//    0 = Timer0 is configured as a 16-bit timer/counter
#define T0CS        T0CONbits.T0CS      // Timer0 Clock Source Select bit
//    1 = Transition on T0CKI pin
//    0 = Internal instruction cycle clock (CLKO)
#define T0SE        T0CONbits.T0SE      // Timer0 Source Edge Select bit
//    1 = Increment on high-to-low transition on T0CKI pin
//    0 = Increment on low-to-high transition on T0CKI pin
#define PSA         T0CONbits.PSA       // Timer0 Prescaler Assignment bit
//    1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler.
//    0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
#define T0PS        T0CONbits.T0PS      // Timer0 Prescaler Select bits
//    111 = 1:256 Prescale value
//    110 = 1:128 Prescale value
//    101 = 1:64 Prescale value
//    100 = 1:32 Prescale value
//    011 = 1:16 Prescale value
//    010 = 1:8 Prescale value
//    001 = 1:4 Prescale value
//    000 = 1:2 Prescale value





#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

