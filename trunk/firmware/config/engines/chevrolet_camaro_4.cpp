/*
 * @file chevrolet_camaro_4.cpp
 *
 *
 * set_engine_type 35
 *
 * @date Oct 16, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "chevrolet_camaro_4.h"

EXTERN_ENGINE
;

void setCamaro4(DECLARE_ENGINE_PARAMETER_F) {

	engineConfiguration->specs.displacement = 5.7;
	engineConfiguration->specs.cylindersCount = 8;

}


