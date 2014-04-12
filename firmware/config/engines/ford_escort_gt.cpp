/**
 * @file	ford_escort_gt.cpp
 *
 * FORD_ESCORT_GT = 14
 *
 * @date Apr 11, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "ford_escort_gt.h"
#include "engine_math.h"

void setFordEscortGt(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_FORD_ESCORT_GT;

	engineConfiguration->cylindersCount = 4;
	engineConfiguration->firingOrder = FO_1_THEN_3_THEN_4_THEN2;
	engineConfiguration->globalTriggerAngleOffset = 175;
	engineConfiguration->ignitionOffset = 98 - 11;
	engineConfiguration->injectionOffset = 59;

	setSingleCoilDwell(engineConfiguration);
	engineConfiguration->ignitionMode = IM_ONE_COIL;
}



