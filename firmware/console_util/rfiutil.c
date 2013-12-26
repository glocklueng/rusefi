/**
 * @file    rfiutil.c
 * @brief   Number to string conversion code
 *
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include <string.h>
#include "rfiutil.h"

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

static char* itoa_signed(char *p, int num, unsigned radix) {
	if (num < 0) {
		*p++ = '-';
		char *end = ltoa_internal(p, -num, radix);
		*end = 0;
		return end;
	}
	char *end = ltoa_internal(p, num, radix);
	*end = 0;
	return end;
}

char* itoa(char *p, int num) {
	return itoa_signed(p, num, 10);
}

char hexChar(int v) {
	v = v & 0xF;
	if (v < 10)
		return '0' + v;
	return 'A' - 10 + v;
}

// todo: why does it not compile if I make this function 'inline'?
int isIsrContext(void) {
	/**
	 * Unfortunately ChibiOS has two versions of methods for different
	 * contexts.
	 */
	return dbg_isr_cnt > 0;
}

void chVTSetAny(VirtualTimer *vtp, systime_t time, vtfunc_t vtfunc, void *par) {
	if (isIsrContext()) {
		chSysLockFromIsr()
		;

		if (chVTIsArmedI(vtp))
			chVTResetI(vtp);

		chVTSetI(vtp, time, vtfunc, par);
		chSysUnlockFromIsr()
		;
	} else {
		chSysLock()
		;
		if (chVTIsArmedI(vtp))
			chVTResetI(vtp);
		chVTSetI(vtp, time, vtfunc, par);
		chSysUnlock()
		;
	}
}

void printHistogram(Logging *logging, histogram_s *histogram) {
	int report[5];
	int len = hsReport(histogram, report);

	resetLogging(logging);
	appendMsgPrefix(logging);
	appendPrintf(logging, "histogram %s [", histogram->name);
	for (int i = 0; i < len; i++)
		appendPrintf(logging, "%d ", report[i]);
	appendPrintf(logging, "]%s", DELIMETER);
	scheduleLogging(logging);
}
