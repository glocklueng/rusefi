/*
 * @file obd2.cpp
 *
 * ISO 15765-4
 *
 * @date Jun 9, 2015
 * @author Andrey Belomutskiy, (c) 2012-2015
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "main.h"
#include "obd2.h"
#include "can_hw.h"

extern CANTxFrame txmsg;

static LoggingWithStorage logger("obd2");

void obdOnCanPacketRx(CANRxFrame *rx) {
	if (rx->SID != OBD_TEST_REQUEST) {
		return;
	}
	scheduleMsg(&logger, "Got OBD message");
	if (rx->data8[0] == 2 && rx->data8[1] == OBD_CURRENT_DATA && rx->data8[2] == PID_SUPPORTED_PIDS_REQUEST) {
		scheduleMsg(&logger, "Got lookup request");

		commonTxInit(OBD_TEST_RESPONSE);
		txmsg.data8[0] = 6; // 6 bytes
		txmsg.data8[1] = 0x41; // mode 1
		txmsg.data8[2] = PID_SUPPORTED_PIDS_REQUEST;

		setTxBit(3, 8 - PID_COOLANT_TEMP);

		setTxBit(4, 16 - PID_RPM);
		setTxBit(4, 16 - PID_TIMING_ADVANCE);
		setTxBit(4, 16 - PID_INTAKE_TEMP);

		setTxBit(5, 24 - PID_THROTTLE);

		sendMessage();
	} else if (rx->data8[0] == 1 && rx->data8[1] == OBD_STORED_DIAGNOSTIC_TROUBLE_CODES) {
		scheduleMsg(&logger, "Got stored DTC request");

	}
}


