/*#ifndef	_HTC_H_
 #warning Header file pic16f72x.h included directly. Use #include <htc.h> instead.
#endif

 /* header file for the MICROCHIP PIC microcontroller
	16F722
	16F723
	16F724
	16F726
	16F727
	16LF722
	16LF723
	16LF724
	16LF726
	16LF727
 */

#ifndef	__PIC16F72X_H
#define	__PIC16F72X_H

// Special function register definitions

static volatile       unsigned char	INDF		@ 0x00;
static volatile       unsigned char	TMR0		@ 0x001;
static volatile       unsigned char	PCL		@ 0x002;
static volatile       unsigned char	STATUS		@ 0x003;
static                unsigned char	FSR		@ 0x004;
static volatile       unsigned char	PORTA		@ 0x005;
static volatile       unsigned char	PORTB		@ 0x006;
static volatile       unsigned char	PORTC		@ 0x007;
#if defined(_16F724) || defined(_16F727) || defined(_16LF724) || defined(_16LF727)
static volatile       unsigned char	PORTD		@ 0x008;
#endif
static volatile       unsigned char	PORTE		@ 0x009;
static volatile       unsigned char	PCLATH		@ 0x00A;
static volatile       unsigned char	INTCON		@ 0x00B;
static volatile       unsigned char	PIR1		@ 0x00C;
static volatile       unsigned char	PIR2		@ 0x00D;
static volatile       unsigned char	TMR1L		@ 0x00E;
static volatile       unsigned char	TMR1H		@ 0x00F;
static                unsigned char	T1CON		@ 0x010;
static volatile       unsigned char	TMR2		@ 0x011;
static                unsigned char	T2CON		@ 0x012;
static volatile       unsigned char	SSPBUF		@ 0x013;
static volatile       unsigned char	SSPCON		@ 0x014;
static volatile       unsigned char	CCPR1L		@ 0x015;
static volatile       unsigned char	CCPR1H		@ 0x016;
static volatile       unsigned char	CCP1CON		@ 0x017;
static volatile       unsigned char	RCSTA		@ 0x018;
static volatile       unsigned char	TXREG		@ 0x019;
static volatile       unsigned char	RCREG		@ 0x01A;
static volatile       unsigned char	CCPR2L		@ 0x01B;
static volatile       unsigned char	CCPR2H		@ 0x01C;
static volatile       unsigned char	CCP2CON		@ 0x01D;
static volatile       unsigned char	ADRES		@ 0x01E;
static volatile       unsigned char	ADCON0		@ 0x01F;
static          bank1 unsigned char	OPTION		@ 0x081;
static volatile bank1 unsigned char	TRISA		@ 0x085;
static volatile bank1 unsigned char	TRISB		@ 0x086;
static volatile bank1 unsigned char	TRISC		@ 0x087;
#if defined(_16F724) || defined(_16F727) || defined(_16LF724) || defined(_16LF727)
static volatile bank1 unsigned char	TRISD		@ 0x088;
#endif
static volatile bank1 unsigned char	TRISE		@ 0x089;
static          bank1 unsigned char	PIE1		@ 0x08C;
static          bank1 unsigned char	PIE2		@ 0x08D;
static volatile bank1 unsigned char	PCON		@ 0x08E;
static volatile bank1 unsigned char	T1GCON		@ 0x08F;
static volatile bank1 unsigned char	OSCCON		@ 0x090;
static          bank1 unsigned char	OSCTUNE		@ 0x091;
static          bank1 unsigned char	PR2		@ 0x092;
static          bank1 unsigned char	SSPADD		@ 0x093;
// Alternate function
static          bank1 unsigned char	SSPMSK		@ 0x093;
static volatile bank1 unsigned char	SSPSTAT		@ 0x094;
static          bank1 unsigned char	WPUB		@ 0x095;
static          bank1 unsigned char	IOCB		@ 0x096;
static volatile bank1 unsigned char	TXSTA		@ 0x098;
static          bank1 unsigned char	SPBRG		@ 0x099;
static          bank1 unsigned char	APFCON		@ 0x09C;
static volatile bank1 unsigned char	FVRCON		@ 0x09D;
static          bank1 unsigned char	ADCON1		@ 0x09F;
static volatile bank2 unsigned char	CPSCON0		@ 0x108;
static          bank2 unsigned char	CPSCON1		@ 0x109;
static volatile bank2 unsigned char	PMDATL		@ 0x10C;
// Alternate definition
static volatile bank2 unsigned char	EEDATA		@ 0x10C;
static          bank2 unsigned char	PMADRL		@ 0x10D;
// Alternate definition
static          bank2 unsigned char	EEADR		@ 0x10D;
static volatile bank2 unsigned char	PMDATH		@ 0x10E;
// Alternate definition
static volatile bank2 unsigned char	EEDATH		@ 0x10E;
static          bank2 unsigned char	PMADRH		@ 0x10F;
// Alternate definition
static          bank2 unsigned char	EEADRH		@ 0x10F;
static          bank3 unsigned char	ANSELA		@ 0x185;
static          bank3 unsigned char	ANSELB		@ 0x186;
#if defined(_16F724) || defined(_16F727) || defined(_16LF724) || defined(_16LF727)
static          bank3 unsigned char	ANSELD		@ 0x188;
static          bank3 unsigned char	ANSELE		@ 0x189;
#endif
static volatile bank3 unsigned char	PMCON1		@ 0x18C;


