/*
 * main.c
 *
 *  Created on: Nov 29, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 *      http://rusefi.com/
 */

#include <halconf.h>
#include <ch.h>
#include <hal.h>

#include "main.h"

#include "rficonsole.h"
#include "hardware.h"
#include "engine_controller.h"
#include "status_loop.h"
#if EFI_ENGINE_EMULATOR
#include "engine_emulator.h"
#endif
#include "rficonsole_logic.h"
#include "tunerstudio.h"

int main(void) {
	/*
	 * ChibiOS/RT initialization
	 */
	halInit();
	chSysInit();

	/**
	 * First we should initialize serial port console, it's important to know what's going on
	 */
	initializeConsole();
	/**
	 * Initialize hardware drivers
	 */
	initHardware();
	/**
	 * Now let's initialize actual engine control logic
	 */
	initEngineContoller();

#if EFI_ENGINE_EMULATOR
	initEngineEmulator();
#endif

	initStatusLoop();

	print("Running main loop\r\n");
	while (TRUE) {
		printState();
#if EFI_TUNER_STUDIO
		updateTunerStudioState();
#endif
		chThdSleepMilliseconds(5);
	}
	return 0;
}
