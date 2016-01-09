/**
 * @file    interpolation.cpp
 * @brief	Linear interpolation algorithms
 *
 * @date Oct 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
 * @author Dmitry Sidin, (c) 2015
 */

#if DEBUG_FUEL
#include <stdio.h>
#endif

#include <math.h>

#include "main.h"
#include "efilib2.h"
#include "interpolation.h"

int needInterpolationLogging = true;

#define BINARY_PERF true

Logging * logger;

#if BINARY_PERF

#define COUNT 10000

float array16[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

static void testBinary(void) {
	const int size16 = 16;

	uint32_t totalOld = 0;
	uint32_t totalNew = 0;

	for (int v = 0; v <= 16; v++) {
		uint32_t timeOld;
		{
			uint32_t start = GET_TIMESTAMP();
			int temp = 0;
			for (int i = 0; i < COUNT; i++) {
				temp += findIndex(array16, size16, v);
			}
			timeOld = GET_TIMESTAMP() - start;
		}
		uint32_t timeNew;
		{
			uint32_t start = GET_TIMESTAMP();
			int temp = 0;
			for (int i = 0; i < COUNT; i++) {
				temp += findIndex2(array16, size16, v);
			}
			timeNew = GET_TIMESTAMP() - start;
		}
		scheduleMsg(logger, "for v=%d old=%d ticks", v, timeOld);
		scheduleMsg(logger, "for v=%d new=%d ticks", v, timeNew);

		totalOld += timeOld;
		totalNew += timeNew;
	}
	scheduleMsg(logger, "totalOld=%d ticks", totalOld);
	scheduleMsg(logger, "totalNew=%d ticks", totalNew);

}

#endif

FastInterpolation::FastInterpolation() {
	init(0, 0, 1, 1);
}

FastInterpolation::FastInterpolation(float x1, float y1, float x2, float y2) {
	init(x1, y1, x2, y2);
}

void FastInterpolation::init(float x1, float y1, float x2, float y2) {
	if (x1 == x2) {
		firmwareError("init: Same x1 and x2 in interpolate: %f/%f", x1, x2);
		return;
	}
	a = INTERPOLATION_A(x1, y1, x2, y2);
	b = y1 - a * x1;
}

float FastInterpolation::getValue(float x) {
	return a * x + b;
}

/** @brief	Linear interpolation by two points
 *
 * @param	x1 key of the first point
 * @param	y1 value of the first point
 * @param	x2 key of the second point
 * @param	y2 value of the second point
 * @param	X key to be interpolated
 *
 * @note	For example, "interpolate(engineConfiguration.tpsMin, 0, engineConfiguration.tpsMax, 100, adc);"
 */
float interpolateMsg(const char *msg, float x1, float y1, float x2, float y2, float x) {
	// todo: double comparison using EPS
	if (x1 == x2) {
		/**
		 * we could end up here for example while resetting bins while changing engine type
		 */
		warning(OBD_PCM_Processor_Fault, "interpolate%s: Same x1 and x2 in interpolate: %f/%f", msg, x1, x2);
		return NAN;
	}

	// a*x1 + b = y1
	// a*x2 + b = y2
//	efiAssertVoid(x1 != x2, "no way we can interpolate");
	float a = INTERPOLATION_A(x1, y1, x2, y2);
	float b = y1 - a * x1;
	float result = a * x + b;
#if	DEBUG_FUEL
	printf("x1=%f y1=%f x2=%f y2=%f\r\n", x1, y1, x2, y2);
	printf("a=%f b=%f result=%f\r\n", a, b, result);
#endif
	return result;
}

float interpolate(float x1, float y1, float x2, float y2, float x) {
	return interpolateMsg("", x1, y1, x2, y2, x);
}

int findIndex2(const float array[], unsigned size, float value) {
	efiAssert(!cisnan(value), "NaN in findIndex", 0);
	efiAssert(size > 1, "NaN in findIndex", 0);
//	if (size <= 1)
//		return size && *array <= value ? 0 : -1;

	signed i = 0;
	//unsigned b = 1 << int(log(float(size) - 1) / 0.69314718055994530942);
	unsigned b = size >> 1; // in our case size is always a power of 2
	efiAssert(b + b == size, "Size not power of 2", -1);
	for (; b; b >>= 1) {
		unsigned j = i | b;
		/**
		 * it should be
		 * "if (j < size && array[j] <= value)"
		 * but in our case size is always power of 2 thus size is always more then j
		 */
		// efiAssert(j < size, "size", 0);
		if (array[j] <= value)
			i = j;
	}
	return i || *array <= value ? i : -1;
}

/** @brief	Binary search
 * @returns	the highest index within sorted array such that array[i] is greater than or equal to the parameter
 * @note If the parameter is smaller than the first element of the array, -1 is returned.
 */
int findIndex(const float array[], int size, float value) {
	efiAssert(!cisnan(value), "NaN in findIndex", 0);

	if (value < array[0])
		return -1;
	int middle;

	int left = 0;
	int right = size;

	// todo: extract binary search as template method?
	while (true) {
#if 0
		// that's an assertion to make sure we do not loop here
		size--;
		efiAssert(size > 0, "Unexpected state in binary search", 0);
#endif

		// todo: compare current implementation with
		// http://eigenjoy.com/2011/01/21/worlds-fastest-binary-search/
		// ?
		middle = (left + right) / 2;

//		print("left=%d middle=%d right=%d: %f\r\n", left, middle, right, array[middle]);

		if (middle == left)
			break;

		if (value < array[middle]) {
			right = middle;
		} else if (value > array[middle]) {
			left = middle;
		} else {
			break;
		}
	}

	return middle;
}

/**
 * @brief	One-dimensional table lookup with linear interpolation
 */
float interpolate2d(float value, float bin[], float values[], int size) {
	int index = findIndex(bin, size, value);

	if (index == -1)
		return values[0];
	if (index == size - 1)
		return values[size - 1];

	return interpolateMsg("2d", bin[index], values[index], bin[index + 1], values[index + 1], value);
}

/**
 * @brief	Two-dimensional table lookup with linear interpolation
 */
float interpolate3d(float x, float xBin[], int xBinSize, float y, float yBin[], int yBinSize, float* map[]) {
	if (cisnan(x)) {
		warning(OBD_PCM_Processor_Fault, "%f: x is NaN in interpolate3d", x);
		return NAN;
	}
	if (cisnan(y)) {
		warning(OBD_PCM_Processor_Fault, "%f: y is NaN in interpolate3d", y);
		return NAN;
	}

	int xIndex = findIndex(xBin, xBinSize, x);
#if	DEBUG_INTERPOLATION
	if (needInterpolationLogging)
		printf("X index=%d\r\n", xIndex);
#endif
	int yIndex = findIndex(yBin, yBinSize, y);
	if (xIndex < 0 && yIndex < 0) {
#if	DEBUG_INTERPOLATION
		if (needInterpolationLogging)
			printf("X and Y are smaller than smallest cell in table: %d\r\n", xIndex);
#endif
		return map[0][0];
	}

	if (xIndex < 0) {
#if	DEBUG_INTERPOLATION
		if (needInterpolationLogging)
			printf("X is smaller than smallest cell in table: %dr\n", xIndex);
#endif
		if (yIndex == yBinSize - 1)
			return map[0][yIndex];
		float keyMin = yBin[yIndex];
		float keyMax = yBin[yIndex + 1];
		float rpmMinValue = map[0][yIndex];
		float rpmMaxValue = map[0][yIndex + 1];

		return interpolateMsg("3d", keyMin, rpmMinValue, keyMax, rpmMaxValue, y);
	}

	if (yIndex < 0) {
#if	DEBUG_INTERPOLATION
		if (needInterpolationLogging)
			printf("Y is smaller than smallest cell in table: %d\r\n", yIndex);
#endif
		// no interpolation should be fine here.
		return map[xIndex][0];
	}

	if (xIndex == xBinSize - 1 && yIndex == yBinSize - 1) {
#if	DEBUG_INTERPOLATION
		if (needInterpolationLogging)
			printf("X and Y are larger than largest cell in table: %d %d\r\n", xIndex, yIndex);
#endif
		return map[xBinSize - 1][yBinSize - 1];
	}

	if (xIndex == xBinSize - 1) {
#if	DEBUG_INTERPOLATION
		if (needInterpolationLogging)
			printf("TODO BETTER LOGGING x overflow %d\r\n", yIndex);
#endif
		// todo: implement better handling - y interpolation
		return map[xBinSize - 1][yIndex];
	}

	if (yIndex == yBinSize - 1) {
#if	DEBUG_INTERPOLATION
		if (needInterpolationLogging)
			printf("Y is larger than largest cell in table: %d\r\n", yIndex);
#endif
		// todo: implement better handling - x interpolation
		return map[xIndex][yBinSize - 1];
	}

	/*
	 * first we find the interpolated value for this RPM
	 */
	int rpmMaxIndex = xIndex + 1;

	float xMin = xBin[xIndex];
	float xMax = xBin[xIndex + 1];
	float rpmMinKeyMinValue = map[xIndex][yIndex];
	float rpmMaxKeyMinValue = map[xIndex + 1][yIndex];

	float keyMinValue = interpolate(xMin, rpmMinKeyMinValue, xMax, rpmMaxKeyMinValue, x);

#if	DEBUG_INTERPOLATION
	if (needInterpolationLogging) {
		printf("X=%f:\r\nrange %f - %f\r\n", x, xMin, xMax);
		printf("X interpolation range %f   %f result %f\r\n", rpmMinKeyMinValue, rpmMaxKeyMinValue, keyMinValue);
	}
#endif

	int keyMaxIndex = yIndex + 1;
	float keyMin = yBin[yIndex];
	float keyMax = yBin[keyMaxIndex];
	float rpmMinKeyMaxValue = map[xIndex][keyMaxIndex];
	float rpmMaxKeyMaxValue = map[rpmMaxIndex][keyMaxIndex];

	float keyMaxValue = interpolateMsg("3d", xMin, rpmMinKeyMaxValue, xMax, rpmMaxKeyMaxValue, x);

#if	DEBUG_INTERPOLATION
	if (needInterpolationLogging) {
		printf("key=%f:\r\nrange %f - %f\r\n", y, keyMin, keyMax);
		printf("key interpolation range %f   %f result %f\r\n", rpmMinKeyMaxValue, rpmMaxKeyMaxValue, keyMaxValue);
	}
#endif

	float result = interpolateMsg("3d", keyMin, keyMinValue, keyMax, keyMaxValue, y);
	return result;
}

void setTableValue(float bins[], float values[], int size, float key, float value) {
	int index = findIndex(bins, size, key);
	if (index == -1)
		index = 0;
	values[index] = value;
}

void initInterpolation(Logging *sharedLogger) {
	logger = sharedLogger;
#if BINARY_PERF && ! EFI_UNIT_TEST
	addConsoleAction("binarytest", testBinary);
#endif

}