/* Definitions for STATUS register */
static volatile       bit	CARRY		@ ((unsigned)&STATUS*8)+0;
static volatile       bit	DC		@ ((unsigned)&STATUS*8)+1;
static volatile       bit	ZERO		@ ((unsigned)&STATUS*8)+2;
static volatile       bit	PD		@ ((unsigned)&STATUS*8)+3;
static volatile       bit	TO		@ ((unsigned)&STATUS*8)+4;
static                bit	RP0		@ ((unsigned)&STATUS*8)+5;
static                bit	RP1		@ ((unsigned)&STATUS*8)+6;
static                bit	IRP		@ ((unsigned)&STATUS*8)+7;

/* Definitions for PORTA register */
static volatile       bit	RA0		@ ((unsigned)&PORTA*8)+0;
static volatile       bit	RA1		@ ((unsigned)&PORTA*8)+1;
static volatile       bit	RA2		@ ((unsigned)&PORTA*8)+2;
static volatile       bit	RA3		@ ((unsigned)&PORTA*8)+3;
static volatile       bit	RA4		@ ((unsigned)&PORTA*8)+4;
static volatile       bit	RA5		@ ((unsigned)&PORTA*8)+5;
static volatile       bit	RA6		@ ((unsigned)&PORTA*8)+6;
static volatile       bit	RA7		@ ((unsigned)&PORTA*8)+7;

/* Definitions for PORTB register */
static volatile       bit	RB0		@ ((unsigned)&PORTB*8)+0;
static volatile       bit	RB1		@ ((unsigned)&PORTB*8)+1;
static volatile       bit	RB2		@ ((unsigned)&PORTB*8)+2;
static volatile       bit	RB3		@ ((unsigned)&PORTB*8)+3;
static volatile       bit	RB4		@ ((unsigned)&PORTB*8)+4;
static volatile       bit	RB5		@ ((unsigned)&PORTB*8)+5;
static volatile       bit	RB6		@ ((unsigned)&PORTB*8)+6;
static volatile       bit	RB7		@ ((unsigned)&PORTB*8)+7;

/* Definitions for PORTC register */
static volatile       bit	RC0		@ ((unsigned)&PORTC*8)+0;
static volatile       bit	RC1		@ ((unsigned)&PORTC*8)+1;
static volatile       bit	RC2		@ ((unsigned)&PORTC*8)+2;
static volatile       bit	RC3		@ ((unsigned)&PORTC*8)+3;
static volatile       bit	RC4		@ ((unsigned)&PORTC*8)+4;
static volatile       bit	RC5		@ ((unsigned)&PORTC*8)+5;
static volatile       bit	RC6		@ ((unsigned)&PORTC*8)+6;
static volatile       bit	RC7		@ ((unsigned)&PORTC*8)+7;

