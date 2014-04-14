/**
 * @file	efilib2.cpp
 *
 * @date Apr 14, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "efilib2.h"

Overflow64Counter::Overflow64Counter() {
	currentBase = 0;
	currentValue = 0;
}

void Overflow64Counter::offer(uint32_t value) {
	if(value < currentValue) {
		// new value less than previous value means there was an overflow in that 32 bit counter
		currentBase += 0x100000000LL;
	}
	currentValue = value;
}

uint64_t Overflow64Counter::get(void) {
	return currentBase + currentValue;
}
