/* 
 * File:   adc.h
 * Author: wouter
 *
 * Created on 22 december 2014, 19:22
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

/** I N C L U D E S *************************************************/
#include <p18f2550.h>


/** D E F I N E S ***************************************************/
#define MSB_MASK    0x0300
#define MSB_SHIFT   8
#define LSB_MASK    0x00FF

/** V A R I A B L E S ***********************************************/

    #define CHS     ADCON0bits.CHS          // Analog Channel Select

    #define VCFG0   ADCON1bits.VCFG0        // Voltage Configuration bit Vref-
    #define VCFG1   ADCON1bits.VCFG1        // Voltage Configuration bit Vref+
    #define PCFG    ADCON1bits.PCFG         // 

    #define ADFM    ADCON2bits.ADFM
    #define ACQT    ADCON2bits.ACQT
    #define ADCS    ADCON2bits.ADCS
    #define ADON    ADCON0bits.ADON

    #define GO_DONE ADCON0bits.GO_DONE

/** P R O T O T Y P E S *********************************************/

void adc_init(void);
void adc_enable(void);
void adc_disable(void);
int  adc_sample(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

