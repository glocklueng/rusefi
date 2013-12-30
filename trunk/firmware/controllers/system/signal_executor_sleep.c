/**
 * @file	signal_executor_sleep.c
 * @brief   Asynchronous output signal code
 *
 * Here we have the simplest, thread-based implementation of signal executor.
 * TODO: https://sourceforge.net/p/rusefi/tickets/6/
 *
 * @date Feb 10, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#include "main.h"
#include "io_pins.h"
#include "signal_executor.h"
#include "rficonsole.h"
#include "datalogging.h"
#include "rpm_calculator.h"
#include "injector_central.h"
#include "engine_math.h"

extern int pinDefaultState[IO_PIN_COUNT];

#if EFI_WAVE_ANALYZER

/**
 * Signal executors feed digital events right into WaveChart used by Sniffer tab of Dev Console
 */
#include "wave_analyzer.h"

#endif /* EFI_WAVE_ANALYZER */

#if EFI_SIGNAL_EXECUTOR_SLEEP

static void commonSchedule(VirtualTimer *timer, int delay, vtfunc_t callback, void *param) {
	if (delay == 0) {
		/**
		 * in case of zero delay, we should invoke the callback
		 */
		callback(param);
		return;
	}

	lockAnyContext();
	int isArmed = chVTIsArmedI(timer);
	if (isArmed)
		chVTResetI(timer);

	chVTSetI(timer, delay, callback, param);
	unlockAnyContext();
}

static void turnHigh(OutputSignal *signal) {
#if EFI_DEFAILED_LOGGING
	signal->hi_time = chTimeNow();
#endif /* EFI_DEFAILED_LOGGING */
	// turn the output level ACTIVE
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(signal->io_pin, TRUE ^ pinDefaultState[signal->io_pin]);
	// sleep for the needed duration

#if EFI_WAVE_ANALYZER
	addWaveChartEvent(signal->name, "up");
#endif /* EFI_WAVE_ANALYZER */
}

static void turnLow(OutputSignal *signal) {
	// turn off the output
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(signal->io_pin, FALSE ^ pinDefaultState[signal->io_pin]);

#if EFI_DEFAILED_LOGGING
	systime_t after = chTimeNow();
	debugInt(&signal->logging, "a_time", after - signal->hi_time);
	scheduleLogging(&signal->logging);
#endif /* EFI_DEFAILED_LOGGING */

#if EFI_WAVE_ANALYZER
	addWaveChartEvent(signal->name, "down");
#endif /* EFI_WAVE_ANALYZER */
}

void scheduleByAngle(VirtualTimer *timer, float angle, vtfunc_t callback, void *param) {
	int delay = getOneDegreeTime(getCurrentRpm()) * angle;
	commonSchedule(timer, delay, callback, param);
}

/**
 *
 * @param	delay	the number of ticks before the output signal
 * 					immediate output if delay is zero
 * @param	dwell	the number of ticks of output duration
 *
 */
void scheduleOutput(OutputSignal *signal, int delay, int dwell) {
	chDbgCheck(dwell >= 0, "dwell cannot be negative");

	scheduleOutputBase(signal, delay, dwell);

	commonSchedule(&signal->hw.signalTimer, delay, (vtfunc_t) &turnHigh, (void *) signal);
	commonSchedule(&signal->hw.signalTimerDown, delay + dwell, (vtfunc_t) &turnLow, (void*)signal);

	time_t now = chTimeNow();
	signal->last_scheduling_time = now;
}

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
	signal->io_pin = ioPin;
	signal->name = getPinName(ioPin);
	signal->duration = 0;
	initOutputSignalBase(signal);
}

#endif /* EFI_SIGNAL_EXECUTOR_SLEEP */
