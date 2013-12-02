/**
 * \addtogroup outputs
 * \{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */

#include "shift.h"

void shiftOutMsbFirst(uint8_t data) {
	uint8_t i = 7;
	uint8_t s = 0;
	do {
		((data<<s)&0x80) ? setHigh(OUT) : setLow(OUT);
		pulse(IO_CLK);
		s++;
	} while (i--);
}

void shiftOutLsbFirst(uint8_t data) {
	uint8_t i = 7;
	uint8_t s = 0;
	do {
		((data>>s)&0x01) ? setHigh(OUT) : setLow(OUT);
		pulse(IO_CLK);
		s++;
	} while (i--);
}

/** \} */
