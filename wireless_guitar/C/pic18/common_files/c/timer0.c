#include <p18f2550.h>
#include "../h/timer0.h"

/*************************************************
                        Initialize TIMER0
 **************************************************/
    void init_timer0(unsigned char eight_bit, unsigned char presc, unsigned char presc_val) {
        TMR0ON = 0;
        T08BIT = eight_bit;     // 8 bit mode
        T0CS   = 0;     // Internal clock
        T0CS   = 0;     // Low-High transition
        PSA    = presc;     // no prescaler
        T0PS   = presc_val; // supa slow

        TMR0L = 0;
        TMR0ON = 1;
    }
    

/*************************************************
                        Functions
 **************************************************/
    void enable_timer0(char start_value) {
        TMR0L = start_value;
        TMR0ON = 1;
    }
    void disable_timer0(void) {
        TMR0ON = 0;
    }