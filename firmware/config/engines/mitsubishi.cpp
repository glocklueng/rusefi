/**
 * @file	mitsubishi.cpp
 *
 * @date Aug 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "mitsubishi.h"

void setMitsubishiConfiguration(engine_configuration_s *engineConfiguration, board_configuration_s *boardConfiguration) {
	engineConfiguration->engineType = MITSU_4G93;

	engineConfiguration->triggerConfig.triggerType = TT_MITSU;

}


