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
#include "main_loop.h"
#include "engine_configuration.h"

static OutputSignal injectors[MAX_INJECTOR_COUNT];

static Logging logger;

int isInjectionEnabled = TRUE;
myfloat globalFuelCorrection = 1;

extern EngineConfiguration2 *engineConfiguration2;

static int is_injector_enabled[MAX_INJECTOR_COUNT];

void assertCylinderId(int cylinderId, char *msg) {
	int isValid = cylinderId >= 1 && cylinderId <= engineConfiguration2->cylindersCount;
	if (!isValid) {
		//scheduleSimpleMsg(&logger, "cid=", cylinderId);
		print("ERROR [%s] cid=%d\r\n", msg, cylinderId);
		chDbgAssert(isValid, "Cylinder ID", null);
	}
}

/**
 * This method schedules asynchronous fuel squirt
 */
void scheduleFuelInjection(int offsetSysTicks, int lengthSysTicks, int cylinderId) {
	assertCylinderId(cylinderId, "scheduleFuelInjection");

	if (!isInjectorEnabled(cylinderId))
		return;

	OutputSignal *injector = &injectors[cylinderId - 1];

	scheduleOutput(injector, offsetSysTicks, lengthSysTicks);
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
	chDbgCheck(id >=0 && id < engineConfiguration2->cylindersCount, "injector id");
	is_injector_enabled[id] = value;
	printStatus();
}

static void setGlobalFuelCorrection(int value) {
	if (value < 10 || value > 500)
		return;
	scheduleSimpleMsg(&logger, "setting fuel mult=", value);
	globalFuelCorrection = value / 100.0;
}

void initInjectorCentral(void) {
	initLogging(&logger, "InjectorCentral");

	for (int i = 0; i < engineConfiguration2->cylindersCount; i++)
		is_injector_enabled[i] = true;
	printStatus();

	initOutputSignal("Injector 1", &injectors[0], INJECTOR_1_OUTPUT, INJECTOR_1_XOR);
	initOutputSignal("Injector 2", &injectors[1], INJECTOR_2_OUTPUT, INJECTOR_2_XOR);
	initOutputSignal("Injector 3", &injectors[2], INJECTOR_3_OUTPUT, INJECTOR_3_XOR);
	initOutputSignal("Injector 4", &injectors[3], INJECTOR_4_OUTPUT, INJECTOR_4_XOR);
	initOutputSignal("Injector 5", &injectors[4], INJECTOR_5_OUTPUT, INJECTOR_5_XOR);

	addConsoleActionII("injector", setInjectorEnabled);
	addConsoleActionI("gfc", setGlobalFuelCorrection);
}
