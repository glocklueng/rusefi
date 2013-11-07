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

float interpolate2d(float value, float bin[], float values[], int size) {
	int index = findIndex(bin, size, value);

	if (index == -1)
		return values[0];
	if (index == size - 1)
		return values[size - 1];

	return interpolate(bin[index], values[index], bin[index + 1],
			values[index + 1], value);
}

float interpolate3d(float x, float xBin[], int xBinSize, float y, float yBin[], int yBinSize, float* map[]) {

	int rpm_index = findIndex(xBin, xBinSize, x);
#if	DEBUG_INTERPOLATION
	printf("rpm index=%d\r\n", rpm_index);
#endif
	int key_index = findIndex(yBin, yBinSize, y);
	if (rpm_index < 0 && key_index < 0) {
#if	DEBUG_INTERPOLATION
		printf("rpm and key are smaller than smallest cell in table: %d\r\n",
				rpm_index);
#endif
		return map[0][0];
	}

	if (rpm_index < 0) {
#if	DEBUG_INTERPOLATION
		printf("rpm is smaller than smallest cell in table: %dr\n", rpm_index);
#endif
		// no interpolation should be fine here.
		return map[0][key_index];
	}

	if (key_index < 0) {
#if	DEBUG_INTERPOLATION
		printf("rpm and key are smaller than smallest cell in table: %d\r\n",
				rpm_index);
#endif
		// no interpolation should be fine here.
		return map[rpm_index][0];
	}

	/**
	 * first we find the interpolated value for this RPM
	 */
	int rpmMaxIndex = rpm_index == xBinSize - 1 ? rpm_index : rpm_index + 1;

	int rpmMin = xBin[rpm_index];
	int rpmMax = xBin[rpmMaxIndex];
	float rpmMinKeyMinValue = map[rpm_index][key_index];
	float rpmMaxKeyMinValue = map[rpmMaxIndex][key_index];

	float keyMinValue = interpolate(rpmMin, rpmMinKeyMinValue, rpmMax,
			rpmMaxKeyMinValue, x);

#if	DEBUG_INTERPOLATION
	printf("rpm=%d:\r\nrange %d - %d\r\n", x, rpmMin, rpmMax);
	printf("rpm interpolation range %f   %f result %f\r\n", rpmMinKeyMinValue,
			rpmMaxKeyMinValue, keyMinValue);
#endif

	int keyMaxIndex = key_index == yBinSize - 1 ? key_index : key_index + 1;
	float keyMin = yBin[key_index];
	float keyMax = yBin[keyMaxIndex];
	float rpmMinKeyMaxValue = map[rpm_index][keyMaxIndex];
	float rpmMaxKeyMaxValue = map[rpmMaxIndex][keyMaxIndex];

	float keyMaxValue = interpolate(rpmMin, rpmMinKeyMaxValue, rpmMax,
			rpmMaxKeyMaxValue, x);

#if	DEBUG_INTERPOLATION
	printf("key=%f:\r\nrange %f - %f\r\n", y, keyMin, keyMax);
	printf("key interpolation range %f   %f result %f\r\n", rpmMinKeyMaxValue,
			rpmMaxKeyMaxValue, keyMaxValue);
#endif

	float result = interpolate(keyMin, keyMinValue, keyMax, keyMaxValue, y);
	return result;
}
