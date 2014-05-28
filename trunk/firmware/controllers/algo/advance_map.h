/*
 * @file advance_map.h
 *
 * @date Mar 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef ADVANCE_H_
#define ADVANCE_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#define AD_LOAD_COUNT 16
#define AD_RPM_COUNT 16

float getAdvance(int rpm, float engineLoad);
void prepareTimingMap(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ADVANCE_H_ */
