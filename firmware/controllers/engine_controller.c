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
#include "trigger_input.h"
#include "engine_controller.h"
#include "rpm_calculator.h"
#include "idle_thread.h"
#include "settings.h"
#include "signal_executor.h"
#include "main_trigger_callback.h"
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
#include "advance_map.h"
#include "pin_repository.h"
#include "rficonsole_logic.h"
#include "pwm_generator.h"
#include "fuel_math.h"

#define _10_MILLISECONDS (10 * TICKS_IN_MS)

extern engine_configuration_s *engineConfiguration;

/**
 * CH_FREQUENCY is the number of system ticks in a second
 */
#define FUEL_PUMP_DELAY (4 * CH_FREQUENCY)

static VirtualTimer everyMsTimer;
static VirtualTimer fuelPumpTimer;

static Logging logger;

static engine_configuration2_s ec2;
engine_configuration2_s * engineConfiguration2 = &ec2;

int isCranking(void) {
	int rpm = getRpm();
	return isCrankingR(rpm);
}

static void updateStatusLeds(void) {
	int is_cranking = isCranking();
	setOutputPinValue(LED_RUNNING, getRpm() > 0 && !is_cranking);
	setOutputPinValue(LED_CRANKING, is_cranking);
}

static void updateErrorCodes(void) {
	/**
	 * technically we can set error codes right inside the getMethods, but I a bit on a fence about it
	 */
	setError(isValidIntakeAirTemperature(getIntakeAirTemperature()), OBD_Intake_Air_Temperature_Circuit_Malfunction);
	setError(isValidCoolantTemperature(getCoolantTemperature()), OBD_Engine_Coolant_Temperature_Circuit_Malfunction);
}

static void fanRelayControl(void) {

	int isCurrentlyOn = getOutputPinValue(FAN_RELAY);
	int newValue;
	if (isCurrentlyOn) {
		// if the fan is already on, we keep it on till the 'fanOff' temperature
		newValue = getCoolantTemperature() > engineConfiguration->fanOffTemperature;
	} else {
		newValue = getCoolantTemperature() > engineConfiguration->fanOnTemperature;
	}

	if (isCurrentlyOn != newValue) {
		scheduleMsg(&logger, "FAN relay: %s", newValue ? "ON" : "OFF");
		setOutputPinValue(FAN_RELAY, newValue);
	}
}

static void onEveny10Milliseconds(void *arg) {
	updateStatusLeds();

	updateErrorCodes();

	fanRelayControl();

	// schedule next invocation
	chVTSetAny(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

static void initPeriodicEvents(void) {
	// schedule first invocation
	chVTSetAny(&everyMsTimer, _10_MILLISECONDS, &onEveny10Milliseconds, 0);
}

static void fuelPumpOff(void *arg) {
	if (getOutputPinValue(FUEL_PUMP_RELAY))
		scheduleMsg(&logger, "fuelPump OFF at %s%d", portname(FUEL_PUMP_PORT ), FUEL_PUMP_PIN);
	turnOutputPinOff(FUEL_PUMP_RELAY);
}

static void fuelPumpOn(ShaftEvents signal, int index) {
	if (index != 0)
		return; // let's not abuse the timer - one time per revolution would be enough
	if (!getOutputPinValue(FUEL_PUMP_RELAY))
		scheduleMsg(&logger, "fuelPump ON at %s%d", portname(FUEL_PUMP_PORT ), FUEL_PUMP_PIN);
	turnOutputPinOn(FUEL_PUMP_RELAY);
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

void printTemperatureInfo(void) {
	float rClt = getResistance(&engineConfiguration2->clt);
	float rIat = getResistance(&engineConfiguration2->iat);

	scheduleMsg(&logger, "CLT R=%f on channel %d", rClt, engineConfiguration2->clt.channel);
	scheduleMsg(&logger, "IAT R=%f on channel %d", rIat, engineConfiguration2->iat.channel);

	scheduleMsg(&logger, "cranking fuel %fms @ %fC", engineConfiguration->crankingSettings.fuelAtMinTempMs,
			engineConfiguration->crankingSettings.coolantTempMinC);
	scheduleMsg(&logger, "cranking fuel %fms @ %fC", engineConfiguration->crankingSettings.fuelAtMaxTempMs,
			engineConfiguration->crankingSettings.coolantTempMaxC);
}

void initEngineContoller(void) {
	initLogging(&logger, "Engine Controller");

	initSettings();
	initSensors();

	initPwmGenerator();

	initAnalogChart();

#ifdef EFI_WAVE_ANALYZER
	initWaveAnalyzer();
#endif

	prepareFuelMap();
	prepareTimingMap();

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
	initMalfunctionCentral();

#if EFI_ELECTRONIC_THROTTLE_BODY
	initElectronicThrottle();
#endif /* EFI_ELECTRONIC_THROTTLE_BODY */
	initMalfunctionIndicator();
	initMapAveraging();

	/**
	 * This method initialized the main listener which actually runs injectors & ignition
	 */
	initMainEventListener();

#if EFI_IDLE_CONTROL
	startIdleThread();
#endif

	initFuelPump();

	addConsoleAction("tempinfo", printTemperatureInfo);

}
