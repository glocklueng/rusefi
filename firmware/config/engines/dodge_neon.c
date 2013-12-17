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

extern EngineConfiguration2 engineConfiguration2;

void configureShaftPositionEmulatorShape(PwmConfig *state) {
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 7000;

	engineConfiguration2.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
	resetEventList(&config->crankingInjectionEvents);

}

#endif /* EFI_ENGINE_DODGE_NEON */

