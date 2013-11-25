/**
 * @file	output_pins.c
 * @brief	It could be that the main purpose of this file is the status LED blinking
 *
 *  Created on: Jan 24, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <board.h>
#include "main.h"
#include "output_pins.h"

#include "pin_repository.h"
#include "gpio_helper.h"
#include "pinout.h"
#include "print.h"

static OutputPin outputs[OUTPUT_PIN_COUNT];
static PinEnum leds[] = { LED_CRANKING, LED_RUNNING, LED_FATAL, LED_ALIVE3, LED_ALIVE2, LED_DEBUG };

/**
 * blinking thread to show that we are alive
 */
static WORKING_AREA(blinkingThreadStack, 128);

void turnOutputPinOn(PinEnum pin) {
	setOutputPinValue(pin, TRUE);
}

void turnOutputPinOff(PinEnum pin) {
	setOutputPinValue(pin, FALSE);
}

/**
 * @brief todo
 */
void setOutputPinValue(PinEnum pin, int value) {
	setPinValue(&outputs[pin], value);
}

static void blinkingThread_s(void *arg) {
	chRegSetThreadName("blinking");
	while (TRUE) {
		int delay = is_serial_ready() ? 100 : 33;

		setOutputPinValue(LED_ALIVE3, 0);
		setOutputPinValue(LED_ALIVE2, 1);
		chThdSleepMilliseconds(delay);
		setOutputPinValue(LED_ALIVE3, 1);
		setOutputPinValue(LED_ALIVE2, 0);
		chThdSleepMilliseconds(delay);
	}
}

void outputPinRegister(char *msg, int ledIndex, GPIO_TypeDef *port, uint32_t pin) {
	initOutputPin(msg, &outputs[ledIndex], port, pin);

	setOutputPinValue(ledIndex, FALSE);
}

/**
 * This method would blink all the LEDs just to test them
 */
static void initialLedsBlink(void) {
	int size = sizeof(leds) / sizeof(leds[0]);
	for (int i = 0; i < size; i++)
		setOutputPinValue(leds[i], 1);

	chThdSleepMilliseconds(100);

	for (int i = 0; i < size; i++)
		setOutputPinValue(leds[i], 0);
}

void initOutputPins(void) {
	outputPinRegister("is cranking status", LED_CRANKING, GPIOD, GPIOD_LED3);
	outputPinRegister("is running status", LED_RUNNING, GPIOD, GPIOD_LED4);
	outputPinRegister("alive1", LED_FATAL, GPIOD, GPIOD_LED5);
	outputPinRegister("is alive status2", LED_ALIVE3, GPIOD, GPIOD_LED6);

	outputPinRegister("is alive status 2", LED_ALIVE2, GPIOC, 13);
	outputPinRegister("alive1", LED_DEBUG, GPIOD, 6);
	outputPinRegister("sparkout1", SPARKOUT_1_OUTPUT, SPARK_1_PORT, SPARK_1_PIN);
	outputPinRegister("sparkout2", SPARKOUT_2_OUTPUT, GPIOE, 6);

	// todo: should we move this code closer to the injection logic?
	outputPinRegister("injector1", INJECTOR_1_OUTPUT, INJECTOR_1_PORT, INJECTOR_1_PIN);
	outputPinRegister("injector2", INJECTOR_2_OUTPUT, INJECTOR_2_PORT, INJECTOR_2_PIN);
	outputPinRegister("injector3", INJECTOR_3_OUTPUT, INJECTOR_3_PORT, INJECTOR_3_PIN);
	outputPinRegister("injector4", INJECTOR_4_OUTPUT, INJECTOR_4_PORT, INJECTOR_4_PIN);

	// todo: should we move this code closer to the fuel pump logic?
	outputPinRegister("fuel pump", FUEL_PUMP, FUEL_PUMP_PORT, FUEL_PUMP_PIN);

	initialLedsBlink();

	// digit 1
	/*
	 ledRegister(LED_HUGE_0, GPIOB, 2);
	 ledRegister(LED_HUGE_1, GPIOE, 7);
	 ledRegister(LED_HUGE_2, GPIOE, 8);
	 ledRegister(LED_HUGE_3, GPIOE, 9);
	 ledRegister(LED_HUGE_4, GPIOE, 10);
	 ledRegister(LED_HUGE_5, GPIOE, 11);
	 ledRegister(LED_HUGE_6, GPIOE, 12);

	 // digit 2
	 ledRegister(LED_HUGE_7, GPIOE, 13);
	 ledRegister(LED_HUGE_8, GPIOE, 14);
	 ledRegister(LED_HUGE_9, GPIOE, 15);
	 ledRegister(LED_HUGE_10, GPIOB, 10);
	 ledRegister(LED_HUGE_11, GPIOB, 11);
	 ledRegister(LED_HUGE_12, GPIOB, 12);
	 ledRegister(LED_HUGE_13, GPIOB, 13);

	 // digit 3
	 ledRegister(LED_HUGE_14, GPIOE, 0);
	 ledRegister(LED_HUGE_15, GPIOE, 2);
	 ledRegister(LED_HUGE_16, GPIOE, 4);
	 ledRegister(LED_HUGE_17, GPIOE, 6);
	 ledRegister(LED_HUGE_18, GPIOE, 5);
	 ledRegister(LED_HUGE_19, GPIOE, 3);
	 ledRegister(LED_HUGE_20, GPIOE, 1);
	 */

	chThdCreateStatic(blinkingThreadStack, sizeof(blinkingThreadStack),
	NORMALPRIO, (tfunc_t) blinkingThread_s, NULL);
}

