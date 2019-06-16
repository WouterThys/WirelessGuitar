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

#include "dsp.h"
#include "system.h"

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
#define Fs         10000        // Sample frequency
#define Fn         (Fs/2)       // Nyquist frequency
#define SAMPPRD    (FCY/Fs)-1   // Sample Period
#define NUMSAMP     24          // Number of samples to take = 6 blocks x 4 samples

// Uart defines
#define BAUDRATE     57600
#define BRGVAL       ((FCY/BAUDRATE)/16) - 1
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
 * lTIMEOUT
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
 * 
 */
typedef enum {
    aINIT, aSEARCH_A, aSEARCH_HW, aPREPARE, aTRANSMIT, aIDLE, aMETRONOOM
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
    pINIT, pSEARCH_A, pSEARCH_HW, pPREPARE, pTRANSMIT, pIDLE
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

#define smMENU_MIN   0
#define smMENU_MAX   2


// Nordic nRF variables
extern volatile uint8_t PTX;
extern volatile uint8_t ACK;
extern uint8_t payload[]; //holds the payload
extern uint8_t nrf_int_status;
extern uint8_t send_flag,pl_place;
extern uint8_t nrf_int_status;
extern uint8_t int_flag;
extern uint16_t fail;

extern uint16_t pwm_count1,pwm_count2,pwm_switch;
extern uint16_t pwm1[NUMSAMP], pwm2[NUMSAMP];
extern uint16_t uart_block_count;

extern uint8_t payload[PL_LENGTH]; //holds the payload
extern uint8_t payload1[PL_LENGTH]; //holds the payload (test)
extern uint8_t payload2[PL_LENGTH]; //holds the payload (test)

void PwmValues();
void PwmValues1();
void PwmValues2();
extern uint16_t PwmVal[NUMSAMP];   // Pwm values
extern uint16_t PwmVal1[NUMSAMP];   // Pwm values (test)
extern uint16_t PwmVal2[NUMSAMP];   // Pwm values (test)

extern void metronoom(uint16_t maatsoort, uint16_t tempo);
extern uint16_t tmp_cnt, play, tempo_flag, tone, tone_cnt;
extern uint16_t sine_cnt, tempo_cnt;
extern uint16_t freq_cnt;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_DEFS_VARS_H */

