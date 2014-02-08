/**
 * @file	test_util.c
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>

#include "test_util.h"
#include "cyclic_buffer.h"
#include "main.h"
#include "histogram.h"

#include "malfunction_central.h"
#include "rficonsole_logic.h"

#include "nmea.h"

static cyclic_buffer sb;

void testCyclicBuffer(void) {
	print("*************************************** testCyclicBuffer\r\n");

	cbInit(&sb);
	cbAdd(&sb, 10);

	assertEquals(10, cbSum(&sb, 3));

	cbAdd(&sb, 2);
	assertEquals(12, cbSum(&sb, 2));
}

void testHistogram(void) {
	print("******************************************* testHistogram\r\n");

	initHistograms();

	assertEquals(80, histogramGetIndex(239));
	assertEquals(223, histogramGetIndex(239239));
	assertEquals(364, histogramGetIndex(239239239));

	histogram_s h;

	resetHistogram(&h, "test");

	int result[5];
	assertEquals(0, hsReport(&h, result));

	hsAdd(&h, 10);
	assertEquals(1, hsReport(&h, result));
	assertEquals(10, result[0]);

	// let's add same value one more time
	hsAdd(&h, 10);
	assertEquals(2, hsReport(&h, result));
	assertEquals(10, result[0]);
	assertEquals(10, result[1]);

	hsAdd(&h, 10);
	hsAdd(&h, 10);
	hsAdd(&h, 10);

	hsAdd(&h, 1000);
	hsAdd(&h, 100);

	assertEquals(5, hsReport(&h, result));

	assertEquals(5, result[0]);
	assertEquals(10, result[1]);
	assertEquals(10, result[2]);
	assertEquals(100, result[3]);
	// values are not expected to be exactly the same, it's the shape what matters
	assertEquals(1011, result[4]);
}

void testMalfunctionCentral(void) {
	print("******************************************* testMalfunctionCentral\r\n");
	initMalfunctionCentral();

	error_codes_set_s localCopy;

	// on start-up error storage should be empty
	getErrorCodes(&localCopy);
	assertEquals(0, localCopy.count);

	obd_code_e code = OBD_Engine_Coolant_Temperature_Circuit_Malfunction;

	// this should not crash
	removeError(code);

	// let's add one error and validate
	addError(code);
	getErrorCodes(&localCopy);
	assertEquals(1, localCopy.count);
	assertEquals(code, localCopy.error_codes[0]);

	// let's add same error one more time
	print("adding same code again\r\n");
	addError(code);
	getErrorCodes(&localCopy);
	// same code should be only present in the set once
	assertEquals(1, localCopy.count);

	code = OBD_Intake_Air_Temperature_Circuit_Malfunction;
	addError(code);
	getErrorCodes(&localCopy);
	// todo:	assertEquals(2, localCopy.count);

	for (int code = 0; code < 100; code++) {
		addError((obd_code_e) code);
	}
	getErrorCodes(&localCopy);
	assertEquals(MAX_ERROR_CODES_COUNT, localCopy.count);

	// now we have full array and code below present
	removeError(code);
	getErrorCodes(&localCopy);
	assertEquals(MAX_ERROR_CODES_COUNT - 1, localCopy.count);
}

void sendOutConfirmation(char *value, int i) {
	// test implementation
}

static int lastInteger = -1;
static int lastInteger2 = -1;

static void testEchoI(int param) {
	lastInteger = param;
}

static void testEchoII(int param, int param2) {
	lastInteger = param;
	lastInteger2 = param2;
}

static char *lastFirst = NULL;
static char *lastThird = NULL;

static void testEchoSSS(char *first, char *second, char *third) {
	lastFirst = first;
	lastThird = third;
}

#define UNKNOWN_COMMAND "dfadasdasd"

static loc_t GPSdata;

static char nmeaMessage[1000];

void testGpsParser(void) {
	print("******************************************* testGpsParser\r\n");

	// we need to pass a mutable string, not a constant because the parser would be modifying the string
	strcpy(nmeaMessage, "$GPRMC,173843,A,3349.896,N,11808.521,W,000.0,360.0,230108,013.4,E*69");
	gps_location(&GPSdata, nmeaMessage);
	assertEqualsM("latitude", 0, GPSdata.latitude);
	assertEqualsM("speed", 0, GPSdata.speed);


	strcpy(nmeaMessage, "$GPGGA,111609.14,5001.27,N,3613.06,E,3,08,0.0,10.2,M,0.0,M,0.0,0000*70");
	gps_location(&GPSdata, nmeaMessage);
	assertEqualsM("latitude", 50.0212, GPSdata.latitude);
	assertEqualsM("speed", 0, GPSdata.speed);


	strcpy(nmeaMessage, "$GPRMC,111609.14,A,5001.27,N,3613.06,E,11.2,0.0,261206,0.0,E*50");
	gps_location(&GPSdata, nmeaMessage);
	assertEqualsM("latitude", 0, GPSdata.latitude);
	assertEqualsM("speed", 11.2, GPSdata.speed);


	char *buff[] = {
			"$GPGSV,2,1,08,01,05,005,80,02,05,050,80,03,05,095,80,04,05,140,80*7f",
			"$GPGSV,2,2,08,05,05,185,80,06,05,230,80,07,05,275,80,08,05,320,80*71",
			"$GPGSA,A,3,01,02,03,04,05,06,07,08,00,00,00,00,0.0,0.0,0.0*3a",
			"$GPVTG,217.5,T,208.8,M,000.00,N,000.01,K*4C" };
	for (int it = 0; it < 4; ++it) {
		gps_location(&GPSdata, buff[it]);
		print("GPS latitude = %f, speed = %f\r\n", GPSdata.latitude, GPSdata.speed);
	}
}

// this buffer is needed because on Unix you would not be able to change static char constants
static char buffer[300];

void testConsoleLogic(void) {
	print("******************************************* testConsoleLogic\r\n");
	resetConsoleActions();

	helpCommand();

	char *ptr = validateSecureLine(UNKNOWN_COMMAND);
	assertEquals(0, strcmp(UNKNOWN_COMMAND, ptr));
	assertEquals(10, tokenLength(UNKNOWN_COMMAND));

	// handling invalid token should work
	strcpy(buffer, "sdasdafasd asd");
	handleConsoleLine(buffer);

	print("\r\naddConsoleActionI\r\n");
	addConsoleActionI("echoi", testEchoI);
	strcpy(buffer, "echoi 239");
	handleConsoleLine(buffer);
	assertEquals(239, lastInteger);

	print("\r\naddConsoleActionII\r\n");
	addConsoleActionII("echoii", testEchoII);
	strcpy(buffer, "echoii 22 239");
	handleConsoleLine(buffer);
	assertEquals(22, lastInteger);
	assertEquals(239, lastInteger2);

	print("\r\addConsoleActionSSS\r\n");
	addConsoleActionSSS("echosss", testEchoSSS);
	strcpy(buffer, "echosss 111 222 333");
	handleConsoleLine(buffer);
	assertEquals(111, atoi(lastFirst));
	assertEquals(333, atoi(lastThird));

	addConsoleActionSSS("GPS", testGpsParser);
}

