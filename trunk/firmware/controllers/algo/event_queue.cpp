/**
 * @file event_queue.cpp
 * This is a data structure which keeps track of all pending events
 * Implemented as a linked list, which is fine since the number of
 * pending events is pretty low
 * todo: MAYBE migrate to a better data structure, but that's low priority
 *
 * this data structure is NOT thread safe
 *
 * @date Apr 17, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "event_queue.h"
#include "efitime.h"
#include "utlist.h"

#if EFI_SIGNAL_EXECUTOR_ONE_TIMER

EventQueue::EventQueue() {
	head = NULL;
}

void EventQueue::insertTask(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param) {
	if (callback == NULL)
		firmwareError("NULL callback");
	uint64_t time = nowUs + delayUs;

	scheduling->momentUs = time;
	scheduling->callback = callback;
	scheduling->param = param;

	scheduling_s * elt;
	LL_FOREACH(head, elt)
	{
		if (elt == scheduling) {
			firmwareError("re-adding element into event_queue");
			return;
		}
	}

	LL_PREPEND(head, scheduling);
}

//void EventQueue::insertTask(scheduling_s *scheduling, int delayUs, schfunc_t callback, void *param) {
//	insertTask(scheduling, getTimeNowUs(), delayUs, callback, param);
//}

/**
 * Get the timestamp of the soonest pending action
 */
uint64_t EventQueue::getNextEventTime(uint64_t nowUs) {
	scheduling_s * current;
	// this is a large value which is expected to be larger than any real time
	uint64_t result = EMPTY_QUEUE;

	LL_FOREACH(head, current)
	{
		efiAssert(current->momentUs > nowUs, "executeAll should have been called");
		if (current->momentUs < result)
			result = current->momentUs;
	}
	return result;
}

/**
 * Invoke all pending actions prior to specified timestamp
 */
void EventQueue::executeAll(uint64_t now) {
	scheduling_s * current, *tmp;

	scheduling_s * executionList = NULL;

// here we need safe iteration because we are removing elements
	LL_FOREACH_SAFE(head, current, tmp)
	{
		if (current->momentUs <= now) {
			LL_DELETE(head, current);
//			LL_PREPEND(executionList, current);
			current->callback(current->param);
		}
	}
	LL_FOREACH(executionList, current)
	{
	}

}

void EventQueue::clear(void) {
	head = NULL;
}

#endif /* EFI_SIGNAL_EXECUTOR_ONE_TIMER */

