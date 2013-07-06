/*
 * listener_array.h
 *
 *  Created on: Jan 1, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef LISTENER_ARRAY_H_
#define LISTENER_ARRAY_H_


#define MAX_INT_LISTENER_COUNT 5

typedef void (*IntListener)(int value);

typedef void (*ArgIntListener)(void *arg, int value);


typedef struct {
	int currentListenersCount;
	IntListener callbacks[MAX_INT_LISTENER_COUNT];
	void * args[MAX_INT_LISTENER_COUNT];
} IntListenerArray;

void registerCallback(IntListenerArray *array, IntListener handler, void *arg);
void invokeCallbacks(IntListenerArray *array, int value);
void invokeArgCallbacks(IntListenerArray *array, int value);
void invokeCallbacks2I(IntListenerArray *array, int value, int value2);

#endif /* LISTENER_ARRAY_H_ */
