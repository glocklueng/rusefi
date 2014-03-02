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

engine_configuration_s engineConfiguration;
engine_configuration2_s engineConfiguration2;

void setOutputPinValue(io_pin_e pin, int logicValue) {
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

static PwmConfig configuration;

static void triggerEmulatorCallback(PwmConfig *state, int stateIndex) {
//	print("hello %d\r\n", chTimeNow());
}

void rusEfiFunctionalTest(void) {
	initializeConsole();

	resetConfigurationExt(FORD_ASPIRE_1996, &engineConfiguration, &engineConfiguration2);


	float gRpm = 1200 * engineConfiguration.rpmMultiplier / 60.0; // per minute converted to per second
	configuration.period = frequency2period(gRpm);


	trigger_shape_s *s = &engineConfiguration2.triggerShape;
	int *pinStates[2] = {s->wave.waves[0].pinStates, s->wave.waves[1].pinStates};
	weComplexInit("position sensor", &configuration, s->size, s->wave.switchTimes, 2, pinStates, triggerEmulatorCallback);
}

static size_t wt_writes(void *ip, const uint8_t *bp, size_t n) {
	printToWin32Console(bp);
	return DELEGATE->vmt->write(DELEGATE, bp, n);
}

static size_t wt_reads(void *ip, uint8_t *bp, size_t n) {
	return DELEGATE->vmt->read(DELEGATE, bp, n);
}

static char putMessageBuffer[2];

static msg_t wt_put(void *ip, uint8_t b) {
	putMessageBuffer[0] = b;
	putMessageBuffer[1] = 0;
	printToWin32Console(putMessageBuffer);
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
	ts->vmt    = &vmt;
}