#if defined(_16F724) || defined(_16F727) || defined(_16LF724) || defined(_16LF727)
/* Definitions for PORTD register */
static volatile       bit	RD0		@ ((unsigned)&PORTD*8)+0;
static volatile       bit	RD1		@ ((unsigned)&PORTD*8)+1;
static volatile       bit	RD2		@ ((unsigned)&PORTD*8)+2;
static volatile       bit	RD3		@ ((unsigned)&PORTD*8)+3;
static volatile       bit	RD4		@ ((unsigned)&PORTD*8)+4;
static volatile       bit	RD5		@ ((unsigned)&PORTD*8)+5;
static volatile       bit	RD6		@ ((unsigned)&PORTD*8)+6;
static volatile       bit	RD7		@ ((unsigned)&PORTD*8)+7;

/* Definitions for PORTE register */
static volatile       bit	RE0		@ ((unsigned)&PORTE*8)+0;
static volatile       bit	RE1		@ ((unsigned)&PORTE*8)+1;
static volatile       bit	RE2		@ ((unsigned)&PORTE*8)+2;
#endif
static volatile       bit	RE3		@ ((unsigned)&PORTE*8)+3;

/* Definitions for INTCON register */
static volatile       bit	RBIF		@ ((unsigned)&INTCON*8)+0;
// Alternate definition for backward compatibility
static volatile       bit	RABIF		@ ((unsigned)&INTCON*8)+0;
static volatile       bit	INTF		@ ((unsigned)&INTCON*8)+1;
static volatile       bit	T0IF		@ ((unsigned)&INTCON*8)+2;
static                bit	RBIE		@ ((unsigned)&INTCON*8)+3;
// Alternate definition for backward compatibility
static                bit	RABIE		@ ((unsigned)&INTCON*8)+3;
static                bit	INTE		@ ((unsigned)&INTCON*8)+4;
static                bit	T0IE		@ ((unsigned)&INTCON*8)+5;
static                bit	PEIE		@ ((unsigned)&INTCON*8)+6;
static                bit	GIE		@ ((unsigned)&INTCON*8)+7;

/* Definitions for PIR1 register */
static volatile       bit	TMR1IF		@ ((unsigned)&PIR1*8)+0;
static volatile       bit	TMR2IF		@ ((unsigned)&PIR1*8)+1;
static volatile       bit	CCP1IF		@ ((unsigned)&PIR1*8)+2;
static volatile       bit	SSPIF		@ ((unsigned)&PIR1*8)+3;
static volatile       bit	TXIF		@ ((unsigned)&PIR1*8)+4;
static volatile       bit	RCIF		@ ((unsigned)&PIR1*8)+5;
static volatile       bit	ADIF		@ ((unsigned)&PIR1*8)+6;
static volatile       bit	TMR1GIF		@ ((unsigned)&PIR1*8)+7;

/* Definitions for PIR2 register */
static volatile       bit	CCP2IF		@ ((unsigned)&PIR2*8)+0;

/* Definitions for T1CON register */
static                bit	TMR1ON		@ ((unsigned)&T1CON*8)+0;
static                bit	T1SYNC		@ ((unsigned)&T1CON*8)+1;
static                bit	T1OSCEN		@ ((unsigned)&T1CON*8)+2;
static                bit	T1CKPS0		@ ((unsigned)&T1CON*8)+3;
static                bit	T1CKPS1		@ ((unsigned)&T1CON*8)+4;
static                bit	TMR1CS0		@ ((unsigned)&T1CON*8)+5;
static                bit	TMR1CS1		@ ((unsigned)&T1CON*8)+6;

/* Definitions for T2CON register */
static                bit	T2CKPS0		@ ((unsigned)&T2CON*8)+0;
static                bit	T2CKPS1		@ ((unsigned)&T2CON*8)+1;
static                bit	TMR2ON		@ ((unsigned)&T2CON*8)+2;
static                bit	TOUTPS0		@ ((unsigned)&T2CON*8)+3;
static                bit	TOUTPS1		@ ((unsigned)&T2CON*8)+4;
static                bit	TOUTPS2		@ ((unsigned)&T2CON*8)+5;
static                bit	TOUTPS3		@ ((unsigned)&T2CON*8)+6;

