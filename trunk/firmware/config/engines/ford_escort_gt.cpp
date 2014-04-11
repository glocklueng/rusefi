/**
 * @file	ford_escort_gt.cpp
 *
 * FORD_ESCORT_GT = 14
 *
 * @date Apr 11, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "ford_escort_gt.h"

void setFordEscortGt(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->triggerConfig.triggerType = TT_FORD_ESCORT_GT;
}



