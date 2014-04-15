/*
 * @file    rfiutil.h
 * @brief   Number to string conversion header
 *
 * @date Nov 15, 2012
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef RFIUTIL_H_
#define RFIUTIL_H_

#include "global.h"
#include "histogram.h"
#include "datalogging.h"

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

#define _MAX_FILLER 11

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

char* itoa10(uint8_t *p, int num);
char hexC(int v);
int isIsrContext(void);
void chVTSetAny(VirtualTimer *vtp, systime_t time, vtfunc_t vtfunc, void *par);
void printHistogram(Logging *logging, histogram_s *histogram);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RFIUTIL_H_ */
