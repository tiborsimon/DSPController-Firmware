/*
 * input.h
 *
 * Created: 10/10/2013 10:11:16 AM
 *  Author: Tibor
 */ 


#ifndef INPUT_H_
#define INPUT_H_

#include "includes.h"

#define DEBOUNCE_MASK	0x0f

#define PREVIOUS_MASK	0x8000
#define PREVIOUS_SET	PREVIOUS_MASK
#define PREVIOUS_CLEAR	0x7fff

#define ACTUAL_MASK		0x4000
#define ACTUAL_SET		ACTUAL_MASK
#define ACTUAL_CLEAR	0xbfff

#define SHORT_MASK		0x2000
#define SHORT_SET		SHORT_MASK
#define SHORT_CLEAR		0xdfff

#define LONG_MASK		0x1000
#define LONG_SET		LONG_MASK
#define LONG_CLEAR		0xefff

#define COUNTER_MASK	0x0fff
#define COUNTER_CLEAR	0xf000
#define COUNTER_THRESHOLD 1000

extern volatile uint8_t debounce[32];

/**
 * Button's status
 *  | 15             | 14           | 13          | 12         | 11 : 0             |
 *  | previous state | actual state | short press | long press | long press counter |
 */
extern volatile uint16_t button_status[32];

void input_init();





#endif /* INPUT_H_ */