/* Definitions for SSPCON register */
static                bit	SSPM0		@ ((unsigned)&SSPCON*8)+0;
static                bit	SSPM1		@ ((unsigned)&SSPCON*8)+1;
static                bit	SSPM2		@ ((unsigned)&SSPCON*8)+2;
static                bit	SSPM3		@ ((unsigned)&SSPCON*8)+3;
static                bit	CKP		@ ((unsigned)&SSPCON*8)+4;
static                bit	SSPEN		@ ((unsigned)&SSPCON*8)+5;
static volatile       bit	SSPOV		@ ((unsigned)&SSPCON*8)+6;
static volatile       bit	WCOL		@ ((unsigned)&SSPCON*8)+7;

/* Definitions for CCP1CON register */
static                bit	CCP1M0		@ ((unsigned)&CCP1CON*8)+0;
static                bit	CCP1M1		@ ((unsigned)&CCP1CON*8)+1;
static                bit	CCP1M2		@ ((unsigned)&CCP1CON*8)+2;
static                bit	CCP1M3		@ ((unsigned)&CCP1CON*8)+3;
static                bit	DC1B0		@ ((unsigned)&CCP1CON*8)+4;
static                bit	DC1B1		@ ((unsigned)&CCP1CON*8)+5;

/* Definitions for RCSTA register */
static volatile       bit	RX9D		@ ((unsigned)&RCSTA*8)+0;
static volatile       bit	OERR		@ ((unsigned)&RCSTA*8)+1;
static volatile       bit	FERR		@ ((unsigned)&RCSTA*8)+2;
static                bit	ADDEN		@ ((unsigned)&RCSTA*8)+3;
static                bit	CREN		@ ((unsigned)&RCSTA*8)+4;
static                bit	SREN		@ ((unsigned)&RCSTA*8)+5;
static                bit	RX9		@ ((unsigned)&RCSTA*8)+6;
static                bit	SPEN		@ ((unsigned)&RCSTA*8)+7;

/* Definitions for CCP2CON register */
static                bit	CCP2M0		@ ((unsigned)&CCP2CON*8)+0;
static                bit	CCP2M1		@ ((unsigned)&CCP2CON*8)+1;
static                bit	CCP2M2		@ ((unsigned)&CCP2CON*8)+2;
static                bit	CCP2M3		@ ((unsigned)&CCP2CON*8)+3;
static                bit	DC2B0		@ ((unsigned)&CCP2CON*8)+4;
static                bit	DC2B1		@ ((unsigned)&CCP2CON*8)+5;

/* Definitions for ADCON0 register */
static                bit	ADON		@ ((unsigned)&ADCON0*8)+0;
static				  bit	GODONE		@((unsigned)&ADCON0*8)+1;
static                bit	CHS0		@ ((unsigned)&ADCON0*8)+2;
static                bit	CHS1		@ ((unsigned)&ADCON0*8)+3;
static                bit	CHS2		@ ((unsigned)&ADCON0*8)+4;
static                bit	CHS3		@ ((unsigned)&ADCON0*8)+5;

/* Definitions for OPTION register */
static          bank1 bit	PS0		@ ((unsigned)&OPTION*8)+0;
static          bank1 bit	PS1		@ ((unsigned)&OPTION*8)+1;
static          bank1 bit	PS2		@ ((unsigned)&OPTION*8)+2;
static          bank1 bit	PSA		@ ((unsigned)&OPTION*8)+3;
static          bank1 bit	T0SE		@ ((unsigned)&OPTION*8)+4;
static          bank1 bit	T0CS		@ ((unsigned)&OPTION*8)+5;
static          bank1 bit	INTEDG		@ ((unsigned)&OPTION*8)+6;
static          bank1 bit	RBPU		@ ((unsigned)&OPTION*8)+7;
// Alternate definition for backward compatibility
static          bank1 bit	RABPU		@ ((unsigned)&OPTION*8)+7;

