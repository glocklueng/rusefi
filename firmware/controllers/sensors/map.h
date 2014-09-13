#ifndef MAP_H_
#define MAP_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "sensor_types.h"

/**
 * @return Raw MAP sensor value right now
 */
float getRawMap(void);
float getBaroPressure(void);
/**
 * @return MAP value averaged within a window of measurement
 */
float getMap(void);
float getMapVoltage(void);
float getMapByVoltage(float voltage);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
