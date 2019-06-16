#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <delay.h>         /* Includes delay functions                        */
#include "../../common_files/common_defs&vars.h"
#include "../../common_files/nRF24L01.h"
#include "wl_module.h"
#include "user.h"


// *** VARIABLES *** //
volatile uint8_t PTX; // Flag which denotes transmitting mode
uint8_t payload[PL_LENGTH]; //holds the payload


void nrf_init(void) {
    // Initialize and enable spi module
    InitSpiMaster();

    // Define CSN, CE as Output, IRQ as Input, set them to default
    TRISBbits.TRISB2 = 0; // CE
    TRISBbits.TRISB1 = 0; // CSN
    TRISBbits.TRISB0 = 1; // IRQ

    // Clear the nRF interrupt status flag
    nrf_int_status = 0;

    nrf_CE_L;   // No nrf rw
    nrf_CSN_H;  // No SPI rw
}

void nrf_tx_config(uint8_t tx_nr, uint8_t AckMode) {
    uint8_t tx_addr[5]; // Default 5 bytes address widths
    TX_POWERDOWN;
    nrf_CE_L;   // No nrf rw
    nrf_CSN_H;  // No SPI rw
    // Set RF channel
    nrf_config_register(RF_CH, nrf_CH);
    // Set data speed & Output Power configured in wl_module.h
    nrf_config_register(RF_SETUP, nrf_RF_SETUP);
    //Config the CONFIG Register (Mask IRQ, CRC, etc)
    nrf_config_register(CONFIG, nrf_CONFIG_TX);
    // Disable auto acknowledgement function
    nrf_config_register(EN_AA, AckMode);
    // Set waiting time to 750µs, no retransmit
    nrf_config_register(SETUP_RETR, (SETUP_RETR_ARD_500 | SETUP_RETR_ARC_1));
    // Clear all STATUS bits
    nrf_config_register(STATUS, nrf_STATUS);

    //set the TX address for the pipe with the same number as the iteration
    switch (tx_nr) {
        case 0: //setup TX address as default RX address for pipe 0 (E7:E7:E7:E7:E7)
            tx_addr[0] = tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RX_ADDR_P0_B0_DEFAULT_VAL;
            nrf_set_TADDR(tx_addr);
            nrf_set_RADDR(tx_addr);
            break;
        case 1: //setup TX address as default RX address for pipe 1 (C2:C2:C2:C2:C2)
            tx_addr[0] = tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RX_ADDR_P1_B0_DEFAULT_VAL;
            nrf_set_TADDR(tx_addr);
            nrf_set_RADDR(tx_addr);
            break;
        case 2: //setup TX address as default RX address for pipe 2 (C2:C2:C2:C2:C3)
            tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RX_ADDR_P1_B0_DEFAULT_VAL;
            tx_addr[0] = RX_ADDR_P2_DEFAULT_VAL;
            nrf_set_TADDR(tx_addr);
            nrf_set_RADDR(tx_addr);
            break;
        case 3: //setup TX address as default RX address for pipe 3 (C2:C2:C2:C2:C4)
            tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RX_ADDR_P1_B0_DEFAULT_VAL;
            tx_addr[0] = RX_ADDR_P3_DEFAULT_VAL;
            nrf_set_TADDR(tx_addr);
            nrf_set_RADDR(tx_addr);
            break;
        case 4: //setup TX address as default RX address for pipe 4 (C2:C2:C2:C2:C5)
            tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RX_ADDR_P1_B0_DEFAULT_VAL;
            tx_addr[0] = RX_ADDR_P4_DEFAULT_VAL;
            nrf_set_TADDR(tx_addr);
            nrf_set_RADDR(tx_addr);
            break;
        case 5: //setup TX address as default RX address for pipe 5 (C2:C2:C2:C2:C6)
            tx_addr[1] = tx_addr[2] = tx_addr[3] = tx_addr[4] = RX_ADDR_P1_B0_DEFAULT_VAL;
            tx_addr[0] = RX_ADDR_P5_DEFAULT_VAL;
            nrf_set_TADDR(tx_addr);
            nrf_set_RADDR(tx_addr);
            break;
    }

    PTX = 0;
    TX_POWERUP;

}


void nrf_rx_config(uint8_t tx_nr, uint8_t AckMode) {
    // Power down
    RX_POWERDOWN;

    // Ready to init registers
    nrf_CE_L;
    nrf_CSN_H;

    // Set RF channel
    nrf_config_register(RF_CH,nrf_CH);
    // Set data speed & Output Power configured in wl_module.h
    nrf_config_register(RF_SETUP,nrf_RF_SETUP);
    // Set length of incoming payload
    nrf_config_register(tx_nr, PL_LENGTH);
    // Disable auto acknowledgement function
    nrf_config_register(EN_AA, AckMode);
    //Config the CONFIG Register (Mask IRQ, CRC, etc)
    nrf_config_register(CONFIG, nrf_CONFIG_RX);
    // Set waiting time to 750µs, no retransmit
    nrf_config_register(SETUP_RETR, (SETUP_RETR_ARD_750 | SETUP_RETR_ARC_5));
    // Clear all STATUS bits
    nrf_config_register(STATUS, nrf_STATUS);
    // Clear FIFO
    WriteSpi_8b(FLUSH_RX);
    WriteSpi_8b(FLUSH_TX);

    PTX = 0;        // Start in receiving mode
    RX_POWERUP;     // Power up in receiving mode
}

