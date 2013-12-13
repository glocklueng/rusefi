/**
 * @file	can_hw.c
 * @brief	CAN bus low level code
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "can_hw.h"
#include "pin_repository.h"
#include "rficonsole_logic.h"

static Logging logger;
/*
 * Internal loopback mode, 500KBaud, automatic wakeup, automatic recover
 * from abort mode.
 * See section 22.7.7 on the STM32 reference manual.
 */
static const CANConfig canConfig = {
  CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
  CAN_BTR_SJW(0) | CAN_BTR_TS2(1) |
  CAN_BTR_TS1(8) | CAN_BTR_BRP(6)
};

static CANRxFrame rxFrame;

static void canRead(void) {
	scheduleSimpleMsg(&logger, "waiting for CAN ", 0);
	canReceive(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &rxFrame, TIME_INFINITE);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.FMI);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.TIME);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.DLC);
	scheduleSimpleMsg(&logger, "GOT CAN ", rxFrame.SID);
}

void initCan(void) {
	initLogging(&logger, "CAN driver");

	canObjectInit(&EFI_CAN_DEVICE);
	canStart(&EFI_CAN_DEVICE, &canConfig);

	mySetPadMode("CAN TX", EFI_CAN_TX_PORT, EFI_CAN_TX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_TX_AF));
	mySetPadMode("CAN RX", EFI_CAN_RX_PORT, EFI_CAN_RX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_RX_AF));

	addConsoleAction("canr", canRead);
}

