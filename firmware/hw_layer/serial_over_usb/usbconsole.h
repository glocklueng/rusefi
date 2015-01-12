/**
 * @file    usbconsole.h
 *
 * @date Oct 14, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef USBCONSOLE_H_
#define USBCONSOLE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void usb_serial_start(void);
bool is_usb_serial_ready(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USBCONSOLE_H_ */
