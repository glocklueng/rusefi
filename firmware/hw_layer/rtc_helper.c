/**
 * @file rtc_helper.c
 * @brief Real Time Clock helper
 *
 * @date Feb 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include <string.h> 
#include <time.h>
#include "main.h"
#include "chrtclib.h"
#include "rtc_helper.h"

static void date_help(void) {
	print("Usage: date_help\r\n");
	print("       date_get\r\n");
	print("       date_set N\r\n");
	print("where N is time in seconds sins Unix epoch\r\n");
	print(
			"		Human readable time   \tSeconds\r\n \
		1 hour	\t\t3600 seconds\r\n \
		1 day	\t\t86400 seconds\r\n \
		1 week	\t\t604800 seconds\r\n \
		1 month (30.44 days)\t2629743 seconds\r\n \
		1 year (365.24 days)\t31556926 seconds\r\n \
		or convert via http://www.epochconverter.com/\r\n");
}

static void date_get(void) {
	static time_t unix_time;
	struct tm timp;

	unix_time = rtcGetTimeUnixSec(&RTCD1);
	if (unix_time == -1) {
		print("incorrect time in RTC cell\r\n");
	} else {
		print("%D%s", unix_time, " - unix time\r\n");
		rtcGetTimeTm(&RTCD1, &timp);
		print("Current RTC time in GMT is: ");
		print("%04u-%02u-%02u %02u:%02u:%02u\r\n", timp.tm_year + 1900, timp.tm_mon + 1, timp.tm_mday, timp.tm_hour,
				timp.tm_min, timp.tm_sec);
	}
}

static void date_set(char *strDate) {
	static time_t unix_time;
	if (strlen(strDate) > 0) {
		unix_time = (double) atof(strDate);
		if (unix_time > 0) {
			rtcSetTimeUnixSec(&RTCD1, unix_time);
			return;
		}
	}
	print("date_set Date parameter %s is wrong\r\n", strDate);
}

static void date_set_tm(struct tm *timp) {
	rtcSetTimeTm(&RTCD1, timp);
}

static void date_get_tm(struct tm *timp) {
	rtcGetTimeTm(&RTCD1, timp);
}

void initRtc(void) {
	// yes, it's my begin time  and we always start from this one 1391894433 - 2014-02-08 21:20:03
	rtcSetTimeUnixSec(&RTCD1, 1391894433);
	addConsoleAction("date_get", &date_get);
	addConsoleActionS("date_set", &date_set);
	addConsoleAction("date_help", &date_help);
}
