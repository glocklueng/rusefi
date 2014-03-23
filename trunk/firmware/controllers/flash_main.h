/**
 * @file    flash_main.h
 * @brief
 *
 * @date Sep 19, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef FLASH_MAIN_H_
#define FLASH_MAIN_H_

#include "engine_configuration.h"
#include "crc.h"

#define FLASH_DATA_VERSION 20140320

typedef struct {
	int version;
	persistent_config_s persistentConfiguration;
	crc value;
} FlashState;

void initFlash(void);
void writeToFlash(void);

#endif /* FLASH_MAIN_H_ */
