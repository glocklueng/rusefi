/*
 * @file gm_2_2.cpp
 *
 * set_engine_type 30
 *
 * @date Apr 9, 2015
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#include "global.h"
#include "gm_2_2.h"

EXTERN_ENGINE
;

void setGm2_2(DECLARE_ENGINE_PARAMETER_F) {
	setOperationMode(engineConfiguration, FOUR_STROKE_CAM_SENSOR);
	engineConfiguration->trigger.type = TT_ONE_PLUS_TOOTHED_WHEEL_60_2;

	boardConfiguration->triggerInputPins[0] = GPIOC_6;
	boardConfiguration->triggerInputPins[1] = GPIOA_8;
}
