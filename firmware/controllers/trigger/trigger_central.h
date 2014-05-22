/*
 * @file	trigger_central.h
 *
 * @date Feb 23, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef TRIGGER_CENTRAL_H_
#define TRIGGER_CENTRAL_H_

#include "rusefi_enums.h"
#include "listener_array.h"

typedef void (*ShaftPositionListener)(ShaftEvents signal, int index);

#ifdef __cplusplus
#include "ec2.h"

class TriggerCentral {
public:
	void addEventListener(ShaftPositionListener handler, const char *name);
	void handleShaftSignal(configuration_s *configuration, ShaftEvents signal, uint64_t nowUs);

	IntListenerArray triggerListeneres;
};
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void addTriggerEventListener(ShaftPositionListener handler, const char *name);
uint64_t getCrankEventCounter(void);
uint64_t getStartOfRevolutionIndex(void);
int isSignalDecoderError(void);
void hwHandleShaftSignal(ShaftEvents signal);
void initTriggerCentral(void);
void printAllCallbacksHistogram(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TRIGGER_CENTRAL_H_ */
