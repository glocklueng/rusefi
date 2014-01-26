/*
 * @file	engine_math.h
 *
 * @date Jul 13, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ENGINE_MATH_H_
#define ENGINE_MATH_H_

//float getDefaultVE(int rpm);

float getDefaultFuel(int rpm, float map);
//float getTCharge(int rpm, int tps, float coolantTemp, float airTemp);

float getStartingFuel(float coolantTemperature);

float getOneDegreeTime(int rpm);
float getCrankshaftRevolutionTime(int rpm);

typedef struct {
	float coolantTempMinC;
	float coolantTempMaxC;
	float fuelAtMinTempMs;
	float fuelAtMaxTempMs;

	/**
	 * This value controls what RPM values we consider 'cranking' (any RPM below 'crankingRpm')
	 * Anything above 'crankingRpm' would be 'running'
	 */
	short int crankingRpm;
} cranking_parameters_s;

float fixAngle(float angle);
float getTriggerEventAngle(int triggerEventIndex);

#endif /* ENGINE_MATH_H_ */
