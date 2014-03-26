/**
 * @file    tps.h
 * @brief
 *
 *
 * @date Nov 15, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef TPS_H_
#define TPS_H_

#include "global.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

float getTPS(void);
int getTPS10bitAdc(void);
float getTPSVoltage(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
