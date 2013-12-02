/**
 * \addtogroup lcd
 * \{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 */

#include "output.h"
#include <string.h>



/*================================================================
   I N I T I A L I Z A T I O N   F U N C T I O N S
================================================================*/

void lcd_init() {
	// we start in 8bit mode, try to set 4 bit mode
	lcd_write4bits(0x03, 0);
	_delay_us(4500); // wait min 4.1ms

	// second try
	lcd_write4bits(0x03, 0);
	_delay_us(4500); // wait min 4.1ms
	
	// third go!
	lcd_write4bits(0x03, 0);
	_delay_us(150);

	// finally, set to 4-bit interface
	lcd_write4bits(0x02, 0);
	
	// we are in 4 bit mode
	// enter entry mode: increment, no display shift
	lcd_command(0x06);
	
	// turn on the display with blinking display
	lcd_command(0x0c);
	
	// set 4bit mode again, 2 lines, 5x7 characters
	lcd_command(0x2c);
	
	// clear display
	lcd_command(0x01);
	
	// wait for clearing
	_delay_ms(2);
}


/*================================================================
   C O N T R O L   F U N C T I O N S
================================================================*/

void lcd_clear() {
	lcd_command(0x01);
	_delay_us(1640);
}

void lcd_home() {
	lcd_command(0x02);
}

void lcd_newLine() {
	lcd_command(0xa8);
}


/*================================================================
   S T R I N G   F U N C T I O N S
================================================================*/

void lcd_writeString(char *s) {
	uint8_t len = strlen(s);
	uint8_t i;
	for (i = 0; i < len ; i++) {
		lcd_write(s[i]);
		_delay_us(100);
	}
}

/*================================================================
   C O M M U N I C A T I O N   F U N C T I O N S
================================================================*/

// high level driver
void lcd_command(uint8_t value) {
	cli();
	lcd_write4bits(value>>4, 0);
	lcd_write4bits(value, 0);
	sei();
}

void lcd_write(char value) {
	cli();
	lcd_write4bits(value>>4, 1);
	lcd_write4bits(value, 1);
	sei();
}

// low level data pushing
void lcd_write4bits(uint8_t value, uint8_t mode) {
	int mask = (mode) ? (LCD_BL | LCD_RS) : (LCD_BL);
	int data = 0;

	data = value<<3 & 0b01111000;
	data |= mask;
	
	shiftOutMsbFirst(data | LCD_E);
	shiftOutMsbFirst(_led_r);
	shiftOutLsbFirst(_led_l);
	pulse(OUT_LATCH);
	
	shiftOutMsbFirst(data);
	shiftOutMsbFirst(_led_r);
	shiftOutLsbFirst(_led_l);
	pulse(OUT_LATCH);
}


void refreshLeds() {
	cli();
	shiftOutMsbFirst(LCD_BL);
	shiftOutMsbFirst(_led_r);
	shiftOutLsbFirst(_led_l);
	pulse(OUT_LATCH);
	sei();
}

/** \} */
