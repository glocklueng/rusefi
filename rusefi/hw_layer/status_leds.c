/*
 * status_leds.c
 *
 *  Created on: Jan 24, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <board.h>
#include "main.h"
#include "status_leds.h"

#include "pin_repository.h"

int ledCurrentStatus[LED_COUNT];
GPIO_TypeDef *ledPort[LED_COUNT];
int ledPin[LED_COUNT];

/**
 * blinking thread to show that we are alive
 */
static WORKING_AREA(blinkingThreadStack, 128);

void setStatusLed(int ledIndex, int value) {
	if (ledCurrentStatus[ledIndex] == value)
		return;

	GPIO_TypeDef *port = ledPort[ledIndex];
	int pin = ledPin[ledIndex];

	palWritePad(port, pin, value);
}

static void blinkingThread_s(void *arg) {
	while (TRUE) {
		setStatusLed(LED_ALIVE1, 0);
		setStatusLed(LED_ALIVE2, 1);
		chThdSleepMilliseconds(100);
		setStatusLed(LED_ALIVE1, 1);
		setStatusLed(LED_ALIVE2, 0);
		chThdSleepMilliseconds(100);
	}
}

void ledRegister(char *msg, int led, GPIO_TypeDef *port, uint32_t pinNumber) {
	ledCurrentStatus[led] = -1;
	ledPort[led] = port;
	ledPin[led] = pinNumber;

	mySetPadMode(msg, port, pinNumber, PAL_MODE_OUTPUT_PUSHPULL);
	setStatusLed(led, FALSE);
}

void initStatusLeds() {
	ledRegister("is alive status", LED_ALIVE1, GPIOD, GPIOD_LED3);
	ledRegister("is alive status 2", LED_ALIVE2, GPIOC, 13);
	ledRegister("is cranking status", LED_CRANKING, GPIOD, GPIOD_LED4);
	ledRegister("alive1", LED_RPM, GPIOD, GPIOD_LED5);
	ledRegister("alive1", LED_DEBUG, GPIOD, 2);
	ledRegister("sparkout", LED_SPARKOUT_1, GPIOD, 3);
	ledRegister("sparkout", LED_SPARKOUT_2, GPIOE, 6);
//	ledRegister(LED_SPARKOUT, GPIOD, 0);
//	ledRegister(LED_EMULATOR, GPIOE, 3); // pin is shared with dist_emulator
	ledRegister("injector1", LED_INJECTOR_1, INJECTOR_1_PORT, INJECTOR_1_PIN);
	ledRegister("injector2", LED_INJECTOR_2, GPIOC, 7);
	ledRegister("injector3", LED_INJECTOR_3, GPIOC, 9);
	ledRegister("injector4", LED_INJECTOR_4, GPIOA, 9);


	/* digit 1 */
/*
	ledRegister(LED_HUGE_0, GPIOB, 2);
	ledRegister(LED_HUGE_1, GPIOE, 7);
	ledRegister(LED_HUGE_2, GPIOE, 8);
	ledRegister(LED_HUGE_3, GPIOE, 9);
	ledRegister(LED_HUGE_4, GPIOE, 10);
	ledRegister(LED_HUGE_5, GPIOE, 11);
	ledRegister(LED_HUGE_6, GPIOE, 12);
	/* digit 2 */
	/*
	ledRegister(LED_HUGE_7, GPIOE, 13);
	ledRegister(LED_HUGE_8, GPIOE, 14);
	ledRegister(LED_HUGE_9, GPIOE, 15);
	ledRegister(LED_HUGE_10, GPIOB, 10);
	ledRegister(LED_HUGE_11, GPIOB, 11);
	ledRegister(LED_HUGE_12, GPIOB, 12);
	ledRegister(LED_HUGE_13, GPIOB, 13);
	/* digit 3 */
/*
	ledRegister(LED_HUGE_14, GPIOE, 0);
	ledRegister(LED_HUGE_15, GPIOE, 2);
	ledRegister(LED_HUGE_16, GPIOE, 4);
	ledRegister(LED_HUGE_17, GPIOE, 6);
	ledRegister(LED_HUGE_18, GPIOE, 5);
	ledRegister(LED_HUGE_19, GPIOE, 3);
	ledRegister(LED_HUGE_20, GPIOE, 1);
*/

	chThdCreateStatic(blinkingThreadStack, sizeof(blinkingThreadStack),
			NORMALPRIO, blinkingThread_s, NULL );
}
