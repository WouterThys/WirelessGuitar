/** @package 

        pinouts.h

*/
#ifndef NORDIC_H
#define NORDIC_H


/****************************************************************************/
/*              S Y S T E M   I N C L U D E   F I L E S                     */
/****************************************************************************/
//#include "cpu.h"
//#include "types.h"

#include "pinouts.h"

//#include "delay.h"
//#include "eeprom.h"
#include "nordic_i2c.h"
#include "adjustableparameters.h"


/****************************************************************************/
/*               L O C A L   I N C L U D E   F I L E S                      */
/****************************************************************************/


/****************************************************************************/
/*                 M A C R O   D E F I N I T I O N S                        */
/****************************************************************************/


/****************************************************************************/
/*                  T Y P E   D E F I N I T I O N S                         */
/****************************************************************************/


void Nordic_Wakeup(void);
void Nordic_Wakeup2(void);

extern BYTE Nordic_Readback ( BYTE  address,  BYTE  data8);

#define ForceRelink()   (Nordic_Send(0x36,0x10))
BYTE AddressChangeCheck(void);
void SaveNordicAddress(BYTE index);
void SetDefaultAddress(void);




extern BYTE N_ADDR;



#endif // ndef NORDIC_H

