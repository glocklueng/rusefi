/**
 * @file	audi_aan.c
 * @brief	Audo AAN default engine configuration
 *
 * @date Nov 24, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_AUDI_AAN

#include "engine_controller.h"

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	/**
	 * One signal per cam shaft revolution
	 */
	int pinStates0[] = { 1, 0 };
	myfloat switchTimes[] = { 0.8, 1 };

	int *pinStates[2] = { pinStates0 };

	weComplexInit("distributor", state, 0, 2, switchTimes, 1, pinStates);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
	registerActuatorEvent(&config->ignitionEvents, 0, 1, 0);
	registerActuatorEvent(&config->ignitionEvents, 0, 2, 90);
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
}

#endif /* EFI_ENGINE_AUDI_AAN */
