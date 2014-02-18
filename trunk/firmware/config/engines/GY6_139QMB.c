/**
 * @file	GY6_139QMB.c
 * @brief	139qmb default engine configuration
 *
 * @date Feb 13, 2014
 * @author rus084
 * @author Andrey Belomutskiy, (c) 2012-2014 *
 */

#include "GY6_139QMB.h"
#include "engine_configuration.h"

void setGy6139qmbDefaultEngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 9000;
	engineConfiguration->crankingSettings.crankingRpm = 800;
	engineConfiguration->analogInputDividerCoefficient = 1.52;
	engineConfiguration->engine_load_mode = LM_MAP;
	engineConfiguration->cylindersCount = 1;
	engineConfiguration->rpmMultiplier = 1;

	engineConfiguration->firingOrder = FO_ONE_CYLINDER;

	/**
	 * We treat the trigger as 1/0 toothed wheel
	 */
	engineConfiguration->triggerConfig.totalToothCount = 1;
	engineConfiguration->triggerConfig.skippedToothCount = 0;
	engineConfiguration->triggerConfig.isSynchronizationNeeded = FALSE;
}

void setGy6139qmbengine_configuration2_s(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2) {
}

