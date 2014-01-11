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
}

static void configureEngineEventHandler(EventHandlerConfiguration *config) {
	float x = 51;

	resetEventList(&config->crankingInjectionEvents);

	resetEventList(&config->injectionEvents);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_4_OUTPUT), x);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_2_OUTPUT), x + 180);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_1_OUTPUT), x + 360);
	registerActuatorEvent(&config->injectionEvents, 0, addOutputSignal(INJECTOR_3_OUTPUT), x + 540);

	resetEventList(&config->ignitionEvents);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_2_OUTPUT), x + 180);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 360);
	registerActuatorEvent(&config->ignitionEvents, 0, addOutputSignal(SPARKOUT_1_OUTPUT), x + 540);
}

void setDodgeNeonEngineConfiguration2(EngineConfiguration2 *engineConfiguration2) {
	configureTriggerShape(&engineConfiguration2->triggerShape);

	configureEngineEventHandler(&engineConfiguration2->engineEventConfiguration);

	engineConfiguration2->triggerShape.shaftPositionEventCount = ((2 - 1) * 2);
	engineConfiguration2->triggerShape.useRiseEdge = FALSE;
}

#endif /* EFI_SUPPORT_DODGE_NEON */

