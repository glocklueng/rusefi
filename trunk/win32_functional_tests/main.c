/*
 ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "main.h"
//#include "shell.h"
#include "chprintf.h"
#include "rusEfiFunctionalTest.h"

#define SHELL_WA_SIZE       THD_WA_SIZE(4096)
#define CONSOLE_WA_SIZE     THD_WA_SIZE(4096)
//#define TEST_WA_SIZE        THD_WA_SIZE(4096)

#define cputs(msg) chMsgSend(cdtp, (msg_t)msg)

static Thread *cdtp;
//static Thread *shelltp1;
//static Thread *shelltp2;

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[]) {
	size_t n, size;

	(void) argv;
	if (argc > 0) {
		chprintf(chp, "Usage: mem\r\n");
		return;
	}
	n = chHeapStatus(NULL, &size);
	chprintf(chp, "core free memory : %u bytes\r\n", chCoreStatus());
	chprintf(chp, "heap fragments   : %u\r\n", n);
	chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[]) {
	static const char *states[] = { THD_STATE_NAMES };
	Thread *tp;

	(void) argv;
	if (argc > 0) {
		chprintf(chp, "Usage: threads\r\n");
		return;
	}
	chprintf(chp, "    addr    stack prio refs     state time\r\n");
	tp = chRegFirstThread();
	do {
		chprintf(chp, "%.8lx %.8lx %4lu %4lu %9s %lu\r\n", (uint32_t) tp, (uint32_t) tp->p_ctx.esp,
				(uint32_t) tp->p_prio, (uint32_t) (tp->p_refs - 1), states[tp->p_state], (uint32_t) tp->p_time);
		tp = chRegNextThread(tp);
	} while (tp != NULL);
}

/*
 * Console print server done using synchronous messages. This makes the access
 * to the C printf() thread safe and the print operation atomic among threads.
 * In this example the message is the zero terminated string itself.
 */
static msg_t console_thread(void *arg) {

	(void) arg;
	while (!chThdShouldTerminate()) {
		Thread *tp = chMsgWait();
		puts((char *) chMsgGet(tp));
		fflush(stdout);
		chMsgRelease(tp, RDY_OK);
	}
	return 0;
}

/**
 * @brief Shell termination handler.
 *
 * @param[in] id event id.
 */
static void termination_handler(eventid_t id) {

	chThdSleepMilliseconds(10);

	cputs("Init: shell on SD1 terminated");
	chSysLock();
	chOQResetI(&SD1.oqueue);
	chSysUnlock();

//  if (shelltp2 && chThdTerminated(shelltp2)) {
//    chThdWait(shelltp2);
//    shelltp2 = NULL;
//    chThdSleepMilliseconds(10);
//    cputs("Init: shell on SD2 terminated");
//    chSysLock();
//    chOQResetI(&SD2.oqueue);
//    chSysUnlock();
//  }
}

static EventListener sd1fel, sd2fel;

/**
 * @brief SD1 status change handler.
 *
 * @param[in] id event id.
 */
static void sd1_handler(eventid_t id) {
	flagsmask_t flags;

	(void) id;
	flags = chEvtGetAndClearFlags(&sd1fel);
	if ((flags & CHN_CONNECTED)) {
		cputs("Init: connection on SD1");
	}
	if (flags & CHN_DISCONNECTED) {
		cputs("Init: disconnection on SD1");
		chSysLock();
		chIQResetI(&SD1.iqueue);
		chSysUnlock();
	}
}

/**
 * @brief SD2 status change handler.
 *
 * @param[in] id event id.
 */
static void sd2_handler(eventid_t id) {
	flagsmask_t flags;

	(void) id;
	flags = chEvtGetAndClearFlags(&sd2fel);
	if ((flags & CHN_CONNECTED)) {
		cputs("Init: connection on SD2");
	}
	if (flags & CHN_DISCONNECTED) {
		cputs("Init: disconnection on SD2");
		chSysLock();
		chIQResetI(&SD2.iqueue);
		chSysUnlock();
	}
}

static evhandler_t fhandlers[] = { termination_handler, sd1_handler, sd2_handler };

/*------------------------------------------------------------------------*
 * Simulator main.                                                        *
 *------------------------------------------------------------------------*/
int main(void) {
	EventListener tel;

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	/*
	 * Serial ports (simulated) initialization.
	 */
	sdStart(&SD1, NULL);
	sdStart(&SD2, NULL);

	/*
	 * Console thread started.
	 */
	cdtp = chThdCreateFromHeap(NULL, CONSOLE_WA_SIZE, NORMALPRIO + 1, console_thread, NULL);

	/*
	 * Initializing connection/disconnection events.
	 */
	cputs("Shell service started on SD1, SD2");
	cputs("  - Listening for connections on SD1");
	chEvtRegister(chnGetEventSource(&SD1), &sd1fel, 1);
	cputs("  - Listening for connections on SD2");
	chEvtRegister(chnGetEventSource(&SD2), &sd2fel, 2);

	rusEfiFunctionalTest();

	/*
	 * Events servicing loop.
	 */
	while (!chThdShouldTerminate())
		chEvtDispatch(fhandlers, chEvtWaitOne(ALL_EVENTS));

	/*
	 * Clean simulator exit.
	 */
	chEvtUnregister(chnGetEventSource(&SD1), &sd1fel);
	chEvtUnregister(chnGetEventSource(&SD2), &sd2fel);
	return 0;
}

//void print(const char *format, ...) {
//	va_list ap;
//	va_start(ap, format);
//	vprintf(format, ap);
//	va_end(ap);
//}

int systicks2ms(int systicks) {
	return systicks / TICKS_IN_MS;
}

void onFatalError(const char *msg, char * file, int line) {
}

void warning(char *msg, float value) {
	printf("Warning: %s %f\r\n", msg, value);
}

void fatal(char *x) {
	printf(x);
	exit(-1);
}

//void sendOutConfirmation(char *value, int i) {
//}

int hasFatalError(void) {
	return false;
}
int getVersion(void) {
	return 239;
}

//void chDbgPanic(const char *msg, char * file, int line) {
//		printf("assert failed: %s\r\n", "namic");
//		exit(-1);
//}
//

//void print(const char *format, ...) {
//	va_list ap;
//	va_start(ap, format);
//	vprintf(format, ap);
//	va_end(ap);
//}
//
