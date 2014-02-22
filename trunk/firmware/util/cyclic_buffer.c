/**
 * @file	cyclic_buffer.c
 * @brief	A cyclic buffer is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end.
 *
 * http://en.wikipedia.org/wiki/Circular_buffer
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "cyclic_buffer.h"
#include <string.h>

void cbInit(cyclic_buffer *cb) {
	memset((void*) cb->elements, 0, sizeof(cb->elements));
	cb->currentIndex = 0;
}

void cbAdd(cyclic_buffer *cb, int value) {
	cb->currentIndex++;
	if (cb->currentIndex == CB_MAX_SIZE)
		cb->currentIndex = 0;
	cb->elements[cb->currentIndex] = value;

	cb->count++;
}

int cbSum(cyclic_buffer *cb, int length) {
	int l = length > cb->count ? cb->count : length;
	int result = 0;
	int ci = cb->currentIndex; // local copy to increase thread-safery
	for (int i = 0; i < l; i++) {
		int index = ci - i;
		while (index < 0)
			index += CB_MAX_SIZE;

		result += cb->elements[index];
	}
	return result;
}
