#ifndef _HAL_H_
#define _HAL_H_

#include "includes.h"

/*==========================================================
  H A R D W A R E   A B S T R A C T I O N   L A Y E R
===========================================================*/

// SHIFT REGISTERS
#define IO_CLK_DDR 		DDRC
#define IO_CLK_PORT		PORTC
#define IO_CLK_PIN 		PC0

#define OUT_LATCH_DDR 	DDRC
#define OUT_LATCH_PORT	PORTC
#define OUT_LATCH_PIN 	PC1

#define IN_LOAD_DDR 	DDRC
#define IN_LOAD_PORT	PORTC
#define IN_LOAD_PIN 	PC2

#define OUT_DDR 		DDRC
#define OUT_PORT		PORTC
#define OUT_PIN 		PC3

#define IN_1_DDR 		DDRC
#define IN_1_PORT		PORTC
#define IN_1_PIN 		PC4

#define IN_2_DDR 		DDRC
#define IN_2_PORT		PORTC
#define IN_2_PIN 		PC5

#define IN_3_DDR 		DDRB
#define IN_3_PORT		PORTB
#define IN_3_PIN 		PB0

#define IN_4_DDR 		DDRB
#define IN_4_PORT		PORTB
#define IN_4_PIN 		PB1


// ENCODERS
#define E1_A_DDR 		DDRD
#define E1_A_PORT		PORTD
#define E1_A_PIN 		PD3

#define E1_B_DDR 		DDRD
#define E1_B_PORT		PORTD
#define E1_B_PIN 		PD2

#define E2_A_DDR 		DDRD
#define E2_A_PORT		PORTD
#define E2_A_PIN 		PD5

#define E2_B_DDR 		DDRD
#define E2_B_PORT		PORTD
#define E2_B_PIN 		PD4

#define E3_A_DDR 		DDRD
#define E3_A_PORT		PORTD
#define E3_A_PIN 		PD6

#define E3_B_DDR 		DDRD
#define E3_B_PORT		PORTD
#define E3_B_PIN 		PD7


// INPUTS
// INPUT SHIFT REG 1
#define IN_1_A	0x01
#define IN_1_B	0x02
#define IN_1_C	0x04
#define IN_1_D	0x08
#define IN_1_E	0x10
#define IN_1_F	0x20
#define IN_1_G	0x40
#define IN_1_H	0x80

// INPUT SHIFT REG 2
#define IN_2_A	0x01
#define IN_2_B	0x02
#define IN_2_C	0x04
#define IN_2_D	0x08
#define IN_2_E	0x10
#define IN_2_F	0x20
#define IN_2_G	0x40
#define IN_2_H	0x80

// INPUT SHIFT REG 3
#define IN_3_A	0x01
#define IN_3_B	0x02
#define IN_3_C	0x04
#define IN_3_D	0x08
#define IN_3_E	0x10
#define IN_3_F	0x20
#define IN_3_G	0x40
#define IN_3_H	0x80

// INPUT SHIFT REG 4
#define IN_4_A	0x01
#define IN_4_B	0x02
#define IN_4_C	0x04
#define IN_4_D	0x08
#define IN_4_E	0x10
#define IN_4_F	0x20
#define IN_4_G	0x40
#define IN_4_H	0x80

// DIP SWITCH
#define DIP_1	IN_1_A
#define DIP_2	IN_1_B
#define DIP_3	IN_1_C
#define DIP_4	IN_1_D
#define DIP_5	IN_1_E
#define DIP_6	IN_1_F
#define DIP_7	IN_1_G
#define DIP_8	IN_1_H

// ENCODER BUTTONS
#define	E1 		IN_2_A
#define	E2 		IN_2_B
#define	E3 		IN_2_C

// FUNCTION BUTTONS
#define	F1 		IN_2_D
#define	F2 		IN_2_E
#define	F3 		IN_2_F
#define	F4 		IN_2_G

// ARROW BUTTONS
#define	A1 		IN_3_D
#define	A2 		IN_2_H
#define	A3 		IN_3_B
#define	A4 		IN_3_C
#define	A5 		IN_3_A

// NUMPAD
#define	N1 		IN_4_A
#define	N2 		IN_4_B
#define	N3 		IN_4_C
#define	N4 		IN_4_D
#define	N5 		IN_4_E
#define	N6 		IN_4_F
#define	N7 		IN_4_G
#define	N8 		IN_4_H
#define	N9 		IN_3_H
#define	N10 	IN_3_E
#define	N11 	IN_3_F
#define	N12 	IN_3_G


// MACROS
#define setOutput(ddr, pin) ((ddr) |= (1 << (pin)))
#define setInput(ddr, pin)	((ddr) &= ~(1 << (pin)))
#define setInputWithPullup(ddr, port, pin)	do { \
												(ddr) &= ~(1 << (pin)); \
												(port) |= (1 << (pin)); \
											} while (0)
#define setLow(port, pin) 	((port) &=  ~(1 << (pin)))
#define setHigh(port, pin) 	((port) |= (1 << (pin)))
#define pulse(port, pin) 	do { \
								setHigh((port), (pin)); \
                            	setLow((port), (pin)); \
                         	} while (0)
							 
#define negativePulse(port, pin) 	do { \
								setLow((port), (pin)); \
								setHigh((port), (pin)); \
							} while (0)
							 
#define setLed(L, R) 	do { \
							_led_l = L; \
							_led_r = R; \
						} while (0)

#endif // #ifndef _HAL_H_