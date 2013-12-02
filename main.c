/**
 * \addtogroup main
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */


#include "includes.h"
#include "main.h"



int main(void) {
	
	// local string buffer for the LCD
	char s[16];
	// local cycle counter
	int i = 0;

	// init all of the modules
	io_init();
	input_init();
	lcd_init();
	timer_init();
	usart_logger_init();
	spi_init();
	
	
	// write greetings text on the display
	lcd_home();
	sprintf(s," DSP Controller ");
	lcd_writeString(s);
	lcd_newLine();
	sprintf(s,"      v1.1      ");
	lcd_writeString(s);
	
	// start the core engine
	sei();
	
	
	// infinite loop with LCD and LED handling
	while(1) {
		
		// if LED command was arrived via the spi, write it out atomically
		if (spi_flag == SPI_FLAG_LED) {
			cli();
			setLed(spi_receive_buffer[1],spi_receive_buffer[0]);
			spi_flag = SPI_FLAG_NONE;
			sei();
			refreshLeds();
		}
		
		// if TOP LCD command was arrived via the spi, write it out atomically
		if (spi_flag == SPI_FLAG_LCD_TOP) {
			cli();
			i = 15;
			// copy characters from the SPI buffer to the local buffer
			do {
				s[i] = spi_receive_buffer[i];
			} while (i--);
			spi_flag = SPI_FLAG_NONE;
			sei();
			lcd_home();
			lcd_writeString(s);
		}
		
		// if BOTTOM LCD command was arrived via the spi, write it out atomically
		if (spi_flag == SPI_FLAG_LCD_BOTTOM) {
			cli();
			i = 15;
			do {
				s[i] = spi_receive_buffer[i];
			} while (i--);
			spi_flag = SPI_FLAG_NONE;
			sei();
			lcd_newLine();
			lcd_writeString(s);
		}
	}
	return 0;
}


void io_init() {
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
	
	// IN_LOAD is low active, set it high
	setHigh(IN_LOAD);
}


void timer_init() {
	// Triggers an interrupt in each 0.5 miliseconds.
	// enable Timer/Counter0 Output Compare Match A Interrupt
	TIMSK0 = (1<<OCIE0A);
	
	// set CTC mode
	TCCR0A = (1<<WGM01) | (0<<WGM00);
	
	// prescaler: 64, CTC 125 = 0.5ms interrupts
	OCR0A = 125; // 0.5ms @ div64
	
	// set prescaler to 64
	TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00);  // div 64
}

/** \} */
