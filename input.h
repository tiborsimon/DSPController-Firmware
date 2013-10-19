/**
 * \addtogroup inputs
 * \{
 * \file
 * \author Tibor Simon <tiborsimon@tibor-simon.com>
 * \version 1.0
 *
 * \ref license
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "includes.h"


/**
 * \addtogroup buttons
 * \{
 * The system that handles the buttons connected to the shift registers is very simple and reliable. It uses only two registers
 * for each 32 buttons: the debounce register and the status register. The algorithm runs every 1 ms. It was triggered by a timer
 * interrupt that kicks in every 0.5 ms, so a simple waiting code prevent the run every second interrupt.
 *
 * The status register contains the following bits:
 *  15             | 14           | 13          | 12         | 11        | 10 : 0
 *  :------------- | :----------- | :---------- | :--------- | :-------- | :-----------------
 *  previous state | actual state | short press | long press | long lock | long press counter
 *
 * - \b previous \b state: stores the previous debounced state of the given button
 * - \b actual \b state: contains the actual debounced state of the given button
 * - \b short \b press: it latches when a short press event is occured
 * - \b long \b press: it latches when a long press event is occured. It is in exclusive relation with the short press bit.
 * - \b long \b lock: because the debounce algorithm fires the long press event during the key is pressed down, there need to be some lock that prevents the re-triggering of the long press event when the software reads out and clears the long press flag.
 * - \b long \b press counter: counter that counts when the given button is pressed down. It will be cleared when an event is occured.
 *
 * It generates three type of events:
 * - \b actual \b value: nothing fancy, the actual debounced button state
 * - \b short \b press: the user pressed and released the button before the counter reached the long press threshold
 * - \b long \b press: the user pressed and held down the button. Long press event is triggered, when the counter reaches the treshold value.
 *
 */

/*==============================================================
  I N P U T   B U T T O N S
==============================================================*/

#define DEBOUNCE_MASK	0x0f					/**< Mask that determines the length of the debounce register. Masked out bits are ignored.  */

#define PREVIOUS_MASK	0x8000					/**< Mask for the \a previous \a bit. */
#define PREVIOUS_SET	PREVIOUS_MASK			/**< Variable that sets the \a previous \a bit. For  the more readable code. [it needs OR logic] */
#define PREVIOUS_CLEAR	0x7fff					/**< Variable that clears the \a previous \a bit. [it needs AND logic] */

#define ACTUAL_MASK		0x4000					/**< Mask for the \a actual \a bit. */
#define ACTUAL_SET		ACTUAL_MASK				/**< Variable that sets the \a actual \a bit. For  the more readable code. [it needs OR logic] */
#define ACTUAL_CLEAR	0xbfff					/**< Variable that clears the \a actual \a bit. [it needs AND logic] */

#define SHORT_MASK		0x2000					/**< Mask for the \a short \a bit. */
#define SHORT_SET		SHORT_MASK				/**< Variable that sets the \a short \a bit. For  the more readable code. [it needs OR logic] */
#define SHORT_CLEAR		0xdfff					/**< Variable that clears the \a short \a bit. [it needs AND logic] */

#define LONG_MASK		0x1000					/**< Mask for the \a long \a bit. */
#define LONG_SET		LONG_MASK				/**< Variable that sets the \a long \a bit. For  the more readable code. [it needs OR logic] */
#define LONG_CLEAR		0xefff					/**< Variable that clears the \a long \a bit. [it needs AND logic] */

#define LOCK_MASK		0x0800					/**< Mask for the \a lock \a bit. */
#define LOCK_SET		LOCK_MASK				/**< Variable that sets the \a lock \a bit. For  the more readable code. [it needs OR logic] */
#define LOCK_CLEAR		0xf7ff					/**< Variable that clears the \a lock \a bit. [it needs AND logic] */

#define COUNTER_MASK	0x07ff					/**< Mask for the long press \a counter. */
#define COUNTER_CLEAR	0xf800					/**< Variable that clears the \a counter. [it needs AND logic] */

#define COUNTER_THRESHOLD	350					/**< The limit that determines the length of the long press event. It may be adjustable in a later release. */


extern volatile uint8_t debounce[32]; /**< Debounce register that is functioning as a shift register. New sampled data are shifted in this register. The algorithm processes these data. */

