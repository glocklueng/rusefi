/*
 * idle_controller.c
 *
 *  Created on: May 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "idle_controller.h"

void idleInit(IdleValveState *idle) {
	idle->value = DEFAULT_IDLE_DUTY;
	setTargetRpm(idle, DEFAULT_TARGET_RPM);
	idle->timeOfLastIdleChange = 0;
}

void setTargetRpm(IdleValveState *idle, int targetRpm) {
	idle->targetRpmRangeLeft = targetRpm * 0.93;
	idle->targetRpmRangeRight = targetRpm * 1.07;
}

static int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

static int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

/**
 * now - current time in seconds
 */
int getIdle(IdleValveState *idle, int currentRpm, int now) {
	if (currentRpm == 0) {
		idle->value = DEFAULT_IDLE_DUTY;
		return idle->value;
	}

	if (now - idle->timeOfLastIdleChange < IDLE_PERIOD) {
		// too soon to adjust anything - exiting
		return idle->value;
	}

	if (currentRpm > idle->targetRpmRangeLeft
			&& currentRpm < idle->targetRpmRangeRight) {
		// current RPM is good enough
		return idle->value;
	}

	if (currentRpm >= idle->targetRpmRangeRight && idle->value > MIN_IDLE) {
		// RPM is too high
		idle->value -= IDLE_DECREASE_STEP;
		idle->timeOfLastIdleChange = now;
		idle->value = max(idle->value, MIN_IDLE);
		return idle->value;
	}

	idle->value = min(idle->value + IDLE_INCREASE_STEP, MAX_IDLE);

	// we are here if RPM is too low

	return idle->value;

}
