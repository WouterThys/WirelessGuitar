/* 
 * File:   interrupts.h
 * Author: wouter
 *
 * Created on 3 maart 2015, 13:06
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#ifdef	__cplusplus
extern "C" {
#endif


#define TMR3_IP     7
#define INT1_IP     6
#define U1RX_IP     5
#define TMR4_IP     3


  void InitInterrupts(void);
  void DisableInterrupts (void);
  void EnableInterrupts(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

