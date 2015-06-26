/**
 * @file    ego.h
 * @brief
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef EGO_H_
#define EGO_H_

#include "main.h"
#include "rusefi_enums.h"
#include "engine_configuration.h"

float getAfr(DECLARE_ENGINE_PARAMETER_F);
void setEgoSensor(ego_sensor_e type DECLARE_ENGINE_PARAMETER_S);

#endif
