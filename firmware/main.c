/**
 * @file	main.c
 * @brief C main entry point
 *
 * This file is so simple in anticipation of C++ migration under https://sourceforge.net/p/rusefi/tickets/33/
 *
 * @date Nov 29, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
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
