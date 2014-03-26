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
	engineConfiguration->rpmHardLimit = 7000;

	boardConfiguration->ignitionPinMode = OM_OPENDRAIN;

	setThermistorConfiguration(&engineConfiguration->cltThermistorConf, 0, 32500, 30, 7550, 100, 700);
	engineConfiguration->cltThermistorConf.bias_resistor = 2200;

	engineConfiguration->crankingSettings.coolantTempMaxC = 37.7; // 5ms at 37.7C
	engineConfiguration->crankingSettings.fuelAtMaxTempMs = 5;

	engineConfiguration->crankingSettings.coolantTempMinC = -40; // 26ms at -40C
	engineConfiguration->crankingSettings.fuelAtMinTempMs = 26;

	engineConfiguration->triggerConfig.syncRatioFrom = 0.72 * 0.8;
	engineConfiguration->triggerConfig.syncRatioTo = 0.72 * 1.3;

	engineConfiguration->triggerConfig.isSynchronizationNeeded = TRUE;
	engineConfiguration->triggerConfig.useRiseEdge = FALSE;

	engineConfiguration->triggerConfig.triggerType = TT_DODGE_NEON;
	engineConfiguration->ignitionMode = IM_INDIVIDUAL_COILS;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;

	engineConfiguration->ignitionOffset = 360 + 51;
	engineConfiguration->injectionOffset = 360 + 51;
	engineConfiguration->triggerShapeSynchPointIndex = 1;
}

void setDodgeNeonengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
	EventHandlerConfiguration *config = &engineConfiguration2->engineEventConfiguration;

	addFuelEvents(engineConfiguration, engineConfiguration2, &config->crankingInjectionEvents, engineConfiguration->crankingInjectionMode);
	addFuelEvents(engineConfiguration, engineConfiguration2, &config->injectionEvents, engineConfiguration->injectionMode);
}

#endif /* EFI_SUPPORT_DODGE_NEON */

