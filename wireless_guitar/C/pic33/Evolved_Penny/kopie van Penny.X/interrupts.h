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

  void InintInterrupts(void);
  void DisableInterrupts (void);
  void EnableInterrupts(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