uint8_t nrf_find_rx(uint8_t rx_nr) {
    nrf_send_array(payload, PL_LENGTH); // Send something that can be acknowledged
    while (!(nrf_int_status & NRF_INT_MASK)); // Wait for interrupt to come
    nrf_int_status &= ~NRF_INT_MASK; // Clear the flag
    if (nrf_int_status & (1 << TX_DS)) { // IRQ: Package has been sent and acknowledged
        return 1;
    } else {
        return 0;
    }
}

void nrf_config_register(uint8_t reg, uint8_t value) {
    nrf_CSN_L;
    WriteSpi_8b(W_REGISTER | (REGISTER_MASK & reg));
    WriteSpi_8b(value);
    nrf_CSN_H;
}


 uint8_t nrf_read_register(uint8_t reg) {
    unsigned char tmp;
    nrf_CSN_L;
    WriteSpi_8b(R_REGISTER | (REGISTER_MASK & reg));
    tmp = WriteSpi_8b(NOOP);
    nrf_CSN_H;
    return tmp;
}


void nrf_write_register(uint8_t reg, uint8_t * value, uint8_t len) {
    nrf_CSN_L;
    WriteSpi_8b(W_REGISTER | (REGISTER_MASK & reg));
    WriteSpi_array(value,len);
    nrf_CSN_H;
}


void nrf_send_byte(uint8_t value) {
//    while (PTX) {}                  // Wait until last paket is send

    nrf_CE_L;

    PTX = 1;                        // Set to transmitter mode
    TX_POWERUP;                     // Power up

    nrf_CSN_L;                      // Pull down chip select
    WriteSpi_8b( FLUSH_TX );              // Write cmd to flush tx fifo
    nrf_CSN_H;                      // Pull up chip select

    nrf_CSN_L;                      // Pull down chip select
    WriteSpi_8b( W_TX_PAYLOAD );    // Write cmd to write payload
    WriteSpi_8b(value);             // Write payload
    nrf_CSN_H;                      // Pull up chip select

    nrf_CE_H;                       // Start transmission
    Delay_us(10);
    nrf_CE_L;
}

void nrf_send_array(uint8_t * value, uint8_t len) {
//    while (PTX) {}                  // Wait until last paket is send
    
    nrf_CE_L;                       // Hold CE low

    PTX = 1;                        // Set to transmitter mode
    TX_POWERUP;                     // Power up

    nrf_CSN_L;                      // Pull down chip select
    WriteSpi_8b( FLUSH_TX );        // Write cmd to flush tx fifo
    nrf_CSN_H;                      // Pull up chip select

    nrf_CSN_L;                      // Pull down chip select
    WriteSpi_8b( W_TX_PAYLOAD );    // Write cmd to write payload
    WriteSpi_array(value,len);      // Write payload
    nrf_CSN_H;                      // Pull up chip select

    nrf_CE_H;                       // Start transmission
    Delay_us(10);
    nrf_CE_L;
}

uint8_t nrf_get_data_byte(void) {
    unsigned char status,data;
    nrf_CE_L;
    nrf_CSN_L;                                 // Pull down chip select
    status = WriteSpi_8b( R_RX_PAYLOAD );      // Send cmd to read rx payload
    data = WriteSpi_8b(NOOP);                  // Read payload
    nrf_CSN_H;                                 // Pull up chip select
    nrf_config_register(STATUS,(1<<RX_DR));    // Reset status registe
    nrf_CE_H;
    return data;
}

uint8_t nrf_get_data_array(uint8_t * data) {
    unsigned char status;
//    nrf_CE_L;
    nrf_CSN_L;                                 // Pull down chip select
    status = WriteSpi_8b( R_RX_PAYLOAD );      // Send cmd to read rx payload
    ReadSpi_array(data,data,PL_LENGTH);        // Read payload
    nrf_CSN_H;                                 // Pull up chip select
    nrf_config_register(STATUS,(1<<RX_DR));    // Reset status register
//    nrf_CE_H;
    return status;
}

void nrf_set_RADDR(uint8_t * adr) {
    //nrf_CE_L;
    nrf_write_register(RX_ADDR_P0,adr,5);
    //nrf_CE_H;
}

void nrf_set_TADDR(uint8_t * adr)
// Sets the transmitting address
{
    nrf_write_register(TX_ADDR, adr,5);
}