/**
 * Button's status
 *  15             | 14           | 13          | 12         | 11        | 10 : 0
 *  :------------- | :----------- | :---------- | :--------- | :-------- | :-----------------
 *  previous state | actual state | short press | long press | long lock | long press counter
 */
extern volatile uint16_t button_status[32];

/*==============================================================
  Q U E R Y   F U N C T I O N   F O R   T H E   B U T T O N S 
==============================================================*/


// #define EVENT_NOTHING		0x00	/**< Return value for the query function. */
// #define EVENT_LONG_PRESS	0x01	/**< Return value for the query function. */
// #define EVENT_SHORT_PRESS	0x02	/**< Return value for the query function. */


/**
 * Function that queries the events. If an event is triggered it returns the event, and clears 
 * the corresponding status atomically.
 * \param[in] p Index to the button you want to query. [0..31]
 * \returns The triggered event.
 */
uint8_t get_button_event( uint8_t p );

/** \} */

/**
 * \addtogroup encoders
 * \{
 * The system that do the processing of the encoders is triggered by a timer interrupt. The interrupt kicks in 
 * every 0.5 ms. It uses 3 register: 
 * - \b encoder_debounce[6]: 8 bit debounce register that is used like a shift register 
 * - \b encoder_counter[3]: 8 bit signed register, that stores the 3 encoders value
 * - \b encoder_status[6]: 8 bit status register for each encoder signal (A and B for each encoder)
 *
 * Status register bits:
 * 7              | 6            | 5      | 4 : 0
 * :------------- | :----------- | :----- | :-------
 * previous state | actual state | master | reserved
 * 
 * - \b previous \b state: it stores the previous debounced signal state
 * - \b actual \b state: it stores the actual debounced signal state
 * - \b master: it is set when the corresponding signal is the A encoder signal. The algorithm uses this bit to determine at which signal needs to detect the rising edge.
 *
 * The algorithm uses one encoder signal edge to determine rotation direction.
 */

/*==============================================================
  E N C O D E R S
==============================================================*/

#define E_DEBOUNCE_MASK		0x07					/**< Mask for the long press \a counter. */

#define E_PREVIOUS_MASK		0x80					/**< Mask for the \a previous \a bit. */
#define E_PREVIOUS_SET		E_PREVIOUS_MASK			/**< Variable that sets the \a previous \a bit. For  the more readable code. [it needs OR logic] */
#define E_PREVIOUS_CLEAR	0x7f					/**< Variable that clears the \a previous \a bit. [it needs AND logic] */

#define E_ACTUAL_MASK		0x40					/**< Mask for the \a actual \a bit. */
#define E_ACTUAL_SET		E_ACTUAL_MASK			/**< Variable that sets the \a actual \a bit. For  the more readable code. [it needs OR logic] */
#define E_ACTUAL_CLEAR		0xbf					/**< Variable that clears the \a actual \a bit. [it needs AND logic] */

#define E_MASTER_MASK		0x20					/**< Mask for the \a master \a bit. */
#define E_MASTER_SET		E_MASTER_MASK			/**< Variable that sets the \a master \a bit. For  the more readable code. [it needs OR logic] */
#define E_MASTER_CLEAR		0xdf					/**< Variable that clears the \a master \a bit. [it needs AND logic] */

extern volatile uint8_t encoder_debounce[6];  /**< Debounce register that debounces the encoders raw signals. */
extern volatile int8_t encoder_counter[3];  /**< Counter register for each encoders. It is a signed register, it uses two's complement.  */

/**
 * Encoder's status
 * 7              | 6            | 5      | 4 : 0
 * :------------- | :----------- | :----- | :------
 * previous state | actual state | master | counter
 */
extern volatile int8_t encoder_status[6];

/*==============================================================
  Q U E R Y   F U N C T I O N   F O R   T H E   E N C O D E R S 
==============================================================*/

/**
 * Function that returns the current counter value of the given encoder.
 * If the value isn't zero, it clears the counter atomically.
 * \param[in] p Index to the encoder you want to query. [0..2]
 * \returns The triggered event.
 */
int8_t get_encoder_value( uint8_t p );

/** \} */



/*==============================================================
  C O M M O N   F U N C T I O N S
==============================================================*/

extern volatile uint8_t status[16];
extern volatile uint8_t status_ready;

/**
 * Function that initializes the registers for the debounce algorithm.
 */
void input_init();



#endif /* INPUT_H_ */
/** \} */