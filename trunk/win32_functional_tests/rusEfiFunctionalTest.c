/**
 * @file	rusEfiFunctionalTest.c
 *
 * @date Mar 1, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "global.h"
#include "rusEfiFunctionalTest.h"
#include "eficonsole.h"
#include "engine_configuration.h"
#include "rusefi_enums.h"

engine_configuration_s engineConfiguration;
engine_configuration2_s engineConfiguration2;

void setOutputPinValue(io_pin_e pin, int logicValue) {
}

//void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
//
//}

int isCranking(void) {
	return 0;
}

void idleDebug(char *msg, int value) {

}

float getMap(void) {
	return 0;
}

void rusEfiFunctionalTest(void) {
	initializeConsole();

	resetConfigurationExt(FORD_ASPIRE_1996, &engineConfiguration, &engineConfiguration2);

}
