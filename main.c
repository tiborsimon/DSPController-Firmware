/*
 * DSPControllerB.c
 *
 * Created: 10/5/2013 12:29:35 AM
 *  Author: Tibor
 */ 


#include "includes.h"
#include "main.h"



int main(void) {
	
	char s[16];
	int i = 0;

	io_init();
	input_init();
	lcd_init();
	timer_init();
	usart_logger_init();
	spi_init();
	
	/*
	welcome_screen(s);
	
	while(!(SPSR & (1<<SPIF)));
	
	
	lcd_home();
	sprintf(s,"     Ready!     ");
	lcd_writeString(s);
	
	lcd_newLine();
	sprintf(s,"                ");
	lcd_writeString(s);
	
	lcd_clear();
	SPDR = 0x80;
	
	*/
	
	lcd_home();
	sprintf(s," DSP Controller ");
	lcd_writeString(s);
	lcd_newLine();
	sprintf(s,"      v1.1      ");
	lcd_writeString(s);
	
	sei();
	
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
				s[i] = spi_receive_buffer[i];
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


#define LED_ANIM_DUR	5
#define LED_ANIM_MOD	2

void led_up() {
	setLed(0x01,0x01);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+3*LED_ANIM_MOD);
	
	setLed(0x03,0x03);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+2*LED_ANIM_MOD);
	
	setLed(0x07,0x07);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+2*LED_ANIM_MOD);
	
	setLed(0x0f,0x0f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x0f,0x0f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x0f,0x0f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x1f,0x1f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x3f,0x3f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR);
	
	setLed(0x7f,0x7f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR);
	
	setLed(0xff,0xff);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR);
}

void led_down() {
	setLed(0xff,0xff);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR);
	
	setLed(0x7f,0x7f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR);
	
	setLed(0x3f,0x3f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR);
	
	setLed(0x1f,0x1f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x0f,0x0f);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x07,0x07);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+LED_ANIM_MOD);
	
	setLed(0x03,0x03);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+2*LED_ANIM_MOD);
	
	setLed(0x01,0x01);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+2*LED_ANIM_MOD);
	
	setLed(0x00,0x00);
	refreshLeds();
	_delay_ms(LED_ANIM_DUR+3*LED_ANIM_MOD);
}

void welcome_screen(char* s) {
	
	lcd_home();
	sprintf(s," DSP Controller ");
	lcd_writeString(s);
	lcd_newLine();
	sprintf(s,"      v1.1      ");
	lcd_writeString(s);
	
	_delay_ms(1500);
	
	lcd_newLine();
	sprintf(s,"  Simon  Tibor  ");
	lcd_writeString(s);
	
	_delay_ms(700);
	
	led_up();
	led_down();
	
	_delay_ms(50);
	
	led_up();
	led_down();
	
	lcd_home();
	sprintf(s,"   Waiting for  ");
	lcd_writeString(s);
	lcd_newLine();
	sprintf(s,"SPI connection..");
	lcd_writeString(s);
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