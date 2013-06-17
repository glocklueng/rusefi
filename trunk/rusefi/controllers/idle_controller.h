/*
 * idle_controller.h
 *
 *  Created on: May 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef IDLE_CONTROLLER_H_
#define IDLE_CONTROLLER_H_

// 70% duty cycle by default
#define DEFAULT_IDLE_DUTY 60

#define DEFAULT_TARGET_RPM 1200

#define IDLE_PERIOD 1

#define MIN_IDLE 10
#define MAX_IDLE 90
#define IDLE_INCREASE_STEP 1
#define IDLE_DECREASE_STEP 1


typedef struct {
	int time;

	int targetRpmRangeLeft, targetRpmRangeRight;

	int value;
	int timeOfLastIdleChange;
} IdleValveState;

void idleInit(IdleValveState *idle);
int getIdle(IdleValveState *idle, int currentRpm, int time);
void setTargetRpm(IdleValveState *idle, int targetRpm);

#endif /* IDLE_CONTROLLER_H_ */
