/**
 * @file	dodge_neon.c
 *
 * DODGE_NEON_1995 = 2
 *
 * @date Dec 16, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"

#if EFI_SUPPORT_DODGE_NEON || defined(__DOXYGEN__)

#include "dodge_neon.h"
#include "engine_configuration.h"
#include "thermistors.h"
#include "engine_math.h"

void setDodgeNeonEngineConfiguration(engine_configuration_s *engineConfiguration,
		board_configuration_s *boardConfiguration) {
	// set_rpm_hard_limit 400
	engineConfiguration->rpmHardLimit = 4000; // yes, 4k. let's play it safe for now

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, 0, 32500, 30, 7550, 100, 700);
	engineConfiguration->cltThermistorConf.bias_resistor = 2700;

	engineConfiguration->crankingSettings.coolantTempMaxC = 37.7; // 5ms at 37.7C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 5;

	engineConfiguration->crankingSettings.coolantTempMinC = -40; // 26ms at -40C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 26;

	engineConfiguration->triggerConfig.syncRatioFrom = 0.72 * 0.8;
	engineConfiguration->triggerConfig.syncRatioTo = 0.72 * 1.3;

	engineConfiguration->triggerConfig.isSynchronizationNeeded = TRUE;
	engineConfiguration->triggerConfig.useRiseEdge = FALSE;
	engineConfiguration->needSecondTriggerInput = FALSE;

	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->injectionMode = IM_SEQUENTIAL;

	engineConfiguration->triggerConfig.triggerType = TT_DODGE_NEON;
	// set_ignition_mode 2
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;
	//
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	// set_global_trigger_offset_angle 510
	engineConfiguration->globalTriggerAngleOffset = 510;
	engineConfiguration->ignitionOffset = 621;
	engineConfiguration->injectionOffset = 621;

	// set_ignition_pin_mode 0
	boardConfiguration->ignitionPinMode = OM_DEFAULT;
}

void setDodgeNeonengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
}

#endif /* EFI_SUPPORT_DODGE_NEON */

