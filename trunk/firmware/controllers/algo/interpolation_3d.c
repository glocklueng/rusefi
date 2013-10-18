/*
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    interpolation_3d.c
 */

#include <stdio.h>
#include "main.h"
#include "interpolation_3d.h"
#include "engine_math.h"

float interpolate3d(int rpm, float y, float rpmBin[], int rpmBinSize, float yBin[], int yBinSize, float* map[]) {

	int rpm_index = findIndex(rpmBin, rpmBinSize, rpm);
#if	DEBUG_INTERPOLATION
	printf("rpm index=%d\r\n", rpm_index);
#endif
	int key_index = findIndex(yBin, yBinSize, y);
	if (rpm_index < 0 || key_index < 0) {
#if	DEBUG_INTERPOLATION
		printf("rpm or key is lower then smallest cell in table: %f\r\n", rpm_index);
#endif
		return map[0][0];
	}

	/**
	 * first we find the interpolated value for this RPM
	 */
	int rpmMaxIndex = rpm_index == rpmBinSize - 1 ? rpm_index : rpm_index + 1;

	int rpmMin = rpmBin[rpm_index];
	int rpmMax = rpmBin[rpmMaxIndex];
	float rpmMinKeyMinValue = map[rpm_index][key_index];
	float rpmMaxKeyMinValue = map[rpmMaxIndex][key_index];

	float keyMinValue = interpolate(rpmMin, rpmMinKeyMinValue, rpmMax, rpmMaxKeyMinValue, rpm);

#if	DEBUG_INTERPOLATION
	printf("rpm=%d:\r\nrange %d - %d\r\n", rpm, rpmMin, rpmMax);
	printf("rpm interpolation range %f   %f result %f\r\n", rpmMinKeyMinValue, rpmMaxKeyMinValue, keyMinValue);
#endif

	int keyMaxIndex = key_index == yBinSize - 1 ? key_index : key_index + 1;
	float keyMin = yBin[key_index];
	float keyMax = yBin[keyMaxIndex];
	float rpmMinKeyMaxValue = map[rpm_index][keyMaxIndex];
	float rpmMaxKeyMaxValue = map[rpmMaxIndex][keyMaxIndex];

	float keyMaxValue = interpolate(rpmMin, rpmMinKeyMaxValue, rpmMax, rpmMaxKeyMaxValue, rpm);

#if	DEBUG_INTERPOLATION
	printf("key=%f:\r\nrange %f - %f\r\n", y, keyMin, keyMax);
	printf("key interpolation range %f   %f result %f\r\n", rpmMinKeyMaxValue, rpmMaxKeyMaxValue, keyMaxValue);
#endif

	float result = interpolate(keyMin, keyMinValue, keyMax, keyMaxValue, y);
	return result;
}
