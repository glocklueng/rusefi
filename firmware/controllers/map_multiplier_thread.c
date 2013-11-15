/*
 * @brief dead code
 *
 *
 * map_multiplier.c
 *
 *  Created on: Jul 23, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "map_multiplier_thread.h"
#include "datalogging.h"
#include "map_adjuster.h"
#include "rpm_reporter.h"
#include "main_loop.h"
#include "wave_math.h"
#include "sensors.h"

static Logging log;

static WORKING_AREA(maThreadStack, 256);

static void mapCallback(int rpm, float key, float value) {
	Logging *logging = &log;
	append(logging, "msg");
	append(logging, DELIMETER);

	append(logging, "map_adjusted: ");
	appendInt(logging, rpm);
	append(logging, " ");
	appendInt(logging, 100 * key);
	append(logging, " ");
	appendInt(logging, 100 * value);

	append(logging, DELIMETER);
	scheduleLogging(logging);
}

static int timeAtNotRunning = 0;

static int isNewState = TRUE;

static void maThread(int param) {
	chRegSetThreadName("map adjustment");

	while (TRUE) {
		chThdSleepMilliseconds(100);

		systime_t now = chTimeNow();
		if (!isRunning()) {
			timeAtNotRunning = now;
			continue;
		}

		int wasNotRunningRecently = overflowDiff(now, timeAtNotRunning) < 60 * CH_FREQUENCY;
		if (!wasNotRunningRecently)
			continue;
		if (isNewState)
			scheduleSimpleMsg(&log, "starting fuel map adjustment at ", now);
		isNewState = FALSE;

		// ideally this should be atomic, but hopefully it's good enough
		int rpm = getCurrentRpm();
		float key = getMaf();
		float afr = getAfr();

		addAfr(rpm, key, afr);
		int total = runMapAdjustments(mapCallback);
		if (total > 0) {
//			scheduleSimpleMsg(&log, "map adjusted for maf ", 100 * key);
		}
	}
}

void initMapAdjusterThread(void) {
	initLogging(&log, "Map self learning thread", log.DEFAULT_BUFFER, sizeof(log.DEFAULT_BUFFER));

	initMapAdjuster();

	chThdCreateStatic(maThreadStack, sizeof(maThreadStack), NORMALPRIO, (tfunc_t)maThread, NULL);
}
