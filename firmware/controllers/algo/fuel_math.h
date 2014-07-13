/**
 * @file	fuel_math.h
 *
 * @date May 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef FUEL_MAP_H_
#define FUEL_MAP_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "engine.h"

void prepareFuelMap(void);

float getBaseFuel(int rpm, float engineLoad);
float getIatCorrection(float iat);
float getInjectorLag(float vBatt);
float getCltCorrection(float clt);
float getRunningFuel(Engine *engine, int rpm, float engineLoad);
float getStartingFuel(float coolantTemperature);
float getFuelMs(int rpm, Engine *engine);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FUEL_MAP_H_ */
