/**
 * @file	io_pins.h
 *
 * @date Jan 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef STATUS_LEDS_H_
#define STATUS_LEDS_H_

#include "rusefi_enums.h"

typedef enum {
	LED_CRANKING, // Orange on-board LED
	LED_RUNNING, // Green on-board LED
	LED_ERROR, // Red on-board LED
	LED_COMMUNICATION_1, // Blue on-board LED
	LED_ALIVE2, // external board LED
	LED_DEBUG,
	LED_EMULATOR,

	SPARKOUT_1_OUTPUT,
	SPARKOUT_2_OUTPUT,
	SPARKOUT_3_OUTPUT,
	SPARKOUT_4_OUTPUT,
	SPARKOUT_5_OUTPUT,
	SPARKOUT_6_OUTPUT,

	INJECTOR_1_OUTPUT,
	INJECTOR_2_OUTPUT,
	INJECTOR_3_OUTPUT,
	INJECTOR_4_OUTPUT,
	INJECTOR_5_OUTPUT,
	INJECTOR_6_OUTPUT,

	ELECTRONIC_THROTTLE_CONTROL_1,
	ELECTRONIC_THROTTLE_CONTROL_2,
	ELECTRONIC_THROTTLE_CONTROL_3,

	/* digit 1 */
	LED_HUGE_0, // B2
	LED_HUGE_1,
	LED_HUGE_2,
	LED_HUGE_3,
	LED_HUGE_4,
	LED_HUGE_5,
	LED_HUGE_6,
	/* digit 2 */
	LED_HUGE_7,
	LED_HUGE_8,
	LED_HUGE_9, // E15
	LED_HUGE_10,
	LED_HUGE_11,
	LED_HUGE_12,
	LED_HUGE_13,
	/* digit 3 */
	LED_HUGE_14,
	LED_HUGE_15,
	LED_HUGE_16,
	LED_HUGE_17,
	LED_HUGE_18,
	LED_HUGE_19,
	LED_HUGE_20,

	// malfunction LED indicator - CheckEngine
	LED_CHECK_ENGINE,
	
	FUEL_PUMP,

	SPI_CS_1,
	SPI_CS_2,
	SPI_CS_3,
	SPI_CS_4,
	SPI_CS_SD_MODULE,

} io_pin_e;

#define IO_PIN_COUNT 100

void initOutputPins(void);
char *getPinName(io_pin_e io_pin);
void turnOutputPinOn(io_pin_e pin);
void turnOutputPinOff(io_pin_e pin);
void setOutputPinValue(io_pin_e pin, int electricalValue);
int getOutputPinValue(io_pin_e pin);
void outputPinRegisterExt(char *msg, io_pin_e ioPin, GPIO_TypeDef *port, uint32_t pin);
void setDefaultPinState(io_pin_e pin, pin_output_mode_e *defaultState);

#endif /* STATUS_LEDS_H_ */
