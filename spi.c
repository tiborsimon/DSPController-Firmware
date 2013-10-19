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
	
	SPDR = 0x00;
	
	spi_state = SPI_STATE_IDLE;
}

/*
void spi_load_transmit_buffer() {
	uint8_t i=31;
	cli();
	do {
		uint8_t event = get_button_event(i);
		if (event != EVENT_NOTHING) {
			SPDR = i;
		} else {
			SPDR = 99;
		}
	} while (i--);
	sei();
}
*/

/*
void spi_add_to_buffer(uint8_t id, uint8_t event) {
	cli();
	uint8_t temp;
	uint8_t type;
	
	if ((id == 12) | (id == 8) | (id == 4) | (id == 0) | (id == 28) | (id == 24) | (id == 20) | (id == 16)) {
		type = EVENT_TYPE_SWITCH;
		if (event == SHORT_EVENT) {
			sei();
			return;
		}
	} else {
		type = EVENT_TYPE_BUTTON;
	}
	
	temp = id | type | event;
	spi_transmit_buffer[spi_pointer++] = temp;
	SPDR = spi_pointer;
	
	sei();
}
*/

void spi_add_down(uint8_t id) {
	cli();
	uint8_t temp = EVENT_DOWN;
	
	switch (id) {
		case 0:		temp |= EVENT_TYPE_DIP |		5; break;
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 4:		temp |= EVENT_TYPE_DIP |		6; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 8:		temp |= EVENT_TYPE_DIP |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 12:	temp |= EVENT_TYPE_DIP |		8; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 16:	temp |= EVENT_TYPE_DIP |		1; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 20:	temp |= EVENT_TYPE_DIP |		2; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 24:	temp |= EVENT_TYPE_DIP |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 28:	temp |= EVENT_TYPE_DIP |		4; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	spi_transmit_buffer[spi_pointer++] = temp;
	SPDR = spi_pointer;
	sei();
}

void spi_add_up(uint8_t id) {
	cli();
	uint8_t temp = EVENT_UP;
	
	switch (id) {
		case 0:		temp |= EVENT_TYPE_DIP |		5; break;
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 4:		temp |= EVENT_TYPE_DIP |		6; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 8:		temp |= EVENT_TYPE_DIP |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 12:	temp |= EVENT_TYPE_DIP |		8; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 16:	temp |= EVENT_TYPE_DIP |		1; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 20:	temp |= EVENT_TYPE_DIP |		2; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 24:	temp |= EVENT_TYPE_DIP |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 28:	temp |= EVENT_TYPE_DIP |		4; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	spi_transmit_buffer[spi_pointer++] = temp;
	SPDR = spi_pointer;
	sei();
}

void spi_add_short_press(uint8_t id) {
	cli();
	uint8_t temp = EVENT_SHORT;
	
	switch (id) {
		case 0:		temp |= EVENT_TYPE_DIP |		5; break;
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 4:		temp |= EVENT_TYPE_DIP |		6; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 8:		temp |= EVENT_TYPE_DIP |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 12:	temp |= EVENT_TYPE_DIP |		8; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 16:	temp |= EVENT_TYPE_DIP |		1; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 20:	temp |= EVENT_TYPE_DIP |		2; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 24:	temp |= EVENT_TYPE_DIP |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 28:	temp |= EVENT_TYPE_DIP |		4; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	spi_transmit_buffer[spi_pointer++] = temp;
	SPDR = spi_pointer;
	sei();
}

void spi_add_long_press(uint8_t id) {
	cli();
	uint8_t temp = EVENT_LONG;
	
	switch (id) {
		case 0:		temp |= EVENT_TYPE_DIP |		5; break;
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 4:		temp |= EVENT_TYPE_DIP |		6; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 8:		temp |= EVENT_TYPE_DIP |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 12:	temp |= EVENT_TYPE_DIP |		8; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 16:	temp |= EVENT_TYPE_DIP |		1; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 20:	temp |= EVENT_TYPE_DIP |		2; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 24:	temp |= EVENT_TYPE_DIP |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 28:	temp |= EVENT_TYPE_DIP |		4; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	spi_transmit_buffer[spi_pointer++] = temp;
	SPDR = spi_pointer;
	sei();
}

void spi_add_encoder(uint8_t id) {
	cli();
	uint8_t temp = 0;
	
	if (id == 0) {
		temp = 13 | (encoder_counter[0]<<4);
		encoder_counter[0] = 0;
	} else if (id == 2) {
		temp = 14 | (encoder_counter[1]<<4);
		encoder_counter[1] = 0;
	} else if (id == 4) {
		temp = 15 | (encoder_counter[2]<<4);
		encoder_counter[2] = 0;
	}
	
	spi_transmit_buffer[spi_pointer++] = temp;
	SPDR = spi_pointer;
	sei();
}

/*
void spi_switch_release(uint8_t id) {
	cli();
	
	if ((id == 12) | (id == 8) | (id == 4) | (id == 0) | (id == 28) | (id == 24) | (id == 20) | (id == 16)) {
		
		spi_transmit_buffer[spi_pointer++] = id | EVENT_TYPE_SWITCH | SHORT_EVENT;
		SPDR = spi_pointer;
	}
	
	sei();
}
*/

ISR(SPI_STC_vect) {
	
	if (spi_state == SPI_STATE_IDLE) {
		if (SPDR == SPI_GET_SIMPLE) {
			if (spi_pointer > 1) {
				spi_state = SPI_STATE_TRANSMIT;
				SPDR = spi_transmit_buffer[--spi_pointer];
			} else if (spi_pointer == 1) {
				SPDR = spi_transmit_buffer[--spi_pointer];
			} else {
				SPDR = spi_pointer;
			}
		}
	} else if (spi_state == SPI_STATE_TRANSMIT) {
		if (--spi_pointer == 0) {
			SPDR = 0;
			spi_state = SPI_STATE_IDLE;
		}
		SPDR = spi_transmit_buffer[spi_pointer];
	}
	
	/*
	if (SPDR == SPI_GET_SIMPLE) {
		if (status_ready) {
			if (--spi_pointer == 0) {
				status_ready = 0;
			}
			SPDR = spi_transmit_buffer[spi_pointer];
		} else {
			// SPDR = 100;
		}
	} else {
		// SPDR = 0;
	}
	*/
	
	
}