/*
 * test_find_index.c
 *
 *  Created on: Oct 30, 2013
 *      Author: Andrey
 */

#include "engine_math.h"
#include "main.h"
#include "interpolation_3d.h"
#include <stdio.h>

void testFindIndex(void) {

	float array[] = { 1, 2, 3, 4, 5 };
	int size = 4;
	int result;

	printf("To the left\r\n");
	result = findIndex(array, size, -1.0);
	assertEquals(-1, result);

	printf("To the right4\r\n");
	result = findIndex(array, size, 10.0);
	assertEquals(3, result);

	printf("To the right5\r\n");
	result = findIndex(array, 5, 10.0);
	assertEquals(4, result);

	printf("On the edge\r\n");
	result = findIndex(array, size, 4.0);
	assertEquals(3, result);

	printf("Another1\r\n");
	result = findIndex(array, size, 3.9);
	assertEquals(2, result);

	printf("Another2\r\n");
	result = findIndex(array, size, 4.1);
	assertEquals(3, result);

	printf("Another3\r\n");
	result = findIndex(array, size, 2);
	assertEquals(1, result);

	printf("Left edge1\r\n");
	result = findIndex(array, size, 1);
	assertEquals(0, result);

	printf("Left edge2\r\n");
	result = findIndex(array, size, 1.1);
	assertEquals(0, result);

	printf("Middle\r\n");
	result = findIndex(array, size, 3);
	assertEquals(2, result);

	size = 5; // now test with off array size

	printf("Middle2\r\n");
	result = findIndex(array, size, 4);
	assertEquals(3, result);

	printf("Middle2\r\n");
	result = findIndex(array, size, 3.1);
	assertEquals(2, result);
}

//static float getValue2(float key, float maf) {
//
//}

void testInterpolate2d(void) {

	float bins4[] = { 1, 2, 3, 4 };
	float values4[] = { 1, 20, 30, 400 };
	int size = 4;

	int result;

	printf("Left size\r\n");
	result = interpolate2d(0, bins4, values4, size);
	assertEquals(1, result);

	printf("Right size\r\n");
	result = interpolate2d(10, bins4, values4, size);
	assertEquals(400, result);

	printf("Middle1\r\n");
	result = interpolate2d(3, bins4, values4, size);
	assertEquals(30, result);

	printf("Middle1\r\n");
	result = interpolate2d(3.5, bins4, values4, size);
	assertEquals(215, result);
}
