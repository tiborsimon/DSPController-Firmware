/**
 * \addtogroup main
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 *
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include "usart_logger.h"
#include "bsp.h"
#include "shift.h"
#include "output.h"
#include "input.h"
#include "spi.h"

#define F_CPU 16000000UL	 /**< CPU clock frequency */
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

/** \} */