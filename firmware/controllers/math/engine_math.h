/*
 * @file	engine_math.h
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

#include "engine_configuration.h"

//float getDefaultVE(int rpm);

float getDefaultFuel(int rpm, float map);
//float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);

float getOneDegreeTime(int rpm);
float getCrankshaftRevolutionTime(int rpm);

int isCrankingR(int rpm);

float fixAngle(float angle);
float getTriggerEventAngle(int triggerEventIndex);
float getEngineLoad(void);

void initializeIgnitionActions(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2);

#endif /* ENGINE_MATH_H_ */
