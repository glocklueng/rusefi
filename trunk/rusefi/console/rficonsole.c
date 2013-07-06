/*
 *  Created on: Nov 15, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#define VERSION_STRING 0.0000001

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "ch.h"
#include "rficonsole.h"
#include "console_io.h"
#include "datalogging.h"

static Logging log;

void consolePutChar(int x) {
	chSequentialStreamPut(CONSOLE_CHANNEL, (uint8_t )(x));
}

static char fatalErrorMessage[200];

void fatal(char *msg) {
	strcpy(fatalErrorMessage, msg);
	chDbgPanic(fatalErrorMessage);
}

static void myfatal() {
	chDbgCheck(0, "my fatal");
}

static void sayOsHello() {
	print("*** rusEFI (c) Andrey Belomutskiy, 2012-2013. All rights reserved.\r\n");
	print("*** Chibios Kernel:       %s\r\n", CH_KERNEL_VERSION);
	print("*** Compiled:     ");
	print(__DATE__);
	print(" - " __TIME__ " \r\n");
	printSimpleMsg(&log, "VERSION=", VERSION_STRING);
	printSimpleMsg(&log, "CH_FREQUENCY=", CH_FREQUENCY);
	printSimpleMsg(&log, "SERIAL_SPEED=", SERIAL_SPEED);

	printSimpleMsg(&log, "CH_DBG_ENABLE_ASSERTS=", CH_DBG_ENABLE_ASSERTS);
	printSimpleMsg(&log, "CH_DBG_ENABLED=", CH_DBG_ENABLED);
	printSimpleMsg(&log, "CH_DBG_SYSTEM_STATE_CHECK=",
			CH_DBG_SYSTEM_STATE_CHECK);
	printSimpleMsg(&log, "CH_DBG_ENABLE_STACK_CHECK=",
			CH_DBG_ENABLE_STACK_CHECK);

	/**
	 * Time to finish output. This is needed to avoid mix-up of this methods output and console command confirmation
	 */
	chThdSleepMilliseconds(5);
}

static void cmd_threads() {
	static const char *states[] = { THD_STATE_NAMES };
	Thread *tp;

	print("    addr    stack prio refs     state time\r\n");
	tp = chRegFirstThread();
	do {
		print("%.8lx [%.8lx] %4lu %4lu %9s %lu %s\r\n", (uint32_t) tp, 0,
				(uint32_t) tp->p_prio, (uint32_t) (tp->p_refs - 1),
				states[tp->p_state], (uint32_t) tp->p_time, tp->p_name);
		tp = chRegNextThread(tp);
	} while (tp != NULL );
}

void initializeConsole() {
	initLogging(&log, "rfi console", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));
	initConsoleLogic();
	startChibiosConsole(&handleConsoleLine);

	sayOsHello();
	addConsoleAction("hello", &sayOsHello);

	addConsoleAction("fatal", &myfatal);
	addConsoleAction("ths", &cmd_threads);
	addDefaultConsoleActions();
}
