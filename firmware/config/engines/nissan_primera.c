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
#include "trigger_decoder.h"
#include "engine_configuration.h"

void setNissanPrimeraengine_configuration2_s(engine_configuration2_s *engineConfiguration2) {
	skippedToothTriggerShapeExt(engineConfiguration2, 60, 2);
}

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
