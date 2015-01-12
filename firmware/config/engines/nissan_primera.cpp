/**
 * @file	nissan_primera.cpp
 *
 * engine_type 5
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"

#if EFI_SUPPORT_NISSAN_PRIMERA || defined(__DOXYGEN__)
#include "nissan_primera.h"

void setNissanPrimeraEngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_TOOTHED_WHEEL_60_2;
}

#endif /* EFI_SUPPORT_NISSAN_PRIMERA */
