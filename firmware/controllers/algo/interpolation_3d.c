/*
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    interpolation_3d.c
 */

#include <stdio.h>
#include <math.h>

#include "main.h"
#include "interpolation_3d.h"
#include "engine_math.h"

float interpolate2d(float value, float bin[], float values[], int size) {
	int index = findIndex(bin, size, value);

	if (index == -1)
		return values[0];
	if (index == size - 1)
		return values[size - 1];

	return interpolate(bin[index], values[index], bin[index + 1], values[index + 1], value);
}

float interpolate3d(float x, float xBin[], int xBinSize, float y, float yBin[], int yBinSize, float* map[]) {
	if (isnan(y)) {
		warning("x is NaN in interpolate3d\r\n", x);
		return NAN;
	}
	if (isnan(y)) {
		warning("y is NaN in interpolate3d\r\n", y);
		return NAN;
	}

	int xIndex = findIndex(xBin, xBinSize, x);
#if	DEBUG_INTERPOLATION
	printf("X index=%d\r\n", xIndex);
#endif
	int yIndex = findIndex(yBin, yBinSize, y);
	if (xIndex < 0 && yIndex < 0) {
#if	DEBUG_INTERPOLATION
		printf("X and Y are smaller than smallest cell in table: %d\r\n",
				xIndex);
#endif
		return map[0][0];
	}

	if (xIndex < 0) {
#if	DEBUG_INTERPOLATION
		printf("X is smaller than smallest cell in table: %dr\n", xIndex);
#endif
		// no interpolation should be fine here.
		return map[0][yIndex];
	}

	if (yIndex < 0) {
#if	DEBUG_INTERPOLATION
		printf("Y is smaller than smallest cell in table: %d\r\n",
				yIndex);
#endif
		// no interpolation should be fine here.
		return map[xIndex][0];
	}

	if (xIndex == xBinSize - 1) {
		// todo: implement better handling
		return map[xBinSize - 1][yBinSize - 1];
	}

	if (yIndex == yBinSize - 1) {
		// todo: implement better handling
		return map[xBinSize - 1][yBinSize - 1];
	}

	/**
	 * first we find the interpolated value for this RPM
	 */
	int rpmMaxIndex = xIndex + 1;

	float xMin = xBin[xIndex];
	float xMax = xBin[xIndex + 1];
	float rpmMinKeyMinValue = map[xIndex][yIndex];
	float rpmMaxKeyMinValue = map[xIndex + 1][yIndex];

	float keyMinValue = interpolate(xMin, rpmMinKeyMinValue, xMax, rpmMaxKeyMinValue, x);

#if	DEBUG_INTERPOLATION
	printf("X=%f:\r\nrange %f - %f\r\n", x, xMin, xMax);
	printf("X interpolation range %f   %f result %f\r\n", rpmMinKeyMinValue,
			rpmMaxKeyMinValue, keyMinValue);
#endif

	int keyMaxIndex = yIndex + 1;
	float keyMin = yBin[yIndex];
	float keyMax = yBin[keyMaxIndex];
	float rpmMinKeyMaxValue = map[xIndex][keyMaxIndex];
	float rpmMaxKeyMaxValue = map[rpmMaxIndex][keyMaxIndex];

	float keyMaxValue = interpolate(xMin, rpmMinKeyMaxValue, xMax, rpmMaxKeyMaxValue, x);

#if	DEBUG_INTERPOLATION
	printf("key=%f:\r\nrange %f - %f\r\n", y, keyMin, keyMax);
	printf("key interpolation range %f   %f result %f\r\n", rpmMinKeyMaxValue,
			rpmMaxKeyMaxValue, keyMaxValue);
#endif

	float result = interpolate(keyMin, keyMinValue, keyMax, keyMaxValue, y);
	return result;
}
