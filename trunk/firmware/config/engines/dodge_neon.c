/**
 * @file	dodge_neon.c
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_SUPPORT_DODGE_NEON

#include "dodge_neon.h"
#include "engine_configuration.h"
#include "main_loop.h"
#include "dist_emulator.h"

extern EngineConfiguration2 *engineConfiguration2;

static void configureTriggerShape(trigger_shape_s *s) {
	triggerShapeInit(s);

	triggerAddEvent(s, 60, T_PRIMARY, 1);
	triggerAddEvent(s, 210, T_PRIMARY, 0);
	triggerAddEvent(s, 420, T_PRIMARY, 1);
	triggerAddEvent(s, 630, T_PRIMARY, 0);
	// voodoo magic - we always need 720 at the end
	triggerAddEvent(s, 720, T_PRIMARY, 0);

	s->syncRatioFrom = 0.72 * 0.8;
	s->syncRatioTo = 0.72 * 1.3;
}

void setDodgeNeonEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;

	engineConfiguration2->triggerShape.shaftPositionEventCount = ((2 - 1) * 2);
}

static void configureEngineEventHandler(EventHandlerConfiguration *config) {
	resetEventList(&config->crankingInjectionEvents);
}

void setDodgeNeonEngineConfiguration2(EngineConfiguration2 *engineConfiguration2) {
	configureTriggerShape(&engineConfiguration2->triggerShape);

	configureEngineEventHandler(&engineConfiguration2->engineEventConfiguration);

	engineConfiguration2->triggerShape.useRiseEdge = FALSE;
}

#endif /* EFI_SUPPORT_DODGE_NEON */

