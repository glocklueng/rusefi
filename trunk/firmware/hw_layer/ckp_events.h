/*
 * ckp_events.h
 *
 *  Created on: Feb 9, 2013
 *      Author: Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef CKP_EVENTS_H_
#define CKP_EVENTS_H_

typedef enum {
	CKP_PRIMARY_UP = 0,
	CKP_PRIMARY_DOWN = 1,
	CKP_SECONDARY_DOWN = 2,
	CKP_SECONDARY_UP = 3,
} CkpEvents;

#endif /* CKP_EVENTS_H_ */
