/**
 * \addtogroup spi
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 *
 */


#ifndef SPI_H_
#define SPI_H_

#define SPI_GET_SIMPLE					0x10		/**< SPI message code that is identical for the DSPController and the HOST. This message initiates a simple event readout. */
#define SPI_GET_WITH_LED				0x11		/**< SPI message code that is identical for the DSPController and the HOST. This message initiates an event readout with led data, sent parallel during the readout. */
#define SPI_GET_WITH_LCD_TOP			0x12		/**< SPI message code that is identical for the DSPController and the HOST. This message initiates an event readout with top lcd data, sent parallel during the readout. */		
#define SPI_GET_WITH_LCD_BOTTOM			0x13		/**< SPI message code that is identical for the DSPController and the HOST. This message initiates an event readout with bottom lcd data, sent parallel during the readout. */
#define SPI_GET_DIP_STATUS				0x14		/**< SPI message code that is identical for the DSPController and the HOST. This message initiates a dip state readout. */

#define SPI_STATE_IDLE					0			/**< SPI state that represents the idle state. The SPI module is waiting for the trigger signal between readouts. */
#define SPI_STATE_TRANSMIT_SIMPLE		1			/**< SPI state that represents the simple readout. The HOST reads out the events. */
#define SPI_STATE_TRANSMIT_LED			2			/**< SPI state that represents the simple readout with LED data. The HOST reads out the events while it sends LED data. */
#define SPI_STATE_TRANSMIT_LCD_TOP		3			/**< SPI state that represents the simple readout with top LCD data. The HOST reads out the events while it sends top LCD data. */
#define SPI_STATE_TRANSMIT_LCD_BOTTOM	4			/**< SPI state that represents the simple readout with bottom LCD data. The HOST reads out the events while it sends bottom LCD data. */
#define SPI_STATE_TRANSMIT_DIP_STATUS	5			/**< SPI state that represents the dip status readout. The HOST reads out the dip status. */

#define SPI_FLAG_NONE					0			/**< Flag, which the SPI module signals the main loop, that there is no incoming data in the buffer. */
#define SPI_FLAG_LED					1			/**< Flag, which the SPI module signals the main loop, that there is LED data in the buffer. */
#define	SPI_FLAG_LCD_TOP				2			/**< Flag, which the SPI module signals the main loop, that there is top LCD data in the buffer. */
#define	SPI_FLAG_LCD_BOTTOM				3			/**< Flag, which the SPI module signals the main loop, that there is bottom LCD data in the buffer. */

#define EVENT_DOWN						0x00		/**< Event part, that represents a down event. The SPI module will assemble the message with this parts. */
#define EVENT_UP						0x40		/**< Event part, that represents a up event. The SPI module will assemble the message with this parts. */
#define EVENT_SHORT						0x80		/**< Event part, that represents a short down event. The SPI module will assemble the message with this parts. */
#define EVENT_LONG						0xc0		/**< Event part, that represents a long down event. The SPI module will assemble the message with this parts. */

#define EVENT_TYPE_NUMPAD				0x00		/**< Event type, that represents a numpad event. */
#define EVENT_TYPE_FUNCTION				0x10		/**< Event type, that represents a function button event. */
#define EVENT_TYPE_ENCODER				0x20		/**< Event type, that represents a encoder event. */
#define EVENT_TYPE_DIP					0x30		/**< Event type, that represents a dip event. */

extern volatile uint8_t spi_state;						/**< SPI state variable, that holds the state of the SPI module. */

extern volatile uint8_t spi_transmit_A_not_B;			/**< Variable that decides which SPI buffer will be the next readable buffer.  */	
extern volatile uint8_t spi_transmit_pointer_A;			/**< Index variable that indexes the last item in the A buffer. */	
extern volatile uint8_t spi_transmit_pointer_B;			/**< Index variable that indexes the last item in the B buffer. */
extern volatile uint8_t spi_transmit_buffer_A[40];		/**< Transmit buffer A, that holds the events that occurred during the input processing. */
extern volatile uint8_t spi_transmit_buffer_B[40];		/**< Transmit buffer B, that holds the events that occurred during the input processing. */

extern volatile uint8_t* spi_transmit_pointer_READ;		/**< Pointer for code simplification that points to the actual READ pointer that indexes the last item in the actual READ buffer. */
extern volatile uint8_t* spi_transmit_buffer_READ;		/**< Pointer for code simplification that points to the actual READ buffer. */
extern volatile uint8_t* spi_transmit_pointer_WRITE;	/**< Pointer for code simplification that points to the actual WRITE pointer that indexes the last item in the actual WRITE buffer. */
extern volatile uint8_t* spi_transmit_buffer_WRITE;		/**< Pointer for code simplification that points to the actual WRITE buffer. */

extern volatile uint8_t spi_receive_pointer;			/**< Index variable to index the last item in the incoming data buffer used for LCD and LED data. */
extern volatile uint8_t	spi_receive_buffer[36];			/**< SPI receive buffer that holds incoming LCD and LED data. */
extern volatile uint8_t spi_flag;						/**< Flag variable that holds the latest incoming event type.*/

/**
 * SPI module API function. This function can be called when an event occurs. This function will process the given id, and will put
 * a down message to the actual WRITE buffer.
 * \param[in] id ID that represents the event source. This is the index of the event source in the input status register.
 */
void spi_add_down(uint8_t id);

/**
 * SPI module API function. This function can be called when an event occurs. This function will process the given id, and will put
 * an up message to the actual WRITE buffer.
 * \param[in] id ID that represents the event source. This is the index of the event source in the input status register.
 */
void spi_add_up(uint8_t id);

/**
 * SPI module API function. This function can be called when an event occurs. This function will process the given id, and will put
 * a short press message to the actual WRITE buffer.
 * \param[in] id ID that represents the event source. This is the index of the event source in the input status register.
 */
void spi_add_short_press(uint8_t id);

/**
 * SPI module API function. This function can be called when an event occurs. This function will process the given id, and will put
 * a long press message to the actual WRITE buffer.
 * \param[in] id ID that represents the event source. This is the index of the event source in the input status register.
 */
void spi_add_long_press(uint8_t id);

/**
 * SPI module API function. This function can be called when an event occurs. This function will process the given id, and will put
 * an encoder message to the actual WRITE buffer.
 * \param[in] id ID that represents the event source. This is the index of the event source in the input status register.
 */
void spi_add_encoder(uint8_t id);

/**
 * This function will change the pointers between the READ and WRITE buffers. The previous READ buffer will be the actual WRITE
 * buffer and vice versa.
 */
void spi_change_transmit_buffers();

/**
 * This function will initialize the SPI module. It configures the SPI hardware as a slave, set the IO pins accordingly,
 * initializes the SPI module's state variable, and the double buffered mechanism.
 */
void spi_init();


#endif /* SPI_H_ */
/** \} */
