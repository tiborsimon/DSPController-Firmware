/*
 * main.h
 *
 * Created: 11/3/2013 2:00:02 PM
 *  Author: Tibor
 */ 


#ifndef MAIN_H_
#define MAIN_H_

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

void timer_init();
void io_init();
void welcome_screen(char* s);



#endif /* MAIN_H_ */