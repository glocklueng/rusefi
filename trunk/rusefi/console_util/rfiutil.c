/*
 *  Created on: Nov 15, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "rfiutil.h"

static int mypow10(int param) {
	switch (param) {
	case 0:
		return 1;
	case 1:
		return 10;
	case 2:
		return 100;
	case 3:
		return 1000;
	case 4:
		return 10000;
	case 5:
		return 100000;
	case 6:
		return 1000000;
	case 7:
		return 10000000;
	case 8:
		return 100000000;
	}
	return 10 * mypow10(10 - 1);
}

int mylog10(int param) {
	if (param < 10)
		return 0;
	if (param < 100)
		return 1;
	if (param < 1000)
		return 2;
	if (param < 10000)
		return 3;
	if (param < 100000)
		return 4;
	if (param < 1000000)
		return 5;
	if (param < 10000000)
		return 6;
	if (param < 100000000)
		return 7;
	return mylog10(param / 10) + 1;
}

static char *ltoa_internal(char *p, long num, unsigned radix) {
	int i;
	char *q;

	q = p + _MAX_FILLER;
	do {
		i = (int) (num % radix);
		i += '0';
		if (i > '9')
			i += 'A' - '0' - 10;
		*--q = i;
	} while ((num /= radix) != 0);

	i = (int) (p + _MAX_FILLER - q);
	do
		*p++ = *q++;
	while (--i);

	return p;
}

char * ftoa(char *pointer, myfloat val, int precision) {
	char *p = pointer;
	if (val < 0) {
		*p++ = '-';
		return ftoa(p, -val, precision);
	}

	int n = (int) val;
	p = ltoa_internal(p, n, 10);

	if (precision < 1)
		return p;
	val -= n;
	*p++ = '.';
	val *= mypow10(precision);

	int len = mylog10((int) val);
	// leading zeros of decimal part
	for (int i = len + 1; i < precision; i++)
		*p++ = '0';
	// decimal part
	p = ltoa_internal(p, (int) val, 10);
	*p = 0;
	return p;
}

char *itoa_signed(char *p, int num, unsigned radix) {
	if (num < 0) {
		*p++ = '-';
		char *end = ltoa_internal(p, -num, radix);
		*end = 0;
		return end;
	}
	char *end =  ltoa_internal(p, num, radix);
	*end = 0;
	return end;
}

void itoa(char *p, int num) {
	itoa_signed(p, num, 10);
}

char hexChar(int v) {
	v = v & 0xF;
	if (v < 10)
		return '0' + v;
	return 'A' - 10 + v;
}

