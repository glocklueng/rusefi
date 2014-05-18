/**
 * @file    flash_main.h
 * @brief
 *
 * @date Sep 19, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef FLASH_MAIN_H_
#define FLASH_MAIN_H_

#include "engine_configuration.h"
#include "crc.h"

#define FLASH_DATA_VERSION 3002

typedef struct {
	int version;
	int size;
	persistent_config_s persistentConfiguration;
	crc_t value;
} FlashState;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void initFlash(void);
void writeToFlash(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FLASH_MAIN_H_ */
