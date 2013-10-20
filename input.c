/*
 * input.c
 * \addtogroup inputs
 * \{
 * Created: 10/10/2013 10:11:29 AM
 *  Author: Tibor
 */ 

#include "input.h"

void input_init() {
	uint8_t i = 31;
	
	// zero out the button registers
	do {
		debounce[i] = 0;
		button_status[i] = 0;
	} while (i--);
	
	// zero out encoder debounce register 
	// set encoder status registers: 
	//		index 0, 2, 4 will be masters -> A signals
	//		all previous and actual value is 1 to prevent false triggering at boot time
	i=5;
	do {
		encoder_debounce[i] = 0;
		encoder_status[i] = i%2 ? 0xc0 : 0xe0;
	} while (i--);
	
	// zero out the encoder counters
	encoder_counter[0] = 0;
	encoder_counter[1] = 0;
	encoder_counter[2] = 0;
}

/**
 * This ISR is provided the Timer Tick event that schedules the debouncing and processing jobs.
 */
ISR(TIMER0_COMPA_vect) {
	
	uint8_t i = 7;
	uint8_t p = 0;
	
	static uint8_t blocker = 0;
	
	sei();
	
	// Toggle SS pin for debug ONLY
	// high(PORTB,PB2);
	// toggle(PINB,PB2);
	
	if (blocker++ >= 1) {
		blocker = 0;
	} else {
		
		// ==============================================================
		//   B U T T O N    D E B O U N C E
		// ==============================================================
				
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
					
					/////////////////////////////////////////////////
					spi_add_up(p);
					/////////////////////////////////////////////////
					
					// clear actual and previous states
					button_status[p] &= PREVIOUS_CLEAR & ACTUAL_CLEAR;
					
					// counter is less than the threshold, and no short or long press was administrated
					if (((button_status[p] & COUNTER_MASK) < COUNTER_THRESHOLD) &
						((button_status[p] & SHORT_MASK) == 0) &
						((button_status[p] & LONG_MASK) == 0) ) {
						// short press
						// button_status[p] |= SHORT_SET;
						
						/////////////////////////////////////////////////
						spi_add_short_press(p);
						/////////////////////////////////////////////////
					}
					
					// clear counter & clear lock
					button_status[p] &= COUNTER_CLEAR & LOCK_CLEAR;
				}
				continue;
			}
			
			if ((debounce[p] & DEBOUNCE_MASK) == DEBOUNCE_MASK ) {
				
				// PREV = 0 ==> rising edge
				if ((button_status[p] & PREVIOUS_MASK) == 0) {
					
					/////////////////////////////////////////////////
					spi_add_down(p);
					/////////////////////////////////////////////////
					
					// clear actual and previous states
					button_status[p] |= PREVIOUS_SET | ACTUAL_SET;
					continue;
				}
				
				// no long or short press, and long press isn't locked
				if (((button_status[p] & LONG_MASK) == 0) &
					((button_status[p] & SHORT_MASK) == 0) &
					((button_status[p] & LOCK_MASK) == 0)) {
						
					// increment the counter
					button_status[p]++;
					
					if ((button_status[p] & COUNTER_MASK) >= COUNTER_THRESHOLD) {
						// threshold reached = long press :: lock
						// button_status[p] |= LONG_SET | LOCK_SET;
						button_status[p] |= LOCK_SET;
						
						/////////////////////////////////////////////////
						spi_add_long_press(p);
						/////////////////////////////////////////////////
					}
				}
			}
		} while (p--);
		
	}
	
	// ==============================================================
	//   E N C O D E R    D E B O U N C E
	// ==============================================================
	
	// read values in
	encoder_debounce[0] = (encoder_debounce[0] << 1) | readValue(E1_A);
	encoder_debounce[1] = (encoder_debounce[1] << 1) | readValue(E1_B);
	
	encoder_debounce[2] = (encoder_debounce[2] << 1) | readValue(E2_A);
	encoder_debounce[3] = (encoder_debounce[3] << 1) | readValue(E2_B);
	
	encoder_debounce[4] = (encoder_debounce[4] << 1) | readValue(E3_A);
	encoder_debounce[5] = (encoder_debounce[5] << 1) | readValue(E3_B);
	
	// process edges
	i = 5;
	
	do {
		// low level reached
		if ((encoder_debounce[i] & E_DEBOUNCE_MASK) == 0) {
			// store actual value
			uint8_t temp = encoder_status[i] & E_ACTUAL_MASK;
			// clear previous and actual value
			encoder_status[i] &= E_PREVIOUS_CLEAR & E_ACTUAL_CLEAR; // + clearing the actual bit
			// store actual value to previous
			encoder_status[i] |= temp<<1;
		}
		
		// high level reached
		if ((encoder_debounce[i] & E_DEBOUNCE_MASK) == E_DEBOUNCE_MASK) {
			// store actual value
			uint8_t temp = encoder_status[i] & E_ACTUAL_MASK;
			// clear previous and actual value
			encoder_status[i] &= E_PREVIOUS_CLEAR;  // not clearing the actual bit, because we will or it with one
			// store actual value to previous
			encoder_status[i] |= (temp<<1) | E_ACTUAL_SET;  // setting the actual bit to one
		}
		
		// if current pin is master, process the edges
		if ((encoder_status[i] & E_MASTER_MASK) != 0) {
			
			// P=1 and A=0 == falling edge
			if ( (encoder_status[i] & (E_ACTUAL_MASK | E_PREVIOUS_MASK) ) == 0x40 ) {
								
				if ((encoder_status[i+1] & E_ACTUAL_MASK) == 0) {
					// turn left
					encoder_counter[i>>1]++;
				} else {
					// turn right
					encoder_counter[i>>1]--;
				}
				
				/////////////////////////////////////////////
				spi_add_encoder(i);
				/////////////////////////////////////////////
				
			}
		}
		
	} while (i--);
	
	// debug ISR execution time
	// low(PORTB,PB2);
}

/**
 * \addtogroup buttons
 * \{
 */
/*
uint8_t get_button_event( uint8_t p ) {
	
	// check for long press
	if ((button_status[p] & LONG_MASK) != 0 ) {
		cli();
		button_status[p] &= LONG_CLEAR;
		sei();
		return EVENT_LONG_PRESS;
	}
	
	// check for short press
	if ((button_status[p] & SHORT_MASK) != 0 ) {
		cli();
		button_status[p] &= SHORT_CLEAR;
		sei();
		return EVENT_SHORT_PRESS;
	}
	
	return EVENT_NOTHING;
}
*/
/** \} */

/**
 * \addtogroup encoders
 * \{
 */
int8_t get_encoder_value( uint8_t p ) {
	
	if (encoder_counter[p] != 0) {
		int8_t ret = encoder_counter[p];
		cli();
		encoder_counter[p] = 0;
		sei();
		return ret;
	}
	return 0;
}
/** \} */


/** \} */