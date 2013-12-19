#ifndef MAP_H_
#define MAP_H_

#define MAP_ANGLE_SIZE 8
#define MAP_WINDOW_SIZE 8

myfloat getMap(void);
float getMapByVoltage(float voltage);

typedef struct {
	float mapSamplingAngleBins[MAP_ANGLE_SIZE];
	float mapSamplingAngle[MAP_ANGLE_SIZE];

	float mapSamplingWindowBins[MAP_WINDOW_SIZE];
	float mapSamplingWindow[MAP_WINDOW_SIZE];

	float Min;
	float Max;
	float Range;
} MapConf;

typedef struct {
	MapConf config;
	int channel;
} Map;

#endif
