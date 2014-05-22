/**
 * @file	engine.h
 *
 * @date May 21, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef ENGINE_H_
#define ENGINE_H_

#include "main.h"
#include "rpm_calculator.h"

class Engine {
public:
	RpmCalculator *rpmCalculator;
	engine_configuration_s *engineConfiguration;
};

#endif /* ENGINE_H_ */
