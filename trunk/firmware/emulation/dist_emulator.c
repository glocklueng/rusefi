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
#include "main_loop.h"
#include "datalogging.h"
#include "pinout.h"
#include "engine_configuration.h"

extern EngineConfiguration2 engineConfiguration2;

static Logging logger;
static volatile int deRpm = 0; // distributor RPM is camshaft RPM

#if defined __GNUC__
static PwmConfig configuration __attribute__((section(".ccm")));
#else
static PwmConfig configuration;
#endif

void setRevolutionPeriod(int value) {
	deRpm = value * engineConfiguration2.rpmMultiplier;
	myfloat gRpm = deRpm / 60.0; // per minute converted to per second
	if (gRpm == 0) {
		configuration.period = 0;
	} else {
		configuration.period = frequency2period(gRpm);
	}
	scheduleSimpleMsg(&logger, "Emulating position sensor(s). RPM=", value);
}

void initShaftPositionEmulator(void) {
#if EFI_EMULATE_POSITION_SENSORS
	print("Emulating %s\r\n", EFI_ENGINE_ID);

	initLogging(&logger, "position sensor(s) emulator");

	initOutputPin("distributor ch1", &configuration.waves[0].outputPin,
			PRIMARY_SHAFT_POSITION_EMULATION_PORT, PRIMARY_SHAFT_POSITION_EMULATION_PIN);

#if EFI_SHAFT_POSTION_NEEDS_SECONDARY
	initOutputPin("distributor ch2", &configuration.waves[1].outputPin,
			SECONDARY_SHAFT_POSITION_EMULATION_PORT, SECONDARY_SHAFT_POSITION_EMULATION_PIN);
#endif /* EFI_SHAFT_POSTION_NEEDS_SECONDARY */

	configureShaftPositionEmulatorShape(&configuration);

	setRevolutionPeriod(DEFAULT_EMULATION_RPM);

	addConsoleActionI("rpm", &setRevolutionPeriod);

#else
	print("No position sensor(s) emulation\r\n");
#endif /* EFI_EMULATE_POSITION_SENSORS */
}
