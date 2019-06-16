/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/**
 * I/O and Peripheral Initialization
 */
void InitApp(void);

/**
 * Initialises the UART1 module
 */
void InitUart1(void);

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

extern char ReceivedChar;

