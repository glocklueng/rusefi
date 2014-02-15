/**
 * @file	status_loop.c
 * @brief Human-readable protocol status messages
 *
 * http://rusefi.com/forum/viewtopic.php?t=263 Dev console overview
 * http://rusefi.com/forum/viewtopic.php?t=210 Commands overview
 *
 *
 * @date Mar 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "status_loop.h"

#include "adc_inputs.h"
#if EFI_WAVE_ANALYZER
#include "wave_analyzer.h"
#endif

#include "engine_state.h"
#include "io_pins.h"
#include "mmc_card.h"

#include "datalogging.h"
#include "shaft_position_input.h"
#include "rficonsole_logic.h"
#include "advance_map.h"

#include "wave_math.h"

#include "fuel_map.h"
#include "main_trigger_callback.h"
#include "engine_math.h"
#include "idle_thread.h"
#include "engine_configuration.h"
#include "lcd_2x16.h"
#include "rfiutil.h"

extern engine_configuration2_s * engineConfiguration2;

#define INITIAL_FULL_LOG TRUE
//#define INITIAL_FULL_LOG FALSE

static volatile int fullLog;
volatile int needToReportStatus = FALSE;
static int prevCkpEventCounter = -1;

static Logging logger;
static Logging logger2;
#if EFI_FILE_LOGGING
static Logging fileLogger;
#endif /* EFI_FILE_LOGGING */
static char LOGGING_BUFFER[500];
#define FULL_LOGGING_KEY "fl"

static time_t timeOfPreviousWarning = (systime_t) -10 * CH_FREQUENCY;

static char* boolean2string(int value) {
	return value ? "YES" : "NO";
}

void setFullLog(int value) {
	print("Setting full logging: %s\r\n", boolean2string(value));
	printSimpleMsg(&logger, FULL_LOGGING_KEY, value);
	fullLog = value;
}

int getFullLog(void) {
	return fullLog;
}

static void printStatus(void) {
	needToReportStatus = TRUE;
}

//float getTCharge1(myfloat tps) {
//	myfloat cltK = tempCtoKelvin(getCoolantTemperature());
//	myfloat iatK = tempCtoKelvin(getIntakeAirTemperature());
//	return getTCharge(getCurrentRpm(), tps, cltK, iatK);
//}

static void reportSensorF(char *caption, float value, int precision) {
	debugFloat(&logger, caption, value, precision);
#if EFI_FILE_LOGGING
	debugFloat(&fileLogger, caption, value, precision);
#endif /* EFI_FILE_LOGGING */
}

static void reportSensorI(char *caption, int value) {
	debugInt(&logger, caption, value);
#if EFI_FILE_LOGGING
	debugInt(&fileLogger, caption, value);
#endif /* EFI_FILE_LOGGING */
}

static void printSensors(void) {
#if EFI_FILE_LOGGING
	resetLogging(&fileLogger);
#endif /* EFI_FILE_LOGGING */

	// current time, in milliseconds
	int nowMs = chTimeNow() / TICKS_IN_MS;
	myfloat sec = ((myfloat) nowMs) / 1000;
	reportSensorF("time", sec, 3);

	reportSensorI("rpm", getCurrentRpm());
	reportSensorF("maf", getMaf(), 2);

	if (engineConfiguration2->hasMapSensor) {
		reportSensorF(getCaption(LP_MAP), getMap(), 2);
	}

	reportSensorF("afr", getAfr(), 2);
	reportSensorF("vref", getVRef(), 2);
	reportSensorF("vbatt", getVBatt(), 2);

	reportSensorF(getCaption(LP_THROTTLE), getTPS(), 2);

	if (engineConfiguration2->hasCltSensor) {
		reportSensorF(getCaption(LP_ECT), getCoolantTemperature(), 2);
	}

	reportSensorF(getCaption(LP_IAT), getIntakeAirTemperature(), 2);

//	debugFloat(&logger, "tch", getTCharge1(tps), 2);

#if EFI_FILE_LOGGING
	appendPrintf(&fileLogger, "\r\n");
	appendToLog(fileLogger.buffer);
#endif /* EFI_FILE_LOGGING */
}

#if EFI_CUSTOM_PANIC_METHOD
extern char *dbg_panic_file;
extern int dbg_panic_line;
#endif

void onDbgPanic(void) {
	setOutputPinValue(LED_ERROR, 1);
}

int hasFatalError(void) {
	return dbg_panic_msg != NULL;
}

