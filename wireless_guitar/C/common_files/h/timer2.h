/* 
 * File:   timer2.h
 * Author: wouter
 *
 * Created on 17 februari 2015, 11:11
 */

#ifndef TIMER2_H
#define	TIMER2_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void init_timer2(void);

    //***************************************//
    //************* T2CON *******************//
    //***************************************//

#define T2CON       T2CON

#define T2OUTPS     T2CONbits.TOUTPS //: Timer2 Output Postscale Select bits
// 0000 = 1:1 Postscale
// 0001 = 1:2 Postscale
// ?
// ?
// ?
// 1111 = 1:16 Postscale
#define TMR2ON      T2CONbits.TMR2ON //: Timer2 On bit
// 1 = Timer2 is on
// 0 = Timer2 is off
#define T2CKPS      T2CONbits.T2CKPS //: Timer2 Clock Prescale Select bits
// 00 = Prescaler is 1
// 01 = Prescaler is 4
// 1x = Prescaler is 16

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER2_H */

