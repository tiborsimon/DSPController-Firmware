/*
 * spi.c
 *
 * Created: 10/15/2013 4:57:51 PM
 *  Author: Tibor
 */

#include "includes.h"


void spi_init() {
	
	// set MISO output
	setOutput(MISO);
	
	// the DSP Controller will be the slave, therefore it doesn't need to set the SPI clock speed.
	// enable SPI and SPI interrupt
	SPCR = (1<<SPE) | (1<<SPIE);
	
	SPDR = 0x55;
}