/**
 * @file event_queue.cpp
 *
 * @date Apr 17, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "event_queue.h"
#include "efitime.h"
#include "utlist.h"

EventQueue::EventQueue() {
	head = NULL;
}

void EventQueue::schedule(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param) {
	uint64_t time = nowUs + delayUs;

//	scheduling->momentUs = time;
	LL_PREPEND(head, scheduling);
}

void EventQueue::schedule(scheduling_s *scheduling, int delayUs, schfunc_t callback, void *param) {
	schedule(scheduling, getTimeNowUs(), delayUs, callback, param);
}

uint64_t EventQueue::getNextEventTime(void) {
	scheduling_s * elt;
	// this is a large value which is expected to be larger than any real time
	uint64_t result = EMPTY_QUEUE;

	LL_FOREACH(head, elt)
	{
//		if (elt->momentUs < result)
//			result = elt->momentUs;

	}
	return result;

}
