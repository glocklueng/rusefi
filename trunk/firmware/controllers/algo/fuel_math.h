/**
 * @file	fuel_math.h
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef FUEL_MAP_H_
#define FUEL_MAP_H_

#include "engine.h"

void prepareFuelMap(engine_configuration_s *engineConfiguration);

float getBaseFuel(Engine *engine, int rpm);
float getBaseTableFuel(engine_configuration_s *engineConfiguration, int rpm, float engineLoad);
float getIatCorrection(engine_configuration_s *engineConfiguration, float iat);
float getInjectorLag(engine_configuration_s *engineConfiguration, float vBatt);
float getCltCorrection(engine_configuration_s *engineConfiguration, float clt);
float getRunningFuel(float baseFuel, Engine *engine, int rpm);
float getCrankingFuel(Engine *engine);
float getCrankingFuel3(engine_configuration_s *engineConfiguration, float coolantTemperature, uint32_t revolutionCounterSinceStart);
float getFuelMs(int rpm DECLATE_ENGINE_PARAMETER);

#endif /* FUEL_MAP_H_ */
