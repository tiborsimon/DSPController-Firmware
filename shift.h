/*
 * shift.h
 *
 * Created: 10/8/2013 7:17:05 PM
 *  Author: Tibor
 */ 


#ifndef SHIFT_H_
#define SHIFT_H_

#include "includes.h"

#define OUT_LATCH pulse(OUT_LATCH_PORT,OUT_LATCH_PIN)

void shiftOutMsbFirst(uint8_t data);
void shiftOutLsbFirst(uint8_t data);



#endif /* SHIFT_H_ */