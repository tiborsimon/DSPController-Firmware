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
	
	uint8_t static debug = 0;
	
	uint8_t i = 7;
	uint8_t p = 0;
	
	if (debug++ < 50) {
		// return;
	}
	
	debug = 0;
	
	// Toggle SS pin for debug ONLY
	// high(PORTB,PB2);
	toggle(PINB,PB2);
	
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
		
		/*
		char k = 19;
		if (p==k) LOG("%d %x\n",p,debounce[p]);
		k += 4;
		if (p==k) LOG("%d %x\n",p,debounce[p]);
		k += 4;
		if (p==k) LOG("%d %x\n",p,debounce[p]);
		k += 4;
		if (p==k) LOG("%d %x\n",p,debounce[p]);
		k += 4;
		*/
		
		if ( (debounce[p] & DEBOUNCE_MASK) == DEBOUNCE_MASK  ) {
			// high(PORTB,PB2);
		} else {
			// low(PORTB,PB2);
		}
		
	} while (p--);
	
	
	
	// debug ISR execution time
	// low(PORTB,PB2);
	
	
}