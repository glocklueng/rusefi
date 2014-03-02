/**
 * @file	ignition_central.c
 * @brief	TODO
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "ignition_central.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "main_trigger_callback.h"
#include "engine_configuration.h"

static Logging logger;

extern engine_configuration_s *engineConfiguration;

void outputPinRegisterExt(char *msg, io_pin_e ioPin, GPIO_TypeDef *port, uint32_t pin, pin_output_mode_e *outputMode);

void initIgnitionCentral(void) {
	initLogging(&logger, "IgnitionCentral");

	outputPinRegisterExt2("sparkout1", SPARKOUT_1_OUTPUT, engineConfiguration->ignitionPins[0], &engineConfiguration->ignitionPinMode);
	outputPinRegisterExt2("sparkout2", SPARKOUT_2_OUTPUT, engineConfiguration->ignitionPins[1], &engineConfiguration->ignitionPinMode);
	outputPinRegisterExt2("sparkout3", SPARKOUT_3_OUTPUT, engineConfiguration->ignitionPins[2], &engineConfiguration->ignitionPinMode);
	outputPinRegisterExt2("sparkout4", SPARKOUT_4_OUTPUT, engineConfiguration->ignitionPins[3], &engineConfiguration->ignitionPinMode);
}

void scheduleSparkOut(OutputSignal *igniter, int offsetSysTicks, int lengthSysTicks) {
	scheduleOutput(igniter, offsetSysTicks, lengthSysTicks, chTimeNow());
}
