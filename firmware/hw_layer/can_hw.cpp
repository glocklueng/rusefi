/**
 * @file	can_hw.cpp
 * @brief	CAN bus low level code
 *
 * todo: this file should be split into two - one for CAN transport level ONLY and
 * another one with actual messages
 *
 * @date Dec 11, 2013
 * @author Andrey Belomutskiy, (c) 2012-2015
 */

#include "main.h"
#include "can_hw.h"
#include "string.h"

#if EFI_PROD_CODE

#include "pin_repository.h"
#include "engine_state.h"
#include "can_header.h"
#include "engine_configuration.h"
#include "vehicle_speed.h"
#endif /* EFI_PROD_CODE */

#if EFI_CAN_SUPPORT || defined(__DOXYGEN__)

EXTERN_ENGINE
;

static int canReadCounter = 0;
static int can_write_ok = 0;
static int can_write_not_ok = 0;
static Logging logger;
static THD_WORKING_AREA(canTreadStack, UTILITY_THREAD_STACK_SIZE);

/*
 * 500KBaud
 * automatic wakeup
 * automatic recover from abort mode
 * See section 22.7.7 on the STM32 reference manual.
 *
 * speed = 42000000 / (BRP + 1) / (1 + TS1 + 1 + TS2 + 1)
 * 42000000 / 7 / 12 = 500000
 *
 *
 */
static const CANConfig canConfig = {
CAN_MCR_ABOM | CAN_MCR_AWUM | CAN_MCR_TXFP,
CAN_BTR_SJW(0) | CAN_BTR_TS2(1) | CAN_BTR_TS1(8) | CAN_BTR_BRP(6) };

static CANRxFrame rxBuffer;
static CANTxFrame txmsg;

// todo: we would need a data structure here
static int engine_rpm = 0;
static float engine_clt = 0;

static int rand = 1212321311;

//static CANDriver *getCanDevice() {
//	if(board)
//}

