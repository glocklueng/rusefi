/**
 * @file	cyclic_buffer.c
 *
 * @date Dec 8, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "cyclic_buffer.h"
#include <string.h>

void cbInit(cyclic_buffer *cb) {
	memset(cb->elements, 0, sizeof(cb->elements));
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
	for (int i = 0; i < l; i++) {
		int index = cb->currentIndex - i;
		while (index < 0)
			index += CB_MAX_SIZE;

		result += cb->elements[index];
	}
	return result;
}
