/* Device header file */
#if defined(__XC16__)
#include <xc.h>
#elif defined(__C30__)
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif
#endif

#include <stdio.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <delay.h>         /* Includes delay functions                        */
#include "../../common_files/system.h"              /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

void metronoom(uint16_t maatsoort, uint16_t tempo) {

}