/* Definitions for TRISA register */
static          bank1 bit	TRISA0		@ ((unsigned)&TRISA*8)+0;
static          bank1 bit	TRISA1		@ ((unsigned)&TRISA*8)+1;
static          bank1 bit	TRISA2		@ ((unsigned)&TRISA*8)+2;
static          bank1 bit	TRISA3		@ ((unsigned)&TRISA*8)+3;
static          bank1 bit	TRISA4		@ ((unsigned)&TRISA*8)+4;
static          bank1 bit	TRISA5		@ ((unsigned)&TRISA*8)+5;
static          bank1 bit	TRISA6		@ ((unsigned)&TRISA*8)+6;
static          bank1 bit	TRISA7		@ ((unsigned)&TRISA*8)+7;

/* Definitions for TRISB register */
static volatile bank1 bit	TRISB0		@ ((unsigned)&TRISB*8)+0;
static volatile bank1 bit	TRISB1		@ ((unsigned)&TRISB*8)+1;
static volatile bank1 bit	TRISB2		@ ((unsigned)&TRISB*8)+2;
static volatile bank1 bit	TRISB3		@ ((unsigned)&TRISB*8)+3;
static volatile bank1 bit	TRISB4		@ ((unsigned)&TRISB*8)+4;
static volatile bank1 bit	TRISB5		@ ((unsigned)&TRISB*8)+5;
static volatile bank1 bit	TRISB6		@ ((unsigned)&TRISB*8)+6;
static volatile bank1 bit	TRISB7		@ ((unsigned)&TRISB*8)+7;

/* Definitions for TRISC register */
static volatile bank1 bit	TRISC0		@ ((unsigned)&TRISC*8)+0;
static volatile bank1 bit	TRISC1		@ ((unsigned)&TRISC*8)+1;
static volatile bank1 bit	TRISC2		@ ((unsigned)&TRISC*8)+2;
static volatile bank1 bit	TRISC3		@ ((unsigned)&TRISC*8)+3;
static volatile bank1 bit	TRISC4		@ ((unsigned)&TRISC*8)+4;
static volatile bank1 bit	TRISC5		@ ((unsigned)&TRISC*8)+5;
static volatile bank1 bit	TRISC6		@ ((unsigned)&TRISC*8)+6;
static volatile bank1 bit	TRISC7		@ ((unsigned)&TRISC*8)+7;

#if defined(_16F724) || defined(_16F727) || defined(_16LF724) || defined(_16LF727)
/* Definitions for TRISD register */
static volatile bank1 bit	TRISD0		@ ((unsigned)&TRISD*8)+0;
static volatile bank1 bit	TRISD1		@ ((unsigned)&TRISD*8)+1;
static volatile bank1 bit	TRISD2		@ ((unsigned)&TRISD*8)+2;
static volatile bank1 bit	TRISD3		@ ((unsigned)&TRISD*8)+3;
static volatile bank1 bit	TRISD4		@ ((unsigned)&TRISD*8)+4;
static volatile bank1 bit	TRISD5		@ ((unsigned)&TRISD*8)+5;
static volatile bank1 bit	TRISD6		@ ((unsigned)&TRISD*8)+6;
static volatile bank1 bit	TRISD7		@ ((unsigned)&TRISD*8)+7;

/* Definitions for TRISE register */
static volatile bank1 bit	TRISE0		@ ((unsigned)&TRISE*8)+0;
static volatile bank1 bit	TRISE1		@ ((unsigned)&TRISE*8)+1;
static volatile bank1 bit	TRISE2		@ ((unsigned)&TRISE*8)+2;
#endif
static volatile bank1 bit	TRISE3		@ ((unsigned)&TRISE*8)+3;

/* Definitions for PIE1 register */
static          bank1 bit	TMR1IE		@ ((unsigned)&PIE1*8)+0;
static          bank1 bit	TMR2IE		@ ((unsigned)&PIE1*8)+1;
static          bank1 bit	CCP1IE		@ ((unsigned)&PIE1*8)+2;
static          bank1 bit	SSPIE		@ ((unsigned)&PIE1*8)+3;
static          bank1 bit	TXIE		@ ((unsigned)&PIE1*8)+4;
static          bank1 bit	RCIE		@ ((unsigned)&PIE1*8)+5;
static          bank1 bit	ADIE		@ ((unsigned)&PIE1*8)+6;
static          bank1 bit	TMR1GIE		@ ((unsigned)&PIE1*8)+7;

