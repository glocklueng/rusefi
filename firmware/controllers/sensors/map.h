#ifndef MAP_H_
#define MAP_H_

/**
 * @return Raw MAP sensor value right now
 */
float getRawMap(void);
/**
 * @return MAP value averaged within a window of measurement
 */
float getMap(void);
float getMapByVoltage(float voltage);

#endif
