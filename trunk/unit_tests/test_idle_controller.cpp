/*
 * @file test_idle_controller.cpp
 *
 * @date Oct 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include <stdio.h>

#include "efitime.h"

void idleDebug(const char *msg, percent_t value) {
	printf("%s\r\n", msg);
}
