/**
 * @file	speed_density.h
 *
 * @date May 29, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef SPEED_DENSITY_H_
#define SPEED_DENSITY_H_

#include "engine_configuration.h"

float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);
void setDetaultVETable(engine_configuration_s *engineConfiguration);

#endif /* SPEED_DENSITY_H_ */
