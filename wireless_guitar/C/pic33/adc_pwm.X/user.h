/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#include "../common_files/system.h"
#include "dsp.h"

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/


/**
 * FOR COMMON FILES
 ******************************************************************************/
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
#define Fs         40000        // Sample frequency
#define Fn         (Fs/2)       // Nyquist frequency
#define SAMPPRD    (FCY/Fs)-1   // Sample Period
#define NUMSAMP     24          // Number of samples to take = 6 blocks x 4 samples

extern uint8_t payload[PL_LENGTH]; //holds the payload
extern uint8_t payload1[PL_LENGTH]; //holds the payload (test)
extern uint8_t payload2[PL_LENGTH]; //holds the payload (test)

void PwmValues();
void PwmValues1();
void PwmValues2();
extern uint16_t PwmVal[NUMSAMP];   // Pwm values
extern uint16_t PwmVal1[NUMSAMP];   // Pwm values (test)
extern uint16_t PwmVal2[NUMSAMP];   // Pwm values (test)


/*******************************************************************************
 *
 */


////// PIC HARDWARE
/**
 * I/O and Peripheral Initialization
 */
void InitApp(void);

////// UART
/**
 * Initialises the UART1 module
 */
void InitUart1(void);

////// ADC & DMA
/**
 * Initialize Adc on port
 */
void InitAdc1(void);

/**
 * Initialize Timer 3 
 */
void InitTmr3(void);

/**
 * Initialise Dma 0
 */
void InitDma0(void);


////// PWM

/**
 * Initialise PWM 1
 */
void InitPwm1(void);


/******************************************************************************/
/* User Extern Variable                                                       */
/******************************************************************************/
extern uint16_t ReceivedChar;

// For Penny (ADC)
extern uint16_t AdcFlag;
extern uint16_t AdcBufferA[NUMSAMP];   // Ping pong buffer A for Adc
extern uint16_t AdcBufferB[NUMSAMP];   // Ping pong buffer B for Adc
extern uint16_t AdcBufferAt[NUMSAMP];   // Ping pong buffer A for Adc (test)
extern uint16_t AdcBufferBt[NUMSAMP];   // Ping pong buffer B for Adc (test)
//extern fractional outputSignal[NUMSAMP]; // Output buffer for the FIR filter output
extern uint16_t dmaBuffer;    // DMA flag

// For Anouchka (PWM)
extern uint16_t pwm_count1,pwm_count2,pwm_switch;
extern uint16_t pwm1[NUMSAMP], pwm2[NUMSAMP];