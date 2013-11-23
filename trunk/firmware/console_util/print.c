/**
 * @file    print.c
 * @brief   print() code
 *
 * print function with float support.
 * It kinda seems like float support is a bit broken :(
 */

#include <stdarg.h>
#include "ch.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "print.h"
#include "chprintf.h"
#include "console_io.h"

#define  PAD_RIGHT   1
#define  PAD_ZERO    2

void print(const char *format, ...) {
	if (!is_serial_ready())
		return;
	va_list ap;
	va_start(ap, format);
	chvprintf((BaseSequentialStream *)CONSOLE_CHANNEL, format, ap);
	va_end(ap);
}
