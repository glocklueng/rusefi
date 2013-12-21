/**
 * @file	can_hw.c
 * @brief	CAN bus low level code
 *
 * todo: this file should be split into two - one for CAN transport level ONLY and
 * another one with actual messages
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "can_hw.h"
#include "pin_repository.h"
#include "rficonsole_logic.h"
#include "string.h"
#include "engine_state.h"

static Logging logger;
static WORKING_AREA(canTreadStack, 512);

/*
 * 500KBaud
 * automatic wakeup
 * automatic recover from abort mode
 * See section 22.7.7 on the STM32 reference manual.
 */
static const CANConfig canConfig = {
CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
CAN_BTR_SJW(0) | CAN_BTR_TS2(1) |
CAN_BTR_TS1(8) | CAN_BTR_BRP(6) };

static CANRxFrame rxBuffer;
static CANTxFrame txmsg;

// todo: we would need a data structure here
static int engine_rpm = 0;
static int engine_clt = 0;

static void printPacket(CANRxFrame *rx) {
	scheduleSimpleMsg(&logger, "GOT FMI ", rx->FMI);
	scheduleSimpleMsg(&logger, "GOT TIME ", rx->TIME);
	scheduleSimpleMsg(&logger, "GOT DLC ", rx->DLC);
	scheduleSimpleMsg(&logger, "GOT SID ", rx->SID);

	if (rx->SID == CAN_BMW_E46_CLUSTER_STATUS) {
		int odometerKm = 10 * (rx->data8[1] << 8) + rx->data8[0];
		int odometerMi = odometerKm * 0.621371;
		scheduleSimpleMsg(&logger, "GOT odometerKm ", odometerKm);
		scheduleSimpleMsg(&logger, "GOT odometerMi ", odometerMi);
		int timeValue = (rx->data8[4] << 8) + rx->data8[3];
		scheduleSimpleMsg(&logger, "GOT time ", timeValue);
	}

	chThdSleepMilliseconds(5);
	print("d0 %d\r\n", rx->data8[0]);
	print("d1 %d\r\n", rx->data8[1]);
	print("d2 %d\r\n", rx->data8[2]);
	print("d3 %d\r\n", rx->data8[3]);
	print("d4 %d\r\n", rx->data8[4]);
	print("d5 %d\r\n", rx->data8[5]);
	print("d6 %d\r\n", rx->data8[6]);
	print("d7 %d\r\n", rx->data8[7]);

	chThdSleepMilliseconds(5);
}

static void setShortValue(CANTxFrame *txmsg, int value, int offset) {
	txmsg->data8[offset] = value;
	txmsg->data8[offset + 1] = value >> 8;
}

static void commonTxInit(int eid) {
	memset(&txmsg, 0, sizeof(txmsg));
	txmsg.IDE = CAN_IDE_STD;
	txmsg.EID = eid;
	txmsg.RTR = CAN_RTR_DATA;
	txmsg.DLC = 8;
}

static void canDashboardBMW(void) {
	//BMW Dashboard
	commonTxInit(CAN_BMW_E46_SPEED);
	setShortValue(&txmsg, 10 * 8, 1);
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE );

	commonTxInit(CAN_BMW_E46_RPM);
	setShortValue(&txmsg, engine_rpm * 6.4, 2);
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE );

	commonTxInit(CAN_BMW_E46_DME2);
	setShortValue(&txmsg, (engine_clt + 48.373) / 0.75, 1);
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE );
}

static void canDashboardFiat(void) {
	//Fiat Dashboard
	commonTxInit(CAN_FIAT_MOTOR_INFO);
	setShortValue(&txmsg, engine_clt - 40, 3); //Coolant Temp
	setShortValue(&txmsg, engine_rpm / 32, 6); //RPM
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE );
}

static void canDashboardVAG(void) {
	//VAG Dashboard
	commonTxInit(CAN_VAG_RPM);
	setShortValue(&txmsg, engine_rpm * 4, 2); //RPM
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE );

	commonTxInit(CAN_VAG_CLT);
	setShortValue(&txmsg, (engine_clt + 48.373) / 0.75, 1); //Coolant Temp
	canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE );
}

// todo: 'typeOfBCN' should become a enum
static void canInfoNBCBroadcast(int typeOfNBC) {
	switch (typeOfNBC) {
	case 0:
		canDashboardBMW();
		break;
	case 1:
		canDashboardFiat();
		break;
	case 2:
		canDashboardVAG();
		break;
	default:
		break;
	}
}

static void canRead(void) {
	scheduleSimpleMsg(&logger, "waiting for CAN ", 0);
	canReceive(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &rxBuffer, TIME_INFINITE );

	printPacket(&rxBuffer);
}

static msg_t canThread(void *arg) {
	while (TRUE) {
		engine_rpm = getCurrentRpm();
		engine_clt = getCoolantTemperature();

		canInfoNBCBroadcast(0);
		chThdSleepMilliseconds(50);
	}
	return -1;
}

void initCan(void) {
	initLogging(&logger, "CAN driver");

#if STM32_CAN_USE_CAN2
	// CAN1 is required for CAN2
	canStart(&CAND1, &canConfig);
	canStart(&CAND2, &canConfig);
#else
	canStart(&CAND1, &canConfig);
#endif

	canStart(&EFI_CAN_DEVICE, &canConfig);
	chThdCreateStatic(canTreadStack, sizeof(canTreadStack), NORMALPRIO, (tfunc_t) canThread, NULL );

	mySetPadMode("CAN TX", EFI_CAN_TX_PORT, EFI_CAN_TX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_TX_AF));
	mySetPadMode("CAN RX", EFI_CAN_RX_PORT, EFI_CAN_RX_PIN, PAL_MODE_ALTERNATE(EFI_CAN_RX_AF));

}
