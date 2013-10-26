/**
 * \addtogroup comm
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */


#ifndef SPI_H_
#define SPI_H_

#define SPI_GET_SIMPLE					0x10
#define SPI_GET_WITH_LED				0x11
#define SPI_GET_WITH_LCD_TOP			0x12			
#define SPI_GET_WITH_LCD_BOTTOM			0x13
#define SPI_GET_DIP_STATUS				0x14

#define SPI_STATE_IDLE					0
#define SPI_STATE_TRANSMIT_SIMPLE		1
#define SPI_STATE_TRANSMIT_LED			2
#define SPI_STATE_TRANSMIT_LCD_TOP		3
#define SPI_STATE_TRANSMIT_LCD_BOTTOM	4
#define SPI_STATE_TRANSMIT_DIP_STATUS	5

#define SPI_FLAG_NONE					0
#define SPI_FLAG_LED					1
#define	SPI_FLAG_LCD_TOP				2
#define	SPI_FLAG_LCD_BOTTOM				3

#define EVENT_DOWN						0x00
#define EVENT_UP						0x40
#define EVENT_SHORT						0x80
#define EVENT_LONG						0xc0

#define EVENT_TYPE_NUMPAD				0x00
#define EVENT_TYPE_FUNCTION				0x10
#define EVENT_TYPE_ENCODER				0x20
#define EVENT_TYPE_DIP					0x30

extern volatile uint8_t spi_state;
extern volatile uint8_t spi_transmit_A_not_B;
extern volatile uint8_t spi_transmit_pointer_A;
extern volatile uint8_t spi_transmit_pointer_B;
extern volatile uint8_t spi_transmit_buffer_A[40];
extern volatile uint8_t spi_transmit_buffer_B[40];

extern volatile uint8_t* spi_transmit_pointer_READ;
extern volatile uint8_t* spi_transmit_buffer_READ;
extern volatile uint8_t* spi_transmit_pointer_WRITE;
extern volatile uint8_t* spi_transmit_buffer_WRITE;

extern volatile uint8_t spi_receive_pointer;
extern volatile uint8_t	spi_receive_buffer[36];
extern volatile uint8_t spi_flag;

void spi_add_down(uint8_t id);
void spi_add_up(uint8_t id);
void spi_add_short_press(uint8_t id);
void spi_add_long_press(uint8_t id);
void spi_add_encoder(uint8_t id);

void spi_change_transmit_buffers();

void spi_init();





#endif /* SPI_H_ */