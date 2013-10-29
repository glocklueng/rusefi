/*
 *  Created on: Dec 9, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    dist_emulator.c
 * @brief   Position sensor(s) emulation code
 */

#include "dist_emulator.h"
#include "rficonsole.h"
#include "main_loop.h"
#include "datalogging.h"
#include "pinout.h"

// because each cam revolution is half of crank revolution
#define EXTRA_RPM_COEFF (1.0 / 2)

static Logging log;
static volatile int deRpm = 0; // distributor RPM is camshaft RPM

#if defined __GNUC__
static PwmConfig configuration __attribute__((section(".bss2")));
#else
static PwmConfig configuration;
#endif

void setRevolutionPeriod(int value) {
	deRpm = value * RPM_MULT;
	myfloat gRpm = deRpm / 60.0; // per minute converted to per second
	if (gRpm == 0) {
		configuration.period = 0;
	} else {
		configuration.period = frequency2period(gRpm);
	}
	scheduleSimpleMsg(&log, "Emulating position sensor(s). RPM=", value);
}

void initShaftPositionEmulator(void) {
#if EFI_EMULATE_POSITION_SENSORS
	print("Emulating %s\r\n", EFI_ENGINE_ID);

	initLogging(&log, "position sensor(s) emulator", log.DEFAULT_BUFFER,
			sizeof(log.DEFAULT_BUFFER));

	initOutputPin("distributor ch1", &configuration.waves[0].outputPin,
			PRIMARY_SHAFT_POSITION_EMULATION_PORT, PRIMARY_SHAFT_POSITION_EMULATION_PIN);

#if EFI_SHAFT_POSTION_NEEDS_SECONDARY
	initOutputPin("distributor ch2", &configuration.waves[1].outputPin,
			SECONDARY_SHAFT_POSITION_EMULATION_PORT, SECONDARY_SHAFT_POSITION_EMULATION_PIN);
#endif

	confgiureShaftPositionEmulatorShape(&configuration);


	setRevolutionPeriod(DEFAULT_EMULATION_RPM);

	addConsoleAction1("rpm", &setRevolutionPeriod);

#else
	print("No position sensor(s) emulation\r\n");
#endif
}
