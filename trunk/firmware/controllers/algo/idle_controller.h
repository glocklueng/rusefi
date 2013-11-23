/**
 * @file	idle_controller.h
 *
 *  Created on: May 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef IDLE_CONTROLLER_H_
#define IDLE_CONTROLLER_H_

// 700� duty cycle by default
#define DEFAULT_IDLE_DUTY 600

#define DEFAULT_TARGET_RPM 1000
//#define DEFAULT_TARGET_RPM 2000

#define IDLE_PERIOD 1

// Per mil (1/1000) values
#define MIN_IDLE 100
#define MAX_IDLE 900
#define IDLE_INCREASE_STEP 5
#define IDLE_DECREASE_STEP 5


typedef struct {
	int time;

	int targetRpmRangeLeft, targetRpmRangeRight;

	int value;
	int timeOfLastIdleChange;
} IdleValveState;

void idleInit(IdleValveState *idle);
int getIdle(IdleValveState *idle, int currentRpm, int time);
void setTargetRpm(IdleValveState *idle, int targetRpm);

// todo: move these somewhere else!
int max(int i1, int i2);
int min(int i1, int i2);

#endif /* IDLE_CONTROLLER_H_ */
