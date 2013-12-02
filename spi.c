/**
 * \addtogroup spi
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */

#include "includes.h"


void spi_init() {
	
	// set MISO output
	setOutput(MISO);
	
	// the DSPController will be the slave, therefore it doesn't need to set the SPI clock speed.
	// enable SPI and SPI interrupt
	SPCR = (1<<SPE) | (1<<SPIE);
	
	SPDR = 0x00;
	
	spi_state = SPI_STATE_IDLE;
	spi_flag = SPI_FLAG_NONE;
	
	// prepare the double buffered transmit mechanism
	spi_transmit_A_not_B = 1;
	spi_transmit_pointer_A = 0;
	spi_transmit_pointer_B = 0;
	
	spi_transmit_pointer_WRITE = &spi_transmit_pointer_A;
	spi_transmit_buffer_WRITE = spi_transmit_buffer_A;
	spi_transmit_pointer_READ = &spi_transmit_pointer_B;
	spi_transmit_buffer_READ = spi_transmit_buffer_B;
}

void spi_change_transmit_buffers() {
	// flip the decider variable
	spi_transmit_A_not_B = !spi_transmit_A_not_B;
	
	// and change the READ buffer to the WRITE buffer and vice versa
	if (spi_transmit_A_not_B) {
		
		spi_transmit_pointer_WRITE = &spi_transmit_pointer_A;
		spi_transmit_buffer_WRITE = spi_transmit_buffer_A;
		
		spi_transmit_pointer_READ = &spi_transmit_pointer_B;
		spi_transmit_buffer_READ = spi_transmit_buffer_B;
		
	} else {
		
		spi_transmit_pointer_WRITE = &spi_transmit_pointer_B;
		spi_transmit_buffer_WRITE = spi_transmit_buffer_B;
		
		spi_transmit_pointer_READ = &spi_transmit_pointer_A;
		spi_transmit_buffer_READ = spi_transmit_buffer_A;
		
	}
}

/**
 * SPI Interrupt handler. The whole SPI state machine takes place here. It is triggered by the SPI hardware after a byte is received.
 */
