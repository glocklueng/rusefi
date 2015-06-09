/*
 * @file obd2.h
 *
 * @date Jun 9, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#ifndef CONTROLLERS_OBD2_H_
#define CONTROLLERS_OBD2_H_

#include "global.h"

#define OBD_TEST_REQUEST 0x7DF

#define OBD_TEST_RESPONSE 0x7E8

#define OBD_SUPPORTED_PIDS_REQUEST 0

#define PID_COOLANT_TEMP 0x05
#define PID_RPM 0x0C
#define PID_TIMING_ADVANCE 0x0E
#define PID_INTAKE_TEMP 0x0F
#define PID_THROTTLE 0x11


void obdOnCanPacketRx(CANRxFrame *rx);

#endif /* CONTROLLERS_OBD2_H_ */
