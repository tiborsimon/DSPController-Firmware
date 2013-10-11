/*
 * input.c
 *
 * Created: 10/10/2013 10:11:29 AM
 *  Author: Tibor
 */ 

#include "input.h"

void input_init() {
	uint8_t i = 31;
	
	do {
		debounce[i] = 0;
		button_status[i] = 0;
	} while (i--);
}



ISR(TIMER0_COMPA_vect) {
	
	uint8_t i = 7;
	uint8_t p = 0;
	
	// Toggle SS pin for debug ONLY
	high(PORTB,PB2);
	// toggle(PINB,PB2);
	
	// start debounce algorithm
	// LOG("most\n");
	
	// load current button states to shift registers
	negativePulse(IN_LOAD);
	
	// read in button states to debounce registers
	do {
		debounce[p] = (debounce[p] << 1) | readValue(IN_1); p++;
		debounce[p] = (debounce[p] << 1) | readValue(IN_2); p++;
		debounce[p] = (debounce[p] << 1) | readValue(IN_3); p++;
		debounce[p] = (debounce[p] << 1) | readValue(IN_4); p++;
		pulse(IO_CLK);
	} while (i--);
	
	// adjust p pointer
	p--;
	
	// run debounce algorithm
	do {
		
		if ((debounce[p] & DEBOUNCE_MASK) == 0) {
			
			// PREV = 1 ==> falling edge
			if ((button_status[p] & PREVIOUS_MASK) != 0) {
				
				LOG("%d falling : %x\n", p, (button_status[p]>>12)&0x3);
				
				// clear actual and previous states
				button_status[p] &= PREVIOUS_CLEAR & ACTUAL_CLEAR;
				
				// counter is less than the threshold, and no short or long press was administrated
				if (((button_status[p] & COUNTER_MASK) < COUNTER_THRESHOLD) &
					((button_status[p] & SHORT_MASK) == 0) &
					((button_status[p] & LONG_MASK) == 0) ) {
						// short press
						button_status[p] |= SHORT_SET;
						LOG("%d short\n", p);
				}
				
				// clear counter
				button_status[p] &= COUNTER_CLEAR;
			}
			continue;
		}
		
		if ((debounce[p] & DEBOUNCE_MASK) == DEBOUNCE_MASK ) {
			
			// PREV = 0 ==> rising edge
			if ((button_status[p] & PREVIOUS_MASK) == 0) {
				
				LOG("%d rising : %x\n", p, (button_status[p]>>12)&0x3);
				
				// clear actual and previous states
				button_status[p] |= PREVIOUS_SET | ACTUAL_SET;
				
				continue;
			}
			
			if (((button_status[p] & LONG_MASK) == 0) &
				((button_status[p] & SHORT_MASK) == 0)) {
				
				// increment the counter
				button_status[p]++;
				// LOG("%d counter: %d\n", p, (button_status[p] & COUNTER_MASK));
				
				if ((button_status[p] & COUNTER_MASK) >= COUNTER_THRESHOLD) {
					// threshold reached = long press
					button_status[p] |= LONG_SET;
					LOG("%d long\n", p);
				}
			}
			
		}
		
	} while (p--);
	
	
	
	// debug ISR execution time
	low(PORTB,PB2);
	
	
}