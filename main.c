/*
 * DSPControllerB.c
 *
 * Created: 10/5/2013 12:29:35 AM
 *  Author: Tibor
 */ 


#include "includes.h"


/*================================================================
  D E C L A R E   G L O B A L   V A R I A B L E S
================================================================*/

// LED BARS
volatile uint8_t _led_l = 0;
volatile uint8_t _led_r = 0;

// INPUT LIBRARY
volatile uint8_t debounce[32];
volatile uint16_t button_status[32];


uint8_t reverseByte( uint8_t x ) {
	x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
	x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
	x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
	return x;
}

void io_init( void ) {
	// shift registers
	setOutput(IO_CLK);
	setOutput(OUT_LATCH);
	setOutput(IN_LOAD);
	setOutput(OUT);
	
	setInput(IN_1);
	setInput(IN_2);
	setInput(IN_3);
	setInput(IN_4);
	
	// encoders
	setInputWPullup(E1_A);
	setInputWPullup(E2_A);
	setInputWPullup(E3_A);
	
	setInputWPullup(E1_B);
	setInputWPullup(E2_B);
	setInputWPullup(E3_B);
	
	/*===========================================================
	  S S   F O R   D E B U G
	===========================================================*/
	
	output(DDRB,PB2);
	
	
	/*===========================================================
	  S E T   D E F A U L T   S T A T E S
	===========================================================*/
	
	setHigh(IN_LOAD);
}

void timer_init() {
	// Triggers an interrupt in each 0.5 miliseconds.
	// enable Timer/Counter0 Output Compare Match A Interrupt
	TIMSK0 = (1<<OCIE0A);
	
	// set CTC mode
	TCCR0A = (1<<WGM01) | (0<<WGM00);
	
	// prescaler: 64, CTC 125 = 0.5ms interrupts
	OCR0A = 125;
	
	// set prescaler to 64
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);  // div 64
	// TCCR0B = (1<<CS02) | (0<<CS01) | (1<<CS00); // div 1024
}



int main(void) {
	
	char s[16];
	
	int i = 0;

	io_init();
	input_init();
	lcd_init();
	timer_init();
	usart_logger_init();
	
	sei();
	
	setLed(0x0f,0xf0);
	
	while(1) {
		
		for (i=0;i<32;i++) {
			if ((button_status[i] & SHORT_MASK) != 0 ) {
				cli();
				button_status[i] &= SHORT_CLEAR;
				sei();
				
				sprintf(s,"%d: SHORT    ",i);
				lcd_home();
				lcd_writeString(s);
			}
			
			if ((button_status[i] & LONG_MASK) != 0 ) {
				cli();
				button_status[i] &= LONG_CLEAR;
				sei();
				
				sprintf(s,"%d: LONG    ",i);
				lcd_home();
				lcd_writeString(s);
			}
			
		}
		
		/*
		sprintf(s,"Dori: %d",i);
		lcd_home();
		
		if (i%2 == 0) {
			lcd_newLine();
		}
		
		lcd_writeString(s);
		
		i++;
		
		_led_r++;
		_led_l--;
		
		_delay_ms(300);
		*/
	}
	
	return 0;
}