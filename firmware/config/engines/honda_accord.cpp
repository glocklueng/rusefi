/**
 * @file	honda_accord.cpp
 *
 * 1995 Honda Accord
 *
 * engine_type 6
 *
 * @date Jan 12, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "engine_configuration.h"
#include "trigger_decoder.h"

void setHondaAccordConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->engineType = HONDA_ACCORD;
//	engineConfiguration->triggerConfig.totalToothCount = 24;
//	engineConfiguration->triggerConfig.skippedToothCount = 2;
}

