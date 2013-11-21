/*
 *  Created on: Sep 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    ford_aspire.c
 */

#include "main.h"
#include <string.h>

#if EFI_ENGINE_FORD_ASPIRE

#include "ford_aspire.h"

#include "sensors.h"
#include "engines.h"
#include "engine_math.h"
#include "settings.h"
#include "rpm_calculator.h"
#include "fuel_map.h"
#include "engine_controller.h"
#include "engine_configuration.h"

extern EngineConfiguration2 engineConfiguration2;
extern EngineConfiguration *engineConfiguration;

static float getCrankingFuel(void) {
	const int fuelOverride = getCrankingInjectionPeriod();
	if (fuelOverride != 0) {
		return fuelOverride / 10.0;
	} else {
		return getStartingFuel(getCoolantTemperature());
	}
}

/**
 * @brief	Length of fuel injection, in milliseconds
 */
float getFuelMs(int rpm) {
	if (isCranking()) {
		return getCrankingFuel();
	} else {
		myfloat fuel = getFuel(rpm, getMaf());
		return fuel;
	}
}

void confgiureShaftPositionEmulatorShape(PwmConfig *state) {
	myfloat x = ASPIRE_MAGIC_DUTY_CYCLE / 4;

	/**
	 * 1993 Ford Aspire has two hall sensors for CKP sensor
	 *
	 * X__X__X__X__  38% duty cycle
	 * __XXXXXX____  50% duty cycle
	 */

	myfloat secondStart = 0.17; //x + (0.25 - x) / 2;

	myfloat switchTimes[] = { x, secondStart, 0.25, 0.25 + x, 0.5, 0.5 + x,
			secondStart + 0.5,
			0.75, 0.75 + x, 1 };

	/**
	 * One signal per cam shaft revolution
	 */
	int pinStates0[] = { 1, 0, 0, 0, 0,
			             0, 1, 1, 1, 1};

	/**
	 * Four signals per cam shaft revolution
	 */
	int pinStates1[] = { 0, 0, 1 /* start of 2nd signal*/ , 0, 1 /* start of 3rd signal*/, 0, 0, 1, 0, 1 };


	int *pinStates[2] = { pinStates0, pinStates1 };

	weComplexInit("distributor", state, 0, 10, switchTimes, 2, pinStates);
}

void configureEngineEventHandler(EventHandlerConfiguration *config) {
  memset(config->injectAtEventIndex, sizeof(config->injectAtEventIndex), 0);
  memset(config->igniteAtEventIndex, sizeof(config->igniteAtEventIndex), 0);
	config->injectAtEventIndex[6] = 1;
	config->injectAtEventIndex[3] = 2;
	config->injectAtEventIndex[8] = 3;
	config->injectAtEventIndex[1] = 4;

	config->igniteAtEventIndex[1] = 1;
	config->igniteAtEventIndex[3] = 1;
	config->igniteAtEventIndex[6] = 1;
	config->igniteAtEventIndex[8] = 1;
}

void setDefaultEngineConfiguration(void) {
	engineConfiguration->tpsMin = 1;
	engineConfiguration->tpsMax = 1000;

	engineConfiguration->rpmHardLimit = 7000;
}
#endif /* EFI_ENGINE_FORD_ASPIRE */
