/**
 * @file    print.c
 * @brief   print() code
 *
 * print function with float support.
 * It kinda seems like float support is a bit broken :(
 */


#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include "console_io.h"
#include "chtypes.h"
#include "print.h"
#include "chstreams.h"
#include "chprintf.h"

void print (const char *format, ...)
{
  va_list ap;
  va_start(ap, format);
  vchprintf(CONSOLE_CHANNEL, format, ap);
  va_end(ap);
}
