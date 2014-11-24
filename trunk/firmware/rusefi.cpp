/**
 * @file	rusefi.cpp
 * @brief Initialization code and main status reporting look
 *
 * @date Dec 25, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

/**
 * @mainpage
 *
 * @section sec_into
 *
 * rusEfi is implemented based on the idea that with modern 100+ MHz microprocessors the relatively
 * undemanding task of internal combustion engine control could be implemented in a high-level, processor-independent
 * (to some extent) manner. Thus the key concepts of rusEfi: dependency on high-level hardware abstraction layer, software-based PWM etc.
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
 * current at 600 RPM - that means 360 degrees would take 100ms so 4ms is 14.4 degrees at current RPM which
 * means we need to start charting the coil at 685.6 degrees.
 *
 * The position sensors at our disposal are not providing us the current position at any moment of time -
 * all we've got is a set of events which are happening at the knows positions. For instance, let's assume that
 * our sensor sends as an event at 0 degrees, at 90 degrees, at 600 degrees and and 690 degrees.
 *
 * So, for this particular sensor the most precise scheduling would be possible if we schedule coil charting
 * as '85.6 degrees after the 600 degrees position sensor event', and spark firing as
 * '10 degrees after the 690 position sensor event'. Considering current RPM, we calculate that '10 degress after' is
 * 2.777ms, so we schedule spark firing at '2.777ms after the 690 position sensor event', thus combining trigger events
 * with time-based offset.
 *
 * @section config Persistent Configuration
 * engine_configuration_s structure is kept in the internal flash memory, it has all the settings. Currently rusefi.ini has a direct mapping of this structure.
 *
 * Please note that due to TunerStudio protocol it's important to have the total structure size in synch between the firmware and TS .ini file -
 * just to make sure that this is not forgotten the size of the structure is hard-coded as PAGE_0_SIZE constant. There is always some 'unused' fields added in advance so that
 * one can add some fields without the pain of increasing the total config page size.
 * <br>See flash_main.cpp
 *
 *
 * @section sec_fuel_injection Fuel Injection
 *
 *
 * @sectuion sec_misc Misc
 *
 * <BR>See main_trigger_callback.cpp for main trigger event handler
 * <BR>See fuel_math.cpp for details on fuel amount logic
 * <BR>See rpm_calculator.cpp for details on how getRpm() is calculated
 *
 */

#include "main.h"
#include "trigger_structure.h"
#include "ec2.h"
#include "hardware.h"
#include "engine_controller.h"
#include "efiGpio.h"

#include "global.h"
extern "C" {

#include "rfi_perftest.h"
#include "rusefi.h"
}
#include "memstreams.h"

#include "eficonsole.h"
#include "status_loop.h"
#include "pin_repository.h"

#if EFI_HD44780_LCD
#include "lcd_HD44780.h"
#endif /* EFI_HD44780_LCD */

#if EFI_ENGINE_EMULATOR || defined(__DOXYGEN__)
#include "engine_emulator.h"
#endif /* EFI_ENGINE_EMULATOR */

static Logging logging;

int main_loop_started = FALSE;

static MemoryStream firmwareErrorMessageStream;
uint8_t errorMessageBuffer[200];
static bool hasFirmwareErrorFlag = FALSE;
extern engine_configuration_s *engineConfiguration;
extern board_configuration_s *boardConfiguration;
extern engine_configuration2_s *engineConfiguration2;
EXTERN_ENGINE
;

char *getFirmwareError(void) {
	return (char*) errorMessageBuffer;
}

void runRusEfi(void) {
	msObjectInit(&firmwareErrorMessageStream, errorMessageBuffer, sizeof(errorMessageBuffer), 0);

	// that's dirty, this assignment should be nicer or in a better spot
	engine->engineConfiguration = engineConfiguration;
	engine->engineConfiguration2 = engineConfiguration2;
	engineConfiguration2->engineConfiguration = engineConfiguration;

	initErrorHandling();

	/**
	 * First data structure keeps track of which hardware I/O pins are used by whom
	 */
	initPinRepository();

	/**
	 * Next we should initialize serial port console, it's important to know what's going on
	 */
	initializeConsole();
	initLogging(&logging, "main");

	engine->init();

	addConsoleAction("reset", scheduleReset);

	/**
	 * Initialize hardware drivers
	 */
	initHardware(&logging, engine);

	initStatusLoop(engine);
	/**
	 * Now let's initialize actual engine control logic
	 * todo: should we initialize some? most? controllers before hardware?
	 */
	initEngineContoller(engine);

#if EFI_PERF_METRICS || defined(__DOXYGEN__)
	initTimePerfActions();
#endif

#if EFI_ENGINE_EMULATOR || defined(__DOXYGEN__)
	initEngineEmulator(engine);
#endif
	startStatusThreads(engine);

	print("Running main loop\r\n");
	main_loop_started = TRUE;
	/**
	 * This loop is the closes we have to 'main loop' - but here we only publish the status. The main logic of engine
	 * control is around main_trigger_callback
	 */
	while (TRUE) {
		efiAssertVoid(getRemainingStack(chThdSelf()) > 128, "stack#1");

#if (EFI_CLI_SUPPORT && !EFI_UART_ECHO_TEST_MODE) || defined(__DOXYGEN__)
		// sensor state + all pending messages for our own dev console
		updateDevConsoleState(engine);
#endif /* EFI_CLI_SUPPORT */

		chThdSleepMilliseconds(boardConfiguration->consoleLoopPeriod);
	}
}

static virtual_timer_t resetTimer;

// todo: move this into a hw-specific file
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

extern int main_loop_started;

static char panicMessage[200];

void chDbgStackOverflowPanic(Thread *otp) {
	strcpy(panicMessage, "stack overflow: ");
#ifdef CH_USE_REGISTRY
	strcat(panicMessage, otp->p_name);
#endif
	chDbgPanic3(panicMessage, __FILE__, __LINE__);
}

// todo: make this a macro, noone can trust these compilers
bool hasFirmwareError(void) {
	return hasFirmwareErrorFlag;
}

// todo: why is this method here and not in error_handling.c ?
void firmwareError(const char *fmt, ...) {
	if (hasFirmwareErrorFlag)
		return;
	setOutputPinValue(LED_ERROR, 1);
	turnAllPinsOff();
	hasFirmwareErrorFlag = TRUE;
	if (indexOf(fmt, '%') == -1) {
		/**
		 * in case of simple error message let's reduce stack usage
		 * because chvprintf might be causing an error
		 */
		strcpy((char*) errorMessageBuffer, fmt);

	} else {
		firmwareErrorMessageStream.eos = 0; // reset
		va_list ap;
		va_start(ap, fmt);
		chvprintf((BaseSequentialStream *) &firmwareErrorMessageStream, fmt, ap);
		va_end(ap);

		firmwareErrorMessageStream.buffer[firmwareErrorMessageStream.eos] = 0; // need to terminate explicitly
	}
}

static char UNUSED_RAM_SIZE[20000];

static char UNUSED_CCM_SIZE[5000] CCM_OPTIONAL;

int getRusEfiVersion(void) {
	if (UNUSED_RAM_SIZE == 0)
		return 1; // this is here to make the compiler happy about the unused array
	if (UNUSED_CCM_SIZE == 0)
		return 1; // this is here to make the compiler happy about the unused array
	return 20141124;
}