static void checkIfShouldHalt(void) {
#if CH_DBG_ENABLED
	if (hasFatalError()) {
		setOutputPinValue(LED_ERROR, 1);
#if EFI_CUSTOM_PANIC_METHOD
		print("my FATAL [%s] at %s:%d\r\n", dbg_panic_msg, dbg_panic_file, dbg_panic_line);
#else
		print("my FATAL [%s] at %s:%d\r\n", dbg_panic_msg);
#endif
		chThdSleepSeconds(1);
		// todo: figure out how we halt exactly
		while (TRUE) {
		}
		chSysHalt();
	}
#endif
}

static systime_t timeOfPreviousReport = (systime_t) -1;

/**
 * @brief Sends all pending data to dev console
 */
void updateDevConsoleState(void) {
	if (!is_serial_ready())
		return;
	checkIfShouldHalt();
	printPending();

	pokeAdcInputs();

	if (!fullLog)
		return;

	systime_t nowSeconds = chTimeNowSeconds();

	int currentCkpEventCounter = getCrankEventCounter();
	if (prevCkpEventCounter == currentCkpEventCounter && timeOfPreviousReport == nowSeconds)
		return;

	timeOfPreviousReport = nowSeconds;

	int rpm = getCurrentRpm();

	prevCkpEventCounter = currentCkpEventCounter;

	printSensors();

	debugInt(&logger, "ckp_c", currentCkpEventCounter);

//	debugInt(&logger, "idl", getIdleSwitch());

//	debugFloat(&logger, "table_spark", getAdvance(rpm, getMaf()), 2);

	myfloat key = getMaf();
	debugFloat(&logger, "fuel_base", getBaseFuel(rpm, key), 2);
	debugFloat(&logger, "fuel_iat", getIatCorrection(getIntakeAirTemperature()), 2);
	debugFloat(&logger, "fuel_clt", getCltCorrection(getCoolantTemperature()), 2);
	debugFloat(&logger, "fuel_lag", getInjectorLag(getVBatt()), 2);
	debugFloat(&logger, "fuel", getRunningFuel(rpm, key), 2);

	debugFloat(&logger, "timing", getAdvance(rpm, key), 2);

//		myfloat map = getMap();
//		myfloat fuel = getDefaultFuel(rpm, map);
//		debugFloat(&logger, "d_fuel", fuel, 2);

#if EFI_WAVE_ANALYZER
	printWave(&logger);
#endif

	printLine(&logger);
}

/*
 * command example:
 * sfm 3500 400
 * that would be 'show fuel for rpm 3500 maf 4.0'
 */

static void showFuelMap(int rpm, int key100) {
	myfloat key = key100 / 100.0;

	float baseFuel = getBaseFuel(rpm, key);

	float iatCorrection = getIatCorrection(getIntakeAirTemperature());
	float cltCorrection = getCltCorrection(getCoolantTemperature());
	float injectorLag = getInjectorLag(getVBatt());
	print("baseFuel=%f\r\n", baseFuel);

	print("iatCorrection=%f cltCorrection=%f injectorLag=%d\r\n", iatCorrection, cltCorrection,
			(int) (100 * injectorLag));

	myfloat value = getRunningFuel(rpm, key);

	print("fuel map rpm=%d, key=%f: %d\r\n", rpm, key, (int) (100 * value));

	scheduleMsg(&logger2, "fuel map value = %f", value);
}

void initStatusLoop(void) {
	initLoggingExt(&logger, "status loop", LOGGING_BUFFER, sizeof(LOGGING_BUFFER));
	initLogging(&logger2, "main event handler");
#if EFI_FILE_LOGGING
	initLogging(&fileLogger, "file logger");
#endif /* EFI_FILE_LOGGING */

	setFullLog(INITIAL_FULL_LOG);

	addConsoleActionII("sfm", showFuelMap);

	addConsoleActionI(FULL_LOGGING_KEY, setFullLog);
	addConsoleAction("status", printStatus);
}

void warning(char *msg, float value) {
	time_t now = chTimeNow();
	if (overflowDiff(now, timeOfPreviousWarning) < CH_FREQUENCY)
		return; // we just had another warning, let's not spam
	timeOfPreviousWarning = now;

	scheduleSimpleMsg(&logger, msg, (int) (1000 * value));
}

static char buffer[10];
void updateHD44780lcd(void) {
	lcd_HD44780_set_position(0, 11);
	lcd_HD44780_print_char('0' + (chTimeNowSeconds() % 10));

	lcd_HD44780_set_position(0, 12);
	char * ptr = itoa(buffer, getCurrentRpm());
	ptr[0] = 0;
	int len = ptr - buffer;
	for (int i = 0; i < 6 - len; i++)
		lcd_HD44780_print_char('_');

	lcd_HD44780_print_string(buffer);

}
