/*
 * status_leds.c
 *
 *  Created on: Jan 24, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <board.h>
#include "main.h"
#include "output_pins.h"

#include "pin_repository.h"

static OutputPin outputs[LED_COUNT];

/**
 * blinking thread to show that we are alive
 */
static WORKING_AREA(blinkingThreadStack, 128);

void setPinValue(OutputPin * outputPin, int value) {
	if (outputPin->currentValue == value)
		return;

	palWritePad(outputPin->port, outputPin->pin, value);
	outputPin->currentValue = value;
}

void setOutputPinValue(int ledIndex, int value) {
	setPinValue(&outputs[ledIndex], value);
}

static void blinkingThread_s(void *arg) {
	chRegSetThreadName("blinking");
	while (TRUE) {
		setOutputPinValue(LED_ALIVE3, 0);
		setOutputPinValue(LED_ALIVE2, 1);
		chThdSleepMilliseconds(100);
		setOutputPinValue(LED_ALIVE3, 1);
		setOutputPinValue(LED_ALIVE2, 0);
		chThdSleepMilliseconds(100);
	}
}

void initOutputPin(char *msg, OutputPin *outputPin, GPIO_TypeDef *port, uint32_t pinNumber) {
	outputPin->currentValue = -1;
	outputPin->port = port;
	outputPin->pin = pinNumber;

	mySetPadMode(msg, port, pinNumber, PAL_MODE_OUTPUT_PUSHPULL);
}

void ledRegister(char *msg, int ledIndex, GPIO_TypeDef *port, uint32_t pin) {
	initOutputPin(msg, &outputs[ledIndex], port, pin);

	setOutputPinValue(ledIndex, FALSE);
}

void initOutputPins() {
	ledRegister("is cranking status", LED_CRANKING, GPIOD, GPIOD_LED3);
	ledRegister("is running status", LED_RUNNING, GPIOD, GPIOD_LED4);
	ledRegister("alive1", LED_FATAL, GPIOD, GPIOD_LED5);
	ledRegister("is alive status2", LED_ALIVE3, GPIOD, GPIOD_LED6);

	ledRegister("is alive status 2", LED_ALIVE2, GPIOC, 13);
	ledRegister("alive1", LED_DEBUG, GPIOD, 2);
	ledRegister("sparkout1", SPARKOUT_1_OUTPUT, SPARK_1_PORT, SPARK_1_PIN);
	ledRegister("sparkout2", SPARKOUT_2_OUTPUT, GPIOE, 6);

	ledRegister("injector1", INJECTOR_1_OUTPUT, INJECTOR_1_PORT, INJECTOR_1_PIN);
	ledRegister("injector2", INJECTOR_2_OUTPUT, INJECTOR_2_PORT, INJECTOR_2_PIN);
	ledRegister("injector3", INJECTOR_3_OUTPUT, INJECTOR_3_PORT, INJECTOR_3_PIN);
	ledRegister("injector4", INJECTOR_4_OUTPUT, INJECTOR_4_PORT, INJECTOR_4_PIN);

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
