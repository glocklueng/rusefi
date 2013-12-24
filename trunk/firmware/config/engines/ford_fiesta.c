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
#include "dist_emulator.h"

extern EngineConfiguration2 *engineConfiguration2;

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	trigger_shape_s *s = &engineConfiguration2->triggerShape;

	skippedToothTriggerShape(s, state, TOTAL_TEETH_COUNT, SKIPPED_TEETH_COUNT);

	int *pinStates[2] = {s->wave.waves[0].pinStates, s->wave.waves[1].pinStates};
	weComplexInit("position sensor", state, 0, s->size, s->wave.switchTimes, 2, pinStates);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
	// injector 1 activated at the 1st tooth event while cranking
	registerActuatorEvent(&config->crankingInjectionEvents, 1, 1, 0);
	// injector 2 activated at the 36th st tooth event while cranking (do not forget - there are 70 events overall, 35 ups and 46 downs
	registerActuatorEvent(&config->crankingInjectionEvents, 36, 2, 0);

	// injector 1 activated at the 1st tooth event while normal running
	registerActuatorEvent(&config->injectionEvents, 1, 1, 0);
	// injector 2 activated at the 36th st tooth event while normal running
	registerActuatorEvent(&config->injectionEvents, 36, 2, 0);

	// spark 1 activated at the 1st tooth event while cranking & normal running
	registerActuatorEvent(&config->ignitionEvents, 1, 1, 0);
	// spark 2 activated at the 36th st tooth event while cranking & normal running
	registerActuatorEvent(&config->ignitionEvents, 36, 2, 0);
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;

	// only crankshaft sensor so far
	engineConfiguration2->rpmMultiplier = 1;

	engineConfiguration2->triggerShape.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
}

#endif /* EFI_ENGINE_FORD_FIESTA */
