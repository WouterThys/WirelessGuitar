
	; HI-TECH C Compiler for PIC10/12/16 MCUs V9.82
	; Copyright (C) 1984-2011 HI-TECH Software
	;Licensed for evaluation purposes only.
	;This licence will expire on Fri, 07 Oct 2011

	; Auto-generated runtime startup code for final link stage.

	;
	; Compiler options:
	;
	; -o1ch_RX_USB_684_V1.cof -m1ch_RX_USB_684_V1.map \
	; --summary=default,-psect,-class,+mem,-hex --output=default,-inhx032 \
	; 1ch_RX_684_USB_V1.p1 Nordic_i2c.p1 nordicmanager.p1 --chip=16F684 -P \
	; --runtime=default,+init,+osccal,+oscval:0,-download,-resetbits,-stackcall,+clib \
	; --opt=default,+asm,-debug,-speed,+space,9 --warn=0 --double=24 \
	; --float=24 --addrqual=request -g --asmlist \
	; --errformat=Error   [%n] %f; %l.%c %s --msgformat=Advisory[%n] %s \
	; --warnformat=Warning [%n] %f; %l.%c %s
	;


	processor	16F684

	global	_main,start,_exit,reset_vec
	fnroot	_main
	psect	config,class=CONFIG,delta=2
	psect	idloc,class=IDLOC,delta=2
	psect	code,class=CODE,delta=2
	psect	powerup,class=CODE,delta=2
	psect	reset_vec,class=CODE,delta=2
	psect	maintext,class=CODE,delta=2
	C	set	0
	Z	set	2
	PCL	set	2
	INDF	set	0

	STATUS	equ	3
	PCLATH	equ	0Ah

	psect	eeprom_data,class=EEDATA,delta=2,space=2
	psect	intentry,class=CODE,delta=2
	psect	functab,class=CODE,delta=2
	global	intlevel0,intlevel1,intlevel2, intlevel3, intlevel4, intlevel5
intlevel0:
intlevel1:
intlevel2:
intlevel3:
intlevel4:
intlevel5:
	psect	init,class=CODE,delta=2
	psect	cinit,class=CODE,delta=2
	psect	text,class=CODE,delta=2
	psect	end_init,class=CODE,delta=2
	psect	clrtext,class=CODE,delta=2
	FSR	set	4
	psect	strings,class=CODE,delta=2,reloc=256

	psect	reset_vec
reset_vec:
	; No powerup routine
	; No interrupt routine


	psect	init
start
_exit
	psect	end_init
	global start_initialization
	ljmp start_initialization	;jump to C runtime clear & initialization

psect bank0,class=BANK0,space=1
psect bank1,class=BANK1,space=1
psect ram,class=RAM,space=1
psect abs1,class=ABS1,space=1
psect common,class=COMMON,space=1
psect sfr0,class=SFR0,space=1
psect sfr1,class=SFR1,space=1


	end	start
