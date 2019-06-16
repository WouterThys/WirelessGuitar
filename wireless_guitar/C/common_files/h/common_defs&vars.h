/* 
 * File:   common_defs&vars.h
 * Author: wouter
 *
 * Created on 25 februari 2015, 12:55
 */

#ifndef COMMON_DEFS_VARS_H
#define	COMMON_DEFS_VARS_H

#ifdef	__cplusplus
extern "C" {
#endif

// Names and adresses of HW modules
#define PENNY       0x50
#define ANOUCHKA    0xA0
#define LCD         0x90

// Uart defines
#define UART_LENGTH  8
#define SER_COMMAND  0  //4b name + 4b state
#define SER_HW       1  // X | X | X | X | P | Pnrf | A | Anrf
 #define HW_Anrf     0x01
 #define HW_A        0x02
 #define HW_Pnrf     0x04
 #define HW_P        0x08

// Payload defines
#define PL_LENGTH   32
#define PL_COMMAND  0
#define PL_MSB      1
#define PL_LSB      2
#define PL_DIFF     3

// RX Queue defines
#define QUEUE_ELEMENTS 64
#define QUEUE_SIZE (QUEUE_ELEMENTS + 1)

// Mask for nrf interrupt (last bit in status register is unused, use as flag)
#define NRF_INT_MASK 0x80

/** LCD Finit State Machine enumerated typedef 
 * states:
 * lINIT, 
 * lSEARCH_A, 
 * lA_SEARCH_P, 
 * lTRANSMIT, 
 * lMENU, 
 * lMENU_UP, 
 * lMENU_DOWN, 
 * lMENU_OK, 
 * lRESET, 
 * lSTEMMEN, 
 * lMETRONOOM, 
 * lMOPJE, 
 * lTETTEN
 */
typedef enum {
    lINIT, lSEARCH_A, lSEARCH_HW, lWAIT, lTRANSMIT, lMENU, lMENU_UP, lMENU_DOWN, lMENU_OK, lRESET, lSTEMMEN, lMETRONOOM, lMOPJE, lTETTEN
} lcd_fsm_state;

/** ANOUCHKA Finit State Machine enumerated typedef
 * states:
 *  pINIT,
 *  pSEARCH_A, 
 *  pA_SEARCH_P, 
 *  pTRANSMIT, 
 *  pPREPARE
 */
typedef enum {
    aINIT, aSEARCH_A, aSEARCH_HW, aPREPARE, aTRANSMIT
} anouchka_fsm_state;

/** PENNY Finit State Machine enumerated typedef
 * states:
 *  pINIT,
 *  pSEARCH_A,
 *  pA_SEARCH_P,
 *  pTRANSMIT,
 *  pPREPARE
 *  pUART
 *  pEND
 */
typedef enum {
    pINIT, pSEARCH_A, pSEARCH_HW, pPREPARE, pTRANSMIT, pUART, pEND
} penny_fsm_state;

/** ANOUCHKA MENU options
 * options:
 * mRESET, 
 * mSTEMMEN, 
 * mMETRONOOM, 
 * mMOPJE, 
 * mTETTEN
 */
typedef enum {
    mMENU, mRESET, mSTEMMEN, mMETRONOOM, mMOPJE, mTETTEN
} menu_state;


// Nordic nRF variables
extern volatile unsigned char PTX;
extern unsigned char payload[]; //holds the payload
extern unsigned char nrf_int_status;
extern unsigned char send_flag,pl_place;
extern unsigned char nrf_int_status;
extern unsigned char int_flag;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_DEFS_VARS_H */

