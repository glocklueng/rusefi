/**
 * @file	nissan_primera.c
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_SUPPORT_NISSAN_PRIMERA

#include "engine_controller.h"
#include "adc_inputs.h"
#include "fuel_map.h"
#include "toothed_wheel_emulator.h"
#include "engine_configuration.h"

#define TOTAL_TEETH_COUNT 60
#define SKIPPED_TEETH_COUNT 2

static void configureEngineEventHandler(EventHandlerConfiguration *injectionConfiguration) {
//	injectionConfiguration->injectAtEventIndex[0] = 1;
//	injectionConfiguration->injectAtEventIndex[2 * 15] = 2;
//	injectionConfiguration->injectAtEventIndex[2 * 30] = 3;
//	injectionConfiguration->injectAtEventIndex[2 * 45] = 4;
}

void setNissanPrimeraEngineConfiguration(EngineConfiguration *engineConfiguration) {
}

void setNissanPrimeraEngineConfiguration2(EngineConfiguration2 *engineConfiguration2) {
	engineConfiguration2->triggerShape.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);

	configureEngineEventHandler(&engineConfiguration2->engineEventConfiguration);

	trigger_shape_s *s = &engineConfiguration2->triggerShape;
	skippedToothTriggerShape(s, TOTAL_TEETH_COUNT, SKIPPED_TEETH_COUNT);
}

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