ISR(SPI_STC_vect) {
	
	//===================================================================================
	//  S P I   I D L E   S T A T E 
	//===================================================================================
	if (spi_state == SPI_STATE_IDLE) {
		
		// Just asking for the events
		if (SPDR == SPI_GET_SIMPLE) {
			
			if (*spi_transmit_pointer_WRITE > 0) {
				
				spi_change_transmit_buffers();
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
				
				spi_state = SPI_STATE_TRANSMIT_SIMPLE;
				
			}  else {
				SPDR = *spi_transmit_pointer_WRITE;
			}
		
		// Get events while sending LED data	
		} else if (SPDR == SPI_GET_WITH_LED) {
			
			if (*spi_transmit_pointer_WRITE > 0) {
				spi_change_transmit_buffers();
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
			} else {
				// if there is no data, it can wait after the led loop
				SPDR = 0;
			}
			
			spi_state = SPI_STATE_TRANSMIT_LED;
			spi_receive_pointer = 2;
			
		// Get events while sending top LCD data
		} else if (SPDR == SPI_GET_WITH_LCD_TOP) {
			
			if (*spi_transmit_pointer_WRITE > 0) {
				
				spi_change_transmit_buffers();
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
				
			} else {
				SPDR = 0;
			}
			
			spi_state = SPI_STATE_TRANSMIT_LCD_TOP;
			spi_receive_pointer = 16;
			
		// Get events while sending bottom LCD data
		} else if (SPDR == SPI_GET_WITH_LCD_BOTTOM) {
		
			if (*spi_transmit_pointer_WRITE > 0) {
				
				spi_change_transmit_buffers();
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
				
			} else {
				SPDR = 0;
			}
			
			spi_state = SPI_STATE_TRANSMIT_LCD_BOTTOM;
			spi_receive_pointer = 16;
			
		// Get DIP status
		} else if (SPDR == SPI_GET_DIP_STATUS) {
		
			SPDR = dip_status;
			spi_state = SPI_STATE_TRANSMIT_DIP_STATUS;

		} else {
			
			SPDR = *spi_transmit_pointer_WRITE;
			
		}
	
	//===================================================================================
	//  S P I   S I M P L E   T R A N S M I T   S T A T E
	//===================================================================================
	} else if (spi_state == SPI_STATE_TRANSMIT_SIMPLE) {
		
		if (*spi_transmit_pointer_READ == 0) {
			SPDR = *spi_transmit_pointer_WRITE;
			spi_state = SPI_STATE_IDLE;
		} else {
			SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
		}
		
		
		
	//===================================================================================
	//  S P I   L E D   T R A N S M I T   S T A T E
	//===================================================================================
	} else if (spi_state == SPI_STATE_TRANSMIT_LED) {
		
		if (--spi_receive_pointer == 0) {
			spi_flag = SPI_FLAG_LED;
			spi_state = SPI_STATE_IDLE;
			SPDR = *spi_transmit_pointer_WRITE;
		} else {
			if (*spi_transmit_pointer_READ > 0) {
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
			} else {
				SPDR = 0;
			}
		}
		
		spi_receive_buffer[spi_receive_pointer] = SPDR;
		
	
	//===================================================================================
	//  S P I   L C D   T O P   T R A N S M I T   S T A T E
	//===================================================================================
	} else if (spi_state == SPI_STATE_TRANSMIT_LCD_TOP) {
	
		if (--spi_receive_pointer == 0) {
			spi_flag = SPI_FLAG_LCD_TOP;
			spi_state = SPI_STATE_IDLE;
			SPDR = *spi_transmit_pointer_WRITE;
		} else {
			if (*spi_transmit_pointer_READ > 0) {
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
			} else {
				SPDR = 0;
			}
		}
		
		spi_receive_buffer[spi_receive_pointer] = SPDR;
		
		
	//===================================================================================
	//  S P I   L C D   B O T T O M   T R A N S M I T   S T A T E
	//===================================================================================
	} else if (spi_state == SPI_STATE_TRANSMIT_LCD_BOTTOM) {
	
		if (--spi_receive_pointer == 0) {
			spi_flag = SPI_FLAG_LCD_BOTTOM;
			spi_state = SPI_STATE_IDLE;
			SPDR = *spi_transmit_pointer_WRITE;
		} else {
			if (*spi_transmit_pointer_READ > 0) {
				SPDR = spi_transmit_buffer_READ[--(*spi_transmit_pointer_READ)];
			} else {
				SPDR = 0;
			}
		}
	
		spi_receive_buffer[spi_receive_pointer] = SPDR;
		
		
	//===================================================================================
	//  S P I   D I P   S T A T U S   T R A N S M I T   S T A T E
	//===================================================================================
	} else if (spi_state == SPI_STATE_TRANSMIT_DIP_STATUS) {
	
		spi_state = SPI_STATE_IDLE;
		SPDR = *spi_transmit_pointer_WRITE;
	
	} // end of spi_state checkings
	
}



//===================================================================================
//  S P I   M O D U L E   A P I   F U N C T I O N S
//===================================================================================

