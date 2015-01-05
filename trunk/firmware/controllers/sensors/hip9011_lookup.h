/**
 * @file	hip9011_lookup.h
 *
 * @date Jan 4, 2015
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#ifndef CONTROLLERS_SENSORS_HIP9011_LOOKUP_H_
#define CONTROLLERS_SENSORS_HIP9011_LOOKUP_H_

#define INT_LOOKUP_SIZE 32
#define GAIN_LOOKUP_SIZE 64
#define BAND_LOOKUP_SIZE 64

#define PIF 3.14159f
#define DESIRED_OUTPUT_VALUE 5.0f

extern const int integratorValues[INT_LOOKUP_SIZE];
extern const float gainLookupInReverseOrder[GAIN_LOOKUP_SIZE];
extern const float bandFreqLookup[BAND_LOOKUP_SIZE];

float getRpmByAngleWindowAndTimeUs(int timeUs, float angleWindowWidth);
int getHip9011GainIndex(float gain);
int getHip9011BandIndex(float bore);
void prepareHip9011RpmLookup(float angleWindowWidth);

#define GAIN_INDEX(gain) (GAIN_LOOKUP_SIZE - 1 - findIndex(gainLookupInReverseOrder, GAIN_LOOKUP_SIZE, (gain)))
#define BAND(bore) (900 / (PIF * (bore) / 2))

extern float rpmLookup[INT_LOOKUP_SIZE];
int getIntegrationIndexByRpm(float rpm);

#endif /* CONTROLLERS_SENSORS_HIP9011_LOOKUP_H_ */
