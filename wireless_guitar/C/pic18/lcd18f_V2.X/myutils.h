/* 
 * File:   myutils.h
 * Author: Avinash
 *
 * Created on 6 June, 2013, 12:30 PM
 */

#ifndef MYUTILS_H
#define	MYUTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

// Hardware defines
#define BUTTON_DOWN !PORTBbits.RB0
#define BUTTON_BACK !PORTBbits.RB1
#define BUTTON_UP   !PORTBbits.RB2
#define BUTTON_OK   !PORTBbits.RB3

#define INP_B_DOWN  0x01
#define INP_B_UP    0x02
#define INP_B_OK    0x04
#define INP_B_BACK  0x08
#define INP_RX_FLAG 0x10

#define LCD_UPDATE() lcd_update()
#define INP_BUTTON_CLEAR() (inputs &= 0x10)
#define INP_UART_CLEAR() (inputs &= 0x0F)


extern void lcd_main_menu_fsm(unsigned char mmOld);
extern void lcd_sub_menu_tetten(void);
extern void lcd_sub_menu_lcd(void);
extern void lcd_sub_menu_metronoom(void);
extern void lcd_update(void);
extern void lcd_time_out(unsigned char mmOld);
extern void lcd_start_up(void);
extern void lcd_screensaver(void);
extern void lcd_connection(void);
extern void _delay_10ms(int length);

extern unsigned char i, j,first, scrs, scrs_cnt, scrs_speed,brightness;
extern unsigned char read_data, new_data, inputs, go_back;

lcd_fsm_state fsm_new_state, fsm_old_state = lINIT;
#define STATE_NEW_STATE(new_state){\
fsm_new_state = new_state;\
lcd_update();\
}

main_menu_state main_menu_old, main_menu_new = mmMENU;
#define mmSTATE_NEW_STATE(new_state){\
main_menu_new = new_state;\
lcd_update();\
}

sub_menu_lcd_state sub_menu_lcd = smBRIGHTNESS;
sub_menu_metronoom_state sub_menu_metronoom = smM1;

#ifdef	__cplusplus
}
#endif

#endif	/* MYUTILS_H */

