/**
 * @file	neo6m.c
 * @brerf	Ublox 6M UART driver
 *
 *
 * http://www.u-blox.com/en/gps-modules/pvt-modules/previous-generations/neo-6-family.html
 *
 * @date Dec 28, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

// todo: some data structure for coordinates location
// todo:
float getCurrentSpeed(void) {
	// todo: calculate speed based on the current and previous locations
	return 0;

}

void initGps(void) {
// todo: we are already USART3_RX as our TunerStudio port
// so the GPS we have USART1. For example we can start with PB7 USART1_RX and PB6 USART1_TX
	// see console_io.c for an example of UART initialization

	// todo: add a thread which would save location. If the GPS 5Hz - we should save the location each 200 ms

	// addConsoleAction("show_location");
}

