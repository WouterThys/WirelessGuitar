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

#include <stdint.h>

// Names and adresses of HW modules
#define PENNY       0x50
#define ANOUCHKA    0xA0
#define LCD         0x90

// Payload defines
#define PL_LENGTH           32  // Length of the payload
#define PL_BLOCK_LENGTH     5   // 4 MSBs in one byte + 4 LSB bytes
#define PL_BLOCKS           6   // 6 blocks per payload
#define PL_COMMAND          0   // Place of payload command
#define PL_BLOCK_START      1   // Place of payload data blocks start
#define PL_END              31  // Place of payload end symbol

#define MSB_MASK            0x0300
#define LSB_MASK            0x00FF

// Adc defines
#define Fs         16000        // Sample frequency
#define Fn         (Fs/2)       // Nyquist frequency
//#define SAMPPRD    (FCY/Fs)-1   // Sample Period
#define NUMSAMP     24          // Number of samples to take = 6 blocks x 4 samples

// Uart defines
#define UART_LENGTH  8
#define SER_COMMAND  0  //4b name + 4b state
#define SER_HW       1  // X | X | X | X | P | Pnrf | A | Anrf
 #define HW_Anrf     0x01
 #define HW_A        0x02
 #define HW_Pnrf     0x04
 #define HW_P        0x08
#define SER_DAT1     2
#define SER_DAT2     3
#define SER_DAT3     4
#define SER_DAT4     5
#define SER_DAT5     6
#define SER_DAT6     7

struct SerialStruct {
  uint8_t TransmitAddress;
  uint8_t Command;
  uint8_t Hardware;
  uint8_t Dat1;
  uint8_t Dat2;
  uint8_t Dat3;
  uint8_t Dat4;
  uint8_t Dat5;
  uint8_t Dat6;
};
extern struct SerialStruct SerialRx;
extern struct SerialStruct SerialTx;



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
    lINIT, lSEARCH_A, lSEARCH_HW, lWAIT, lTRANSMIT, lMENU, lTIMEOUT
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
 */
typedef enum {
    pINIT, pSEARCH_A, pSEARCH_HW, pPREPARE, pTRANSMIT
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
    mmMENU, mmRESET, mmSTEMMEN, mmMETRONOOM, mmMOPJE, mmTETTEN, mmLCD, mmMETRONOOMsm, mmTETTENsm, mmLCDsm
} main_menu_state;

#define mmMENU_MIN    0
#define mmMENU_MAX    6

typedef enum {
    smBRIGHTNESS, smSCRSPEED, smLED
} sub_menu_lcd_state;

#define smMENU_LCD_MIN   0
#define smMENU_LCD_MAX   2

typedef enum {
    smINDICATOR, smM1, smT1, smT2, smT3
} sub_menu_metronoom_state;

#define smMENU_METRONOOM_MIN   0
#define smMENU_METRONOOM_MAX   5
extern unsigned char indicator, m1, t1, t2, t3;

// Nordic nRF variables
extern volatile unsigned char PTX;
extern unsigned char payload[]; //holds the payload
extern unsigned char nrf_int_status;
extern unsigned char send_flag,pl_place;
extern unsigned char nrf_int_status;
extern unsigned char uart_tx_block[UART_LENGTH];
extern unsigned char uart_rx_block[UART_LENGTH];
extern unsigned char uart_block_count;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_DEFS_VARS_H */

