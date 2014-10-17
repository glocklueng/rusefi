/**
 * @file    engine_controller.h
 * @brief   Controllers package entry point header
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef ENGINE_STATUS_H_
#define ENGINE_STATUS_H_

#include "global.h"
#include "signal_executor.h"
#include "engine_configuration.h"
#include "engine.h"

char * getPinNameByAdcChannel(adc_channel_e hwChannel, char *buffer);
void initEngineContoller(void);

#endif /* ENGINE_STATUS_H_ */
