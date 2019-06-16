/* 
 * File:   uart_m.h
 * Author: wouter
 *
 * Created on 4 januari 2015, 15:37
 */

#ifndef UART_M_H
#define	UART_M_H

#ifdef	__cplusplus
extern "C" {
#endif

/** I N C L U D E S *************************************************/


/** V A R I A B L E S ***********************************************/
extern char new_data;

/** P R O T O T Y P E S *********************************************/

void init_uart_m(int baud, char TX_inv, char RX_inv);
void uart_write_m(char data);
void uart_write_string(char * text);
char uart_read_m(void);
void uart_read_string(char *Output, unsigned int length);
void enable_uart_m(void);
void disable_uart_m(void);
void terminal_write_m(const char data[],signed int );
void lcd_write(unsigned char data);
void uart_write_block(unsigned char *data, unsigned char length);
void SerialTransmit(void);


#define RX  TRISCbits.TRISC7		//RX pin
#define TX  TRISCbits.TRISC6		//TX pin

    //***************************************//
    //************* TXSTA *******************//
    //***************************************//
/**Clock Source Select bit*/
#define CSRC    TXSTAbits.CSRC 
//Asynchronous mode:
// Don?t care.
//Synchronous mode:
// 1 = Master mode (clock generated internally from BRG)
// 0 = Slave mode (clock from external source)

/**9-Bit Transmit Enable bit*/
#define TX9     TXSTAbits.TX9 
// 1 = Selects 9-bit transmission
// 0 = Selects 8-bit transmission

/**Transmit Enable bit (1)*/
#define TXEN    TXSTAbits.TXEN 
// 1 = Transmit enabled
// 0 = Transmit disabled

/**EUSART Mode Select bit*/
#define SYNC    TXSTAbits.SYNC 
// 1 = Synchronous mode
// 0 = Asynchronous mode

/**Send Break Character bit*/
#define SENDB   TXSTAbits.SENDB 
//Asynchronous mode:
// 1 = Send Sync Break on next transmission (cleared by hardware upon completion)
// 0 = Sync Break transmission completed
//Synchronous mode:
// Don?t care.

/**High Baud Rate Select bit*/
#define BRGH    TXSTAbits.BRGH 
//Asynchronous mode:
// 1 = High speed
// 0 = Low speed
//Synchronous mode:
// Unused in this mode.

/**Transmit Shift Register Status bit*/
#define TRMT    TXSTAbits.TRMT 
// 1 = TSR empty
// 0 = TSR full

/**9th bit of Transmit Data*/
#define TX9D    TXSTAbits.TX9D 
//Can be address/data bit or a parity bit.


    //***************************************//
    //************* RCSTA *******************//
    //***************************************//
/**Serial Port Enable bit*/
#define SPEN    RCSTAbits.SPEN
// 1 = Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
// 0 = Serial port disabled (held in Reset)

/**9-Bit Receive Enable bit*/
#define RX9     RCSTAbits.RX9
// 1 = Selects 9-bit reception
// 0 = Selects 8-bit reception

/**Single Receive Enable bit*/
#define SREN    RCSTAbits.SREN
//Asynchronous mode:
// Don?t care.
//Synchronous mode ? Master:
// 1 = Enables single receive
// 0 = Disables single receive
// This bit is cleared after reception is complete.
//Synchronous mode ? Slave:
// Don?t care.

/**Continuous Receive Enable bit*/
#define CREN    RCSTAbits.CREN
//Asynchronous mode:
// 1 = Enables receiver
// 0 = Disables receiver
//Synchronous mode:
// 1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN)
// 0 = Disables continuous receive

/**Address Detect Enable bit*/
#define ADDEN   RCSTAbits.ADDEN
//Asynchronous mode 9-bit (RX9 = 1):
// 1 = Enables address detection, enables interrupt and loads the receive buffer when RSR<8> is set
// 0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit
//Asynchronous mode 9-bit (RX9 = 0):
// Don?t care.

/**Framing Error bit*/
#define FERR    RCSTAbits.FERR
// 1 = Framing error (can be updated by reading RCREG register and receiving next valid byte)
// 0 = No framing error

/**Overrun Error bit*/
#define OERR    RCSTAbits.OERR
// 1 = Overrun error (can be cleared by clearing bit CREN)
// 0 = No overrun error

/**9th bit of Received Data*/
#define RX9D    RCSTAbits.RX9D
//This can be address/data bit or a parity bit and must be calculated by user firmware.


    //***************************************//
    //************* BAUDCON *****************//
    //***************************************//
/**Auto-Baud Acquisition Rollover Status bit*/
#define ABDOVF  BAUDCONbits.ABDOVF
// 1 = A BRG rollover has occurred during Auto-Baud Rate Detect mode (must be cleared in software)
// 0 = No BRG rollover has occurred

/**Receive Operation Idle Status bit*/
#define RCIDL   BAUDCONbits.RCIDL
// 1 = Receive operation is Idle
// 0 = Receive operation is active

/**Received Data Polarity Select bit*/
#define RXDTP   BAUDCONbits.RXDTP
//Asynchronous mode:
// 1 = RX data is inverted
// 0 = RX data received is not inverted
//Synchronous modes:
// 1 = CK clocks are inverted
// 0 = CK clocks are not inverted

/**Clock and Data Polarity Select bit*/
#define TXCKP   BAUDCONbits.TXCKP
//Asynchronous mode:
// 1 = TX data is inverted
// 0 = TX data is not inverted
//Synchronous modes:
// 1 = CK clocks are inverted
// 0 = CK clocks are not inverted

/**16-Bit Baud Rate Register Enable bit*/
#define BRG16   BAUDCONbits.BRG16
// 1 = 16-bit Baud Rate Generator ? SPBRGH and SPBRG
// 0 = 8-bit Baud Rate Generator ? SPBRG only (Compatible mode), SPBRGH value ignored

/**Wake-up Enable bit*/
#define WUE     BAUDCONbits.WUE
//Asynchronous mode:
// 1 = EUSART will continue to sample the RX pin ? interrupt generated on falling edge; bit cleared in
//  hardware on following rising edge
// 0 = RX pin not monitored or rising edge detected
//Synchronous mode:
// Unused in this mode.

/**Auto-Baud Detect Enable bit*/
#define ABDEN   BAUDCONbits.ABDEN
//Asynchronous mode:
// 1 = Enable baud rate measurement on the next character. Requires reception of a Sync field (55h);
//  cleared in hardware upon completion.
// 0 = Baud rate measurement disabled or completed
//Synchronous mode:
// Unused in this mode.

#ifdef	__cplusplus
}
#endif

#endif	/* UART_M_H */

