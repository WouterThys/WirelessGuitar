#include <p18f2550.h>
#include "../h/adc.h"

/*************************************************
                        Initialize ADC
 **************************************************/
unsigned int data;

void adc_init() {
    CHS = 0b0000;    // PORT A0
    VCFG0 = 1;       // ref
    VCFG1 = 1;       // ref
    PCFG = 0b1011;   // A0,A2,A3 analog in
    ADFM = 1;        // right justified
    ACQT = 0b110;    // Tad
    ADCS = 0b001;    // Fosc
    ADON = 0;

    TRISAbits.RA0 = 1; // Analog in
    TRISAbits.RA2 = 1; // Vref-
    TRISAbits.RA3 = 1; // Vref+
}
/*************************************************
                        Functions
 **************************************************/
void adc_enable() {
    ADON = 1;
}

void adc_disable() {
    ADON = 0;
}

int adc_sample() {
    data = 0;
    GO_DONE = 1;
    while(GO_DONE) {}
    data = ((0x0000 | ADRESH)<<8) | ADRESL;
    return data;
}