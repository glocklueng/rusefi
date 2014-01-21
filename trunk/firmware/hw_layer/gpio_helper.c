/*
 * @file    gpio_helper.c
 * @brief   General I/O helper
 *
 * @date Aug 25, 2013
 * @author pc
 */

#ifndef GPIO_HELPER_C_
#define GPIO_HELPER_C_

#include <hal.h>

#include "pin_repository.h"
#include "gpio_helper.h"

/**
 * @brief Initialize the hardware output pin while also assigning it a logical name
 */
void initOutputPinExt(char *msg, OutputPin *outputPin, GPIO_TypeDef *port, uint32_t pinNumber, iomode_t mode) {
	outputPin->currentLogicValue = -1;
	outputPin->port = port;
	outputPin->pin = pinNumber;

	mySetPadMode(msg, port, pinNumber, mode);
}

void initOutputPin(char *msg, OutputPin *outputPin, GPIO_TypeDef *port, uint32_t pinNumber) {
	initOutputPinExt(msg, outputPin, port, pinNumber, PAL_MODE_OUTPUT_PUSHPULL);
}

int getLogicPinValue(OutputPin * outputPin) {
	return outputPin->currentLogicValue;
}

/**
 * Set's the value of the pin. On this layer the value is assigned as is, without any conversion.
 */
void setPinValue(OutputPin * outputPin, int electricalValue, int logicValue) {
	if (getLogicPinValue(outputPin) == logicValue)
		return;

	palWritePad(outputPin->port, outputPin->pin, electricalValue);
	outputPin->currentLogicValue = logicValue;
}

#endif /* GPIO_HELPER_C_ */
