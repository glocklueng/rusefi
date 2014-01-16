/**
 * @file	io_pins.c
 * @brief	It could be that the main purpose of this file is the status LED blinking
 *
 * @date Jan 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <board.h>
#include "main.h"
#include "io_pins.h"

#include "pin_repository.h"
#include "gpio_helper.h"
#include "pinout.h"
#include "status_loop.h"
#include "shaft_position_input.h"
#include "main_trigger_callback.h"
#include "trigger_decoder.h"

static pin_output_mode_e *pinDefaultState[IO_PIN_COUNT];
static OutputPin outputs[IO_PIN_COUNT];
static io_pin_e leds[] = { LED_CRANKING, LED_RUNNING, LED_ERROR, LED_COMMUNICATION_1, LED_ALIVE2, LED_DEBUG, LED_CHECK_ENGINE };

/**
 * blinking thread to show that we are alive
 */
static WORKING_AREA(comBlinkingStack, UTILITY_THREAD_STACK_SIZE);

/**
 * error thread to show error condition (blinking LED means non-fatal error)
 */
static WORKING_AREA(errBlinkingStack, UTILITY_THREAD_STACK_SIZE);

void turnOutputPinOn(io_pin_e pin) {
	setOutputPinValue(pin, TRUE);
}

void turnOutputPinOff(io_pin_e pin) {
	setOutputPinValue(pin, FALSE);
}

/**
 * @return 0 for OM_DEFAULT and OM_OPENDRAIN
 */

static int getElectricalValue0(pin_output_mode_e mode) {
	return mode == OM_INVERTED || mode == OM_OPENDRAIN_INVERTED;
}

/**
 * @return 1 for OM_DEFAULT and OM_OPENDRAIN
 */
static int getElectricalValue1(pin_output_mode_e mode) {
	return mode == OM_DEFAULT || mode == OM_OPENDRAIN;
}

static int getElectricalValue(int logicalValue, pin_output_mode_e mode) {
	return logicalValue ? getElectricalValue1(mode) : getElectricalValue0(mode);
}


/**
 * @brief Sets the value according to current electrical settings
 */
void setOutputPinValue(io_pin_e pin, int logicValue) {
	setPinValue(&outputs[pin], getElectricalValue(logicValue, *pinDefaultState[pin]));
}

int getOutputPinValue(io_pin_e pin) {
	return getPinValue(&outputs[pin]);
}

void setDefaultPinState(io_pin_e pin, pin_output_mode_e *outputMode) {
	pinDefaultState[pin] = outputMode;
	setOutputPinValue(pin, 0); // initial state
}

static void comBlinkingThread(void *arg) {
	chRegSetThreadName("comm blinking");
	while (TRUE) {
		int delay = is_serial_ready() ? 100 : 33;

		setOutputPinValue(LED_COMMUNICATION_1, 0);
		setOutputPinValue(LED_ALIVE2, 1);
		chThdSleepMilliseconds(delay);

		setOutputPinValue(LED_COMMUNICATION_1, 1);
		setOutputPinValue(LED_ALIVE2, 0);
		chThdSleepMilliseconds(delay);
	}
}

static void errBlinkingThread(void *arg) {
	chRegSetThreadName("err blinking");
	while (TRUE) {
		int delay = 33;
		if (isTriggerDecoderError() || isIgnitionTimingError())
			setOutputPinValue(LED_ERROR, 1);
		chThdSleepMilliseconds(delay);
		if (!hasFatalError())
			setOutputPinValue(LED_ERROR, 0);
		chThdSleepMilliseconds(delay);
	}
}

void outputPinRegister(char *msg, io_pin_e ioPin, GPIO_TypeDef *port, uint32_t pin) {
	initOutputPin(msg, &outputs[ioPin], port, pin);

	setOutputPinValue(ioPin, FALSE);
}

void outputPinRegisterExt(char *msg, io_pin_e ioPin, GPIO_TypeDef *port, uint32_t pin) {
	outputPinRegister(msg, ioPin, port, pin);
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

char *getPinName(io_pin_e io_pin) {
	switch(io_pin) {
	case SPARKOUT_1_OUTPUT:
		return "Spark 1";
	case SPARKOUT_2_OUTPUT:
		return "Spark 2";
	case SPARKOUT_3_OUTPUT:
		return "Spark 3";
	case SPARKOUT_4_OUTPUT:
		return "Spark 4";

	case INJECTOR_1_OUTPUT:
		return "Injector 1";
	case INJECTOR_2_OUTPUT:
		return "Injector 2";
	case INJECTOR_3_OUTPUT:
		return "Injector 3";
	case INJECTOR_4_OUTPUT:
		return "Injector 4";
	case INJECTOR_5_OUTPUT:
		return "Injector 5";
	default:
		return "No name";
	}
}


void initOutputPins(void) {
	outputPinRegister("is cranking status", LED_CRANKING, STATUS_LED_1_PORT, STATUS_LED_1_PIN);
	outputPinRegister("is running status", LED_RUNNING, STATUS_LED_2_PORT, STATUS_LED_2_PIN);
	outputPinRegister("error", LED_ERROR, STATUS_LED_3_PORT, STATUS_LED_3_PIN);
	outputPinRegister("communication status 1", LED_COMMUNICATION_1, STATUS_LED_4_PORT, STATUS_LED_4_PIN);

	outputPinRegister("communication status 2", LED_ALIVE2, EXTRA_LED_1_PORT, EXTRA_LED_1_PIN);
	outputPinRegister("alive1", LED_DEBUG, GPIOD, 6);
	
	outputPinRegister("MalfunctionIndicator",LED_CHECK_ENGINE, LED_CHECK_ENGINE_PORT, LED_CHECK_ENGINE_PIN);

	outputPinRegister("spi CS1", SPI_CS_1, SPI_CS1_PORT, SPI_CS1_PIN);
	outputPinRegister("spi CS2", SPI_CS_2, SPI_CS2_PORT, SPI_CS2_PIN);
	outputPinRegister("spi CS3", SPI_CS_3, SPI_CS3_PORT, SPI_CS3_PIN);
	outputPinRegister("spi CS4", SPI_CS_4, SPI_CS4_PORT, SPI_CS4_PIN);
	outputPinRegister("spi CS5", SPI_CS_SD_MODULE, SPI_SD_MODULE_PORT, SPI_SD_MODULE_PIN);

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

	chThdCreateStatic(comBlinkingStack, sizeof(comBlinkingStack), NORMALPRIO, (tfunc_t) comBlinkingThread, NULL);
	chThdCreateStatic(errBlinkingStack, sizeof(errBlinkingStack), NORMALPRIO, (tfunc_t) errBlinkingThread, NULL);
}

