/**
 * @file	main.c
 * @brief C main entry point
 *
 * This file is so simple in anticipation of C++ migration under https://sourceforge.net/p/rusefi/tickets/33/
 *
 * @date Nov 29, 2012
 * @author Andrey Belomutskiy, (c) 2012-2014
 *      http://rusefi.com/
 */

#include "global.h"

#include "main.h"

#include "rusefi.h"

int main(void) {
	/*
	 * ChibiOS/RT initialization
	 */
	halInit();
	chSysInit();

	runRusEfi();
	return 0;
}

void DebugMonitorVector(void) {

	chDbgPanic("DebugMonitorVector", __FILE__, __LINE__);

	while (TRUE)
		;
}

void UsageFaultVector(void) {

	chDbgPanic("UsageFaultVector", __FILE__, __LINE__);

  while (TRUE)
    ;
}

void BusFaultVector(void) {

	chDbgPanic("BusFaultVector", __FILE__, __LINE__);

  while (TRUE)
    ;
}

void HardFaultVector(void) {

	chDbgPanic("HardFaultVector", __FILE__, __LINE__);

  while (TRUE)
    ;
}


