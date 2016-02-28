/**
 * @file	mazda_626.cpp
 * MAZDA_626
 * set_engine_type 28
 *
 * @date Jan 16, 2015
 * @author Andrey Belomutskiy, (c) 2012-2016
 */

#include "main.h"
#include "mazda_626.h"
#include "engine_math.h"
#include "honda_accord.h"
#include "custom_engine.h"
#include "allsensors.h"
#include "fsio_impl.h"
#include "settings.h"

EXTERN_ENGINE;

void setMazda626EngineConfiguration(DECLARE_ENGINE_PARAMETER_F) {
	setCustomEngineConfiguration(PASS_ENGINE_PARAMETER_F);

	setOperationMode(engineConfiguration, FOUR_STROKE_CRANK_SENSOR);
//	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL_60_2;
	engineConfiguration->trigger.type = TT_60_2_VW;
//	engineConfiguration->trigger.type = TT_MAZDA_DOHC_1_4;

	// with this complex trigger we do not need this by default
	boardConfiguration->sensorChartMode = SC_OFF;

	engineConfiguration->useOnlyRisingEdgeForTrigger = true;

	engineConfiguration->injectionMode = IM_BATCH;
	// enable two_wire_batch_injection
	engineConfiguration->twoWireBatchInjection = true;
	// enable two_wire_wasted_spark
	engineConfiguration->twoWireBatchIgnition = true;

	// chartsize 600
	engineConfiguration->engineChartSize = 600;

	engineConfiguration->sensorChartFrequency = 2;

	engineConfiguration->injector.flow = 330;
	engineConfiguration->specs.displacement = 2.0;

	// set_global_trigger_offset_angle 284
	engineConfiguration->globalTriggerAngleOffset = 284;
	// set_ignition_mode 2
	engineConfiguration->ignitionMode = IM_WASTED_SPARK;

	// set_cranking_timing_angle 15
	engineConfiguration->crankingTimingAngle = 8;
	engineConfiguration->crankingChargeAngle = 70;

	// set_cranking_fuel 9
	engineConfiguration->cranking.baseFuel = 9;

	engineConfiguration->rpmHardLimit = 6000;

	engineConfiguration->tpsMin = 80;
	engineConfiguration->tpsMax = 764;

	setAlgorithm(LM_SPEED_DENSITY PASS_ENGINE_PARAMETER);
	setFuelLoadBin(0, 100 PASS_ENGINE_PARAMETER);

	// set_whole_fuel_map 9
	setWholeFuelMap(9 PASS_ENGINE_PARAMETER);

// set_whole_timing_map 10
	setWholeTimingTable(10 PASS_ENGINE_PARAMETER);

	// http://s1.micp.ru/tOb0U.png
	setThermistorConfiguration(&engineConfiguration->clt, -15, 5900, 23, 1750, 97, 165);
	// http://s2.micp.ru/I6Cfe.png
	setThermistorConfiguration(&engineConfiguration->iat, 23, 1750, 41, 810, 97, 165);
	engineConfiguration->iat.config.bias_resistor = 1820;

	commonFrankensoAnalogInputs(engineConfiguration);
//	engineConfiguration->map.sensor.hwChannel = EFI_ADC_4;
	engineConfiguration->mafAdcChannel = EFI_ADC_NONE;

	// todo: 8.2 or 10k?
	engineConfiguration->vbattDividerCoeff = ((float) (10 + 33)) / 10 * 2;

	engineConfiguration->map.sensor.type = MT_SUBY_DENSO;

	// http://s2.micp.ru/vJ9Sd.png
	engineConfiguration->engineLoadAccelLength = 12;
	engineConfiguration->engineLoadAccelEnrichmentThreshold = 1;
	engineConfiguration->engineLoadAccelEnrichmentMultiplier = 0.25;

	engineConfiguration->tpsAccelLength = 12;
	engineConfiguration->tpsAccelEnrichmentThreshold = 10;
	engineConfiguration->tpsAccelEnrichmentMultiplier = 0.06;


// todo	engineConfiguration->afr.hwChannel = EFI_ADC_3;
	setEgoSensor(ES_Innovate_MTX_L PASS_ENGINE_PARAMETER);


//#if EFI_FSIO || defined(__DOXYGEN__)
//	// backup main relay pin
//	setFsio(0, GPIOE_6, "1" PASS_ENGINE_PARAMETER);
//#endif

	engineConfiguration->externalKnockSenseAdc = EFI_ADC_4;
}
