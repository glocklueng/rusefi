/*
 *  Created on: Nov 15, 2012
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef RFIUTIL_H_
#define RFIUTIL_H_

#include "global.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define _MAX_FILLER 11

int strLength(char *msgp);
char* itoa(char *p, int num);
char* itoa_signed(char *p, int num, unsigned radix);
char hexC(int v);
char* ftoa(char *pointer, myfloat val, int precision);

#endif /* RFIUTIL_H_ */