/* Definitions for PIE2 register */
static          bank1 bit	CCP2IE		@ ((unsigned)&PIE2*8)+0;

/* Definitions for PCON register */
static volatile bank1 bit	BOR		@ ((unsigned)&PCON*8)+0;
static volatile bank1 bit	POR		@ ((unsigned)&PCON*8)+1;

/* Definitions for T1GCON register */
static          bank1 bit	T1GSS0		@ ((unsigned)&T1GCON*8)+0;
static          bank1 bit	T1GSS1		@ ((unsigned)&T1GCON*8)+1;
static volatile bank1 bit	T1GVAL		@ ((unsigned)&T1GCON*8)+2;
static volatile bank1 bit	T1GGO		@ ((unsigned)&T1GCON*8)+3;
static          bank1 bit	T1GSPM		@ ((unsigned)&T1GCON*8)+4;
static          bank1 bit	T1GTM		@ ((unsigned)&T1GCON*8)+5;
static          bank1 bit	T1GPOL		@ ((unsigned)&T1GCON*8)+6;
static          bank1 bit	TMR1GE		@ ((unsigned)&T1GCON*8)+7;

/* Definitions for OSCCON register */
static          bank1 bit	ICSS		@ ((unsigned)&OSCCON*8)+0;
static          bank1 bit	ICSL		@ ((unsigned)&OSCCON*8)+1;
static          bank1 bit	IRCF0		@ ((unsigned)&OSCCON*8)+2;
static          bank1 bit	IRCF1		@ ((unsigned)&OSCCON*8)+3;

/* Definitions for OSCTUNE register */
static          bank1 bit	TUN0		@ ((unsigned)&OSCTUNE*8)+0;
static          bank1 bit	TUN1		@ ((unsigned)&OSCTUNE*8)+1;
static          bank1 bit	TUN2		@ ((unsigned)&OSCTUNE*8)+2;
static          bank1 bit	TUN3		@ ((unsigned)&OSCTUNE*8)+3;
static          bank1 bit	TUN4		@ ((unsigned)&OSCTUNE*8)+4;
static          bank1 bit	TUN5		@ ((unsigned)&OSCTUNE*8)+5;

/* Definitions for SSPSTAT register */
static volatile bank1 bit	BF		@ ((unsigned)&SSPSTAT*8)+0;
static volatile bank1 bit	UA		@ ((unsigned)&SSPSTAT*8)+1;
static volatile bank1 bit	RW		@ ((unsigned)&SSPSTAT*8)+2;
static volatile bank1 bit	START		@ ((unsigned)&SSPSTAT*8)+3;
static volatile bank1 bit	STOP		@ ((unsigned)&SSPSTAT*8)+4;
static volatile bank1 bit	DA		@ ((unsigned)&SSPSTAT*8)+5;
static          bank1 bit	CKE		@ ((unsigned)&SSPSTAT*8)+6;
static          bank1 bit	SMP		@ ((unsigned)&SSPSTAT*8)+7;

/* Definitions for WPUB register */
static          bank1 bit	WPUB0		@ ((unsigned)&WPUB*8)+0;
static          bank1 bit	WPUB1		@ ((unsigned)&WPUB*8)+1;
static          bank1 bit	WPUB2		@ ((unsigned)&WPUB*8)+2;
static          bank1 bit	WPUB3		@ ((unsigned)&WPUB*8)+3;
static          bank1 bit	WPUB4		@ ((unsigned)&WPUB*8)+4;
static          bank1 bit	WPUB5		@ ((unsigned)&WPUB*8)+5;
static          bank1 bit	WPUB6		@ ((unsigned)&WPUB*8)+6;
static          bank1 bit	WPUB7		@ ((unsigned)&WPUB*8)+7;

