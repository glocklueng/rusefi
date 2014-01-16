/**
 * @file	ignition_central.c
 * @brief	TODO
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "ignition_central.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "main_trigger_callback.h"
#include "engine_configuration.h"

static Logging logger;

extern EngineConfiguration *engineConfiguration;

void initIgnitionCentral(void) {
	initLogging(&logger, "IgnitionCentral");

	outputPinRegisterExt("sparkout1", SPARKOUT_1_OUTPUT, SPARK_1_PORT, SPARK_1_PIN, &engineConfiguration->ignitionPinMode);
	outputPinRegisterExt("sparkout2", SPARKOUT_2_OUTPUT, SPARK_2_PORT, SPARK_2_PIN, &engineConfiguration->ignitionPinMode);
	outputPinRegisterExt("sparkout3", SPARKOUT_3_OUTPUT, SPARK_3_PORT, SPARK_3_PIN, &engineConfiguration->ignitionPinMode);
	outputPinRegisterExt("sparkout4", SPARKOUT_4_OUTPUT, SPARK_4_PORT, SPARK_4_PIN, &engineConfiguration->ignitionPinMode);
}

void scheduleSparkOut(OutputSignal *igniter, int offsetSysTicks, int lengthSysTicks) {
//	chDbgAssert(igniterId >= 1 && igniterId <= MAX_IGNITER_COUNT, "igniter ID", null);

//	OutputSignal *igniter = &igniters[igniterId - 1];

	scheduleOutput(igniter, offsetSysTicks, lengthSysTicks, chTimeNow());
}
