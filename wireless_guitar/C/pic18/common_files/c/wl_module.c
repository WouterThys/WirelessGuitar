#include <p18f2550.h>
#include "../h/common_defs&vars.h"
#include "../h/nRF24L01.h"
#include "../h/wl_module.h"
#include "../h/spi_tx.h"


// *** DEFINES *** //
#define _XTAL_FREQ 48000000

// *** VARIABLES *** //
volatile unsigned char PTX; // Flag which denotes transmitting mode
unsigned char payload[PL_LENGTH]; //holds the payload


void nrf_init(void) {
    // Initialize and enable spi module
    spi_init_master();
    spi_enable();

    // Define CSN, CE as Output, IRQ as Input, set them to default
    TRISBbits.TRISB4 = 0; // CE
    TRISBbits.TRISB3 = 0; // CSN
    TRISBbits.TRISB2 = 1; // IRQ

    nrf_CE_L;   // No nrf rw
    nrf_CSN_H;  // No SPI rw
}

void nrf_tx_config(unsigned char tx_nr) {
    unsigned char tx_addr[5]; // Default 5 bytes address widths

    // Set RF channel
    nrf_config_register(RF_CH, nrf_CH);
    // Set data speed & Output Power configured in wl_module.h
    nrf_config_register(RF_SETUP, nrf_RF_SETUP);
    //Config the CONFIG Register (Mask IRQ, CRC, etc)
    nrf_config_register(CONFIG, nrf_CONFIG_TX);
    // Disable auto acknowledgement function
    nrf_config_register(EN_AA, nrf_ENAA_P0);
    // Set waiting time to 750µs, no retransmit
    nrf_config_register(SETUP_RETR, (SETUP_RETR_ARD_750 | SETUP_RETR_ARC_10));
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


void nrf_rx_config(void) {
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
    nrf_config_register(RX_PW_P0, PL_LENGTH);
    // Disable auto acknowledgement function
    nrf_config_register(EN_AA, nrf_ENAA_P0);
    //Config the CONFIG Register (Mask IRQ, CRC, etc)
    nrf_config_register(CONFIG, nrf_CONFIG_RX);
    // Set waiting time to 750µs, no retransmit
    nrf_config_register(SETUP_RETR, (SETUP_RETR_ARD_750 | SETUP_RETR_ARC_10));
    // Clear all STATUS bits
    nrf_config_register(STATUS, nrf_STATUS);
    // Clear FIFO
    spi_w(FLUSH_RX);
    spi_w(FLUSH_TX);
}


void nrf_config_register(unsigned char reg, unsigned char value) {
    nrf_CSN_L;
    spi_w(W_REGISTER | (REGISTER_MASK & reg));
    spi_w(value);
    nrf_CSN_H;
}


 unsigned char nrf_read_register(unsigned char reg) {
    unsigned char tmp;
    nrf_CSN_L;
    spi_w(R_REGISTER | (REGISTER_MASK & reg));
    tmp = spi_w(NOOP);
    nrf_CSN_H;
    return tmp;
}


void nrf_write_register(unsigned char reg, unsigned char * value, unsigned char len) {
    nrf_CSN_L;
    spi_w(W_REGISTER | (REGISTER_MASK & reg));
    spi_w_array(value,len);
    nrf_CSN_H;
}


void nrf_send_byte(unsigned char value) {
    while (PTX) {}                  // Wait until last paket is send

    nrf_CE_L;

    PTX = 1;                        // Set to transmitter mode
    TX_POWERUP;                     // Power up

    nrf_CSN_L;                      // Pull down chip select
    spi_w( FLUSH_TX );              // Write cmd to flush tx fifo
    nrf_CSN_H;                      // Pull up chip select

    nrf_CSN_L;                      // Pull down chip select
    spi_w( W_TX_PAYLOAD );          // Write cmd to write payload
    spi_w(value);                   // Write payload
    nrf_CSN_H;                      // Pull up chip select

    nrf_CE_H;                       // Start transmission
    __delay_us(10);
    nrf_CE_L;
}

void nrf_send_array(unsigned char * value, unsigned char len) {
    while (PTX) {}                  // Wait until last paket is send

    nrf_CE_L;

    PTX = 1;                        // Set to transmitter mode
    TX_POWERUP;                     // Power up

    nrf_CSN_L;                      // Pull down chip select
    spi_w( FLUSH_TX );              // Write cmd to flush tx fifo
    nrf_CSN_H;                      // Pull up chip select

    nrf_CSN_L;                      // Pull down chip select
    spi_w( W_TX_PAYLOAD );          // Write cmd to write payload
    spi_w_array(value,len);         // Write payload
    nrf_CSN_H;                      // Pull up chip select

    nrf_CE_H;                       // Start transmission
    __delay_us(10);
    nrf_CE_L;
}

extern unsigned char nrf_get_data_byte(void) {
    unsigned char status,data;
    nrf_CE_L;
    nrf_CSN_L;                                 // Pull down chip select
    status = spi_w( R_RX_PAYLOAD );            // Send cmd to read rx payload
    data = spi_w(NOOP);                        // Read payload
    nrf_CSN_H;                                 // Pull up chip select
    nrf_config_register(STATUS,(1<<RX_DR));    // Reset status registe
    nrf_CE_H;
    return data;
}

extern unsigned char nrf_get_data_array(unsigned char * data) {
    unsigned char status;
    //nrf_CE_L;
    nrf_CSN_L;                                 // Pull down chip select
    status = spi_w( R_RX_PAYLOAD );            // Send cmd to read rx payload
    spi_rw_array(data,data,PL_LENGTH);       // Read payload
    nrf_CSN_H;                                 // Pull up chip select
    nrf_config_register(STATUS,(1<<RX_DR));    // Reset status register
    //nrf_CE_H;
    return status;
}

void nrf_set_RADDR(unsigned char * adr) {
    //nrf_CE_L;
    nrf_write_register(RX_ADDR_P0,adr,5);
    //nrf_CE_H;
}

void nrf_set_TADDR(unsigned char * adr)
// Sets the transmitting address
{
    nrf_write_register(TX_ADDR, adr,5);
}

