/**
 * @file    flash_main.h
 * @brief
 *
 * @date Sep 19, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef FLASH_MAIN_H_
#define FLASH_MAIN_H_

#include "engine_configuration.h"
#include "engine.h"

#define FLASH_DATA_VERSION 6130

void readFromFlash(void);
void initFlash(Engine *engine);

/**
 * Because of hardware-related issues, stm32f4 chip is totally
 * frozen while we are writing to internal flash. Writing the configuration takes
 * about 1-2 seconds, we cannot afford to do that while the engine is
 * running so we postpone the write until the engine is stopped.
 */
void writeToFlash(void);
void setNeedToWriteConfiguration(void);
/**
 * @return true if an flash write is pending
 */
bool getNeedToWriteConfiguration(void);
void writeToFlashIfPending(void);

#endif /* FLASH_MAIN_H_ */
