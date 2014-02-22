/**
 * @file    rficonsole.c
 * @brief   Console package entry point code
 *
 *
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "rficonsole.h"
#include "console_io.h"
#include "rusefi.h"

static Logging logger;

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

static void sayHello(void) {
	print("*** rusEFI (c) Andrey Belomutskiy, 2012-2014. All rights reserved.\r\n");
	printMsg(&logger, "rusEFI VERSION=%d", getVersion());
	print("*** Chibios Kernel:       %s\r\n", CH_KERNEL_VERSION);
	print("*** Compiled:     " __DATE__ " - " __TIME__ " \r\n");
	print("COMPILER=%s\r\n", __VERSION__);
	printMsg(&logger, "CH_FREQUENCY=%d", CH_FREQUENCY);
	printMsg(&logger, "SERIAL_SPEED=%d", SERIAL_SPEED);
	printMsg(&logger, "STM32_ADCCLK=%d", STM32_ADCCLK);
	printMsg(&logger, "STM32_TIMCLK1=%d", STM32_TIMCLK1);
	printMsg(&logger, "STM32_TIMCLK2=%d", STM32_TIMCLK2);
	printMsg(&logger, "STM32_PCLK1=%d", STM32_PCLK1);
	printMsg(&logger, "STM32_PCLK2=%d", STM32_PCLK2);

	printMsg(&logger, "CH_DBG_ENABLE_ASSERTS=%d", CH_DBG_ENABLE_ASSERTS);
	printMsg(&logger, "CH_DBG_ENABLED=%d", CH_DBG_ENABLED);
	printMsg(&logger, "CH_DBG_SYSTEM_STATE_CHECK=%d", CH_DBG_SYSTEM_STATE_CHECK);
	printMsg(&logger, "CH_DBG_ENABLE_STACK_CHECK=%d", CH_DBG_ENABLE_STACK_CHECK);

	printMsg(&logger, "EFI_WAVE_ANALYZER=%d", EFI_WAVE_ANALYZER);
#ifdef EFI_TUNER_STUDIO
	printMsg(&logger, "EFI_TUNER_STUDIO=%d", EFI_TUNER_STUDIO);
#else
	printMsg(&logger, "EFI_TUNER_STUDIO=%d", 0);
#endif

#ifdef EFI_SIGNAL_EXECUTOR_SLEEP
	printMsg(&logger, "EFI_SIGNAL_EXECUTOR_SLEEP=%d", EFI_SIGNAL_EXECUTOR_SLEEP);
#endif

#ifdef EFI_SIGNAL_EXECUTOR_HW_TIMER
	printMsg(&logger, "EFI_SIGNAL_EXECUTOR_HW_TIMER=%d", EFI_SIGNAL_EXECUTOR_HW_TIMER);
#endif



#ifdef EFI_TUNER_STUDIO_OVER_USB
	printMsg(&logger, "EFI_TUNER_STUDIO_OVER_USB=%d", EFI_TUNER_STUDIO_OVER_USB);
#else
	printMsg(&logger, "EFI_TUNER_STUDIO_OVER_USB=%d", 0);
#endif
	printMsg(&logger, "EFI_SHAFT_POSITION_INPUT=%d", EFI_SHAFT_POSITION_INPUT);
	printMsg(&logger, "EFI_INTERNAL_ADC=%d", EFI_INTERNAL_ADC);

//	printSimpleMsg(&logger, "", );
//	printSimpleMsg(&logger, "", );


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

void sendOutConfirmation(char *value, int i) {
	scheduleSimpleMsg(&logger, value, i);
}

void initializeConsole() {
	initIntermediateLoggingBuffer();
	initConsoleLogic();

	startChibiosConsole(&handleConsoleLine);

	initLogging(&logger, "console");

	sayHello();
	addConsoleAction("hello", sayHello);
	addConsoleAction("reset", scheduleReset);

	addConsoleAction("fatal", myfatal);
	addConsoleAction("ths", cmd_threads);
	addDefaultConsoleActions();
}
