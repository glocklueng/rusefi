/**
 * @file	signal_executor.c
 *
 * todo: we should split this file into two:
 * one for pure scheduling and another one for signal output which would
 * use the scheduling
 *
 * @date Dec 4, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
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
#include "signal_executor.h"

#if EFI_WAVE_CHART
#include "rpm_calculator.h"
#endif

#if EFI_WAVE_ANALYZER

/**
 * Signal executors feed digital events right into WaveChart used by Sniffer tab of Dev Console
 */
#include "wave_analyzer.h"

#endif /* EFI_WAVE_ANALYZER */

#if EFI_PROD_CODE || EFI_SIMULATOR
static Logging logger;
#endif

void initSignalExecutor(void) {
#if EFI_PROD_CODE || EFI_SIMULATOR
	initLogging(&logger, "s exec");
#endif
	initSignalExecutorImpl();
}

void initOutputSignal(OutputSignal *signal, io_pin_e ioPin) {
	signal->io_pin = ioPin;
}

void turnPinHigh(io_pin_e pin) {
#if EFI_DEFAILED_LOGGING
//	signal->hi_time = hTimeNow();
#endif /* EFI_DEFAILED_LOGGING */
	// turn the output level ACTIVE
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(pin, TRUE);
	// sleep for the needed duration

#if EFI_PROD_CODE || EFI_SIMULATOR
	if (pin == SPARKOUT_1_OUTPUT || pin == SPARKOUT_3_OUTPUT) {
//		time_t now = hTimeNow();
//		float an = getCrankshaftAngle(now);
//		scheduleMsg(&logger, "spark up%d %d", pin, now);
//		scheduleMsg(&logger, "spark angle %d %f", (int)an, an);
	}
#endif

#if EFI_WAVE_CHART
	addWaveChartEvent(getPinName(pin), WC_UP, "");
#endif /* EFI_WAVE_ANALYZER */
}

void turnPinLow(io_pin_e pin) {
	// turn off the output
	// todo: this XOR should go inside the setOutputPinValue method
	setOutputPinValue(pin, false);

#if EFI_DEFAILED_LOGGING
	systime_t after = hTimeNow();
	debugInt(&signal->logging, "a_time", after - signal->hi_time);
	scheduleLogging(&signal->logging);
#endif /* EFI_DEFAILED_LOGGING */

#if EFI_WAVE_CHART
	addWaveChartEvent(getPinName(pin), WC_DOWN, "");
#endif /* EFI_WAVE_ANALYZER */
}

int getRevolutionCounter(void);

/**
 *
 * @param	delay	the number of ticks before the output signal
 * 					immediate output if delay is zero
 * @param	dwell	the number of ticks of output duration
 *
 */
void scheduleOutput(OutputSignal *signal, float delayMs, float durationMs) {
	if (durationMs < 0) {
		firmwareError("duration cannot be negative: %d", durationMs);
		return;
	}
	if (cisnan(durationMs)) {
		firmwareError("NaN in scheduleOutput", durationMs);
		return;
	}

	int index = getRevolutionCounter() % 2;
	scheduling_s * sUp = &signal->signalTimerUp[index];
	scheduling_s * sDown = &signal->signalTimerDown[index];

	scheduleTask(sUp, (int)MS2US(delayMs), (schfunc_t) &turnPinHigh, (void *) signal->io_pin);
	scheduleTask(sDown, (int)MS2US(delayMs + durationMs), (schfunc_t) &turnPinLow, (void*) signal->io_pin);
}

const char *getPinName(io_pin_e io_pin) {
	switch (io_pin) {
	case SPARKOUT_1_OUTPUT:
		return "spa1";
	case SPARKOUT_2_OUTPUT:
		return "spa2";
	case SPARKOUT_3_OUTPUT:
		return "spa3";
	case SPARKOUT_4_OUTPUT:
		return "spa4";
	case SPARKOUT_5_OUTPUT:
		return "spa5";
	case SPARKOUT_6_OUTPUT:
		return "spa6";
	case SPARKOUT_7_OUTPUT:
		return "spa7";
	case SPARKOUT_8_OUTPUT:
		return "spa8";

	case INJECTOR_1_OUTPUT:
		return "inj1";
	case INJECTOR_2_OUTPUT:
		return "inj2";
	case INJECTOR_3_OUTPUT:
		return "inj3";
	case INJECTOR_4_OUTPUT:
		return "inj4";
	case INJECTOR_5_OUTPUT:
		return "inj5";
	case INJECTOR_6_OUTPUT:
		return "inj6";
	case INJECTOR_7_OUTPUT:
		return "inj7";
	case INJECTOR_8_OUTPUT:
		return "inj8";
	default:
		return "Pin needs name";
	}
}
