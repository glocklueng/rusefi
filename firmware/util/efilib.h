/**
 * @file	efilib.h
 *
 * @date Feb 21, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef EFILIB_H_
#define EFILIB_H_

#include "stdint.h"

// number of milliseconds in one period of given frequency (per second)
#define frequency2period(freq) (((float)1000) / (freq))

#ifndef FALSE
#define FALSE       0
#endif
#ifndef TRUE
#define TRUE        (!FALSE)
#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define ERROR_CODE -11223344

int indexOf(const char *string, char ch);
float atoff(const char *string);
int atoi(const char *string);
int cisnan(float f);

int absI(int32_t value);
float absF(float value);
int maxI(int i1, int i2);
int minI(int i1, int i2);
float maxF(float i1, float i2);

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* EFILIB_H_ */
