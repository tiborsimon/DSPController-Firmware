/**
 * \addtogroup main
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */


#ifndef MAIN_H_
#define MAIN_H_

/*================================================================
  D E C L A R E   G L O B A L   V A R I A B L E S
================================================================*/

// LED BARS
volatile uint8_t _led_l = 0;					/**< Global variable that holds the left led bar's current value. */
volatile uint8_t _led_r = 0;					/**< Global variable that holds the right led bar's current value.. */

// INPUT MODULE VARIABLES
volatile uint8_t debounce[32];					/**< Global array of variables that act as a debounce registers fr the buttons. */
volatile uint16_t button_status[32];			/**< Global array of variables that store the buttons' status information. */

volatile uint8_t encoder_debounce[6];			/**< Global array of variables that act as a debounce registers for the encoders. */
volatile int8_t encoder_counter[3];				/**< Global array that holds the actual encoder increments. */
volatile uint8_t encoder_status[6];				/**< Global array that holds the encoders' status information. */

volatile uint8_t dip_status;					/**< Global variable that contains the current dip status. */

// SPI VARIABLES
volatile uint8_t spi_state;						/**< Global variable that holds the actual SPI state. */

volatile uint8_t spi_transmit_A_not_B;			/**< Global variable that decides which SPI buffer will be the next readable buffer. */
volatile uint8_t spi_transmit_pointer_A;		/**< Global variable that . */
volatile uint8_t spi_transmit_pointer_B;		/**< Global variable that . */
volatile uint8_t spi_transmit_buffer_A[40];		/**< Global variable that . */
volatile uint8_t spi_transmit_buffer_B[40];		/**< Global variable that . */

volatile uint8_t* spi_transmit_pointer_READ;	/**< Global variable that . */
volatile uint8_t* spi_transmit_buffer_READ;		/**< Global variable that . */
volatile uint8_t* spi_transmit_pointer_WRITE;	/**< Global variable that . */
volatile uint8_t* spi_transmit_buffer_WRITE;	/**< Global variable that . */

volatile uint8_t spi_receive_pointer;			/**< Global variable that . */
volatile uint8_t spi_receive_buffer[36];		/**< Global variable that . */
volatile uint8_t spi_flag;						/**< Global variable that . */

/**
 * Initialize Timer0 to Output Compare Match A Interrupt @ 0.5 ms. This interrupt will trigger 
 * all input processing algorithm.
 */
void timer_init(void);

/**
 * Initialize the AVR IO ports. It uses the macros defined in the BSP file.
 */
void io_init(void);

/**
 * Entry point of the firmware.
 */
int main(void);



#endif /* MAIN_H_ */
/** \} */
