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

// INPUT LIBRARY VARIABLES
volatile uint8_t debounce[32];
volatile uint16_t button_status[32];

volatile uint8_t encoder_debounce[6];
volatile int8_t encoder_counter[3];
volatile int8_t encoder_status[6];

volatile uint8_t status[16];
volatile uint8_t status_ready;

// SPI VARIABLES
volatile uint8_t spi_state;
volatile uint8_t spi_pointer;
volatile uint8_t spi_transmit_buffer[16];


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
	  S E T   D E F A U L T   S T A T E S
	===========================================================*/
	
	setHigh(IN_LOAD);
}

/**
 * Init Timer0 to Output Compare Match A Interrupt @ 0.5 ms.
 */
void timer_init() {
	// Triggers an interrupt in each 0.5 miliseconds.
	// enable Timer/Counter0 Output Compare Match A Interrupt
	TIMSK0 = (1<<OCIE0A);
	
	// set CTC mode
	TCCR0A = (1<<WGM01) | (0<<WGM00);
	
	// prescaler: 64, CTC 125 = 0.5ms interrupts
	OCR0A = 125; // 0.5ms @ div64
	// OCR0A = 250; // 1ms @ div64
	
	// set prescaler to 64
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);  // div 64
	// TCCR0B = (1<<CS02) | (0<<CS01) | (1<<CS00); // div 1024
}

void print_prev(uint8_t p, uint8_t prev) {
	char s[16];
	
	if (prev == 1) {
		sprintf(s,"%d: LONG       ",p);
		lcd_newLine();
		lcd_writeString(s);
	}
	
	if (prev == 2) {
		sprintf(s,"%d: SHORT       ",p);
		lcd_newLine();
		lcd_writeString(s);
	}
	
}



int main(void) {
	
	char s[16];
	
	int i = 0;
	
	// uint8_t p_prev = 0;
	// uint8_t press_prev = 0;
	

	io_init();
	input_init();
	lcd_init();
	timer_init();
	usart_logger_init();
	spi_init();
	
	sei();
	
	setLed(0x01,0x01);
	
	sprintf(s," DSP Controller");
	lcd_writeString(s);
	lcd_newLine();
	sprintf(s,"    demo app");
	lcd_writeString(s);
	
	while(1) {
		
		/*
		// loop through the buttons and ask for events
		for (i=0;i<32;i++) {
			
			uint8_t button_event = get_button_event(i);
			
			if ( button_event == EVENT_SHORT_PRESS ) {
				
				sprintf(s,"%d: SHORT       ",i);
				lcd_home();
				lcd_writeString(s);
				
				print_prev(p_prev,press_prev);
				p_prev = i;
				press_prev = 2;
			}
			
			if ( button_event == EVENT_LONG_PRESS ) {
				
				sprintf(s,"%d: LONG       ",i);
				lcd_home();
				lcd_writeString(s);
				
				print_prev(p_prev,press_prev);
				p_prev = i;
				press_prev = 1;
			}
			
		} */
		
		// get encoders values
		for (i=0;i<3;i++) {
			
			int8_t encoder_value = get_encoder_value(i);
			
			if (encoder_value > 0) {
				
				if (i==0) {
					_led_l = _led_l<<1 | 0x01;
					refreshLeds();
				}
				
				if (i==2) {
					_led_r = _led_r<<1 | 0x01;
					refreshLeds();
				}
				
				if (i==1) {
					_led_r = _led_r<<1 | 0x01;
					_led_l = _led_l<<1 | 0x01;
					refreshLeds();
				}
				
			} else if (encoder_value < 0) {
				
				if (i==0) {
					_led_l = _led_l>>1 | 0x01;
					refreshLeds();
				}
				
				if (i==2) {
					_led_r = _led_r>>1 | 0x01;
					refreshLeds();
				}
				
				if (i==1) {
					_led_r = _led_r>>1 | 0x01;
					_led_l = _led_l>>1 | 0x01;
					refreshLeds();
				}
				
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