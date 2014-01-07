/**
 * \addtogroup bsp
 * \{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */

#ifndef _HAL_H_
#define _HAL_H_

	#include "includes.h"

	/*=======================================================================================
	  S I G N A L   N A M E S
	=======================================================================================*/
	
	#define IO_CLK			IO_CLK			/**< Clk line for all of the shift registers. */
	#define OUT_LATCH		OUT_LATCH		/**< Latch signal for the output shift registers. */
	#define IN_LOAD			IN_LOAD			/**< Load signal for the input shift registers. */
	#define OUT				OUT				/**< Serial data out for the output shift registers. */
	#define IN_1			IN_1			/**< Input serial data line from the first input shift register. */
	#define IN_2			IN_2			/**< Input serial data line from the second input shift register. */
	#define IN_3			IN_3			/**< Input serial data line from the third input shift register. */
	#define IN_4			IN_4			/**< Input serial data line from the fourth input shift register. */
	#define E1_A			E1_A			/**< First encoder's A signal. */
	#define E1_B			E1_B			/**< First encoder's B signal. */
	#define E2_A			E2_A			/**< Second encoder's A signal. */
	#define E2_B			E2_B			/**< Second encoder's B signal. */
	#define E3_A			E3_A			/**< Third encoder's A signal. */
	#define E3_B			E3_B			/**< Third encoder's B signal. */
	#define MOSI			MOSI			/**< SPI MOSI signal. */
	#define MISO			MISO			/**< SPI MISO signal. */
	#define SCK				SCK				/**< SPI SCK signal. */
	#define SS				SS				/**< SPI SS signal. */		



	/*=======================================================================================
	  SIGNALS TO IO PORTS  ::  S P I
	=======================================================================================*/
	
	#define MOSI_DDR 		DDRB			/**< Data Direction Register for MOSI. */
	#define MOSI_PORT		PORTB			/**< Port Register for MOSI. */
	#define MOSI_PIN		PINB			/**< Pin Register for MOSI. */
	#define MOSI_NAME 		PB3				/**< Pin name for MOSI. */
	
	#define MISO_DDR 		DDRB			/**< Data Direction Register for MISO. */
	#define MISO_PORT		PORTB			/**< Port Register for MISO. */
	#define MISO_PIN		PINB			/**< Pin Register for MISO. */
	#define MISO_NAME 		PB4				/**< Pin name for MISO. */
	
	#define SS_DDR 			DDRB			/**< Data Direction Register for SS. */
	#define SS_PORT			PORTB			/**< Port Register for SS. */
	#define SS_PIN			PINB			/**< Pin Register for SS. */
	#define SS_NAME 		PB2				/**< Pin name for SS. */
	
	#define SCK_DDR 		DDRB			/**< Data Direction Register for SCK. */
	#define SCK_PORT		PORTB			/**< Port Register for SCK. */
	#define SCK_PIN			PINB			/**< Pin Register for SCK. */
	#define SCK_NAME 		PB5				/**< Pin name for SCK. */
	
	
	/*=======================================================================================
	  SIGNALS TO IO PORTS  ::  S H I F T   R E G I S T E R S
	=======================================================================================*/
	
	#define IO_CLK_DDR 		DDRC			/**< Data Direction Register for IO_CLK. */
	#define IO_CLK_PORT		PORTC			/**< Port Register for IO_CLK. */
	#define IO_CLK_PIN		PINC			/**< Pin Register for IO_CLK. */
	#define IO_CLK_NAME 	PC0				/**< Pin name for IO_CLK. */

	#define OUT_LATCH_DDR 	DDRC			/**< Data Direction Register for OUT_LATCH. */
	#define OUT_LATCH_PORT	PORTC			/**< Port Register for OUT_LATCH. */
	#define OUT_LATCH_PIN	PINC			/**< Pin Register for OUT_LATCH. */
	#define OUT_LATCH_NAME 	PC1				/**< Pin name for OUT_LATCH. */

	#define IN_LOAD_DDR 	DDRC			/**< Data Direction Register for IN_LOAD. */
	#define IN_LOAD_PORT	PORTC			/**< Port Register for IN_LOAD. */
	#define IN_LOAD_PIN		PINC			/**< Pin Register for IN_LOAD. */
	#define IN_LOAD_NAME 	PC2				/**< Pin name for IN_LOAD. */

	#define OUT_DDR 		DDRC			/**< Data Direction Register for OUT. */
	#define OUT_PORT		PORTC			/**< Port Register for OUT. */
	#define OUT_PIN			PINC			/**< Pin Register for OUT. */
	#define OUT_NAME 		PC3				/**< Pin name for OUT. */

	#define IN_1_DDR 		DDRC			/**< Data Direction Register for IN_1. */
	#define IN_1_PORT		PORTC			/**< Port Register for IN_1. */
	#define IN_1_PIN		PINC			/**< Pin Register for IN_1. */
	#define IN_1_NAME 		PC4				/**< Pin name for IN_1. */

	#define IN_2_DDR 		DDRC			/**< Data Direction Register for IN_2. */
	#define IN_2_PORT		PORTC			/**< Port Register for IN_2. */
	#define IN_2_PIN		PINC			/**< Pin Register for IN_2. */
	#define IN_2_NAME 		PC5				/**< Pin name for IN_2. */

	#define IN_3_DDR 		DDRB			/**< Data Direction Register for IN_3. */
	#define IN_3_PORT		PORTB			/**< Port Register for IN_3. */
	#define IN_3_PIN		PINB			/**< Pin Register for IN_3. */
	#define IN_3_NAME 		PB0				/**< Pin name for IN_3. */

	#define IN_4_DDR 		DDRB			/**< Data Direction Register for IN_4. */
	#define IN_4_PORT		PORTB			/**< Port Register for IN_4. */
	#define IN_4_PIN		PINB			/**< Pin Register for IN_4. */
	#define IN_4_NAME		PB1				/**< Pin name for IN_4. */


	/*=======================================================================================
	  SIGNALS TO IO PORTS  ::  E N C O D E R S
	=======================================================================================*/
	
	#define E1_A_DDR 		DDRD			/**< Data Direction Register for E1_A. */
	#define E1_A_PORT		PORTD			/**< Port Register for E1_A. */
	#define E1_A_PIN		PIND			/**< Pin Register for E1_A. */
	#define E1_A_NAME 		PD3				/**< Pin name for E1_A. */

	#define E1_B_DDR 		DDRD			/**< Data Direction Register for E1_B. */
	#define E1_B_PORT		PORTD			/**< Port Register for E1_B. */
	#define E1_B_PIN		PIND			/**< Pin Register for E1_B. */
	#define E1_B_NAME 		PD2				/**< Pin name for E1_B. */

	#define E2_A_DDR 		DDRD			/**< Data Direction Register for E2_A. */
	#define E2_A_PORT		PORTD			/**< Port Register for E2_A. */
	#define E2_A_PIN		PIND			/**< Pin Register for E2_A. */
	#define E2_A_NAME 		PD5				/**< Pin name for E2_A. */

	#define E2_B_DDR 		DDRD			/**< Data Direction Register for E2_B. */
	#define E2_B_PORT		PORTD			/**< Port Register for E2_B. */
	#define E2_B_PIN		PIND			/**< Pin Register for E2_B. */
	#define E2_B_NAME 		PD4				/**< Pin name for E2_B. */

	#define E3_A_DDR 		DDRD			/**< Data Direction Register for E3_A. */
	#define E3_A_PORT		PORTD			/**< Port Register for E3_A. */
	#define E3_A_PIN		PIND			/**< Pin Register for E3_A. */
	#define E3_A_NAME 		PD6				/**< Pin name for E3_A. */

	#define E3_B_DDR 		DDRD			/**< Data Direction Register for E3_B. */
	#define E3_B_PORT		PORTD			/**< Port Register for E3_B. */
	#define E3_B_PIN		PIND			/**< Pin Register for E3_B. */
	#define E3_B_NAME 		PD7				/**< Pin name for E3_B. */


	/*=======================================================================================
	  INPUT DEFINITIONS  ::  I N P U T   S H I F T   R E G I S T E R   1
	=======================================================================================*/
	
	#define IN_1_A	0x01		/**< Association for shift register IN_1. */
	#define IN_1_B	0x02		/**< Association for shift register IN_1. */
	#define IN_1_C	0x04		/**< Association for shift register IN_1. */
	#define IN_1_D	0x08		/**< Association for shift register IN_1. */
	#define IN_1_E	0x10		/**< Association for shift register IN_1. */
	#define IN_1_F	0x20		/**< Association for shift register IN_1. */
	#define IN_1_G	0x40		/**< Association for shift register IN_1. */
	#define IN_1_H	0x80		/**< Association for shift register IN_1. */

	/*=======================================================================================
	  INPUT DEFINITIONS  ::  I N P U T   S H I F T   R E G I S T E R   2
	=======================================================================================*/
	
	#define IN_2_A	0x01		/**< Association for shift register IN_2. */
	#define IN_2_B	0x02		/**< Association for shift register IN_2. */
	#define IN_2_C	0x04		/**< Association for shift register IN_2. */
	#define IN_2_D	0x08		/**< Association for shift register IN_2. */
	#define IN_2_E	0x10		/**< Association for shift register IN_2. */
	#define IN_2_F	0x20		/**< Association for shift register IN_2. */
	#define IN_2_G	0x40		/**< Association for shift register IN_2. */
	#define IN_2_H	0x80		/**< Association for shift register IN_2. */

	/*=======================================================================================
	  INPUT DEFINITIONS  ::  I N P U T   S H I F T   R E G I S T E R   3
	=======================================================================================*/
	
	#define IN_3_A	0x01		/**< Association for shift register IN_3. */
	#define IN_3_B	0x02		/**< Association for shift register IN_3. */
	#define IN_3_C	0x04		/**< Association for shift register IN_3. */
	#define IN_3_D	0x08		/**< Association for shift register IN_3. */
	#define IN_3_E	0x10		/**< Association for shift register IN_3. */
	#define IN_3_F	0x20		/**< Association for shift register IN_3. */
	#define IN_3_G	0x40		/**< Association for shift register IN_3. */
	#define IN_3_H	0x80		/**< Association for shift register IN_3. */

	/*=======================================================================================
	  INPUT DEFINITIONS  ::  I N P U T   S H I F T   R E G I S T E R   4
	=======================================================================================*/
	
	#define IN_4_A	0x01		/**< Association for shift register IN_4. */
	#define IN_4_B	0x02		/**< Association for shift register IN_4. */
	#define IN_4_C	0x04		/**< Association for shift register IN_4. */
	#define IN_4_D	0x08		/**< Association for shift register IN_4. */
	#define IN_4_E	0x10		/**< Association for shift register IN_4. */
	#define IN_4_F	0x20		/**< Association for shift register IN_4. */
	#define IN_4_G	0x40		/**< Association for shift register IN_4. */
	#define IN_4_H	0x80		/**< Association for shift register IN_4. */


	/*=======================================================================================
	  INPUT DEFINITIONS  ::  D I P   S W I T C H
	=======================================================================================*/
	
	#define DIP_1	IN_1_A		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_2	IN_1_B		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_3	IN_1_C		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_4	IN_1_D		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_5	IN_1_E		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_6	IN_1_F		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_7	IN_1_G		/**< Association between input source and shift register pin for the DIP_SWITCH.*/
	#define DIP_8	IN_1_H		/**< Association between input source and shift register pin for the DIP_SWITCH.*/


	/*=======================================================================================
	  INPUT DEFINITIONS  ::  E N C O D E R   B U T T O N S
	=======================================================================================*/
	
	#define	E1 		IN_2_A		/**< Association between input source and shift register pin for the encoder buttons.*/
	#define	E2 		IN_2_B		/**< Association between input source and shift register pin for the encoder buttons.*/
	#define	E3 		IN_2_C		/**< Association between input source and shift register pin for the encoder buttons.*/


	/*=======================================================================================
	  INPUT DEFINITIONS  ::  F U N C T I O N   B U T T O N S
	=======================================================================================*/
	
	#define	F1 		IN_2_D		/**< Association between input source and shift register pin for the FUNCTION BUTTONS.*/
	#define	F2 		IN_2_E		/**< Association between input source and shift register pin for the FUNCTION BUTTONS.*/
	#define	F3 		IN_2_F		/**< Association between input source and shift register pin for the FUNCTION BUTTONS.*/
	#define	F4 		IN_2_G		/**< Association between input source and shift register pin for the FUNCTION BUTTONS.*/


	/*=======================================================================================
	  INPUT DEFINITIONS  ::  A R R O W   B U T T O N S 
	=======================================================================================*/
	
	#define	A1 		IN_3_D		/**< Association between input source and shift register pin for the ARROW BUTTONS.*/
	#define	A2 		IN_2_H		/**< Association between input source and shift register pin for the ARROW BUTTONS.*/
	#define	A3 		IN_3_B		/**< Association between input source and shift register pin for the ARROW BUTTONS.*/
	#define	A4 		IN_3_C		/**< Association between input source and shift register pin for the ARROW BUTTONS.*/
	#define	A5 		IN_3_A		/**< Association between input source and shift register pin for the ARROW BUTTONS.*/


	/*=======================================================================================
	  INPUT DEFINITIONS  ::  N U M P A D
	=======================================================================================*/
	
	#define	N1 		IN_4_A		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N2 		IN_4_B		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N3 		IN_4_C		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N4 		IN_4_D		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N5 		IN_4_E		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N6 		IN_4_F		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N7 		IN_4_G		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N8 		IN_4_H		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N9 		IN_3_H		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N10 	IN_3_E		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N11 	IN_3_F		/**< Association between input source and shift register pin for the NUMPAD.*/
	#define	N12 	IN_3_G		/**< Association between input source and shift register pin for the NUMPAD.*/


	/*=======================================================================================
	  MACRO  ::  O U T P U T   C O N F I G U R A T I O N S 
	=======================================================================================*/
	
	/**
	 * Low level macro that configures the given pin as an output.
	 * \param[in] ddr DDR register that corresponds to the given pin.
	 * \param[in] name The name of the given pin.
	 */
	#define output(ddr,name)	((ddr) |= (1 << (name)))
	
	/**
	 * Low level macro that configures the given pin as an input.
	 * \param[in] ddr DDR register that corresponds to the given pin.
	 * \param[in] name The name of the given pin.
	 */
	#define input(ddr,name)		((ddr) &= ~(1 << (name)))

	/**
	 * Higher level macro to configure the given pin to output. It
	 * uses the low level macro to do this.
	 * \param[in] name The name of the given pin.
	 */
	#define setOutput(name)		output(name##_DDR,name##_NAME)
	
	/**
	 * Higher level macro to configure the given pin to input. It
	 * uses the low level macro to do this.
	 * \param[in] name The name of the given pin.
	 */
	#define setInput(name)		input(name##_DDR,name##_NAME)

	/**
	 * Higher level macro to configure the given pin to input and
	 * it turns on it's internal pullup resistor. It uses the low 
	 * level macro to do this.
	 * \param[in] name The name of the given pin.
	 */
	#define setInputWPullup(name) \
		do { \
			output(name##_DDR,name##_NAME); \
			(name##_PORT) |= (1 << (name##_NAME)); \
		} while (0)
		
	
	/*=======================================================================================
	  MACRO  ::  L O G I C A L   S T A T E   A S S I G N S 
	=======================================================================================*/
	
	/**
	 * Low level macro that toggles a pin based on the AVR IO architecture's hardware XOR feature.
	 * \param[in] pin The PINX register for the given pin.
	 * \param[in] name The name of the given pin.
	 */
	#define toggle(pin,name)	((pin) |= (1 << (name)))
	
	/**
	 * Low level macro that sets the given pin to low logical state.
	 * \param[in] port The PORTX register for the given pin.
	 * \param[in] name The name of the given pin.
	 */
	#define low(port,name)		((port) &=  ~(1 << (name)))
	
	/**
	 * Low level macro that sets the given pin to high logical state.
	 * \param[in] port The PORTX register for the given pin.
	 * \param[in] name The name of the given pin.
	 */
	#define high(port,name)		((port) |= (1 << (name)))
				
	/**
	 * Higher level macro for setting the given pin state to low logic level.
	 * \param[in] name The name of the given pin.
	 */						
	#define setLow(name)		low(name##_PORT,name##_NAME)
	
	/**
	 * Higher level macro for setting the given pin state to high logic level.
	 * \param[in] name The name of the given pin.
	 */	
	#define setHigh(name)		high(name##_PORT,name##_NAME)
	
	
	/*=======================================================================================
	  MACRO  ::  R E A D I N G   F R O M   P I N 
	=======================================================================================*/
	
	/**
	 * Low level macro that reads the logical value of the given pin.
	 * \param[in] pin PINX register corresponding to the given pin.
	 * \param[in] name The name of the given pin.
	 */
	#define read(pin,name)		(((pin) & (1<<name)) >> name)
	
	/**
	 * Higher level read macro that reads a pin's logical value.
	 * \param[in] name The name of the given pin.
	 */
	#define readValue(name)		read(name##_PIN,name##_NAME)


	/*=======================================================================================
	  MACRO  ::  P U L S I N G   A   P I N 
 	=======================================================================================*/

	/**
	 * It pulses the given pin. Pulse characteristic: LOW - HIGH - LOW
	 * \param[in] name The name of the given pin.
	 */	
	#define pulse(name) \
		do { \
			setHigh(name); \
			setLow(name); \
		} while (0)
			
	/**
	 * It pulses negatively the given pin. Pulse characteristic: HIGH - LOW - HIGH
	 * \param[in] name The name of the given pin.
	 */					 
	#define negativePulse(name) \
		do { \
			setLow(name); \
			setHigh(name); \
		} while (0)
	
	
	/*=======================================================================================
	  MACRO  ::  G L O B A L   L E D   B A R S
	=======================================================================================*/
	
	/**
	 * This macro sets the two led bar's global variables that hold the current
	 * led bar configurations.
	 * \param[in] L Values for the left led bar.
	 * \param[in] R Values for the right led bar.
	 */					 
	#define setLed(L, R) \
		do { \
			_led_l = L; \
			_led_r = R; \
		} while (0)

#endif // #ifndef _HAL_H_
/** \} */
