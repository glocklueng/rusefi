/*
 * gpio_helper.h
 *
 *  Created on: Aug 25, 2013
 *      Author: pc
 */

#ifndef GPIO_HELPER_H_
#define GPIO_HELPER_H_

/**
 * @brief   Single output pin
 */
typedef struct {
	GPIO_TypeDef *port;
	int pin;
	/**
	 * we track current pin status so that we do not touch the actual hardware if we want to write new pin bit
	 * which is same as current pin value. This maybe helps in case of status leds, but maybe it's a total over-engineering
	 */
	int currentValue;
} OutputPin;

void initOutputPin(char *msg, OutputPin *outputPin, GPIO_TypeDef *port, uint32_t pinNumber);
void setPinValue(OutputPin * outputPin, int value);

#endif /* GPIO_HELPER_H_ */
