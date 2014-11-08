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

EventQueue::EventQueue() {
	head = NULL;
	lateDelay = 100;
}

bool EventQueue::checkIfPending(scheduling_s *scheduling) {
	return assertNotInList<scheduling_s>(head, scheduling);
}

void EventQueue::insertTask(scheduling_s *scheduling, uint64_t timeX, schfunc_t callback, void *param) {
	if (callback == NULL)
		firmwareError("NULL callback");

	int alreadyPending = checkIfPending(scheduling);
	if (alreadyPending)
		return;

	scheduling->momentX = timeX;
	scheduling->callback = callback;
	scheduling->param = param;

	LL_PREPEND(head, scheduling);
}

//void EventQueue::insertTask(scheduling_s *scheduling, int delayUs, schfunc_t callback, void *param) {
//	insertTask(scheduling, getTimeNowUs(), delayUs, callback, param);
//}

/**
 * On this layer it does not matter which units are used - us, ms ot nt.
 * Get the timestamp of the soonest pending action
 */
uint64_t EventQueue::getNextEventTime(uint64_t nowX) {
	scheduling_s * current;
	// this is a large value which is expected to be larger than any real time
	uint64_t nextTimeUs = EMPTY_QUEUE;

	int counter = 0;
	LL_FOREACH(head, current)
	{
		if (++counter > QUEUE_LENGTH_LIMIT) {
			firmwareError("Is this list looped #2?");
			return EMPTY_QUEUE;
		}
		if (current->momentX <= nowX) {
			/**
			 * looks like we end up here after 'writeconfig' (which freezes the firmware) - we are late
			 * for the next scheduled event
			 */
			uint64_t mock = nowX + 100;
			if (mock < nextTimeUs)
				nextTimeUs = mock;
		} else {
			if (current->momentX < nextTimeUs)
				nextTimeUs = current->momentX;
		}
	}
	return nextTimeUs;
}

/**
 * Invoke all pending actions prior to specified timestamp
 * @return true if at least one action was executed
 */
bool EventQueue::executeAll(uint64_t now) {
	scheduling_s * current, *tmp;

	scheduling_s * executionList = NULL;

	int counter = 0;

	// we need safe iteration because we are removing elements inside the loop
	LL_FOREACH_SAFE(head, current, tmp)
	{
		if (++counter > QUEUE_LENGTH_LIMIT) {
			firmwareError("Is this list looped?");
			return false;
		}
		if (current->momentX <= now) {
			LL_DELETE(head, current);
			LL_PREPEND(executionList, current);
		}
	}

	/*
	 * we need safe iteration here because 'callback' might change change 'current->next'
	 * while re-inserting it into the queue from within the callback
	 */
	bool result = (executionList != NULL);
	LL_FOREACH_SAFE(executionList, current, tmp)
	{
		current->callback(current->param);
	}
	return result;
}

int EventQueue::size(void) {
	scheduling_s *tmp;
	int result;
	LL_COUNT(head, tmp, result);
	return result;
}

scheduling_s *EventQueue::getForUnitText(int index) {
	scheduling_s * current;

	LL_FOREACH(head, current)
	{
		if (index == 0)
			return current;
		index--;
	}
	return NULL;
}

void EventQueue::clear(void) {
	head = NULL;
}
