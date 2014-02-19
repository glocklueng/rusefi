/**
 * @file	rusefi.c
 * @brief Initialization code and main status reporting look
 *
 * @date Dec 25, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
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
 * the secondary signal. There is no software filtering so the signals are expected to be valid.
 *
 * The decoder is configured to act either on the primary signal rise or on the primary signal fall. It then compares the duration
 * of time from the previous signal to the duration of time from the signal before previous, and if the ratio falls into the configurable
 * range between 'syncRatioFrom' and 'syncRatioTo' this is assumed to be the synchronizing event.
 *
 * For instance, for a 36/1 skipped tooth wheel the ratio range for synchronization is from 1.5 to 3
 *
 * A single tooth primary signal is handled as a special case.
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


#include "global.h"

#include "main.h"
#include "rusefi.h"
#include "rficonsole.h"
#include "hardware.h"
#include "engine_controller.h"
#include "status_loop.h"
#if EFI_ENGINE_EMULATOR
#include "engine_emulator.h"
#endif
#include "rficonsole_logic.h"
#include "tunerstudio.h"

int main_loop_started = FALSE;

void runRusEfi(void) {
	/**
	 * First we should initialize serial port console, it's important to know what's going on
	 */
	initializeConsole();

	/**
	 * Initialize hardware drivers
	 */
	initHardware();

	initStatusLoop();
	/**
	 * Now let's initialize actual engine control logic
	 */
	initEngineContoller();

#if EFI_ENGINE_EMULATOR
	initEngineEmulator();
#endif

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

#if EFI_TUNER_STUDIO
		// sensor state for EFI Analytics Tuner Studio
		updateTunerStudioState();
#endif /* EFI_TUNER_STUDIO */


#if EFI_HD44780_LCD
		updateHD44780lcd();
#endif


		chThdSleepMilliseconds(5);
	}
}

int systicks2ms(int systicks) {
	return systicks / TICKS_IN_MS;
}