static void printPacket(CANRxFrame *rx) {
//	scheduleMsg(&logger, "CAN FMI %x", rx->FMI);
//	scheduleMsg(&logger, "TIME %x", rx->TIME);
	scheduleMsg(&logger, "SID %x/%x %x %x %x %x %x %x %x %x", rx->SID, rx->DLC, rx->data8[0], rx->data8[1],
			rx->data8[2], rx->data8[3], rx->data8[4], rx->data8[5], rx->data8[6], rx->data8[7]);

	if (rx->SID == CAN_BMW_E46_CLUSTER_STATUS) {
		int odometerKm = 10 * (rx->data8[1] << 8) + rx->data8[0];
		int odometerMi = (int) (odometerKm * 0.621371);
		scheduleMsg(&logger, "GOT odometerKm %d", odometerKm);
		scheduleMsg(&logger, "GOT odometerMi %d", odometerMi);
		int timeValue = (rx->data8[4] << 8) + rx->data8[3];
		scheduleMsg(&logger, "GOT time %d", timeValue);
	}
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

static void sendMessage2(int size) {
	txmsg.DLC = size;
	msg_t result = canTransmit(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &txmsg, TIME_INFINITE);
	if (result == RDY_OK) {
		can_write_ok++;
	} else {
		can_write_not_ok++;
	}
}

static void sendMessage() {
	sendMessage2(8);
}

#if EFI_PROD_CODE

static void canDashboardBMW(void) {
	//BMW Dashboard
	commonTxInit(CAN_BMW_E46_SPEED);
	setShortValue(&txmsg, 10 * 8, 1);
	sendMessage();

	commonTxInit(CAN_BMW_E46_RPM);
	setShortValue(&txmsg, (int) (engine_rpm * 6.4), 2);
	sendMessage();

	commonTxInit(CAN_BMW_E46_DME2);
	setShortValue(&txmsg, (int) ((engine_clt + 48.373) / 0.75), 1);
	sendMessage();
}

static void canMazdaRX8(void) {
	rand = rand * 17;

//	commonTxInit(0x300);
//	sendMessage2(0);

	commonTxInit(CAN_MAZDA_RX_RPM_SPEED);

	float kph = getVehicleSpeed();

	setShortValue(&txmsg, SWAP_UINT16(engine_rpm * 4), 0);
	setShortValue(&txmsg, 0xFFFF, 2);
	setShortValue(&txmsg, SWAP_UINT16((int )(100 * kph + 10000)), 4);
	setShortValue(&txmsg, 0, 6);
	sendMessage();

	commonTxInit(CAN_MAZDA_RX_STATUS_2);
	txmsg.data8[0] = 0xFE; //Unknown
	txmsg.data8[1] = 0xFE; //Unknown
	txmsg.data8[2] = 0xFE; //Unknown
	txmsg.data8[3] = 0x34; //DSC OFF in combo with byte 5 Live data only seen 0x34
	txmsg.data8[4] = 0x00; // B01000000; // Brake warning B00001000;  //ABS warning
	txmsg.data8[5] = 0x40; // TCS in combo with byte 3
	txmsg.data8[6] = 0x00; // Unknown
	txmsg.data8[7] = 0x00; // Unused

	commonTxInit(CAN_MAZDA_RX_STATUS_2);
	txmsg.data8[0] = 0x98; //temp gauge //~170 is red, ~165 last bar, 152 centre, 90 first bar, 92 second bar
	txmsg.data8[1] = 0x00; // something to do with trip meter 0x10, 0x11, 0x17 increments by 0.1 miles
	txmsg.data8[2] = 0x00; // unknown
	txmsg.data8[3] = 0x00; //unknown
	txmsg.data8[4] = 0x01; //Oil Pressure (not really a gauge)
	txmsg.data8[5] = 0x00; //check engine light
	txmsg.data8[6] = 0x00; //Coolant, oil and battery
	txmsg.data8[7] = 0x00; //unused
	sendMessage();
}

static void canDashboardFiat(void) {
	//Fiat Dashboard
	commonTxInit(CAN_FIAT_MOTOR_INFO);
	setShortValue(&txmsg, (int) (engine_clt - 40), 3); //Coolant Temp
	setShortValue(&txmsg, engine_rpm / 32, 6); //RPM
	sendMessage();
}

static void canDashboardVAG(void) {
	//VAG Dashboard
	commonTxInit(CAN_VAG_RPM);
	setShortValue(&txmsg, engine_rpm * 4, 2); //RPM
	sendMessage();

	commonTxInit(CAN_VAG_CLT);
	setShortValue(&txmsg, (int) ((engine_clt + 48.373) / 0.75), 1); //Coolant Temp
	sendMessage();
}

static void canInfoNBCBroadcast(can_nbc_e typeOfNBC) {
	switch (typeOfNBC) {
	case CAN_BUS_NBC_BMW:
		canDashboardBMW();
		break;
	case CAN_BUS_NBC_FIAT:
		canDashboardFiat();
		break;
	case CAN_BUS_NBC_VAG:
		canDashboardVAG();
		break;
	case CAN_BUS_MAZDA_RX8:
		canMazdaRX8();
		break;
	default:
		break;
	}
}

static void canRead(void) {
	scheduleMsg(&logger, "waiting for CAN");
	canReceive(&EFI_CAN_DEVICE, CAN_ANY_MAILBOX, &rxBuffer, TIME_INFINITE);

	canReadCounter++;
	printPacket(&rxBuffer);
}

static void writeStateToCan(void) {
	engine_rpm = getRpm();
	engine_clt = 123; //getCoolantTemperature(engine);

	canInfoNBCBroadcast(engineConfiguration->canNbcType);
}

static msg_t canThread(void *arg) {
	chRegSetThreadName("CAN");
	while (true) {
		if (engineConfiguration->canWriteEnabled)
			writeStateToCan();

		if (engineConfiguration->canReadEnabled)
			canRead(); // todo: since this is a blocking operation, do we need a separate thread for 'write'?

		if (engineConfiguration->canSleepPeriod < 10) {
			warning(OBD_PCM_Processor_Fault, "%d too low CAN", engineConfiguration->canSleepPeriod);
			engineConfiguration->canSleepPeriod = 50;
		}

		chThdSleepMilliseconds(engineConfiguration->canSleepPeriod);
	}
#if defined __GNUC__
	return -1;
#endif
}

static void canInfo(void) {
	scheduleMsg(&logger, "CAN TX %s", hwPortname(boardConfiguration->canTxPin));
	scheduleMsg(&logger, "CAN RX %s", hwPortname(boardConfiguration->canRxPin));
	scheduleMsg(&logger, "type=%d canReadEnabled=%s canWriteEnabled=%s period=%d", engineConfiguration->canNbcType,
			boolToString(engineConfiguration->canReadEnabled), boolToString(engineConfiguration->canWriteEnabled),
			engineConfiguration->canSleepPeriod);

	scheduleMsg(&logger, "CAN rx count %d/tx ok %d/tx not ok %d", canReadCounter, can_write_ok, can_write_not_ok);
}

#endif /* EFI_PROD_CODE */


void initCan(void) {
#if EFI_PROD_CODE
	if (!engineConfiguration->isCanEnabled)
		return;
#endif /* EFI_PROD_CODE */

	initLogging(&logger, "CAN driver");

#if STM32_CAN_USE_CAN2
	// CAN1 is required for CAN2
	canStart(&CAND1, &canConfig);
	canStart(&CAND2, &canConfig);
#else
	canStart(&CAND1, &canConfig);
#endif

	canStart(&EFI_CAN_DEVICE, &canConfig);
#if EFI_PROD_CODE

	chThdCreateStatic(canTreadStack, sizeof(canTreadStack), NORMALPRIO, (tfunc_t) canThread, NULL);

	mySetPadMode2("CAN TX", boardConfiguration->canTxPin, PAL_MODE_ALTERNATE(EFI_CAN_TX_AF));
	mySetPadMode2("CAN RX", boardConfiguration->canRxPin, PAL_MODE_ALTERNATE(EFI_CAN_RX_AF));

	addConsoleAction("caninfo", canInfo);
#endif /* EFI_PROD_CODE */
}

#endif /* EFI_CAN_SUPPORT */
