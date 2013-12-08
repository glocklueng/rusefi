/**
 * @file	output_pins.h
 *
 * @date Jan 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef STATUS_LEDS_H_
#define STATUS_LEDS_H_

typedef enum {
	LED_CRANKING, // Orange on-board led
	LED_ALIVE2, // ext board
	LED_RUNNING, // Green on-board led
	LED_FATAL, // Red on-board led
	LED_DEBUG,
	LED_EMULATOR,
	LED_ALIVE3,

	SPARKOUT_1_OUTPUT,
	SPARKOUT_2_OUTPUT,

	INJECTOR_1_OUTPUT,
	INJECTOR_2_OUTPUT,
	INJECTOR_3_OUTPUT,
	INJECTOR_4_OUTPUT,
	INJECTOR_5_OUTPUT,

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

	FUEL_PUMP,

} PinEnum;

#define OUTPUT_PIN_COUNT 100

void initOutputPins(void);
void turnOutputPinOn(PinEnum pin);
void turnOutputPinOff(PinEnum pin);
void setOutputPinValue(PinEnum pin, int value);
int getOutputPinValue(PinEnum pin);

#endif /* STATUS_LEDS_H_ */
