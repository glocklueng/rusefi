/**
 * @file    usbconsole.c
 * @brief	USB-over-serial configuration
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"

#if EFI_PROD_CODE

#include "usbconsole.h"
#include "usbcfg.h"
#include "efifeatures.h"

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
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

	/*
	 * Activates the serial driver 2 using the driver default configuration.
	 */
	sdStart(&SD2, NULL);
}

bool is_usb_serial_ready(void) {
	return SDU1.config->usbp->state == USB_ACTIVE;
}

#endif
