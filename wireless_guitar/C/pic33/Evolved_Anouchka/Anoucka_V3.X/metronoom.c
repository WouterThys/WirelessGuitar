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

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <delay.h>         /* Includes delay functions                        */
#include "../../common_files/system.h"              /* System funct/params, like osc/peripheral config */
#include "../../common_files/common_defs&vars.h"    /* Common defines for all the PICs */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "sinewave.h"

uint16_t  play, tempo_flag, tone;
uint16_t tmp_cnt, sine_cnt, tempo_cnt , tone_cnt, freq_cnt;
void metronoom(uint16_t maatsoort, uint16_t tempo) {
    if(tempo_flag) {
        tempo_flag = 0;
        tmp_cnt++;
        if(tmp_cnt >= (3600/tempo)) {
            if(tone_cnt == 0)
                tone = 3;
            else
                tone = 2;

            tone_cnt++;
            if(tone_cnt == maatsoort)
                tone_cnt = 0;

            play = 0;
            sine_cnt = 0;
            tmp_cnt = 0;
        }
    }

}

void __attribute__((__interrupt__, no_auto_psv)) _T4Interrupt(void) {
    if (play < 280) {
        MDC = __sinus[sine_cnt];
        sine_cnt += tone;
        if (sine_cnt >= 100)
            sine_cnt = 0;
        play++;
    } else {
        MDC = 1024;
    }

    tempo_cnt++;
    if (tempo_cnt >= 333) {
        tempo_flag = 1;
        tempo_cnt = 0;
    }

    _T4IF = 0;
}
