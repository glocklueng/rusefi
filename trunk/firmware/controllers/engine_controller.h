/**
 * @file    engine_controller.h
 * @brief   Controllers package entry point header
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_STATUS_H_
#define ENGINE_STATUS_H_

#include "global.h"
#include "signal_executor.h"
#include "engine_configuration.h"

int isCrankingR(int rpm);
int isCranking(void);
void printTemperatureInfo(void);
void initEngineContoller(void);
void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration);

#endif /* ENGINE_STATUS_H_ */
