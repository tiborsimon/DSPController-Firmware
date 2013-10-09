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
#include "hal.h"
#include "shift.h"
#include "lcd.h"

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

extern volatile uint8_t _led_l;
extern volatile uint8_t _led_r;



// #endif /* INCLUDES_H_ */