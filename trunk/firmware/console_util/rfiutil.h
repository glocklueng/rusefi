/*
 *  Created on: Nov 15, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    rfiutil.h
 * @brief   Number to string conversion header
 */

#ifndef RFIUTIL_H_
#define RFIUTIL_H_

#include "global.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define _MAX_FILLER 11

char* itoa(char *p, int num);
char* itoa_signed(char *p, int num, unsigned radix);
char hexC(int v);
char* ftoa(char *pointer, myfloat val, int precision);
int isIsrContext(void);
void chVTSetAny(VirtualTimer *vtp, systime_t time, vtfunc_t vtfunc, void *par);

#endif /* RFIUTIL_H_ */
