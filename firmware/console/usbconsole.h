/**
 * @file    usbconsole.h
 *
 *  Created on: Oct 14, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef USBCONSOLE_H_
#define USBCONSOLE_H_

void usb_serial_start(void);
int is_serial_ready(void);
int is_usb_serial_ready(void);

#endif /* USBCONSOLE_H_ */
