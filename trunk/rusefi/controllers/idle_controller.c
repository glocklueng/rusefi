/*
 * idle_controller.c
 *
 *  Created on: May 22, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "idle_controller.h"

void idleDebug(char *msg, int value);
int isCranking();

static int lastGoodValue = DEFAULT_IDLE_DUTY;

void idleInit(IdleValveState *idle) {
	idle->value = DEFAULT_IDLE_DUTY;
	setTargetRpm(idle, DEFAULT_TARGET_RPM);
	idle->timeOfLastIdleChange = 0;
}

void setTargetRpm(IdleValveState *idle, int targetRpm) {
	idle->targetRpmRangeLeft = targetRpm * 0.93;
	idle->targetRpmRangeRight = targetRpm * 1.07;
}

int min(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

static int wasCrankingTime;

static int setNewValue(IdleValveState *idle, int currentRpm, int now, char * msg, int newValue) {
	newValue = max(newValue, MIN_IDLE);
	newValue = min(newValue, MAX_IDLE);

	if (idle->value != newValue) {
		idleDebug(msg, currentRpm);
		idle->timeOfLastIdleChange = now;
	}

	idle->value = newValue;
	return newValue;
}

static int changeValue(IdleValveState *idle, int currentRpm, int now, char * msg, int delta) {
	int newValue = idle->value + delta;
	return setNewValue(idle, currentRpm, now, msg, newValue);
}

/**
 * now - current time in seconds
 */
int getIdle(IdleValveState *idle, int currentRpm, int now) {
	if (currentRpm == 0 || isCranking()) {
		wasCrankingTime = now;
		return setNewValue(idle, currentRpm, now, "cranking value: ", DEFAULT_IDLE_DUTY);
	}

	if (currentRpm < 0.7 * idle->targetRpmRangeLeft) {
		return setNewValue(idle, currentRpm, now, "RPMs are seriously low: ", lastGoodValue);
	}

	if (now - idle->timeOfLastIdleChange < IDLE_PERIOD) {
		// too soon to adjust anything - exiting
		return idle->value;
	}

	if (currentRpm > idle->targetRpmRangeLeft && currentRpm < idle->targetRpmRangeRight) {
		// current RPM is good enough
		// todo: need idle signal input
		//lastGoodValue = idle->value;
		return idle->value;
	}

	if (currentRpm >= idle->targetRpmRangeRight + 100)
		return changeValue(idle, currentRpm, now, "rpm is too high: ", -IDLE_DECREASE_STEP);

	if (currentRpm >= idle->targetRpmRangeRight)
		return changeValue(idle, currentRpm, now, "rpm is a bit too high: ", -1);

	// we are here if RPM is low, let's see how low
//	if (currentRpm < 0.7 * idle->targetRpmRangeLeft) {
//		// todo: act faster in case of really low RPM?
//		return setNewValue(idle, currentRpm, now, "RPMs are seriously low: ", 15 * IDLE_INCREASE_STEP);
//	} else
	if (currentRpm < idle->targetRpmRangeLeft - 100) {
		return changeValue(idle, currentRpm, now, "RPMs are low: ", IDLE_INCREASE_STEP);
	}
	return changeValue(idle, currentRpm, now, "RPMs are a bit low: ", 1);
}
