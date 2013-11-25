/**
 * @file	engine_emulator.c
 * @brief	Entry point for all the emulation and analysis code
 *
 *  Created on: Mar 15, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "engine_emulator.h"

#include "rficonsole_logic.h"
#include "status_loop.h"
#include "dist_emulator.h"
#include "advance_map.h"
#include "wave_analyzer.h"
#include "fuel_map.h"
#include "pin_repository.h"
#include "poten.h"
//#include "rfi_perftest.h"

static WORKING_AREA(eeThreadStack, 256);

#define DIAG_PORT GPIOD
#define DIAG_PIN 0

void setDiag(int value) {
	print("Setting diag: %d\r\n", value);
	palWritePad(DIAG_PORT, DIAG_PIN, value);
}

#define PERIOD 3000

void emulate(void) {
	print("Emulating...\r\n");
	setDiag(1);
	chThdSleep(1);
	setFullLog(1);

	for (int i = 400; i <= 1300; i++) {
		if (i % 50 != 0)
			continue;
		setRevolutionPeriod(i);
		chThdSleepMilliseconds(PERIOD);
	}

	setRevolutionPeriod(0);

	setFullLog(0);
	setDiag(0);
	chThdSleep(1);
	print("Emulation DONE!\r\n");
}

static int flag = FALSE;

static msg_t eeThread(void *arg) {
	chRegSetThreadName("Engine");

	while (TRUE) {
		while (!flag)
			chThdSleepMilliseconds(10);
		flag = FALSE;
		emulate();
	}
	return (msg_t)NULL;
}

void startEmulator(void) {
	flag = TRUE;
}

static void printAdvance(int rpm, int maf100) {
	float advance = getAdvance(rpm, maf100 / 100.0);
	print("advance for %d rpm %d maf100: %f\r\n", rpm, maf100, advance);
}

static void initECUstimulator(void) {
	mySetPadMode("TEN", DIAG_PORT, DIAG_PIN,
	PAL_MODE_OUTPUT_PUSHPULL);

	addConsoleActionI("diag", setDiag);
	addConsoleAction("emu", startEmulator);
	addConsoleAction2I("ad", printAdvance);

	setDiag(1);

	chThdCreateStatic(eeThreadStack, sizeof(eeThreadStack), NORMALPRIO, (tfunc_t) eeThread, NULL);
}

void initEngineEmulator(void) {
//	initTimePerfActions();

	initPotentiometers();
	//initECUstimulator();
	initShaftPositionEmulator();
}
