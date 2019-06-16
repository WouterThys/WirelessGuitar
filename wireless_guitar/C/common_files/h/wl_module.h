

#ifndef _WL_MODULE_H_
#define _WL_MODULE_H_

#include <xc.h>
#include "nRF24L01.h"

// WL-Module settings
#define nrf_CH			3   // (2400 + nrf_CH)Mhz +
#define nrf_RF_DR_HIGH          0   //0 = 1Mbps, 1 = 2Mpbs
#define nrf_RF_SETUP		(RF_SETUP_RF_PWR_0 | RF_SETUP_RF_DR_1000)     // Output power 0dBm, 1Mbps
#define nrf_CONFIG_TX		((1<<MASK_RX_DR) | (1<<EN_CRC) | (1<<CRCO)) // Mask the interrupt, enable 2byte crc, PTX
#define nrf_CONFIG_RX		((1<<MASK_TX_DS) | (1<<EN_CRC) | (1<<CRCO)) // Mask the interrupt, enable 2byte crc, PRX
#define nrf_ENAA_P5             EN_AA_ENAA_P5
#define nrf_ENAA_P4             EN_AA_ENAA_P4
#define nrf_ENAA_P3             EN_AA_ENAA_P3
#define nrf_ENAA_P2             EN_AA_ENAA_P2
#define nrf_ENAA_P1             EN_AA_ENAA_P1
#define nrf_ENAA_P0             EN_AA_ENAA_P0
#define nrf_ENAA_NONE           EN_AA_ENAA_NONE
#define nrf_TX_NR_0		0
#define nrf_TX_NR_1		1
#define nrf_TX_NR_2		2
#define nrf_TX_NR_3		3
#define nrf_TX_NR_4		4
#define nrf_TX_NR_5		5
#define nrf_STATUS              ((1<<RX_DR) | (1<<TX_DS) | (1<<MAX_RT))    // Write 1 to clear

// Pin definitions for chip select and chip enabled of the wl-module
#define CE  LATB4 // RB4
#define CSN LATB3 // RB3
#define IRQ LATB2 // RB2

// Definitions for selecting and enabling wl_module module
#define nrf_CSN_H     LATBbits.CSN = 1;
#define nrf_CSN_L     LATBbits.CSN = 0;
#define nrf_CE_H      LATBbits.CE = 1;
#define nrf_CE_L      LATBbits.CE = 0;

// Defines for setting the wl_module registers for transmitting or receiving mode
/**
 * Power up the transmitter, keep CONFIG register as initialised
 */
#define TX_POWERUP nrf_config_register(CONFIG, nrf_CONFIG_TX | ( (1<<PWR_UP) | (0<<PRIM_RX) ) )

/**
 * Power up the receiver, keep CONFIG register as initialised
 */
#define RX_POWERUP nrf_config_register(CONFIG, nrf_CONFIG_RX | ( (1<<PWR_UP) | (1<<PRIM_RX) ) )

/**
 * Power Down the transmitter, keep CONFIG register as initialised
 */
#define TX_POWERDOWN nrf_config_register(CONFIG, nrf_CONFIG_TX | ( (0<<PWR_UP) | (0<<PRIM_RX) ) )

/**
 * Power Down the receiver, keep CONFIG register as initialised
 */
#define RX_POWERDOWN nrf_config_register(CONFIG, nrf_CONFIG_RX | ( (0<<PWR_UP) | (1<<PRIM_RX) ) )

// Public standard functions

/**
 * Initialize the nfr module
 * Initializes pins and interrupt to communicate with the wl_module
 * Should be called in the early initializing phase at startup.
 */
extern void nrf_init(void);

/**
 * Configure the nfr module as transmitter
 * Sets the wl-module as one of the six senders.
 * Define for every sender a unique Number (wl_module_TX_NR_x) when you call this Function.
 * Each TX will get a TX-Address corresponding to the RX-Device.
 * RX_Address_Pipe_0 must be the same as the TX-Address
 * @param tx_nr set which pipe needs to be configured to send on
 */
extern void nrf_tx_config(unsigned char tx_nr);

/**
 * Configure the nfr module as receiver
 * Sets the important registers in the wl-module and powers the module
 * in receiving mode
 */
extern void nrf_rx_config(void);

/**
 * Send ONE wireless byte, make sure the payload length is also one byte
 * @param value byte to send wireless
 */
extern void nrf_send_byte(unsigned char value);

/**
 * Send ARRAY of bytes
 * @param value array to send
 * @param len length of the array, should be the same as the payload length
 */
extern void nrf_send_array(unsigned char * value, unsigned char len);

/**
 * Load the adress for receiving
 * @param adr
 */
extern void nrf_set_RADDR(unsigned char * adr);

/**
 * Load the adress for transmitting
 * @param adr
 */
extern void nrf_set_TADDR(unsigned char * adr);

/**
 * Get data array from the payload
 * @param data array to write data in
 * @return return STATUS register
 */
extern unsigned char nrf_get_data(unsigned char * data);

extern unsigned char nrf_get_data_byte(void);

/**
 * Get data array from the payload
 * @param data array to write data in
 * @return return STATUS register
 */
extern unsigned char nrf_get_data_array(unsigned char * data);


/**
 * Configure ONE nfr module register
 * Clocks only one byte into the given wl-module register
 * @param reg which register needs to be configured
 * @param value what is the value for the register
 */
extern void nrf_config_register(unsigned char reg, unsigned char value);

/**
 * Read the nfr module registers
 * Reads only one byte registers
 * @param reg register to read
 * @return value of the red register
 */
extern unsigned char nrf_read_register(unsigned char reg);

/**
 * Confige MORE nrf module registers
 * Writes an array of bytes into inte the wl-module registers.
 * @param reg register to configure
 * @param value array of bytes to write
 * @param len length of the array
 */
extern void nrf_write_register(unsigned char reg, unsigned char * value, unsigned char len);

#endif /* _SETUP_NRF24L01_H_ */
