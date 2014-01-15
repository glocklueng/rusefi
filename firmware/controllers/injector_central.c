/**
 * @file    injector_central.c
 * @brief	Utility methods related to fuel injection.
 *
 *
 * @date Sep 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "injector_central.h"
#include "main.h"
#include "engines.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "rficonsole_logic.h"
#include "main_trigger_callback.h"
#include "engine_configuration.h"
#include "pin_repository.h"

static Logging logger;

int isInjectionEnabled = TRUE;
myfloat globalFuelCorrection = 1;

extern EngineConfiguration2 *engineConfiguration2;

static int is_injector_enabled[MAX_INJECTOR_COUNT];

void assertCylinderId(int cylinderId, char *msg) {
	int isValid = cylinderId >= 1 && cylinderId <= engineConfiguration2->cylindersCount;
	if (!isValid) {
		// we are here only in case of a fatal issue - at this point it is fine to make some blocking i-o
		//scheduleSimpleMsg(&logger, "cid=", cylinderId);
		print("ERROR [%s] cid=%d\r\n", msg, cylinderId);
		chDbgAssert(TRUE, "Cylinder ID", null);
	}
}

/**
 * This method schedules asynchronous fuel squirt
 */
void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks, OutputSignal *injector) {
//	assertCylinderId(cylinderId, "scheduleFuelInjection");
//
//	if (!isInjectorEnabled(cylinderId))
//		return;

	scheduleOutput(injector, offsetSysTicks, lengthSysTicks, chTimeNow());
}

/**
 * @param cylinderId - from 1 to NUMBER_OF_CYLINDERS
 */
int isInjectorEnabled(int cylinderId) {
	assertCylinderId(cylinderId, "isInjectorEnabled");
	return is_injector_enabled[cylinderId - 1];
}

static void printStatus(void) {
	for (int id = 1; id <= engineConfiguration2->cylindersCount; id++) {
		resetLogging(&logger);

		appendPrintf(&logger, "injector%d%s", id, DELIMETER);
		appendPrintf(&logger, "%d", isInjectorEnabled(id));
		appendPrintf(&logger, DELIMETER);
		scheduleLogging(&logger);
	}
}

static void setInjectorEnabled(int id, int value) {
	chDbgCheck(id >= 0 && id < engineConfiguration2->cylindersCount, "injector id");
	is_injector_enabled[id] = value;
	printStatus();
}

static void setGlobalFuelCorrection(int value) {
	if (value < 10 || value > 500)
		return;
	scheduleSimpleMsg(&logger, "setting fuel mult=", value);
	globalFuelCorrection = value / 100.0;
}

static void fuelBench(char * onStr, char *offStr, char *countStr) {
	float onTime = atof(onStr);
	float offTime = atof(offStr);
	int count = atoi(countStr);

	print("Running fuel bench: ON_TIME=%f, OFF_TIME=%f. Counter=%d\r\n", onTime, offTime, count);
	print("INJECTOR_1_OUTPUT on %s%d\r\n", portname(INJECTOR_1_PORT), INJECTOR_1_PIN);

	for (int i = 0; i < count; i++) {
		setOutputPinValue(INJECTOR_1_OUTPUT, TRUE);
		chThdSleep((int)(onTime * CH_FREQUENCY / 1000));
		setOutputPinValue(INJECTOR_1_OUTPUT, FALSE);
		chThdSleep((int)(offTime * CH_FREQUENCY / 1000));
	}
	print("Done running fuel bench\r\n");
}

void initInjectorCentral(void) {
	initLogging(&logger, "InjectorCentral");

	for (int i = 0; i < engineConfiguration2->cylindersCount; i++)
		is_injector_enabled[i] = true;
	printStatus();

	setDefaultPinState(INJECTOR_1_OUTPUT, OM_DEFAULT);
	setDefaultPinState(INJECTOR_2_OUTPUT, OM_DEFAULT);
	setDefaultPinState(INJECTOR_3_OUTPUT, OM_DEFAULT);
	setDefaultPinState(INJECTOR_4_OUTPUT, OM_DEFAULT);
	setDefaultPinState(INJECTOR_5_OUTPUT, OM_DEFAULT);

	addConsoleActionII("injector", setInjectorEnabled);
	addConsoleActionI("gfc", setGlobalFuelCorrection);

	addConsoleActionSSS("fuelbench", &fuelBench);
}
