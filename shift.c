/*
 * shift.c
 *
 * Created: 10/8/2013 7:17:21 PM
 *  Author: Tibor
 */ 

#include "shift.h"

void shiftOutMsbFirst(uint8_t data) {
	uint8_t i = 7;
	uint8_t s = 0;
	do {
		((data<<s)&0x80) ? setHigh(OUT_PORT, OUT_PIN) : setLow(OUT_PORT, OUT_PIN);
		pulse(IO_CLK_PORT,IO_CLK_PIN);
		s++;
	} while (i--);
}

void shiftOutLsbFirst(uint8_t data) {
	uint8_t i = 7;
	uint8_t s = 0;
	do {
		((data>>s)&0x01) ? setHigh(OUT_PORT, OUT_PIN) : setLow(OUT_PORT, OUT_PIN);
		pulse(IO_CLK_PORT,IO_CLK_PIN);
		s++;
	} while (i--);
}