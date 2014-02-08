/**
 * @file	neo6m.c
 * @brerf	Ublox 6M hardware UART driver
 *
 * http://www.u-blox.com/en/gps-modules/pvt-modules/previous-generations/neo-6-family.html
 *
 * Technically any UART GPS should work with this driver since NMEA protocol is pretty common anyway
 *
 * @date Dec 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 * Kot_dnz 2014
 */

#include <string.h>
#include "main.h"
#include "console_io.h"
#include "rficonsole.h"
#include "pin_repository.h"
#include "nmea.h"
#include "neo6m.h"
#include "datalogging.h"

#if EFI_UART_GPS

static Logging logger;

static SerialConfig GPSserialConfig = { GPS_SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0 };
static WORKING_AREA(GPS_WORKING_AREA, UTILITY_THREAD_STACK_SIZE);

// GPs structure
static loc_t GPSdata;

static int gpsMesagesCount = 0;
static int uartErrors = 0;

// todo: some data structure for coordinates location
// todo:
float getCurrentSpeed(void) {
	return GPSdata.speed;
}

static void printGpsInfo(void) {
	// todo: scheduleMsg()
	print("m=%d,e=%d: GPS speed = %f\r\n", gpsMesagesCount, uartErrors, getCurrentSpeed());

	print("GPS latitude = %f\r\n", GPSdata.latitude);
	print("GPS longitude = %f\r\n", GPSdata.longitude);
}

static void onGpsMessage(char *buffer) {
	gps_location(&GPSdata, buffer);
	gpsMesagesCount++;
}

// we do not want this on stack, right?
static char gps_str[GPS_MAX_STRING];
static EventListener elGPSdata;

static void handleFlags(flagsmask_t flags) {
	if (flags & SD_PARITY_ERROR) {                                          // Parity error happened.
		uartErrors++;
		//print("[GPS] parity error\r\n");
	}
	if (flags & SD_FRAMING_ERROR) {                                       // Framing error happened.
		uartErrors++;
		//print("[GPS] framing error\r\n");
	}
	if (flags & SD_OVERRUN_ERROR) {                                       // Overflow happened.
		uartErrors++;
		//print("[GPS] Overflow\r\n");
	}
	if (flags & SD_NOISE_ERROR) {                                          // Noise on the line.
		uartErrors++;
		//print("[GPS] Noisy line\r\n");
	}
	if (flags & SD_BREAK_DETECTED) {                                       // Break detected.
		uartErrors++;
		//print("[GPS] Break!\r\n");
	}
}

static msg_t GpsThreadEntryPoint(void *arg) {
	(void) arg;
	chRegSetThreadName("GPS thread");

	int count = 0;
	flagsmask_t flags;
	chEvtRegisterMask((EventSource *) chnGetEventSource(GPS_SERIAL_DEVICE), &elGPSdata, EVENT_MASK(1));

	while (TRUE) {
		chEvtWaitOneTimeout(EVENT_MASK(1), MS2ST(10));
		flags = chEvtGetAndClearFlags(&elGPSdata);
		handleFlags(flags);

		if (flags & CHN_INPUT_AVAILABLE) {
			msg_t charbuf = chnGetTimeout(GPS_SERIAL_DEVICE, TIME_IMMEDIATE);
			if (charbuf == 10 || count == GPS_MAX_STRING) {					// if 0xD,0xA or limit
				if (count >= 1)
					gps_str[--count] = '\0';					// delete 0xD

				scheduleMsg(&logger, "got GPS [%s]", gps_str);

				// 'gps_str' string completed
				onGpsMessage(gps_str);
				memset(&gps_str, '\0', GPS_MAX_STRING);			// clear buffer
				count = 0;
			} else {
				if (charbuf != Q_TIMEOUT) {								// else add if not timeout
					gps_str[count++] = charbuf;
				}
			}
		}
	}
#if defined __GNUC__
	return 0;
#endif
}

void initGps(void) {
	initLogging(&logger, "uart gps");

	sdStart(GPS_SERIAL_DEVICE, &GPSserialConfig);
//  GPS we have USART1: PB7 -> USART1_RX and PB6 -> USART1_TX
	mySetPadMode("GPS tx", GPS_PORT, GPS_SERIAL_TX_PIN, PAL_MODE_ALTERNATE(7));
	mySetPadMode("GPS rx", GPS_PORT, GPS_SERIAL_RX_PIN, PAL_MODE_ALTERNATE(7));

// todo: add a thread which would save location. If the GPS 5Hz - we should save the location each 200 ms
	chThdCreateStatic(GPS_WORKING_AREA, sizeof(GPS_WORKING_AREA), NORMALPRIO, GpsThreadEntryPoint, NULL);

	addConsoleAction("gpsinfo", &printGpsInfo);
}

#endif /* EFI_UART_GPS */
