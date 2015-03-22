/**
 * @file pid.cpp
 *
 * http://en.wikipedia.org/wiki/PID_controller
 *
 * @date Sep 16, 2014
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "pid.h"

Pid::Pid(float pFactor, float iFactor, float dFactor, float minResult, float maxResult) {
	this->pFactor = pFactor;
	this->iFactor = iFactor;
	this->dFactor = dFactor;
	this->minResult = minResult;
	this->maxResult = maxResult;

	integration = 0;
	prevError = 0;
}

float Pid::getValue(float target, float input, float dTime) {
	float error = target - input;

	float pTerm = pFactor * error;
	integration += iFactor * dTime * error;
	float dTerm = dFactor / dTime * (error - prevError);

	prevError = error;

	float result = pTerm + integration + dTerm;
	if (result > maxResult) {
//		integration -= result - maxResult;
		result = maxResult;
	} else if (result < minResult) {
//		integration += minResult - result;
		result = minResult;
	}
	return result;
}

void Pid::updateFactors(float pFactor, float iFactor, float dFactor) {
	this->pFactor = pFactor;
	this->iFactor = iFactor;
	this->dFactor = dFactor;
	reset();
}

void Pid::reset(void) {
	integration = 0;
	prevError = 0;
}

float Pid::getP(void) {
	return pFactor;
}

float Pid::getI(void) {
	return iFactor;
}

float Pid::getIntegration(void) {
	return integration;
}

float Pid::getD(void) {
	return dFactor;
}


