/**
 * \addtogroup logger
 * @{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 */

#include <avr/io.h>
#include <stdio.h>
#include "usart_logger.h"

#ifdef LOGGER_ON_

	#ifndef F_CPU
	#define F_CPU 16000000UL /**< CPU clock frequency */
	#endif

	#ifndef BAUD
	#define BAUD 57600  /**< UART baudrate */
	#endif
	
	#include <util/setbaud.h>

	int usart_putchar(char c, FILE *stream) {
		if (c == '\n') {
			usart_putchar('\r', stream);
		}
		loop_until_bit_is_set(UCSR0A, UDRE0);
		UDR0 = c;
		return 0;
	}

	int usart_getchar(FILE *stream) {
		loop_until_bit_is_set(UCSR0A, RXC0);
		return UDR0;
	}

	FILE usart_output = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE); /**< Variable that represents the new output stream. */
	FILE usart_input = FDEV_SETUP_STREAM(NULL, usart_getchar, _FDEV_SETUP_READ);   /**< Variable that represents the new input stream. */
	
#endif // LOGGER_ON_

void usart_logger_init(void) {
#ifdef LOGGER_ON_

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	
	#if USE_2X
	UCSR0A |= _BV(U2X0);
	#else
	UCSR0A &= ~(_BV(U2X0));
	#endif

	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
	
	stdout = &usart_output;
	stdin  = &usart_input;
	
#endif // LOGGER_ON_
}
/** \} */