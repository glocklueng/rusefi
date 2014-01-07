/**
 * @file    print.c
 * @brief   print() code
 *
 */

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "ch.h"

#include "print.h"
#include "chprintf.h"
#include "console_io.h"

void print(const char *format, ...) {
	if (!is_serial_ready())
		return;
	va_list ap;
	va_start(ap, format);
	chvprintf((BaseSequentialStream *)CONSOLE_CHANNEL, format, ap);
	va_end(ap);
}
