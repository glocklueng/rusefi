/**
 * @file	ckp_events.h
 * @brief	Position sensor event enum
 *
 * @date Feb 9, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CKP_EVENTS_H_
#define CKP_EVENTS_H_

typedef enum {
	SHAFT_PRIMARY_UP = 0,
	SHAFT_PRIMARY_DOWN = 1,
	SHAFT_SECONDARY_UP = 2,
	SHAFT_SECONDARY_DOWN = 3,
} ShaftEvents;

#endif /* CKP_EVENTS_H_ */
