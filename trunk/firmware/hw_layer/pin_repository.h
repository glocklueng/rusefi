/*
 * pin_repository.h
 *
 *  Created on: Jan 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    pin_repository.h
 * @brief   I/O pin registry header
 */

#ifndef PIN_REPOSITORY_H_
#define PIN_REPOSITORY_H_

#include "ch.h"
#include "hal.h"

void initPinRepository(void);
void printpin(char *msg, ioportid_t port, int pin);
void mySetPadMode(char *msg, ioportid_t port, ioportmask_t pin, iomode_t mode);
char *portname(GPIO_TypeDef* GPIOx);

#endif /* PIN_REPOSITORY_H_ */
