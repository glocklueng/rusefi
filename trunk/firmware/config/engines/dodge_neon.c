/**
 * @file	dodge_neon.c
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_DODGE_NEON

#include "dodge_neon.h"
#include "engine_configuration.h"
#include "main_loop.h"
#include "dist_emulator.h"

extern EngineConfiguration2 *engineConfiguration2;

void configureShaftPositionEmulatorShape(PwmConfig *state) {

	trigger_shape_s * s = &engineConfiguration2->triggerShape;
	triggerShapeInit(s);

	triggerAddEvent(s, 60, T_PRIMARY, 1);
	triggerAddEvent(s, 210, T_PRIMARY, 0);
	triggerAddEvent(s, 420, T_PRIMARY, 1);
	triggerAddEvent(s, 630, T_PRIMARY, 0);
	// voodoo magic - we always need 720 at the end
	triggerAddEvent(s, 720, T_PRIMARY, 1);

	int *pinStates[2] = { s->wave.waves[0].pinStates, s->wave.waves[1].pinStates };

	weComplexInit("distributor", state, 0, s->size, s->wave.switchTimes, 2, pinStates);
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;

	engineConfiguration2->shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
	resetEventList(&config->crankingInjectionEvents);

}

#endif /* EFI_ENGINE_DODGE_NEON */

