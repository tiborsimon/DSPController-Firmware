/*
 * spi.h
 *
 * Created: 10/15/2013 4:58:22 PM
 *  Author: Tibor
 */ 


#ifndef SPI_H_
#define SPI_H_

#define SPI_GET_SIMPLE			0x10
#define SPI_DATA_READY			85				

#define SPI_STATE_IDLE			0
#define SPI_STATE_TRANSMIT		1

#define EVENT_DOWN				0x00
#define EVENT_UP				0x40
#define EVENT_SHORT				0x80
#define EVENT_LONG				0xc0

#define EVENT_TYPE_NUMPAD		0x00
#define EVENT_TYPE_FUNCTION		0x10
#define EVENT_TYPE_ENCODER		0x20
#define EVENT_TYPE_DIP			0x30

extern volatile uint8_t spi_state;
extern volatile uint8_t spi_pointer;
extern volatile uint8_t spi_transmit_buffer[16];

void spi_add_down(uint8_t id);
void spi_add_up(uint8_t id);
void spi_add_short_press(uint8_t id);
void spi_add_long_press(uint8_t id);
void spi_add_encoder(uint8_t id);

void spi_init();
// void spi_load_transmit_buffer();





#endif /* SPI_H_ */