#include <p18f2550.h>
#include "../h/timer2.h"

/*************************************************
                        Initialize TIMER0
 **************************************************/
    void init_timer2(void) {
        TMR2ON = 0;
        T2OUTPS = 0b0000;
        T2CKPS = 0b01;
        PR2 = 0;
    }
