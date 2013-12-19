/**
 * @file	test_cyclic_buffer.c
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "test_util.h"
#include "cyclic_buffer.h"
#include "main.h"
#include "histogram.h"

static cyclic_buffer sb;

void testCyclicBuffer(void) {

	cbInit(&sb);
	cbAdd(&sb, 10);

	print("testCyclicBuffer\r\n");
	assertEquals(10, cbSum(&sb, 3));

	cbAdd(&sb, 2);
	assertEquals(12, cbSum(&sb, 2));
}

void testHistogram(void) {
	print("testHistogram\r\n");

	initHistograms();

	assertEquals(80, histogramGetIndex(239));
	assertEquals(223, histogramGetIndex(239239));
	assertEquals(364, histogramGetIndex(239239239));
}