/* Definitions for IOCB register */
static          bank1 bit	IOCB0		@ ((unsigned)&IOCB*8)+0;
static          bank1 bit	IOCB1		@ ((unsigned)&IOCB*8)+1;
static          bank1 bit	IOCB2		@ ((unsigned)&IOCB*8)+2;
static          bank1 bit	IOCB3		@ ((unsigned)&IOCB*8)+3;
static          bank1 bit	IOCB4		@ ((unsigned)&IOCB*8)+4;
static          bank1 bit	IOCB5		@ ((unsigned)&IOCB*8)+5;
static          bank1 bit	IOCB6		@ ((unsigned)&IOCB*8)+6;
static          bank1 bit	IOCB7		@ ((unsigned)&IOCB*8)+7;

/* Definitions for TXSTA register */
static volatile bank1 bit	TX9D		@ ((unsigned)&TXSTA*8)+0;
static volatile bank1 bit	TRMT		@ ((unsigned)&TXSTA*8)+1;
static          bank1 bit	BRGH		@ ((unsigned)&TXSTA*8)+2;
static          bank1 bit	SYNC		@ ((unsigned)&TXSTA*8)+3;
static          bank1 bit	TXEN		@ ((unsigned)&TXSTA*8)+4;
static          bank1 bit	TX9		@ ((unsigned)&TXSTA*8)+5;
static          bank1 bit	CSRC		@ ((unsigned)&TXSTA*8)+6;

/* Definitions for SPBRG register */
static          bank1 bit	BRG0		@ ((unsigned)&SPBRG*8)+0;
static          bank1 bit	BRG1		@ ((unsigned)&SPBRG*8)+1;
static          bank1 bit	BRG2		@ ((unsigned)&SPBRG*8)+2;
static          bank1 bit	BRG3		@ ((unsigned)&SPBRG*8)+3;
static          bank1 bit	BRG4		@ ((unsigned)&SPBRG*8)+4;
static          bank1 bit	BRG5		@ ((unsigned)&SPBRG*8)+5;
static          bank1 bit	BRG6		@ ((unsigned)&SPBRG*8)+6;
static          bank1 bit	BRG7		@ ((unsigned)&SPBRG*8)+7;

/* Definitions for APFCON register */
static          bank1 bit	CCP2SEL		@ ((unsigned)&APFCON*8)+0;
static          bank1 bit	SSSEL		@ ((unsigned)&APFCON*8)+1;

/* Definitions for FVRCON register */
static          bank1 bit	ADFVR0		@ ((unsigned)&FVRCON*8)+0;
static          bank1 bit	ADFVR1		@ ((unsigned)&FVRCON*8)+1;
static volatile bank1 bit	FVREN		@ ((unsigned)&FVRCON*8)+2;
static volatile bank1 bit	FVRRDY		@ ((unsigned)&FVRCON*8)+3;

/* Definitions for ADCON1 register */
static          bank1 bit	ADREF0		@ ((unsigned)&ADCON1*8)+0;
static          bank1 bit	ADREF1		@ ((unsigned)&ADCON1*8)+1;
static          bank1 bit	ADCS0		@ ((unsigned)&ADCON1*8)+2;
static          bank1 bit	ADCS1		@ ((unsigned)&ADCON1*8)+3;
static          bank1 bit	ADCS2		@ ((unsigned)&ADCON1*8)+4;

/* Definitions for CPSCON0 register */
static          bank2 bit	T0XCS		@ ((unsigned)&CPSCON0*8)+0;
static volatile bank2 bit	CPSOUT		@ ((unsigned)&CPSCON0*8)+1;
static          bank2 bit	CPSRNG0		@ ((unsigned)&CPSCON0*8)+2;
static          bank2 bit	CPSRNG1		@ ((unsigned)&CPSCON0*8)+3;
static          bank2 bit	CPSON		@ ((unsigned)&CPSCON0*8)+4;

/* Definitions for CPSCON1 register */
static          bank2 bit	CPSCH0		@ ((unsigned)&CPSCON1*8)+0;
static          bank2 bit	CPSCH1		@ ((unsigned)&CPSCON1*8)+1;
static          bank2 bit	CPSCH2		@ ((unsigned)&CPSCON1*8)+2;
static          bank2 bit	CPSCH3		@ ((unsigned)&CPSCON1*8)+3;

