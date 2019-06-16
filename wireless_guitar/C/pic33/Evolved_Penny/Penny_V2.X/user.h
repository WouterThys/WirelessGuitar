/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#include "../../common_files/system.h"
#include "../../common_files/common_defs&vars.h"
#include "dsp.h"

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/


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


////// SPI
/**
 * Initialises the SPI1 module
 */
void InitSpi1(void);

/**
 * Fast Write SPI Byte
 * @param data: data to send
 * @return SPI1BUF (nRF STATUS register)
 */
uint8_t WriteSpi_8b(uint8_t data);

/**
 * Fast Write SPI Byte
 * @param data: data to send
 * @return SPI1BUF (nRF STATUS register)
 */
uint8_t WriteSpi_16b(uint16_t data);

/**
 * Writing SPI data array
 * @param data: data to send
 * @param length: length of the array
 * @return 1
 */
uint8_t WriteSpi_array(uint8_t *data, uint8_t length);

/**
 * Reading SPI data array, always send clock to read the data
 * @param dataout: array to send
 * @param datain: array to read
 * @param length: length of the arrays
 */
void    ReadSpi_array(uint8_t * dataout, uint8_t * datain, uint8_t length);


////// SPI
/**
 * Initialise the Spi Master with DMA to transmit data
 */
void InitSpiMaster(void);

////// TIMER
/**
 * Initialize Timer1 module
 */
void InitTimer1(void);


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


/******************************************************************************/
/* User Extern Variable                                                       */
/******************************************************************************/
extern uint16_t ReceivedChar;
extern uint16_t AdcFlag;
extern uint16_t AdcBufferA[NUMSAMP];   // Ping pong buffer A for Adc
extern uint16_t AdcBufferB[NUMSAMP];   // Ping pong buffer B for Adc
//extern fractional outputSignal[NUMSAMP]; // Output buffer for the FIR filter output
extern uint16_t dmaBuffer;    // DMA flag
