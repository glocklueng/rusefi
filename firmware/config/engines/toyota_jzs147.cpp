/*
 * @file toyota_jzs147.cpp
 *
 * toyota aristo
 * https://en.wikipedia.org/wiki/Lexus_GS
 *
 * set_engine_type 38
 *
 * @date Dec 30, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "toyota_jzs147.h"

EXTERN_ENGINE;

void setToyota_jzs147EngineConfiguration(DECLARE_ENGINE_PARAMETER_F) {

	engineConfiguration->specs.displacement = 3.0;
	engineConfiguration->specs.cylindersCount = 6;

	setOperationMode(engineConfiguration, FOUR_STROKE_CAM_SENSOR);
	engineConfiguration->trigger.type = TT_2JZ;

}



