/**
 * @file    trigger_emulator.c
 * @brief   Position sensor(s) emulation code
 *
 * This file is mostly about initialization, the configuration is
 * provided by the configureShaftPositionEmulatorShape method
 *
 * @date Dec 9, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "trigger_emulator.h"
#include "rficonsole.h"
#include "main_trigger_callback.h"
#include "datalogging.h"
#include "pinout.h"
#include "engine_configuration.h"
#include "pwm_generator.h"
#include "io_pins.h"
#include "pin_repository.h"

extern engine_configuration_s *engineConfiguration;
extern engine_configuration2_s *engineConfiguration2;

static Logging logger;

#if defined __GNUC__
static PwmConfig configuration __attribute__((section(".ccm")));
#else
static PwmConfig configuration;
#endif

void setTriggerEmulatorRPM(int rpm) {
	if (rpm == 0) {
		configuration.period = NAN;
	} else {
		myfloat gRpm = rpm * engineConfiguration2->rpmMultiplier / 60.0; // per minute converted to per second
		configuration.period = frequency2period(gRpm);
	}
	scheduleMsg(&logger, "Emulating position sensor(s). RPM=%d", rpm);
}

void initTriggerEmulator(void) {
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

	setTriggerEmulatorRPM(DEFAULT_EMULATION_RPM);

	int *pinStates[2] = {s->wave.waves[0].pinStates, s->wave.waves[1].pinStates};
	weComplexInit("position sensor", &configuration, s->size, s->wave.switchTimes, 2, pinStates);



	addConsoleActionI("rpm", &setTriggerEmulatorRPM);

#else
	print("No position sensor(s) emulation\r\n");
#endif /* EFI_EMULATE_POSITION_SENSORS */
}
