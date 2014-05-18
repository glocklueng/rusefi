/**
 * @file SingleTimerExecutor.h
 *
 * @date: Apr 18, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef SINGLETIMEREXECUTOR_H_
#define SINGLETIMEREXECUTOR_H_

#include "scheduler.h"
#include "event_queue.h"

class Executor {
public:
	Executor();
	void schedule(scheduling_s *scheduling, uint64_t nowUs, int delayUs, schfunc_t callback, void *param);
	void execute(uint64_t nowUs);
private:
	EventQueue queue;
	bool_t reentrantLock;
	void doExecute(uint64_t nowUs);
	void lock(void);
	void unlock(void);
};

#endif /* SINGLETIMEREXECUTOR_H_ */