void spi_add_down(uint8_t id) {
	cli();
	uint8_t temp = EVENT_DOWN;
	
	// the dip switches were excluded this code, because there is a dedicated dip switch readout mechanism
	switch (id) {
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	// if there is a real event, write it to the WRITE buffer
	if (temp != 0) {
		spi_transmit_buffer_WRITE[(*spi_transmit_pointer_WRITE)++] = temp;
		if (spi_state == SPI_STATE_IDLE) {
			SPDR = *spi_transmit_pointer_WRITE;
		}
	}
	
	sei();
}

void spi_add_up(uint8_t id) {
	cli();
	uint8_t temp = EVENT_UP;
	
	// the dip switches were excluded this code, because there is a dedicated dip switch readout mechanism
	switch (id) {
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	// if there is a real event, write it to the WRITE buffer
	if (temp != 0) {
		spi_transmit_buffer_WRITE[(*spi_transmit_pointer_WRITE)++] = temp;
		if (spi_state == SPI_STATE_IDLE) {
			SPDR = *spi_transmit_pointer_WRITE;
		}
	}
	
	sei();
}

void spi_add_short_press(uint8_t id) {
	cli();
	uint8_t temp = EVENT_SHORT;
	
	// the dip switches were excluded this code, because there is a dedicated dip switch readout mechanism
	switch (id) {
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	// if there is a real event, write it to the WRITE buffer
	if (temp != 0) {
		spi_transmit_buffer_WRITE[(*spi_transmit_pointer_WRITE)++] = temp;
		if (spi_state == SPI_STATE_IDLE) {
			SPDR = *spi_transmit_pointer_WRITE;
		}
	}
	
	sei();
}

void spi_add_long_press(uint8_t id) {
	cli();
	uint8_t temp = EVENT_LONG;
	
	// the dip switches were excluded this code, because there is a dedicated dip switch readout mechanism
	switch (id) {
		case 1:		temp |= EVENT_TYPE_FUNCTION |	6; break;
		case 2:		temp |= EVENT_TYPE_NUMPAD |		9; break;
		case 3:		temp |= EVENT_TYPE_NUMPAD |		8; break;
		case 5:		temp |= EVENT_TYPE_FUNCTION |	4; break;
		case 6:		temp |= EVENT_TYPE_NUMPAD |		12; break;
		case 7:		temp |= EVENT_TYPE_NUMPAD |		7; break;
		case 9:		temp |= EVENT_TYPE_FUNCTION |	3; break;
		case 10:	temp |= EVENT_TYPE_NUMPAD |		11; break;
		case 11:	temp |= EVENT_TYPE_NUMPAD |		6; break;
		case 13:	temp |= EVENT_TYPE_FUNCTION |	2; break;
		case 14:	temp |= EVENT_TYPE_NUMPAD |		10; break;
		case 15:	temp |= EVENT_TYPE_NUMPAD |		5; break;
		case 17:	temp |= EVENT_TYPE_FUNCTION |	1; break;
		case 18:	temp |= EVENT_TYPE_FUNCTION |	5; break;
		case 19:	temp |= EVENT_TYPE_NUMPAD |		4; break;
		case 21:	temp |= EVENT_TYPE_ENCODER |	3; break;
		case 22:	temp |= EVENT_TYPE_FUNCTION |	8; break;
		case 23:	temp |= EVENT_TYPE_NUMPAD |		3; break;
		case 25:	temp |= EVENT_TYPE_ENCODER |	2; break;
		case 26:	temp |= EVENT_TYPE_FUNCTION |	7; break;
		case 27:	temp |= EVENT_TYPE_NUMPAD |		2; break;
		case 29:	temp |= EVENT_TYPE_ENCODER |	1; break;
		case 30:	temp |= EVENT_TYPE_FUNCTION |	9; break;
		case 31:	temp |= EVENT_TYPE_NUMPAD |		1; break;
		default:	temp = 0;
	}
	
	// if there is a real event, write it to the WRITE buffer
	if (temp != 0) {
		spi_transmit_buffer_WRITE[(*spi_transmit_pointer_WRITE)++] = temp;
		if (spi_state == SPI_STATE_IDLE) {
			SPDR = *spi_transmit_pointer_WRITE;
		}
	}
	
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
	
	spi_transmit_buffer_WRITE[(*spi_transmit_pointer_WRITE)++] = temp;
	if (spi_state == SPI_STATE_IDLE) {
		SPDR = *spi_transmit_pointer_WRITE;
	}
	
	sei();
}

/** \} */
