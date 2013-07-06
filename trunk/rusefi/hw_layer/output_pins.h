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

typedef struct {
	GPIO_TypeDef *port;
	int pin;
	/**
	 * we track current pin status so that we do not touch the actual hardware if we want to write new pin bit
	 * which is same as current pin value. This maybe helps in case of status leds, but maybe it's a total over-engineering
	 */
	int currentValue;
} OutputPin;

typedef enum {
	LED_ALIVE1 = 0, // Orange on-board led
	LED_ALIVE2 = 1, // ext board
	LED_CRANKING = 2, // Green on-board led
	LED_RPM = 3, // Red on-board led
	LED_DEBUG = 4,
	LED_EMULATOR = 5,

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

#define LED_COUNT 100

// todo: decide on one API and eliminate the other one. Need to decide between enum for pin indexes and OutputPin?
void initOutputPin(char *msg, OutputPin *outputPin, GPIO_TypeDef *port, uint32_t pinNumber);
void setPinValue(OutputPin * outputPin, int value);

void initOutputPins(void);
void setOutputPinValue(int statusLedEnum, int value);

#endif /* STATUS_LEDS_H_ */
