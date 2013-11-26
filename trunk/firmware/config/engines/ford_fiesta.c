/**
 * @file	ford_fiesta.c
 * @brief	European 1990 Ford Fiesta
 *
 *  Created on: Nov 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_FORD_FIESTA

#include "ford_fiesta.h"
#include "engine_configuration.h"
#include "toothed_wheel_emulator.h"

extern EngineConfiguration2 engineConfiguration2;
extern EngineConfiguration *engineConfiguration;

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	skippedToothPositionEmulatorShape(state);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {

	config->igniteAtEventIndex[1] = 1;
	config->igniteAtEventIndex[36] = 2;
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;
}

#endif /* EFI_ENGINE_FORD_FIESTA */
