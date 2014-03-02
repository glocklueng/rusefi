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



void rusEfiFunctionalTest(void) {
	initializeConsole();

	resetConfigurationExt(FORD_ASPIRE_1996, &engineConfiguration, &engineConfiguration2);

}
