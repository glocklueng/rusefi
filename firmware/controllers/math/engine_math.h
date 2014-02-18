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

float getOneDegreeTimeMs(int rpm);
float getOneDegreeTime(int rpm);
float getCrankshaftRevolutionTime(int rpm);

int isCrankingRT(engine_configuration_s *engineConfiguration, int rpm);
#define isCrankingR(rpm) isCrankingRT(engineConfiguration, rpm)

float fixAngle(float angle);
float getTriggerEventAngle(int triggerEventIndex);

float getEngineLoadT(engine_configuration_s *engineConfiguration);
#define getEngineLoad() getEngineLoadT(engineConfiguration)

void initializeIgnitionActions(engine_configuration_s *engineConfiguration, engine_configuration2_s *engineConfiguration2);

float getSparkDwellMsT(engine_configuration_s *engineConfiguration, int rpm);
#define getSparkDwellMs(rpm) getSparkDwellMsT(engineConfiguration, rpm)

#endif /* ENGINE_MATH_H_ */
