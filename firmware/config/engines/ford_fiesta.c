/**
 * @file	ford_fiesta.c
 * @brief	European 1990 Ford Fiesta
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_FORD_FIESTA

#include "ford_fiesta.h"
#include "engine_configuration.h"
#include "toothed_wheel_emulator.h"

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	skippedToothPositionEmulatorShape(state);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
	registerActuatorEvent(&config->ignitionEvents, 1, 1, 0);
	registerActuatorEvent(&config->ignitionEvents, 36, 2, 0);
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;
}

#endif /* EFI_ENGINE_FORD_FIESTA */
