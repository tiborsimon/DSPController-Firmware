/*
 * DSPControllerB.c
 *
 * Created: 10/5/2013 12:29:35 AM
 *  Author: Tibor
 */ 


#include "includes.h"

volatile uint8_t _led_l = 0;
volatile uint8_t _led_r = 0;



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
	  S E T   D E F A U L T   S T A  T E S
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
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);
}


ISR(TIMER0_COMPA_vect) {
	// Toggle SS pin
	PINB |= (1<<PB2);
	
	
}



int main(void) {
	
	char s[16];
	
	int i = 0;

	usart_logger_init();
	io_init();
	lcd_init();
	
	timer_init();
	
	sei();
	
	setLed(0x0f,0xf0);
	
	while(1) {
		
		sprintf(s,"dori: %d",i);
		lcd_home();
		
		if (i%2 == 0) {
			lcd_newLine();
		}
		
		lcd_writeString(s);
		
		
		
		i++;
		
		_led_r++;
		_led_l--;
		
		_delay_ms(300);
		
		/*
		if (++i>19) {
			i = 0;
		}
		*/
		
		LOG("%d\n",i);
	}
	
	return 0;
}