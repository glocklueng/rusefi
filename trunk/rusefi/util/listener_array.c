/*
 * listener_array.c
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#include "listener_array.h"

void registerCallback(IntListenerArray *array, IntListener handler) {
//	if(array->currentListenersCount==MAX_INT_LISTENER_COUNT)
//		fatal
	array->callbacks[array->currentListenersCount++] = handler;
}

void invokeCallbacks(IntListenerArray *array, int value) {
	for (int i = 0; i < array->currentListenersCount; i++)
		(array->callbacks[i])(value);
}

void invokeCallbacks2I(IntListenerArray *array, int value, int value2) {
	for (int i = 0; i < array->currentListenersCount; i++) {
		void (*callback2I)(int, int) = array->callbacks[i];
		(callback2I)(value, value2);
	}
}

