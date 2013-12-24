/**
 * @file    engine_controller.c
 * @brief   Controllers package entry point code
 *
 *
 *
 * @date Feb 7, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
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
#include "io_pins.h"
#include "tunerstudio.h"
#include "injector_central.h"
#include "ignition_central.h"
#include "rfiutil.h"
#include "engine_configuration.h"
#include "wave_analyzer.h"
#include "allsensors.h"
#include "analog_chart.h"
#include "electronic_throttle.h"
#include "malfunction_indicator.h"
#include "map_averaging.h"
#include "malfunction_central.h"

#define _10_MILLISECONDS (10 * TICKS_IN_MS)

extern EngineConfiguration *engineConfiguration;

/**
 * CH_FREQUENCY is the number of system ticks in a second
 */
#define FUEL_PUMP_DELAY (4 * CH_FREQUENCY)

static VirtualTimer everyMsTimer;
static VirtualTimer fuelPumpTimer;

static Logging logger;

static EngineConfiguration2 ec2;
EngineConfiguration2 * engineConfiguration2 = &ec2;

int isCrankingR(int rpm) {
	return rpm > 0 && rpm < engineConfiguration->crankingSettings.crankingRpm;
}

int isCranking(void) {
	int rpm = getCurrentRpm();
	return isCrankingR(rpm);
}

static void updateStatusLeds(void) {
	int is_cranking = isCranking();
	setOutputPinValue(LED_RUNNING, getCurrentRpm() > 0 && !is_cranking);
	setOutputPinValue(LED_CRANKING, is_cranking);
}

static void updateErrorCodes(void) {
	/**
	 * technically we can set error codes right inside the getMethods, but I a bit on a fence about it
	 */
	setError(isValidIntakeAirTemperature(getIntakeAirTemperature()), OBD_Intake_Air_Temperature_Circuit_Malfunction);
	setError(isValidCoolantTemperature(getCoolantTemperature()), OBD_Engine_Coolant_Temperature_Circuit_Malfunction);
}

static void onEveny10Milliseconds(void *arg) {
	updateStatusLeds();

	updateErrorCodes();

	// schedule next invocation
	chVTSetAny(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

static void initPeriodicEvents(void) {
	// schedule first invocation
	chVTSetAny(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

static void fuelPumpOff(void *arg) {
	if (getOutputPinValue(FUEL_PUMP))
		scheduleSimpleMsg(&logger, "fuelPump=", FALSE);
	turnOutputPinOff(FUEL_PUMP);
}

static void fuelPumpOn(ShaftEvents signal, int index) {
	if (index != 0)
		return; // let's not abuse the timer - one time per revolution would be enough
	if (!getOutputPinValue(FUEL_PUMP))
		scheduleSimpleMsg(&logger, "fuelPump=", TRUE);
	turnOutputPinOn(FUEL_PUMP);
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
	initLogging(&logger, "Engine Controller");

	initSettings();
	initSensors();

	initAnalogChart();

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

#if EFI_SIGNAL_EXECUTOR_SINGLE_TIMER
	initOutputScheduler();
#endif
	initInjectorCentral();
	initIgnitionCentral();

	initElectronicThrottle();
	initMalfunctionIndicator();
	initMapAveraging();

	/**
	 * This method initialized the main listener which actually runs injectors & ignition
	 */
	initMainEventListener();

	startIdleThread();

	initFuelPump();
}
