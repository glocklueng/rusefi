/*
 * status_leds.h
 *
 *  Created on: Jan 24, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef STATUS_LEDS_H_
#define STATUS_LEDS_H_

#include "stm32f4xx_specific.h"
#include "stm32f4xx.h"


typedef enum {
	LED_CRANKING = 0, // Orange on-board led
	LED_ALIVE2 = 1, // ext board
	LED_RUNNING = 2, // Green on-board led
	LED_FATAL = 3, // Red on-board led
	LED_DEBUG = 4,
	LED_EMULATOR = 5,
	LED_ALIVE3 = 6,

	SPARKOUT_1_OUTPUT = 10,
	SPARKOUT_2_OUTPUT = 11,

	INJECTOR_1_OUTPUT = 12,
	INJECTOR_2_OUTPUT = 13,
	INJECTOR_3_OUTPUT = 14,
	INJECTOR_4_OUTPUT = 15,

	/* digit 1 */
	LED_HUGE_0 = 20, // B2
	LED_HUGE_1 = 21,
	LED_HUGE_2 = 22,
	LED_HUGE_3 = 23,
	LED_HUGE_4 = 24,
	LED_HUGE_5 = 25,
	LED_HUGE_6 = 26,
	/* digit 2 */
	LED_HUGE_7 = 27,
	LED_HUGE_8 = 28,
	LED_HUGE_9 = 29, // E15
	LED_HUGE_10 = 30,
	LED_HUGE_11 = 31,
	LED_HUGE_12 = 32,
	LED_HUGE_13 = 33,
	/* digit 3 */
	LED_HUGE_14 = 34,
	LED_HUGE_15 = 35,
	LED_HUGE_16 = 36,
	LED_HUGE_17 = 37,
	LED_HUGE_18 = 38,
	LED_HUGE_19 = 39,
	LED_HUGE_20 = 40,

} PinEnum;

#define OUTPUT_PIN_COUNT 100

void initOutputPins(void);
void setOutputPinValue(int statusLedEnum, int value);

#endif /* STATUS_LEDS_H_ */
