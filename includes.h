/*
 * includes.h
 *
 * Created: 10/8/2013 7:52:42 PM
 *  Author: Tibor
 */ 


// #ifndef INCLUDES_H_
// #define INCLUDES_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include "usart_logger.h"
#include "bsp.h"
#include "shift.h"
#include "output.h"
#include "input.h"

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

/**
 * \addtogroup ledbars
 * \{
 * \brief Global variables
 */
extern volatile uint8_t _led_l;  /**< Global variable that holds the value of the left led bar. */
extern volatile uint8_t _led_r;  /**< Global variable that holds the value of the right led bar. */
/** \} */


// #endif /* INCLUDES_H_ */