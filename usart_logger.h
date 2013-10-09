/**
 * \addtogroup logger
 * \{	
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */

#ifndef USART_LOGGER_H_
#define USART_LOGGER_H_

	// #define LOGGER_ON_ /*!< Comment out this preprocessor variable and USART Logger will not compile to your binary file. */

	#ifdef LOGGER_ON_
		#define LOG(A, ...) printf(A,##__VA_ARGS__)	/**< Logger macro that wraps around the \a printf function. */
		
		/**
		 * Sending a character via the USART interface.
		 * \param[in] c Character to send.
		 * \param[in] stream Reference to the redirected standard IO stream. 
		 */
		int usart_putchar(char c, FILE *stream);
		
		/**
		 * Receiving a character via the USART interface.
		 * \param[in] stream Reference to the redirected standard IO stream. 
		 * \return The received character.
		 */
		int usart_getchar(FILE *stream);
	#else
		#define LOG(A, ...)	 /* n o t h i n g */	/**< Logger macro if logging is turned off */
	#endif
	
	/** Initialization function that configures the UART hardware and redirects the standard IO stream to the UART itself. */
	void usart_logger_init(void);	
	

#endif // USART_LOGGER_H_
/** \} */