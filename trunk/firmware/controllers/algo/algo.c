/*
 * @file	algo.c
 *
 * @date Mar 2, 2014
 * @author Andrey Belomutskiy, (c) 2012-2014
 */

#include "global.h"
#include "algo.h"
//#include "rpm_calculator.h"
#include "advance_map.h"
#include "fuel_math.h"
#include "wave_chart.h"

WaveChart waveChart;

void initAlgo(void) {
#if EFI_WAVE_CHART
	initWaveChart(&waveChart);
#endif

	prepareFuelMap();
	prepareTimingMap();


}
