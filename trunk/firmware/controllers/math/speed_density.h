/**
 * @file	speed_density.h
 *
 * @date May 29, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */
#ifndef SPEED_DENSITY_H_
#define SPEED_DENSITY_H_

#include "engine.h"

float getTCharge(int rpm, float tps, float coolantTemp, float airTemp);
void setDetaultVETable(persistent_config_s *config);
float sdMath(engine_configuration_s *engineConfiguration, float VE, float MAP, float AFR, float tempK);

#define gramm_second_to_cc_minute(gs) ((gs) / 0.0119997981)

#define cc_minute_to_gramm_second(ccm) ((ccm) * 0.0119997981)

void setDetaultVETable(DECLARE_ENGINE_PARAMETER_F);
void initSpeedDensity(DECLARE_ENGINE_PARAMETER_F);
float getSpeedDensityFuel(int rpm DECLARE_ENGINE_PARAMETER_S);

#endif /* SPEED_DENSITY_H_ */
