/**
 * @file    engine_controller.c
 * @brief   Controllers package entry point code
 *
 *
 *
 *  Created on: Feb 7, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "shaft_position_input.h"
#include "engine_controller.h"
#include "rpm_calculator.h"
#include "idle_thread.h"
#include "settings.h"
#include "signal_executor.h"
#include "main_loop.h"
#include "map_multiplier_thread.h"
#include "output_pins.h"
#include "tunerstudio.h"
#include "injector_central.h"
#include "ignition_central.h"
#include "rfiutil.h"
#include "engine_configuration.h"
#include "wave_analyzer.h"

#define _10_MILLISECONDS (10 * TICKS_IN_MS)
/**
 * CH_FREQUENCY is the number of system ticks in a second
 */
#define FUEL_PUMP_DELAY (4 * CH_FREQUENCY)

static VirtualTimer everyMsTimer;
static VirtualTimer fuelPumpTimer;

EngineConfiguration2 engineConfiguration2;

int isCranking(void) {
	int rpm = getCurrentRpm();
	return rpm > 0 && rpm < ENGINE_CRANKING_RPM;
}

int systicks2ms(int systicks) {
	return systicks / TICKS_IN_MS;
}

static void updateStatusLeds(void) {
	int is_cranking = isCranking();
	setOutputPinValue(LED_RUNNING, getCurrentRpm() > 0 && !is_cranking);
	setOutputPinValue(LED_CRANKING, is_cranking);
}

static void onEveny10Milliseconds(void *arg) {
	updateStatusLeds();

	// schedule next invocation
	chVTSetAny(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

static void initPeriodicEvents(void) {
	// schedule first invocation
	chVTSetAny(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

static void fuelPumpOff(void *arg) {
	setOutputPinValue(FUEL_PUMP, 0);
}

static void fuelPumpOn(ShaftEvents signal, int index) {
	if (index != 0)
		return; // let's not abuse the timer - one time per revolution would be enough
	setOutputPinValue(FUEL_PUMP, 1);
	/**
	 * the idea of this implementation is that we turn the pump when the ECU turns on or
	 * if the shafts are spinning and then we are constantly postponing the time when we
	 * will turn it off. Only if the shafts stop the turn off would actually happen.
	 */
	chVTSetAny(&fuelPumpTimer, FUEL_PUMP_DELAY, &fuelPumpOff, 0);
}

static void initFuelPump(void) {
	registerShaftPositionListener(&fuelPumpOn, "fuel pump");
	fuelPumpOn(SHAFT_PRIMARY_UP, 0);
}

void initEngineContoller(void) {
	initSettings();

#ifdef EFI_WAVE_ANALYZER
	initWaveAnalyzer();
#endif

	prepareFuelMap();

	/**
	 * there is an implicit dependency on the fact that 'tachometer' listener is the 1st listener - this case
	 * other listeners can access current RPM value
	 */
	initRpmCalculator();

#if EFI_TUNER_STUDIO
	startTunerStudioConnectivity();
#endif

// multiple issues with this	initMapAdjusterThread();
	initPeriodicEvents();

	initInjectorCentral();
	initIgnitionCentral();

	/**
	 * This method initialized the main listener which actually runs injectors & ignition
	 */
	initMainEventListener();

	startIdleThread();

	initFuelPump();
}
