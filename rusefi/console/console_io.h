/*
 * console_io.h
 *
 *  Created on: Dec 29, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */
#pragma once
#ifndef CONSOLE_IO_H_
#define CONSOLE_IO_H_

#include <ch.h>
#include <hal.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define SERIAL_SPEED (8 * 115200)

#define CONSOLE_CHANNEL (&SD3)

//#define CONSOLE_PORT GPIOB
//#define CONSOLE_TX_PIN 10
//#define CONSOLE_RX_PIN 11

#define CONSOLE_PORT GPIOD
#define CONSOLE_TX_PIN 8
#define CONSOLE_RX_PIN 9

void consolePutChar(int x);
void startChibiosConsole(void (*console_line_callback_p)(char *));

#endif /* CONSOLE_IO_H_ */
