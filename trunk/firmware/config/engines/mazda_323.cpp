/**
 * @file	mazda_323.cpp
 *
 * @date Mar 8, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "mazda_323.h"

void setMazda323EngineConfiguration(engine_configuration_s *engineConfiguration) {
	engineConfiguration->cylindersCount = 4;
	engineConfiguration->displacement = 1.6;

	engineConfiguration->ignitionMode = IM_ONE_COIL;

	/**
	 * We treat the trigger as 4/0 toothed wheel
	 */
	setToothedWheelConfiguration(engineConfiguration, 4, 0);
}
