/*
 * @file malfunction_indicator.c
 * @brief We can blink out OBD-II error codes using Malfunction Indicator Light (MIL)
 *
 *
 * @date Dec 20, 2013
 * @author Konstantin Nikonenko
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "malfunction_indicator.h"


static WORKING_AREA(mfiThreadStack, UTILITY_THREAD_STACK_SIZE);	// declare thread

//  our main thread for show check engine error
static msg_t mfiThread(void *arg) {
	return 0;
}

void initMalfunctionIndicator(void)
{
	// create static thread
	chThdCreateStatic(mfiThreadStack, sizeof(mfiThreadStack), LOWPRIO, (tfunc_t) mfiThread, NULL);
}

