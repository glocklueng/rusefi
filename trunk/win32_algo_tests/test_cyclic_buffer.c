/**
 * @file	test_cyclic_buffer.c
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */


#include "test_cyclic_buffer.h"
#include "cyclic_buffer.h"
#include "main.h"

static cyclic_buffer sb;

void testCyclicBuffer(void) {

	cbInit(&sb);
	cbAdd(&sb, 10);

	print("testCyclicBuffer\r\n");
	assertEquals(10, cbSum(&sb, 3));

	cbAdd(&sb, 2);
	assertEquals(12, cbSum(&sb, 2));
}