/* Definitions for ANSELA register */
static          bank3 bit	ANSA0		@ ((unsigned)&ANSELA*8)+0;
static          bank3 bit	ANSA1		@ ((unsigned)&ANSELA*8)+1;
static          bank3 bit	ANSA2		@ ((unsigned)&ANSELA*8)+2;
static          bank3 bit	ANSA3		@ ((unsigned)&ANSELA*8)+3;
static          bank3 bit	ANSA4		@ ((unsigned)&ANSELA*8)+4;
static          bank3 bit	ANSA5		@ ((unsigned)&ANSELA*8)+5;

/* Definitions for ANSELB register */
static          bank3 bit	ANSB0		@ ((unsigned)&ANSELB*8)+0;
static          bank3 bit	ANSB1		@ ((unsigned)&ANSELB*8)+1;
static          bank3 bit	ANSB2		@ ((unsigned)&ANSELB*8)+2;
static          bank3 bit	ANSB3		@ ((unsigned)&ANSELB*8)+3;
static          bank3 bit	ANSB4		@ ((unsigned)&ANSELB*8)+4;
static          bank3 bit	ANSB5		@ ((unsigned)&ANSELB*8)+5;

#if defined(_16F724) || defined(_16F727) || defined(_16LF724) || defined(_16LF727)
/* Definitions for ANSELD register */
static          bank3 bit	ANSD0		@ ((unsigned)&ANSELD*8)+0;
static          bank3 bit	ANSD1		@ ((unsigned)&ANSELD*8)+1;
static          bank3 bit	ANSD2		@ ((unsigned)&ANSELD*8)+2;
static          bank3 bit	ANSD3		@ ((unsigned)&ANSELD*8)+3;
static          bank3 bit	ANSD4		@ ((unsigned)&ANSELD*8)+4;
static          bank3 bit	ANSD5		@ ((unsigned)&ANSELD*8)+5;
static          bank3 bit	ANSD6		@ ((unsigned)&ANSELD*8)+6;
static          bank3 bit	ANSD7		@ ((unsigned)&ANSELD*8)+7;

/* Definitions for ANSELE register */
static          bank3 bit	ANSE0		@ ((unsigned)&ANSELE*8)+0;
static          bank3 bit	ANSE1		@ ((unsigned)&ANSELE*8)+1;
static          bank3 bit	ANSE2		@ ((unsigned)&ANSELE*8)+2;
#endif

/* Definitions for PMCON1 register */
static volatile bank3 bit	RD		@ ((unsigned)&PMCON1*8)+0;

// Configuration Mask Definitions
#define CONFIG_ADDR	0x2007
// Oscillator configurations 
#define RCCLKO		0x3FFF
#define RCIO		0x3FFE
#define INTCLKO		0x3FFD
#define INTIO		0x3FFC
#define EC		0x3FFB
#define HS		0x3FFA
#define XT		0x3FF9
#define LP		0x3FF8
// Watchdog timer enable 
#define WDTEN		0x3FFF
#define WDTDIS		0x3FF7
// Power up timer enable 
#define PWRTEN		0x3FEF
#define PWRTDIS		0x3FFF
// MCLR pin function 
#define MCLREN		0x3FFF
#define MCLRDIS		0x3FDF
// Protection of flash memory 
#define PROTECT		0x3FBF
#define UNPROTECT	0x3FFF
// Brown out reset enable 
#define BOREN		0x3FFF
#define BOREN_XSLP	0x3EFF
#define BORDIS		0x3CFF
// Brown out reset voltage 
#define BORV25		0x3BFF
#define BORV19		0x3FFF
// INTOSC PLL enable 
#define PLLEN		0x3FFF
#define PLLDIS		0x2FFF
// Debugger enable 
#define DEBUGEN		0x1FFF
#define DEBUGDIS	0x3FFF
#define CONFIG_ADDR2	0x2008
// Voltage regulator capacitor enable - this setting ignored in 16LF devices
#define VCAPRA0		0x3FCF
#define VCAPRA5		0x3FDF
#define VCAPRA6		0x3FEF
#define VCAPDIS		0x3FFF

#endif
