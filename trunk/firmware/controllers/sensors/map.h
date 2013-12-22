#ifndef MAP_H_
#define MAP_H_

#define MAP_ANGLE_SIZE 8
#define MAP_WINDOW_SIZE 8

/**
 * @return Raw MAP sensor value right now
 */
myfloat getRawMap(void);
/**
 * @return MAP value averaged within a window of measurement
 */
myfloat getMap(void);
float getMapByVoltage(float voltage);

typedef struct {
	float samplingAngleBins[MAP_ANGLE_SIZE];
	float samplingAngle[MAP_ANGLE_SIZE];

	float samplingWindowBins[MAP_WINDOW_SIZE];
	float samplingWindow[MAP_WINDOW_SIZE];

	float Min;
	float Max;
	float Range;
} MapConf_s;

typedef struct {
	MapConf_s config;
	int channel;
} map_s;

#endif
