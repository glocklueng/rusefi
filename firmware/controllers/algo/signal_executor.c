/**
 * @file	signal_executor.c
 *
 * todo: we should split this file into two:
 * one for pure scheduling and another one for signal output which would
 * use the scheduling
 *
 * @date Dec 4, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "main.h"
#include "signal_executor.h"

#if EFI_WAVE_ANALYZER

/**
 * Signal executors feed digital events right into WaveChart used by Sniffer tab of Dev Console
 */
#include "wave_analyzer.h"

#endif /* EFI_WAVE_ANALYZER */

#define OUTPUT_SIGNAL_COUNT 40

static OutputSignal signals[OUTPUT_SIGNAL_COUNT];
int outputSignalCount;

void resetOutputSignals(void) {
	outputSignalCount = 0;
}

OutputSignal * addOutputSignal(io_pin_e ioPin) {
	chDbgCheck(outputSignalCount < OUTPUT_SIGNAL_COUNT, "too many output signals");
	OutputSignal *signal = &signals[outputSignalCount++];

	initOutputSignal(signal, ioPin);

	return signal;
}

void initOutputSignalBase(OutputSignal *signal) {
	signal->status = IDLE;
	signal->last_scheduling_time = 0;
	signal->initialized = TRUE;
}

static void turnHigh(OutputSignal *signal) {
#if EFI_DEFAILED_LOGGING
	signal->hi_time = chTimeNow();
#endif /* EFI_DEFAILED_LOGGING */
	// turn the output level ACTIVE
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(signal->io_pin, TRUE);
	// sleep for the needed duration

#if EFI_WAVE_ANALYZER
	addWaveChartEvent(signal->name, "up", "");
#endif /* EFI_WAVE_ANALYZER */
}

static void turnLow(OutputSignal *signal) {
	// turn off the output
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(signal->io_pin, FALSE);

#if EFI_DEFAILED_LOGGING
	systime_t after = chTimeNow();
	debugInt(&signal->logging, "a_time", after - signal->hi_time);
	scheduleLogging(&signal->logging);
#endif /* EFI_DEFAILED_LOGGING */

#if EFI_WAVE_ANALYZER
	addWaveChartEvent(signal->name, "down", "");
#endif /* EFI_WAVE_ANALYZER */
}

/**
 *
 * @param	delay	the number of ticks before the output signal
 * 					immediate output if delay is zero
 * @param	dwell	the number of ticks of output duration
 *
 */
void scheduleOutput(OutputSignal *signal, int delay, int dwell, time_t now) {
	chDbgCheck(dwell >= 0, "dwell cannot be negative");

	scheduleOutputBase(signal, delay, dwell);

	scheduleTask(&signal->signalTimerUp, delay, (schfunc_t) &turnHigh, (void *) signal);
	scheduleTask(&signal->signalTimerDown, delay + dwell, (schfunc_t) &turnLow, (void*)signal);

	signal->last_scheduling_time = now;
}

void scheduleOutputBase(OutputSignal *signal, int offset, int duration) {
	/**
	 * it's better to check for the exact 'TRUE' value since otherwise
	 * we would accept any memory garbage
	 */
	chDbgCheck(signal->initialized == TRUE, "Signal not initialized");
//	signal->offset = offset;
//	signal->duration = duration;
}
