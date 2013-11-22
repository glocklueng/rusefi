/*
 * @file	ford_fiesta.c
 *
 *  Created on: Nov 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_FORD_FIESTA

#include "engine_configuration.h"

extern EngineConfiguration2 engineConfiguration2;
extern EngineConfiguration *engineConfiguration;

void configureShaftPositionEmulatorShape(PwmConfig *state) {

}

void configureEngineEventHandler(EventHandlerConfiguration *config) {

}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;
}

#endif /* EFI_ENGINE_FORD_FIESTA */
