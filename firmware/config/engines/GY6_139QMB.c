/*
 * GY6_139QMB.c
 *
 *  Created on: 13 feb 2014 y.
 *      Author: rus084
 */
#include "GY6_139QMB.h"
#include "engine_configuration.h"

void setGy6139qmbDefaultEngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->rpmHardLimit = 9000;
	engineConfiguration->crankingSettings.crankingRpm = 800;
	engineConfiguration->analogInputDividerCoefficient = 1.52;
	engineConfiguration->engine_load_mode = LM_MAP;
}
void setGy6139qmbengine_configuration2_s(engine_configuration2_s *engineConfiguration2) {
	engineConfiguration2->rpmMultiplier = 1;
	engineConfiguration2->cylindersCount = 1;


}

