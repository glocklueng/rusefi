/**
 * @file	neo6m.c
 * @brerf	Ublox 6M hardware UART driver
 *
 * http://www.u-blox.com/en/gps-modules/pvt-modules/previous-generations/neo-6-family.html
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

#if EFI_UART_GPS

static SerialConfig GPSserialConfig = { GPS_SERIAL_SPEED, 0, USART_CR2_STOP1_BITS | USART_CR2_LINEN, 0 };
static WORKING_AREA(GPS_WORKING_AREA, UTILITY_THREAD_STACK_SIZE);

// GPs structure
static loc_t GPSdata;

// todo: some data structure for coordinates location
// todo:
float getCurrentSpeed(void) {
	return GPSdata.speed;
}

static void printGpsInfo(void) {
	// todo: scheduleMsg()
	print("GPS speed = %f\r\n", getCurrentSpeed());
}

static msg_t GpsThreadEntryPoint(void *arg) {
	(void) arg;
	chRegSetThreadName("GPS thread");

	char gps_str[GPS_MAX_STRING];
	int iter = 0;
	EventListener elGPSdata;
	flagsmask_t flags;
	chEvtRegisterMask((EventSource *) chnGetEventSource(GPS_SERIAL_DEVICE), &elGPSdata, EVENT_MASK(1));

	while (TRUE) {
		chEvtWaitOneTimeout(EVENT_MASK(1), MS2ST(10));
		flags = chEvtGetAndClearFlags(&elGPSdata);
		/*		if(flags & SD_PARITY_ERROR){                                          // Parity error happened.
		 print("[GPS] parity error\r\n");
		 }
		 if(flags & SD_FRAMING_ERROR){                                       // Framing error happened.
		 print("[GPS] framing error\r\n");
		 }
		 if(flags & SD_OVERRUN_ERROR){                                       // Overflow happened.
		 print("[GPS] Overflow\r\n");
		 }
		 if(flags & SD_NOISE_ERROR){                                          // Noise on the line.
		 print("[GPS] Noisy line\r\n");
		 }
		 if(flags & SD_BREAK_DETECTED){                                       // Break detected.
		 print("[GPS] Break!\r\n");
		 }
		 */
		if (flags & CHN_INPUT_AVAILABLE) {
			msg_t charbuf;
			charbuf = chnGetTimeout(GPS_SERIAL_DEVICE, TIME_IMMEDIATE);
			if (charbuf == 10 || iter == GPS_MAX_STRING) {					// if 0xD,0xA or limit
				if (iter >= 1)
					gps_str[--iter] = '\0';						// delete 0xD
				// 'gps_str' string completed, 'iter' = length
				gps_location(&GPSdata, gps_str);
				memset(&gps_str, '\0', GPS_MAX_STRING);						// clear buffer
				iter = 0;
			} else {
				if (charbuf != Q_TIMEOUT) {								// else add if not timeout
					gps_str[iter++] = charbuf;
				}
			}
		}
	}
#if defined __GNUC__
	return 0;
#endif
}

void initGps(void) {
	sdStart(GPS_SERIAL_DEVICE, &GPSserialConfig);
	//  GPS we have USART1: PB7 -> USART1_RX and PB6 -> USART1_TX
	mySetPadMode("GPS tx", GPS_PORT, GPS_SERIAL_TX_PIN, PAL_MODE_ALTERNATE(7));
	mySetPadMode("GPS rx", GPS_PORT, GPS_SERIAL_RX_PIN, PAL_MODE_ALTERNATE(7));

	// todo: add a thread which would save location. If the GPS 5Hz - we should save the location each 200 ms
	chThdCreateStatic(GPS_WORKING_AREA, sizeof(GPS_WORKING_AREA), NORMALPRIO, GpsThreadEntryPoint, NULL);

	addConsoleAction("gpsinfo", &printGpsInfo);
}

#endif /* EFI_UART_GPS */
