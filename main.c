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
	setOutput(IO_CLK_DDR, IO_CLK_PIN);
	setOutput(OUT_LATCH_DDR, OUT_LATCH_PIN);
	setOutput(IN_LOAD_DDR, IN_LOAD_PIN);
	setOutput(OUT_DDR, OUT_PIN);
	
	setInput(IN_1_DDR, IN_1_PIN);
	setInput(IN_2_DDR, IN_2_PIN);
	setInput(IN_3_DDR, IN_3_PIN);
	setInput(IN_4_DDR, IN_4_PIN);
	
	// encoders
	setInputWithPullup(E1_A_DDR, E1_A_PORT, E1_A_PIN);
	setInputWithPullup(E2_A_DDR, E2_A_PORT, E2_A_PIN);
	setInputWithPullup(E3_A_DDR, E3_A_PORT, E3_A_PIN);
	
	setInputWithPullup(E1_B_DDR, E1_B_PORT, E1_B_PIN);
	setInputWithPullup(E2_B_DDR, E2_B_PORT, E2_B_PIN);
	setInputWithPullup(E3_B_DDR, E3_B_PORT, E3_B_PIN);
	
	/*=======================================================================
	  SS PIN FOR DEBUG
	=======================================================================*/
	setOutput(DDRB,PB2);
}

void timer_init() {
	// init timer
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
	setHigh(PORTB,PB2);
	setLow(PORTB,PB2);
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