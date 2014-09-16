/**
 * @file pid.cpp
 *
 * http://en.wikipedia.org/wiki/PID_controller
 *
 * @date Sep 16, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "pid.h"

Pid::Pid(float pFactor, float iFactor, float dFactor) {
	this->pFactor = pFactor;
	this->iFactor = iFactor;
	this->dFactor = dFactor;
}

float Pid::getValue(float input) {
	return 0;
}

