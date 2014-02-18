/**
 * @file	nissan_primera.c
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"

#if EFI_SUPPORT_NISSAN_PRIMERA || defined(__DOXYGEN__)

#include "engine_controller.h"
#include "adc_inputs.h"
#include "trigger_decoder.h"
#include "engine_configuration.h"

void setNissanPrimeraEngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->triggerConfig.totalToothCount = 60;
	engineConfiguration->triggerConfig.skippedToothCount = 2;
}

void setNissanPrimeraengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	initializeSkippedToothTriggerShapeExt(engineConfiguration2, 60, 2);
}

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
