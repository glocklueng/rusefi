/*
 * listener_array.h
 *
 * @date Jan 1, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef LISTENER_ARRAY_H_
#define LISTENER_ARRAY_H_

#include "rusefi_types.h"

#define MAX_INT_LISTENER_COUNT 15

// todo: reorder parameters for consistency?
typedef void (*IntIntVoidListener)(int value1, int value2, void *arg);

// todo: rename 'Arg' to 'Void'?
typedef void (*ArgListener)(void *arg);
typedef void (*ArgIntListener)(void *arg, int value);

// todo: rename this class, that's not just 'callback(int param) anymore
class IntListenerArray {
public:
	IntListenerArray();
	void registerCallback(VoidInt handler, void *arg);
	void registerCallback(Void listener);
	void invokeJustArgCallbacks();
	int currentListenersCount;
	VoidInt callbacks[MAX_INT_LISTENER_COUNT];
	void * args[MAX_INT_LISTENER_COUNT];
};

void invokeCallbacks(IntListenerArray *array, int value);
void invokeJustArgCallbacks(IntListenerArray *array);
void invokeArgIntCallbacks(IntListenerArray *array, int value);
void invokeIntIntCallbacks(IntListenerArray *array, int value, int value2);
void invokeIntIntVoidCallbacks(IntListenerArray *array, int value, int value2);
void clearCallbacks(IntListenerArray *array);

#endif /* LISTENER_ARRAY_H_ */
