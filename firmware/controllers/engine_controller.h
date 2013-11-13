/**
 * @file    engine_controller.h
 * @brief   Controllers package entry point header
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_STATUS_H_
#define ENGINE_STATUS_H_

#include "global.h"
#include "signal_executor.h"

int isCranking(void);
void initEngineContoller(void);
void setDefaultEngineConfiguration(void);

#endif /* ENGINE_STATUS_H_ */
