/**
 * @file neo6m_logic.h
 *
 * @date Dec 30, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef NEO6M_LOGIC_H_
#define NEO6M_LOGIC_H_

typedef struct {
	int todo;
} gps_position_s;

void parseNeo6m(gps_position_s *position, char *);

#endif /* NEO6M_LOGIC_H_ */
