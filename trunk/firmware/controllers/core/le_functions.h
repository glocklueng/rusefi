/**
 * @file le_functions.h
 *
 * @date Oct 5, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#ifndef LE_FUNCTIONS_H_
#define LE_FUNCTIONS_H_

#include "engine.h"
#include "logic_expression.h"

/**
 * In human language that's
 * (time_since_boot < 4) OR (rpm > 0)
 */
// todo: the delay should probably be configurable?
#define FUEL_PUMP_LOGIC "time_since_boot 4 < rpm 0 > OR"

#define AC_RELAY_LOGIC "ac_on_switch"

/**
 * In human language that's
 * (fan and (coolant > fan_off_setting)) OR (coolant > fan_on_setting)
 */
#define FAN_CONTROL_LOGIC "todo"

float getLEValue(Engine *engine, le_action_e action);

#endif /* LE_FUNCTIONS_H_ */
