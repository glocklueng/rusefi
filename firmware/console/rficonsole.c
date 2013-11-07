/*
 *  Created on: Nov 15, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#define VERSION_STRING 2

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "rficonsole.h"
#include "console_io.h"
#include "datalogging.h"

/**
 * @file    rficonsole.c
 * @brief   Console package entry point code
 */

static Logging log;

void consolePutChar(int x) {
	chSequentialStreamPut(CONSOLE_CHANNEL, (uint8_t )(x));
}

void consoleOutputBuffer(char *buf, int size) {
	chSequentialStreamWrite(CONSOLE_CHANNEL, buf, size);
}

static char fatalErrorMessage[200];

void fatal3(char *msg, char *file, int line) {
	strcpy(fatalErrorMessage, msg);
#if EFI_CUSTOM_PANIC_METHOD
	chDbgPanic(fatalErrorMessage, file, line);
#else
	chDbgPanic(fatalErrorMessage);
#endif
}

static void myfatal(void) {
	chDbgCheck(0, "my fatal");
}

static void sayOsHello(void) {
	print("*** rusEFI (c) Andrey Belomutskiy, 2012-2013. All rights reserved.\r\n");
	printSimpleMsg(&log, "rusEFI VERSION=", VERSION_STRING);
	print("*** Chibios Kernel:       %s\r\n", CH_KERNEL_VERSION);
	print("*** Compiled:     " __DATE__ " - " __TIME__ " \r\n");
	print("COMPILER=%s\r\n", __VERSION__);
	printSimpleMsg(&log, "CH_FREQUENCY=", CH_FREQUENCY);
	printSimpleMsg(&log, "SERIAL_SPEED=", SERIAL_SPEED);
	printSimpleMsg(&log, "STM32_ADCCLK=", STM32_ADCCLK);
	printSimpleMsg(&log, "STM32_TIMCLK1=", STM32_TIMCLK1);
	printSimpleMsg(&log, "STM32_TIMCLK2=", STM32_TIMCLK2);

	printSimpleMsg(&log, "CH_DBG_ENABLE_ASSERTS=", CH_DBG_ENABLE_ASSERTS);
	printSimpleMsg(&log, "CH_DBG_ENABLED=", CH_DBG_ENABLED);
	printSimpleMsg(&log, "CH_DBG_SYSTEM_STATE_CHECK=",
			CH_DBG_SYSTEM_STATE_CHECK);
	printSimpleMsg(&log, "CH_DBG_ENABLE_STACK_CHECK=",
			CH_DBG_ENABLE_STACK_CHECK);

	resetLogging(&log);
	append(&log, "msg");
	append(&log, DELIMETER);
	append(&log, EFI_ENGINE_ID);
	printLine(&log);

	printSimpleMsg(&log, "EFI_WAVE_ANALYZER=", EFI_WAVE_ANALYZER);
#ifdef EFI_TUNER_STUDIO
	printSimpleMsg(&log, "EFI_TUNER_STUDIO=", EFI_TUNER_STUDIO);
#else
	printSimpleMsg(&log, "EFI_TUNER_STUDIO=", 0);
#endif

#ifdef EFI_SIGNAL_EXECUTOR_SLEEP
	printSimpleMsg(&log, "EFI_SIGNAL_EXECUTOR_SLEEP=", EFI_SIGNAL_EXECUTOR_SLEEP);
#endif

#ifdef EFI_SIGNAL_EXECUTOR_HW_TIMER
	printSimpleMsg(&log, "EFI_SIGNAL_EXECUTOR_HW_TIMER=", EFI_SIGNAL_EXECUTOR_HW_TIMER);
#endif



#ifdef EFI_TUNER_STUDIO_OVER_USB
	printSimpleMsg(&log, "EFI_TUNER_STUDIO_OVER_USB=", EFI_TUNER_STUDIO_OVER_USB);
#else
	printSimpleMsg(&log, "EFI_TUNER_STUDIO_OVER_USB=", 0);
#endif
	printSimpleMsg(&log, "EFI_SHAFT_POSITION_INPUT=", EFI_SHAFT_POSITION_INPUT);
	printSimpleMsg(&log, "EFI_INTERNAL_ADC=", EFI_INTERNAL_ADC);
	printSimpleMsg(&log, "NUMBER_OF_CYLINDERS=", NUMBER_OF_CYLINDERS);
	printSimpleMsg(&log, "ENGINE_CRANKING_RPM=", ENGINE_CRANKING_RPM);
#ifdef EFI_USE_MULTI_SENSOR_SHAFT_SENSOR
	printSimpleMsg(&log, "EFI_USE_MULTI_SENSOR_SHAFT_SENSOR=", EFI_USE_MULTI_SENSOR_SHAFT_SENSOR);
#endif
#ifdef EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR
	printSimpleMsg(&log, "EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR=", EFI_USE_TOOTHED_SENSOR_SHAFT_SENSOR);
#endif
//	printSimpleMsg(&log, "", );
//	printSimpleMsg(&log, "", );


	/**
	 * Time to finish output. This is needed to avoid mix-up of this methods output and console command confirmation
	 */
	chThdSleepMilliseconds(5);
}

/**
 * This methods prints all threads and their total times
 */
static void cmd_threads(void) {
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
	initConsoleLogic();
	startChibiosConsole(&handleConsoleLine);

	initLogging(&log, "console", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	sayOsHello();
	addConsoleAction("hello", &sayOsHello);

	addConsoleAction("fatal", &myfatal);
	addConsoleAction("ths", &cmd_threads);
	addDefaultConsoleActions();
}
