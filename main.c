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
volatile uint8_t encoder_status[6];

volatile uint8_t dip_status;

// SPI VARIABLES
volatile uint8_t spi_state;

volatile uint8_t spi_transmit_A_not_B;
volatile uint8_t spi_transmit_pointer_A;
volatile uint8_t spi_transmit_pointer_B;
volatile uint8_t spi_transmit_buffer_A[40];
volatile uint8_t spi_transmit_buffer_B[40];

volatile uint8_t* spi_transmit_pointer_READ;
volatile uint8_t* spi_transmit_buffer_READ;
volatile uint8_t* spi_transmit_pointer_WRITE;
volatile uint8_t* spi_transmit_buffer_WRITE;

volatile uint8_t spi_receive_pointer;
volatile uint8_t spi_receive_buffer[36];
volatile uint8_t spi_flag;

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

/*
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
*/



int main(void) {
	
	char s[16];
	
	int i = 0;

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
		
		if (spi_flag == SPI_FLAG_LED) {
			cli();
			setLed(spi_receive_buffer[1],spi_receive_buffer[0]);
			spi_flag = SPI_FLAG_NONE;
			sei();
			refreshLeds();
		}
		
		if (spi_flag == SPI_FLAG_LCD_TOP) {
			cli();
			i = 15;
			do {
				s[15-i] = spi_receive_buffer[i];
			} while (i--);
			spi_flag = SPI_FLAG_NONE;
			sei();
			lcd_home();
			lcd_writeString(s);
		}
		
		if (spi_flag == SPI_FLAG_LCD_BOTTOM) {
			cli();
			i = 15;
			do {
				s[15-i] = spi_receive_buffer[i];
			} while (i--);
			spi_flag = SPI_FLAG_NONE;
			sei();
			lcd_newLine();
			lcd_writeString(s);
		}
		
	}
	
	return 0;
}