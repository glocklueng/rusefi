/**
 * @file	rusEfiFunctionalTest.c
 *
 * @date Mar 1, 2014
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "global.h"
#include "rusEfiFunctionalTest.h"
#include "eficonsole.h"
#include "engine_configuration.h"
#include "rusefi_enums.h"
#include "pwm_generator_logic.h"
#include "wave_math.h"
#include "boards.h"
#include "trigger_central.h"
#include "datalogging.h"
#include "algo.h"
#include "rpm_calculator.h"
#include "wave_chart.h"
#include "status_loop.h"
#include "trigger_emulator_algo.h"
#include "main_trigger_callback.h"
#include "allsensors.h"


extern WaveChart waveChart;

static engine_configuration_s ec;
static engine_configuration2_s ec2;

engine_configuration_s * engineConfiguration = &ec;
engine_configuration2_s *engineConfiguration2 = &ec2;

void setOutputPinValue(io_pin_e pin, int logicValue) {
}

int isInjectionEnabled(void) {
	return TRUE;
}


//void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
//
//}

int isCranking(void) {
	return 0;
}

void idleDebug(char *msg, int value) {

}

float getMap(void) {
	return 0;
}

static int primaryWheelState = FALSE;
static int secondaryWheelState = FALSE;

static void triggerEmulatorCallback(PwmConfig *state, int stateIndex) {
	int newPrimaryWheelState = state->multiWave.waves[0].pinStates[stateIndex];
	int newSecondaryWheelState = state->multiWave.waves[1].pinStates[stateIndex];

	if (primaryWheelState != newPrimaryWheelState) {
		primaryWheelState = newPrimaryWheelState;
		hwHandleShaftSignal(primaryWheelState ? SHAFT_PRIMARY_UP : SHAFT_PRIMARY_DOWN);
	}

	if (secondaryWheelState != newSecondaryWheelState) {
		secondaryWheelState = newSecondaryWheelState;
		hwHandleShaftSignal(secondaryWheelState ? SHAFT_SECONDARY_UP : SHAFT_SECONDARY_DOWN);
	}

//	print("hello %d\r\n", chTimeNow());
}

void rusEfiFunctionalTest(void) {
	initializeConsole();

	initFakeBoard();

	initStatusLoop();

	resetConfigurationExt(FORD_ASPIRE_1996, engineConfiguration, engineConfiguration2);

	initThermistors();
	initAlgo();
	initRpmCalculator();

	initTriggerEmulatorLogic(triggerEmulatorCallback);

	initMainEventListener();

}

void printPendingMessages(void) {
	printPending();
	if (getFullLog()) {
		printSensors();
		finishStatusLine();
		publishChartIfFull(&waveChart);
	}
}

static size_t wt_writes(void *ip, const uint8_t *bp, size_t n) {
	printToWin32Console((char*)bp);
	return DELEGATE->vmt->write(DELEGATE, bp, n);
}

static size_t wt_reads(void *ip, uint8_t *bp, size_t n) {
	return DELEGATE->vmt->read(DELEGATE, bp, n);
}

static char putMessageBuffer[2];

static msg_t wt_put(void *ip, uint8_t b) {
	putMessageBuffer[0] = b;
	putMessageBuffer[1] = 0;
	printToWin32Console((char*)putMessageBuffer);
//	cputs("wt_put");
	return DELEGATE->vmt->put(DELEGATE, b);
}

static msg_t wt_get(void *ip) {
//	cputs("wt_get");
	//return 0;
	return DELEGATE->vmt->get(DELEGATE);
}

static const struct Win32TestStreamVMT vmt = { wt_writes, wt_reads, wt_put, wt_get };

void initTestStream(TestStream *ts) {
	ts->vmt = &vmt;
}

int isSerialOverTcpReady;

int is_serial_ready(void) {
	return isSerialOverTcpReady;
}
