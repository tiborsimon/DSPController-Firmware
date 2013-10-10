/*
 * input.h
 *
 * Created: 10/10/2013 10:11:16 AM
 *  Author: Tibor
 */ 


#ifndef INPUT_H_
#define INPUT_H_

#include "includes.h"

#define DEBOUNCE_MASK	0xffff

extern volatile uint16_t debounce[32];
extern volatile uint16_t button_status[32];

void input_init();





#endif /* INPUT_H_ */