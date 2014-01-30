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

void setNissanPrimeraengine_configuration2_s(engine_configuration2_s *engineConfiguration2) {
	trigger_shape_s *s = &engineConfiguration2->triggerShape;
	int TOTAL_TEETH_COUNT = 60;
	int SKIPPED_TEETH_COUNT = 2;
	engineConfiguration2->triggerShape.shaftPositionEventCount = ((TOTAL_TEETH_COUNT - SKIPPED_TEETH_COUNT) * 2);
	skippedToothTriggerShape(s, TOTAL_TEETH_COUNT, SKIPPED_TEETH_COUNT);
}

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
