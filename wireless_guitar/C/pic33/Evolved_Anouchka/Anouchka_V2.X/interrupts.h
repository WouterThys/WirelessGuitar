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
#define DMA1_IP     4
#define SPI1_IP     3
#define TMR1_IP     2



  void InitInterrupts(void);
  void DisableInterrupts (void);
  void EnableInterrupts(void);


 void QueueInit(void);
 uint16_t QueuePut(uint16_t new_val);
 uint16_t QueueGet(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INTERRUPTS_H */

