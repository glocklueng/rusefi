/**
 * @file    voltage.h
 * @brief
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#ifndef VOLTAGE_H_
#define VOLTAGE_H_

#include "main.h"
#include "engine_configuration.h"

float getVRef(DECLARE_ENGINE_PARAMETER_F);
float getVBatt(DECLARE_ENGINE_PARAMETER_F);
bool hasVBatt(DECLARE_ENGINE_PARAMETER_F);

#endif
