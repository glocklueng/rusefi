/**
 * @file	idle_controller.h
 *
 * @date May 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "engine.h"

#ifndef IDLE_CONTROLLER_H_
#define IDLE_CONTROLLER_H_

// 60% duty cycle by default
#define DEFAULT_IDLE_DUTY 600

#define IDLE_PERIOD 1000

// Percent values
#define MIN_IDLE 10.0f
#define MAX_IDLE 90.0f
#define IDLE_INCREASE_STEP 0.5f
#define IDLE_DECREASE_STEP 0.5f
#define IDLE_INCREASE_SMALL_STEP 0.1F
#define IDLE_DECREASE_SMALL_STEP 0.1F

class IdleValveState {
public:
	IdleValveState();
	void init(DECLARE_ENGINE_PARAMETER_F);
	percent_t getIdle(int currentRpm, efitimems_t now DECLARE_ENGINE_PARAMETER_S);

	int time;

	int targetRpmRangeLeft, targetRpmRangeRight;

	percent_t value;
	efitimems_t timeOfLastIdleChange;
};

void setIdleRpm(IdleValveState *idle, int targetRpm);

void idleDebug(const char *msg, percent_t value);

#endif /* IDLE_CONTROLLER_H_ */
