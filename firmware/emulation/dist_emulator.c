/**
 * @file    dist_emulator.c
 * @brief   Position sensor(s) emulation code
 *
 * This file is mostly about initialization, the configuration is
 * provided by the configureShaftPositionEmulatorShape method
 *
 * @date Dec 9, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "dist_emulator.h"
#include "rficonsole.h"
#include "main_trigger_callback.h"
#include "datalogging.h"
#include "pinout.h"
#include "engine_configuration.h"
#include "pwm_generator.h"
#include "io_pins.h"
#include "pin_repository.h"

extern EngineConfiguration *engineConfiguration;
extern EngineConfiguration2 *engineConfiguration2;

static Logging logger;

#if defined __GNUC__
static PwmConfig configuration __attribute__((section(".ccm")));
#else
static PwmConfig configuration;
#endif

void setRevolutionPeriod(int value) {
	if (value == 0) {
		configuration.period = 0;
	} else {
		myfloat gRpm = value * engineConfiguration2->rpmMultiplier / 60.0; // per minute converted to per second
		configuration.period = frequency2period(gRpm);
	}
	scheduleSimpleMsg(&logger, "Emulating position sensor(s). RPM=", value);
}

void initShaftPositionEmulator(void) {
#if EFI_EMULATE_POSITION_SENSORS
	print("Emulating %s\r\n", getConfigurationName(engineConfiguration));

	initLogging(&logger, "position sensor(s) emulator");


	configuration.outputPins[0] = TRIGGER_EMILATOR_PRIMARY;
	configuration.outputPins[1] = TRIGGER_EMILATOR_SECONDARY;

	outputPinRegister("distributor ch1", configuration.outputPins[0],
	PRIMARY_SHAFT_POSITION_EMULATION_PORT, PRIMARY_SHAFT_POSITION_EMULATION_PIN);

	outputPinRegister("distributor ch2", configuration.outputPins[1],
	SECONDARY_SHAFT_POSITION_EMULATION_PORT, SECONDARY_SHAFT_POSITION_EMULATION_PIN);

	trigger_shape_s *s = &engineConfiguration2->triggerShape;

	int *pinStates[2] = {s->wave.waves[0].pinStates, s->wave.waves[1].pinStates};
	weComplexInit("position sensor", &configuration, 0, s->size, s->wave.switchTimes, 2, pinStates);


	setRevolutionPeriod(DEFAULT_EMULATION_RPM);

	addConsoleActionI("rpm", &setRevolutionPeriod);

#else
	print("No position sensor(s) emulation\r\n");
#endif /* EFI_EMULATE_POSITION_SENSORS */
}
