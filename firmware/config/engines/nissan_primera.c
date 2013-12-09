/**
 * @file	nissan_primera.c
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_ENGINE_DENISVAK

#include "engine_controller.h"
#include "denisvak.h"
#include "adc_inputs.h"
#include "fuel_map.h"
#include "toothed_wheel_emulator.h"

void configureShaftPositionEmulatorShape(PwmConfig *state) {
	skippedToothPositionEmulatorShape(state);
}

void configureEngineEventHandler(EventHandlerConfiguration *injectionConfiguration) {
	injectionConfiguration->injectAtEventIndex[0] = 1;
	injectionConfiguration->injectAtEventIndex[2 * 15] = 2;
	injectionConfiguration->injectAtEventIndex[2 * 30] = 3;
	injectionConfiguration->injectAtEventIndex[2 * 45] = 4;
}

void setDefaultEngineConfiguration(EngineConfiguration *engineConfiguration) {
	engineConfiguration2.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
}

#endif /* EFI_ENGINE_DENISVAK */
