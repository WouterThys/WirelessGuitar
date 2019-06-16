/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#include <xc.h>
#include <p33EP64MC502.h>


#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "system.h"          /* variables/params used by system.c             */

/******************************************************************************/
/* System Level Functions                                                     */
/*                                                                            */
/* Custom oscillator configuration funtions, reset source evaluation          */
/* functions, and other non-peripheral microcontroller initialization         */
/* functions get placed in system.c.                                          */
/*                                                                            */
/******************************************************************************/

/* Refer to the device Family Reference Manual Oscillator section for
information about available oscillator configurations.  Typically
this would involve configuring the oscillator tuning register or clock
switching useing the compiler's __builtin_write_OSCCON functions.
Refer to the C Compiler for PIC24 MCUs and dsPIC DSCs User Guide in the
compiler installation directory /doc folder for documentation on the
__builtin functions.*/

/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{


        /* Disable Watch Dog Timer */
        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to */

       // Clock PLL = 280 MHZ   Fosc = 140 Mhz    Fcy = 70 Mhz
                            // bit 15 Unimplemented: Read as ?0?
                            // bit 14-12 COSC<2:0>: Current Oscillator Selection bits (read-only)
                            // 111 = Fast RC Oscillator (FRC) with Divide-by-n
                            //110 = Fast RC Oscillator (FRC) with Divide-by-16
                            //101 = Low-Power RC Oscillator (LPRC)
                            //100 = Reserved
                            //011 = Primary Oscillator (XT, HS, EC) with PLL
                            //010 = Primary Oscillator (XT, HS, EC)
                            //001 = Fast RC Oscillator (FRC) with divide-by-N and PLL (FRCPLL)
                            //000 = Fast RC Oscillator (FRC)
                            //bit 11 Unimplemented: Read as ?0?
    OSCCONbits.NOSC0 = 1;
    OSCCONbits.NOSC1 = 0;
    OSCCONbits.NOSC2 = 0;   //bit 10-8 NOSC<2:0>: New Oscillator Selection bits(2)
                            //111 = Fast RC Oscillator (FRC) with Divide-by-n
                            //110 = Fast RC Oscillator (FRC) with Divide-by-16
                            //101 = Low-Power RC Oscillator (LPRC)
                            //100 = Reserved
                            //011 = Primary Oscillator (XT, HS, EC) with PLL
                            //010 = Primary Oscillator (XT, HS, EC)
                            //001 = Fast RC Oscillator (FRC) with divide-by-N and PLL (FRCPLL)
                            //000 = Fast RC Oscillator (FRC)
    OSCCONbits.CLKLOCK = 0; //bit 7 CLKLOCK: Clock Lock Enable bit
                            //1 = If (FCKSM0 = 1), then clock and PLL configurations are locked
                            //If (FCKSM0 = 0), then clock and PLL configurations may be modified
                            //0 = Clock and PLL selections are not locked, configurations may be modified
    OSCCONbits.IOLOCK = 0;  //bit 6 IOLOCK: I/O Lock Enable bit
                            //1 = I/O Lock is active
                            //0 = I/O Lock is not active
                            //bit 5 LOCK: PLL Lock Status bit (read-only)
                            //1 = Indicates that PLL is in lock, or PLL start-up timer is satisfied
                            //0 = Indicates that PLL is out of lock, start-up timer is in progress or PLL is disabled
                            //bit 4 Unimplemented: Read as ?0?
                            //bit 3 CF: Clock Fail Detect bit
                            //1 = FSCM has detected clock failure
                            //0 = FSCM has not detected clock failure
                            //bit 2-1 Unimplemented: Read as ?0?
     OSCCONbits.OSWEN = 1;  //bit 0 OSWEN: Oscillator Switch Enable bit
                            //1 = Request oscillator switch to selection specified by NOSC<2:0> bits
                            //0 = Oscillator switch is complete
        while(OSCCONbits.COSC != 0b001);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, only if PLL is needed */
        /* while(OSCCONbits.LOCK != 1); */
}
void PLLset(void)
{
    CLKDIVbits.ROI = 0;             //bit 15 ROI: Recover on Interrupt bit
                                        //1 = Interrupts will clear the DOZEN bit and the processor clock and peripheral clock ratio is set to 1:1
                                        //0 = Interrupts have no effect on the DOZEN bit
    CLKDIVbits.DOZE0 = 0;
    CLKDIVbits.DOZE1 = 0;
    CLKDIVbits.DOZE2 = 0;            //bit 14-12 DOZE<2:0>: Processor Clock Reduction Select bits
                                        //111 = FCY divided by 128
                                        //110 = FCY divided by 64
                                        //101 = FCY divided by 32
                                        //100 = FCY divided by 16
                                        //011 = FCY divided by 8 (default)
                                        //010 = FCY divided by 4
                                        //001 = FCY divided by 2
                                        //000 = FCY divided by 1
    CLKDIVbits.DOZEN = 0;               //bit 11 DOZEN: Doze Mode Enable bit
                                        //1 = DOZE<2:0> field specifies the ratio between the peripheral clocks and the processor clocks
                                        //0 = Processor clock and peripheral clock ratio forced to 1:1
    CLKDIVbits.FRCDIV0 = 0;
    CLKDIVbits.FRCDIV1 = 0;
    CLKDIVbits.FRCDIV2 = 0;              //bit 10-8 FRCDIV<2:0>: Internal Fast RC Oscillator Postscaler bits
                                        //111 = FRC divided by 256
                                        //110 = FRC divided by 64
                                        //101 = FRC divided by 32
                                        //100 = FRC divided by 16
                                        //011 = FRC divided by 8
                                        //010 = FRC divided by 4
                                        //001 = FRC divided by 2
                                        //000 = FRC divided by 1 (default)
    CLKDIVbits.PLLPOST0 = 0;
    CLKDIVbits.PLLPOST1 = 0;            //bit 7-6 PLLPOST<1:0>: PLL VCO Output Divider Select bits (also denoted as ?N2?, PLL postscaler)
                                        //11 = Output divided by 8
                                        //10 = Reserved
                                        //01 = Output divided by 4 (default)
                                        //00 = Output divided by 2
                                    //bit 5 Unimplemented: Read as ?0?
    CLKDIVbits.PLLPRE0 = 0;
    CLKDIVbits.PLLPRE1 = 0;
    CLKDIVbits.PLLPRE2 = 0;
    CLKDIVbits.PLLPRE3 = 0;
    CLKDIVbits.PLLPRE4 = 0;
                                    //bit 4-0 PLLPRE<4:0>: PLL Phase Detector Input Divider Select bits (also denoted as ?N1?, PLL prescaler)
                                        //11111 = Input divided by 33
                                        //?
                                        //?
                                        //?
                                        //00001 = Input divided by 3
                                        //00000 = Input divided by 2 (default)
    PLLFBDbits.PLLDIV = 76;
}

