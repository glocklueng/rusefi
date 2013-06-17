/*
 * engine_status.c
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "rpm_reporter.h"
#include "idle_thread.h"
#include "injector_control.h"
#include "rpm_reporter.h"
#include "sparkout.h"
#include "main_loop.h"


int isCranking() {
	return getCurrentRpm() < 350;
}

/**
 * return the index of sorted array such that array[i] is
 * greater that value
 *
 * return index of last array element (size - 1) is value is
 * higher than last value
 */
int findIndex(myfloat array[], int size, float value) {

	for (int i = 0; i < size; i++) {
		if (value < array[i])
			return i;
	}
	return size - 1;
}

void initEngineContoller() {
	initOutputSignals();

	initInjectorsControl();
	initAspireTachometer();

	initMainLoop();

	startIdleThread();

}

