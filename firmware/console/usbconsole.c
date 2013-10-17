/*
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    usbconsole.c
 */

#include "ch.h"
#include "hal.h"

#include "usbcfg.h"
#include "features.h"

extern SerialUSBDriver SDU1;
extern const SerialUSBConfig serusbcfg;
extern const USBConfig usbcfg;

void usb_serial_start(void) {
	/*
	 * Initializes a serial-over-USB CDC driver.
	 */
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	/*
	 * Activates the USB driver and then the USB bus pull-up on D+.
	 * Note, a delay is inserted in order to not have to disconnect the cable
	 * after a reset.
	 */
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1000);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

	/*
	 * Activates the serial driver 2 using the driver default configuration.
	 * PA2(TX) and PA3(RX) are routed to USART2.
	 */
	sdStart(&SD2, NULL);
	palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7)); palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
}

#ifdef EFI_SERIAL_OVER_USB
int is_serial_ready(void) {
	return SDU1.config->usbp->state == USB_ACTIVE;
}
#endif

