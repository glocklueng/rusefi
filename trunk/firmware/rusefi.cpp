/**
 * @file	rusefi.c
 * @brief Initialization code and main status reporting look
 *
 * @date Dec 25, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

/**
 * @mainpage
 *
 * @section sec_main Brief overview
 *
 * rusEfi runs on crankshaft or camshaft ('trigger') position sensor events.
 * Once per crankshaft revolution we evaluate the amount of needed fuel and
 * the spark timing. Once we have decided on the parameters for this revolution
 * we schedule all the actions to be triggered by the closest trigger event.
 *
 * We also have some utility threads like idle control thread and communication threads.
 *
 *
 *
 * @section sec_trigger Trigger Decoding
 *
 * Our primary trigger decoder is based on the idea of synchronizing the primary shaft signal and simply counting events on
 * the secondary signal. A typical scenario would be when camshaft positions sensor is the primary signal and crankshaft is secondary,
 * but sometimes there would be two signals generated by two camshaft sensors.
 * Another scenario is when we only have crankshaft position sensor, this would make it the primary signal and there would be no secondary signal.
 *
 * There is no software filtering so the signals are expected to be valid. TODO: in reality we are still catching engine stop noise as unrealisticly high RPM.
 *
 * The decoder is configured to act either on the primary signal rise or on the primary signal fall. It then compares the duration
 * of time from the previous signal to the duration of time from the signal before previous, and if the ratio falls into the configurable
 * range between 'syncRatioFrom' and 'syncRatioTo' this is assumed to be the synchronizing event.
 *
 * For instance, for a 36/1 skipped tooth wheel the ratio range for synchronization is from 1.5 to 3
 *
 * Some triggers do not require synchronization, this case we just count signals.
 * A single tooth primary signal would be a typical example when synchronization is not needed.
 *
 *
 *
 *
 *
 * @section sec_scheduler Event Scheduler
 *
 * It is a general agreement to measure all angles in crankshaft angles. In a four stroke
 * engine, a full cycle consists of two revolutions of the crankshaft, so all the angles are
 * running between 0 and 720 degrees.
 *
 * Ignition timing is a great example of a process which highlights the need of a hybrid
 * approach to event scheduling.
 * The most important part of controlling ignition
 * is firing up the spark at the right moment - so, for this job we need 'angle-based' timing,
 * for example we would need to fire up the spark at 700 degrees. Before we can fire up the spark
 * at 700 degrees, we need to charge the ignition coil, for example this dwell time is 4ms - that
 * means we need to turn on the coil at '4 ms before 700 degrees'. Let's  assume that the engine is
 * current at 600 RPM - that means 360 degrees would take 100 ms so 4ms is 14.4 degrees at current RPM which
 * means we need to start charting the coil at 685.6 degrees.
 *
 * The position sensors at our disposal are not providing us the current position at any moment of time -
 * all we've got is a set of events which are happening at the knows positions. For instance, let's assume that
 * our sensor sends as an event at 0 degrees, at 90 degrees, at 600 degrees and and 690 degrees.
 *
 * So, for this particular sensor the most precise scheduling would be possible if we schedule coil charting
 * as '85.6 degrees after the 600 degrees position sensor event', and spark firing as
 * '10 degrees after the 690 position sensor event'
 *
 *
 * @section sec_fuel_injection Fuel Injection
 *
 * See fuel_math.c for details on fuel amount logic
 *
 * @sectuion sec_misc
 *
 * See rpm_calculator.c for details on how getRpm() is calculated
 *
 */

extern "C" {

#include "global.h"

#include "main.h"
#include "rusefi.h"
#include "eficonsole.h"
#include "hardware.h"
#include "engine_controller.h"
#include "lcd_HD44780.h"
#include "status_loop.h"
#include "pin_repository.h"

#include "status_loop.h"
#include "memstreams.h"
}

#if EFI_ENGINE_EMULATOR
#include "engine_emulator.h"
#endif /* EFI_ENGINE_EMULATOR */

static Logging logging;

int main_loop_started = FALSE;

static MemoryStream errorMessageStream;
uint8_t errorMessageBuffer[200];
bool hasFirmwareError = FALSE;

void runRusEfi(void) {
	msObjectInit(&errorMessageStream, errorMessageBuffer, sizeof(errorMessageBuffer), 0);

	/**
	 * First data structure keeps track of which hardware I/O pins are used by whom
	 */
	initPinRepository();

	/**
	 * Next we should initialize serial port console, it's important to know what's going on
	 */
	initializeConsole();
	initLogging(&logging, "main");

	addConsoleAction("reset", scheduleReset);

	/**
	 * Initialize hardware drivers
	 */
	initHardware();

	initStatusLoop();
	/**
	 * Now let's initialize actual engine control logic
	 * todo: should we initialize some? most? controllers before hardware?
	 */
	initEngineContoller();

#if EFI_ENGINE_EMULATOR
	initEngineEmulator();
#endif
	startStatusThreads();

	print("Running main loop\r\n");
	main_loop_started = TRUE;
	/**
	 * This loop is the closes we have to 'main loop' - but here we only publish the status. The main logic of engine
	 * control is around main_trigger_callback
	 */
	while (TRUE) {
#if EFI_CLI_SUPPORT
		// sensor state + all pending messages for our own dev console
		updateDevConsoleState();
#endif /* EFI_CLI_SUPPORT */

		chThdSleepMilliseconds(5);
	}
}

int systicks2ms(int systicks) {
	return systicks / TICKS_IN_MS;
}

static VirtualTimer resetTimer;

static void rebootNow(void) {
	NVIC_SystemReset();
}
/**
 * Some configuration changes require full firmware reset.
 * Once day we will write graceful shutdown, but that would be one day.
 */
void scheduleReset(void) {
	scheduleMsg(&logging, "Rebooting in 5 seconds...");
	lockAnyContext();
	chVTSetI(&resetTimer, 5 * CH_FREQUENCY, (vtfunc_t) rebootNow, NULL);
	unlockAnyContext();
}

extern "C" {
void onFatalError(const char *msg, char * file, int line);
}

void onFatalError(const char *msg, char * file, int line) {
	onDbgPanic();
	lcdShowFatalMessage((char *) msg);
	if (!main_loop_started) {
		print("fatal %s %s:%d\r\n", msg, file, line);
		chThdSleepSeconds(1);
		chSysHalt();
	}
}

void DebugMonitorVector(void) {

	chDbgPanic("DebugMonitorVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void UsageFaultVector(void) {

	chDbgPanic("UsageFaultVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void BusFaultVector(void) {

	chDbgPanic("BusFaultVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void HardFaultVector(void) {

	chDbgPanic("HardFaultVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void firmwareError(const char *fmt, ...) {
	if (hasFirmwareError)
		return;
	hasFirmwareError = TRUE;
	errorMessageStream.eos = 0; // reset
	va_list ap;
	va_start(ap, fmt);
	chvprintf((BaseSequentialStream *) &errorMessageStream, fmt, ap);
	va_end(ap);

	errorMessageStream.buffer[errorMessageStream.eos] = 0; // need to terminate explicitly
}

int getRusEfiVersion(void) {
	return 20140326;
}
