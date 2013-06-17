/*
 * main.c
 *
 *  Created on: Nov 29, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <ch.h>
#include <hal.h>
#include "rficonsole.h"
#include "hardware.h"
#include "engine_controller.h"
#include "status_loop.h"

int main(void) {
	halInit();
	chSysInit();

	initializeConsole();
	initHardware();
	initEngineContoller();

	initStatusLoop();

	print("Running main loop\r\n");
	while (TRUE) {
		printState();
		chThdSleepMilliseconds(1);
	}
	return 0;
}
