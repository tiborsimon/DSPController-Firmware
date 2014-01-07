/**
 * \addtogroup outputs
 * \{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */


#ifndef SHIFT_H_
#define SHIFT_H_

#include "includes.h"

/**
 * Shifts out a byte through the default output pin with the MSB bit first.
 * \param[in] data The byte you want to shift out.
 */
void shiftOutMsbFirst(uint8_t data);

/**
 * Shifts out a byte through the default output pin with the LSB bit first.
 * \param[in] data The byte you want to shift out.
 */
void shiftOutLsbFirst(uint8_t data);



#endif /* SHIFT_H_ */
/** \} */
