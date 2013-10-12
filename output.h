/**
 * \addtogroup lcd
 * \{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */


#ifndef OUTPUT_H_
#define OUTPUT_H_

	#include "includes.h"

	// LCD
	#define LCD_E	0x04  /**< Enable mask, that enables the data sent to the display. */
	#define LCD_BL	0x80  /**< Backlight mask. */
	#define LCD_RS	0x02  /**< Register Select mask. This bit selects between data or command. */

	/*===================================================================
	   I N I T I A L I Z A T I O N   F U N C T I O N S
	===================================================================*/

	/**
	 * Initializes the LCD display. 
	 */
	void lcd_init();


	/*===================================================================
	   C O N T R O L   F U N C T I O N S
	===================================================================*/

	/**
	 * Clears the LCD display. It takes 1.64ms to clear the entire 
	 * display, therefore it recommended to use it only at initialization. 
	 * A better and much faster method to set the cursor back to home, 
	 * and rewrite the screen.
	 */
	void lcd_clear();

	/**
	 * Returns the cursor to the home position (upper row, first 
	 * character). Very fast method. Only takes the time to transfer
	 * the data through the shift registers.
	 */
	void lcd_home();

	/**
	 * Sets the cursor to the second line first character.
	 */
	void lcd_newLine();


	/*===================================================================
	   S T R I N G   F U N C T I O N S
	===================================================================*/

	/**
	 * Writes a given string to the screen at the current cursor position.
	 * \param[in] s The string you want to print to the display.
	 */
	void lcd_writeString(char *s);


	/*===================================================================
	   C O M M U N I C A T I O N   F U N C T I O N S
	===================================================================*/

	/**
	 * Higher level communication function. It sends a command to the 
	 * LCD display.
	 * \param[in] value The command you want to send.
	 */
	void lcd_command(uint8_t value);

	/**
	 * Higher level communication function. It sends a character to the 
	 * LCD display.
	 * \param[in] value The character you want to send.
	 */
	void lcd_write(char value);

	/**
	 * Low level communication function, that sends data to the LCD display
	 * through 4-wire protocol. Due to the construction of the hardware
	 * this function breaks the encapsulation and handles the led bars
	 * via the two global variables \a _led_r and \a _led_l because their
	 * shift registers are in series with the LCD's one.
	 * \param[in] value The command you want to send.
	 * \param[in] mode Decides command or data will be transmitted. mode=1: 
	 * data, mode=0: command.
	 */
	void lcd_write4bits(uint8_t value, uint8_t mode);
	

#endif /* OUTPUT_H_ */
/** \} */