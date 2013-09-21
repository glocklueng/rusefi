/*
 *  Created on: Sep 19, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    flash_main.h
 */

#ifndef FLASH_MAIN_H_
#define FLASH_MAIN_H_

#include "tunerstudio.h"
#include "crc.h"

#define FLASH_DATA_VERSION 239000002

typedef struct {
	int version;
	EngineConfiguration configuration;
	crc value;
} FlashState;

void initFlash(void);
void writeToFlash(void);

#endif /* FLASH_MAIN_H_ */
