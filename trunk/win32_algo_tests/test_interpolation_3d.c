/*
 *  Created on: Oct 17, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

/**
 * @file    test_interpolation_3d.c
 */

#include "test_interpolation_3d.h"
#include <stdio.h>
#include <stdlib.h>

#include "interpolation_3d.h"
#include "main.h"

float rpmBins[5] = { 100, 200, 300, 400, 500 };
float mafBins[4] = { 1, 2, 3, 4 };

float map0[4] = { 1, 2, 3, 4 };
float map1[4] = { 2, 3, 4, 5 };
float map2[4] = { 3, 4, 200, 300 };
float map3[4] = { 4, 200, 500, 600 };
float map4[4] = { 4, 200, 500, 600 };

float *map[5] = { map0, map1, map2, map3, map4 };


static float getValue(float rpm, float maf) {
	return interpolate3d(rpm, maf, rpmBins, 5, mafBins, 4, map);
}

void testInterpolate3d(void) {
	float dwell;
	printf("no interpolation here\r\n");
	dwell = getValue(100, 2);
	assertEquals(2, dwell);

	printf("no interpolation here\r\n");
	dwell = getValue(200, 4);
	assertEquals(5, dwell);

	printf("rpm interpolated value expected1\r\n");
	dwell = getValue(150, 2);
	assertEquals(2.5, dwell);

	printf("rpm interpolated value expected2\r\n");
	dwell = getValue(250, 3);
	assertEquals(102, dwell);

	printf("both rpm and maf interpolated value expected\r\n");
	dwell = getValue(335.3, 3.551);
	assertEquals(360.1, dwell);

	dwell = getValue(410.01, 2.012);
	assertEquals(203.6, dwell);

	dwell = getValue(1000000, 1000);
	assertEquals(4, dwell);

	dwell = getValue(410.01, -1);
	assertEquals(4, dwell);

	dwell = getValue(-1, -1);
	assertEquals(1, dwell);
}
