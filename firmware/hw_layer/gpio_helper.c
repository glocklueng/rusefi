/*
 * gpio_helper.c
 *
 *  Created on: Aug 25, 2013
 *      Author: pc
 */

/**
 * @file    gpio_helper.c
 * @brief   General I/O helper
 */

#ifndef GPIO_HELPER_C_
#define GPIO_HELPER_C_

#include <hal.h>

#include "pin_repository.h"
#include "gpio_helper.h"

void initOutputPin(char *msg, OutputPin *outputPin, GPIO_TypeDef *port, uint32_t pinNumber) {
	outputPin->currentValue = -1;
	outputPin->port = port;
	outputPin->pin = pinNumber;

	mySetPadMode(msg, port, pinNumber, PAL_MODE_OUTPUT_PUSHPULL);
}

void setPinValue(OutputPin * outputPin, int value) {
	if (outputPin->currentValue == value)
		return;

	palWritePad(outputPin->port, outputPin->pin, value);
	outputPin->currentValue = value;
}

#endif /* GPIO_HELPER_C_ */
