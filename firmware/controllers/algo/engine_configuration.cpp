/**
 * @file	engine_configuration.cpp
 * @brief	Utility method related to the engine configuration data structure.
 *
 * @date Nov 22, 2013
 * @author Andrey Belomutskiy, (c) 2012-2016
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
 *
 */

#include "main.h"
#include "engine_configuration.h"
#include "fsio_impl.h"
#include "allsensors.h"
#include "interpolation.h"
#include "trigger_decoder.h"
#include "engine_math.h"
#include "speed_density.h"
#include "advance_map.h"
#if EFI_PROD_CODE || defined(__DOXYGEN__)
#include "electronic_throttle.h"
#include "idle_thread.h"
#include "alternatorController.h"
#endif

#include "hip9011_lookup.h"

#include "custom_engine.h"
#include "acura_rsx.h"
#include "audi_aan.h"
#include "bmw_e34.h"
#include "dodge_neon.h"
#include "ford_aspire.h"
#include "ford_fiesta.h"
#include "ford_1995_inline_6.h"
#include "snow_blower.h"
#include "nissan_primera.h"
#include "honda_accord.h"
#include "GY6_139QMB.h"
#include "mazda_miata_nb.h"
#include "mazda_323.h"
#include "mazda_626.h"
#include "saturn_ion.h"
#include "MiniCooperR50.h"
#include "mazda_miata.h"
#include "citroenBerlingoTU3JP.h"
#include "rover_v8.h"
#include "mitsubishi.h"
#include "subaru.h"
#include "test_engine.h"
#include "sachs.h"
#include "gm_2_2.h"
#include "dodge_ram.h"
#include "vw.h"
#include "dodge_stratus.h"
#include "daihatsu.h"
#include "chevrolet_camaro_4.h"
#include "suzuki_vitara.h"
#include "chevrolet_c20_1973.h"
#include "toyota_jzs147.h"
#include "ford_festiva.h"
#include "lada_kalina.h"

EXTERN_ENGINE;

#if EFI_TUNER_STUDIO || defined(__DOXYGEN__)
#include "tunerstudio.h"
#endif

//#define TS_DEFAULT_SPEED 115200
#define TS_DEFAULT_SPEED 38400

#define xxxxx 0

static fuel_table_t alphaNfuel = {
		{/*0  engineLoad=0.00*/   /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*1  engineLoad=6.66*/   /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*2  engineLoad=13.33*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*3  engineLoad=20.00*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*4  engineLoad=26.66*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*5  engineLoad=33.33*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*6  engineLoad=40.00*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*7  engineLoad=46.66*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*8  engineLoad=53.33*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*9  engineLoad=60.00*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*10 engineLoad=66.66*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*11 engineLoad=73.33*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*12 engineLoad=80.00*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*13 engineLoad=86.66*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*14 engineLoad=93.33*/  /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx},
		{/*15 engineLoad=100.00*/ /*0 800.0*/xxxxx, /*1 1213.0*/xxxxx, /*2 1626.0*/xxxxx, /*3 2040.0*/xxxxx, /*4 2453.0*/xxxxx, /*5 2866.0*/xxxxx, /*6 3280.0*/xxxxx, /*7 3693.0*/xxxxx, /*8 4106.0*/xxxxx, /*9 4520.0*/xxxxx, /*10 4933.0*/xxxxx, /*11 5346.0*/xxxxx, /*12 5760.0*/xxxxx, /*13 6173.0*/xxxxx, /*14 6586.0*/xxxxx, /*15 7000.0*/xxxxx}
		};

static volatile int globalConfigurationVersion = 0;

/**
 * This counter is incremented every time user adjusts ECU parameters online (either via dev console or other
 * tuning software)
 */
int getGlobalConfigurationVersion(void) {
	return globalConfigurationVersion;
}

void incrementGlobalConfigurationVersion(void) {
	globalConfigurationVersion++;
}

/**
 * @brief Sets the same dwell time across the whole getRpm() range
 */
void setConstantDwell(floatms_t dwellMs DECLARE_ENGINE_PARAMETER_S) {
	for (int i = 0; i < DWELL_CURVE_SIZE; i++) {
		engineConfiguration->sparkDwellBins[i] = 1000 * i;
		engineConfiguration->sparkDwell[i] = dwellMs;
	}
}

void setMap(fuel_table_t table, float value) {
	for (int l = 0; l < FUEL_LOAD_COUNT; l++) {
		for (int rpmIndex = 0; rpmIndex < FUEL_RPM_COUNT; rpmIndex++) {
			table[l][rpmIndex] = value;
		}
	}
}

static void setWholeVEMap(float value DECLARE_ENGINE_PARAMETER_S) {
	setMap(config->veTable, value);
}

void setWholeFuelMap(float value DECLARE_ENGINE_PARAMETER_S) {
	setMap(config->fuelTable, value);
}

void setWholeIgnitionIatCorr(float value DECLARE_ENGINE_PARAMETER_S) {
	setMap(config->ignitionIatCorrTable, value);
}

void setFuelTablesLoadBin(float minValue, float maxValue DECLARE_ENGINE_PARAMETER_S) {
	setTableBin2(config->injPhaseLoadBins, FUEL_LOAD_COUNT, minValue, maxValue, 1);
	setTableBin2(config->veLoadBins, FUEL_LOAD_COUNT, minValue, maxValue, 1);
	setTableBin2(config->afrLoadBins, FUEL_LOAD_COUNT, minValue, maxValue, 1);
}

void setTimingMap(ignition_table_t map, float value) {
	for (int l = 0; l < IGN_LOAD_COUNT; l++) {
		for (int r = 0; r < IGN_RPM_COUNT; r++) {
			map[l][r] = value;
		}
	}
}

void setWholeIatCorrTimingTable(float value DECLARE_ENGINE_PARAMETER_S) {
	setTimingMap(config->ignitionIatCorrTable, value);
}

/**
 * See also crankingTimingAngle
 */
void setWholeTimingTable(angle_t value DECLARE_ENGINE_PARAMETER_S) {
	setTimingMap(config->ignitionTable, value);
}

static void initTemperatureCurve(int size, float *bins, float *values, float defaultValue) {
	for (int i = 0; i < size; i++) {
		bins[i] = -40 + i * 10;
		values[i] = defaultValue; // this correction is a multiplier
	}
}

void prepareVoidConfiguration(engine_configuration_s *activeConfiguration) {
	memset(activeConfiguration, 0, sizeof(engine_configuration_s));
	board_configuration_s *boardConfiguration = &activeConfiguration->bc;

	boardConfiguration->triggerInputPins[0] = GPIO_UNASSIGNED;
	boardConfiguration->triggerInputPins[1] = GPIO_UNASSIGNED;
	boardConfiguration->triggerInputPins[2] = GPIO_UNASSIGNED;

	for (int i = 0; i < JOYSTICK_PIN_COUNT; i++) {
		boardConfiguration->joystickPins[i] = GPIO_UNASSIGNED;
	}

	boardConfiguration->acRelayPin = GPIO_UNASSIGNED;
	boardConfiguration->acRelayPinMode = OM_DEFAULT;

#if EFI_PROD_CODE || defined(__DOXYGEN__)
	setDefaultAlternatorParameters();
#endif
#if EFI_ELECTRONIC_THROTTLE_BODY || defined(__DOXYGEN__)
	setDefaultEtbParameters();
#endif
#if EFI_IDLE_CONTROL || defined(__DOXYGEN__)
	setDefaultIdleParameters();
#endif
	boardConfiguration->wboHeaterPin = GPIO_UNASSIGNED;
	boardConfiguration->wboPumpPin = GPIO_UNASSIGNED;

	boardConfiguration->mainRelayPin = GPIO_UNASSIGNED;
	boardConfiguration->mainRelayPinMode = OM_DEFAULT;
	boardConfiguration->idle.solenoidPin = GPIO_UNASSIGNED;
	boardConfiguration->idle.solenoidPinMode = OM_DEFAULT;
	boardConfiguration->fuelPumpPin = GPIO_UNASSIGNED;
	boardConfiguration->fuelPumpPinMode = OM_DEFAULT;
	boardConfiguration->etbControlPin1 = GPIO_UNASSIGNED;
	boardConfiguration->etbControlPin2 = GPIO_UNASSIGNED;
	boardConfiguration->etbDirectionPin1 = GPIO_UNASSIGNED;
	boardConfiguration->etbDirectionPin2 = GPIO_UNASSIGNED;
	boardConfiguration->o2heaterPin = GPIO_UNASSIGNED;

	boardConfiguration->tachOutputPin = GPIO_UNASSIGNED;

	boardConfiguration->malfunctionIndicatorPin = GPIO_UNASSIGNED;
	boardConfiguration->malfunctionIndicatorPinMode = OM_DEFAULT;

	boardConfiguration->fanPin = GPIO_UNASSIGNED;
	boardConfiguration->fanPinMode = OM_DEFAULT;

	boardConfiguration->clutchDownPin = GPIO_UNASSIGNED;
	boardConfiguration->clutchDownPinMode = PI_PULLUP;
	boardConfiguration->clutchUpPin = GPIO_UNASSIGNED;
	boardConfiguration->clutchUpPinMode = PI_PULLUP;

	for (int i = 0;i < INJECTION_PIN_COUNT;i++) {
		boardConfiguration->injectionPins[i] = GPIO_UNASSIGNED;
	}
	boardConfiguration->injectionPinMode = OM_DEFAULT;

	for (int i = 0;i < IGNITION_PIN_COUNT;i++) {
		boardConfiguration->ignitionPins[i] = GPIO_UNASSIGNED;
	}
	boardConfiguration->ignitionPinMode = OM_DEFAULT;
}

void setDefaultBasePins(DECLARE_ENGINE_PARAMETER_F) {
	engineConfiguration->fatalErrorPin = GPIOD_14;
	engineConfiguration->warninigPin = GPIOD_13;
	engineConfiguration->configResetPin = GPIOB_1;
}

// todo: move injector calibration somewhere else?
// todo: add a enum? if we have enough data?
static void setBosch02880155868(DECLARE_ENGINE_PARAMETER_F) {
	// http://www.boschdealer.com/specsheets/0280155868cs.jpg
	engineConfiguration->injector.battLagCorrBins[0] = 6;
	engineConfiguration->injector.battLagCorr[0] = 3.371;

	engineConfiguration->injector.battLagCorrBins[1] = 8;
	engineConfiguration->injector.battLagCorr[1] = 1.974;

	engineConfiguration->injector.battLagCorrBins[2] = 10;
	engineConfiguration->injector.battLagCorr[2] = 1.383;

	engineConfiguration->injector.battLagCorrBins[3] = 11;
	engineConfiguration->injector.battLagCorr[3] = 1.194;

	engineConfiguration->injector.battLagCorrBins[4] = 12;
	engineConfiguration->injector.battLagCorr[4] = 1.04;

	engineConfiguration->injector.battLagCorrBins[5] = 13;
	engineConfiguration->injector.battLagCorr[5] = 0.914;

	engineConfiguration->injector.battLagCorrBins[6] = 14;
	engineConfiguration->injector.battLagCorr[6] = 0.797;

	engineConfiguration->injector.battLagCorrBins[7] = 15;
	engineConfiguration->injector.battLagCorr[7] = 0.726;
}

/**
 * @brief	Global default engine configuration
 * This method sets the global engine configuration defaults. These default values are then
 * overridden by engine-specific defaults and the settings are saved in flash memory.
 *
 * This method is invoked only when new configuration is needed:
 *  * recently re-flashed chip
 *  * flash version of configuration failed CRC check or appears to be older then FLASH_DATA_VERSION
 *  * 'rewriteconfig' command
 *  * 'set_engine_type X' command
 *
 * This method should only change the state of the configuration data structure but should NOT change the state of
 * anything else.
 */
void setDefaultConfiguration(DECLARE_ENGINE_PARAMETER_F) {
#if (! EFI_UNIT_TEST) || defined(__DOXYGEN__)
	memset(&persistentState.persistentConfiguration, 0, sizeof(persistentState.persistentConfiguration));
#endif
	prepareVoidConfiguration(engineConfiguration);

	boardConfiguration->mafSensorType = Bosch0280218037;
	setBosch0280218037(config);

	boardConfiguration->startConsoleInBinaryMode = true;

	engineConfiguration->injector.lag = 0.0;
	setBosch02880155868(PASS_ENGINE_PARAMETER_F);

	engineConfiguration->acCutoffLowRpm = 700;
	engineConfiguration->acCutoffHighRpm = 5000;

	initTemperatureCurve(IAT_CURVE_SIZE, config->iatFuelCorrBins, config->iatFuelCorr, 1);

	engineConfiguration->tachPulseDuractionMs = 4;
	engineConfiguration->tachPulseTriggerIndex = 4;

	initTemperatureCurve(CLT_CURVE_SIZE, config->cltIdleCorrBins, config->cltIdleCorr, PERCENT_MULT);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, -40, 150);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, -30, 150);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, -20, 142);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, -10, 136);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 0, 128);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 10, 119);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 20, 112);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 30, 110);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 40, 106);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 50, 106);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 60, 103);
	setTableValue(config->cltIdleCorrBins, config->cltIdleCorr, CLT_CURVE_SIZE, 70, 101);


	initTemperatureCurve(CLT_CURVE_SIZE, config->cltFuelCorrBins, config->cltFuelCorr, PERCENT_MULT);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, -40, 150);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, -30, 150);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, -20, 142);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, -10, 136);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 0, 128);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 10, 119);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 20, 112);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 30, 110);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 40, 106);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 50, 106);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 60, 103);
	setTableValue(config->cltFuelCorrBins, config->cltFuelCorr, CLT_CURVE_SIZE, 70, 101);

	setConstantDwell(4 PASS_ENGINE_PARAMETER); // 4ms is global default dwell
	engineConfiguration->useConstantDwellDuringCranking = false;

	setFuelLoadBin(1.2, 4.4 PASS_ENGINE_PARAMETER);
	setFuelRpmBin(800, 7000 PASS_ENGINE_PARAMETER);
	setTimingLoadBin(1.2, 4.4 PASS_ENGINE_PARAMETER);
	setTimingRpmBin(800, 7000 PASS_ENGINE_PARAMETER);

	setTableBin2(engineConfiguration->map.samplingAngleBins, MAP_ANGLE_SIZE, 800, 7000, 1);
	setTableBin2(engineConfiguration->map.samplingAngle, MAP_ANGLE_SIZE, 100, 130, 1);
	setTableBin2(engineConfiguration->map.samplingWindowBins, MAP_ANGLE_SIZE, 800, 7000, 1);
	setTableBin2(engineConfiguration->map.samplingWindow, MAP_ANGLE_SIZE, 50, 50, 1);

	// set_whole_timing_map 3
	setWholeFuelMap(3 PASS_ENGINE_PARAMETER);
	setMap(config->afrTable, 14.7);

	setDefaultVETable(PASS_ENGINE_PARAMETER_F);

	setMap(config->injectionPhase, -180);
	setRpmTableBin(config->injPhaseRpmBins, FUEL_RPM_COUNT);
	setFuelTablesLoadBin(10, 160 PASS_ENGINE_PARAMETER);
	setDefaultIatTimingCorrection(PASS_ENGINE_PARAMETER_F);

	setTableBin2(config->fsioTable1LoadBins, FSIO_TABLE_8, 20, 120, 10);
	setRpmTableBin(config->fsioTable1RpmBins, FSIO_TABLE_8);
	setTableBin2(config->fsioTable2LoadBins, FSIO_TABLE_8, 20, 120, 10);
	setRpmTableBin(config->fsioTable2RpmBins, FSIO_TABLE_8);

	initEngineNoiseTable(PASS_ENGINE_PARAMETER_F);

	setThermistorConfiguration(&engineConfiguration->clt, 0, 9500, 23.8889, 2100, 48.8889, 1000);
	engineConfiguration->clt.config.bias_resistor = 1500;

	setThermistorConfiguration(&engineConfiguration->iat, 32, 9500, 75, 2100, 120, 1000);
// todo: this value is way off! I am pretty sure temp coeffs are off also
	engineConfiguration->iat.config.bias_resistor = 2700;


	engineConfiguration->step1rpm = 3000;
 	engineConfiguration->step1timing = 10;
	engineConfiguration->step1RpmWindow = 500;
	engineConfiguration->step1fuelCutEnable = false;
	engineConfiguration->step1SparkCutEnable = false;
	engineConfiguration->step1RpmWindow = 500;

	engineConfiguration->slowAdcAlpha = 1;
	engineConfiguration->engineSnifferRpmThreshold = 2500;
	engineConfiguration->sensorSnifferRpmThreshold = 2500;
	engineConfiguration->rpmHardLimit = 7000;
	engineConfiguration->cranking.rpm = 550;
	engineConfiguration->cutFuelOnHardLimit = true;
	engineConfiguration->cutSparkOnHardLimit = true;

	engineConfiguration->noAccelAfterHardLimitPeriodSecs = 3;

	setTableBin2(engineConfiguration->crankingTpsCoef, CRANKING_CURVE_SIZE, 1, 1, 1);
	setTableBin2(engineConfiguration->crankingTpsBins, CRANKING_CURVE_SIZE, 0, 100, 1);

	config->crankingFuelCoef[0] = 5; // base cranking fuel adjustment coefficient
	config->crankingFuelBins[0] = -20; // temperature in C
	config->crankingFuelCoef[1] = 3.7;
	config->crankingFuelBins[1] = -10;
	config->crankingFuelCoef[2] = 2.6;
	config->crankingFuelBins[2] = 5;
	config->crankingFuelCoef[3] = 2.4;
	config->crankingFuelBins[3] = 20;
	config->crankingFuelCoef[4] = 2.1;
	config->crankingFuelBins[4] = 35;
	config->crankingFuelCoef[5] = 1.8;
	config->crankingFuelBins[5] = 50;
	config->crankingFuelCoef[6] = 1.5;
	config->crankingFuelBins[6] = 65;
	config->crankingFuelCoef[7] = 1;
	config->crankingFuelBins[7] = 90;

	config->crankingCycleCoef[0] = 2;
	config->crankingCycleBins[0] = 10;
	config->crankingCycleCoef[1] = 1;
	config->crankingCycleBins[1] = 31;
	config->crankingCycleCoef[2] = 1;
	config->crankingCycleBins[2] = 52;
	config->crankingCycleCoef[3] = 0.5;
	config->crankingCycleBins[3] = 73;
	config->crankingCycleCoef[4] = 0.5;
	config->crankingCycleBins[4] = 74;
	config->crankingCycleCoef[5] = 0.5;
	config->crankingCycleBins[5] = 75;
	config->crankingCycleCoef[6] = 0.5;
	config->crankingCycleBins[6] = 76;
	config->crankingCycleCoef[7] = 0.5;
	config->crankingCycleBins[7] = 77;


	engineConfiguration->warmupTargetAfrBins[0] = -12;
	engineConfiguration->warmupTargetAfr[0] = 12.3;
	engineConfiguration->warmupTargetAfrBins[1] = 0;
	engineConfiguration->warmupTargetAfr[1] = 13;
	engineConfiguration->warmupTargetAfrBins[2] = 30;
	engineConfiguration->warmupTargetAfr[2] = 13.8;
	engineConfiguration->warmupTargetAfrBins[3] = 60;
	engineConfiguration->warmupTargetAfr[3] = 14.5;

	// todo: set bins
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, -30, 1350);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, -20, 1300);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, -10, 1200);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 0, 1150);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 10, 1100);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 20, 1050);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 30, 1000);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 40, 1000);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 50, 950);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 60, 950);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 70, 930);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 80, 900);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 90, 900);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 100, 1000);
	setTableValue(engineConfiguration->cltIdleRpmBins, engineConfiguration->cltIdleRpm, CLT_CURVE_SIZE, 110, 1100);

	engineConfiguration->cranking.baseFuel = 5;

	engineConfiguration->analogInputDividerCoefficient = 2;

	engineConfiguration->crankingChargeAngle = 70;
	engineConfiguration->timingMode = TM_DYNAMIC;
	engineConfiguration->fixedModeTiming = 50;

	// performance optimization
	boardConfiguration->sensorChartMode = SC_OFF;

	engineConfiguration->map.sensor.hwChannel = EFI_ADC_4;
	engineConfiguration->baroSensor.hwChannel = EFI_ADC_NONE;

	engineConfiguration->pedalPositionChannel = EFI_ADC_NONE;

	engineConfiguration->specs.firingOrder = FO_1_THEN_3_THEN_4_THEN2;
	engineConfiguration->crankingInjectionMode = IM_SIMULTANEOUS;
	engineConfiguration->injectionMode = IM_SEQUENTIAL;

	engineConfiguration->ignitionMode = IM_ONE_COIL;
	engineConfiguration->globalTriggerAngleOffset = 0;
	engineConfiguration->injectionOffset = 0;
	engineConfiguration->ignitionOffset = 0;
	engineConfiguration->overrideCrankingIgnition = true;
	engineConfiguration->sensorChartFrequency = 20;

	engineConfiguration->algorithm = LM_PLAIN_MAF;

	engineConfiguration->vbattDividerCoeff = ((float) (15 + 65)) / 15;

	engineConfiguration->fanOnTemperature = 75;
	engineConfiguration->fanOffTemperature = 70;

	engineConfiguration->tpsMin = convertVoltageTo10bitADC(1.250);
	engineConfiguration->tpsMax = convertVoltageTo10bitADC(4.538);
	engineConfiguration->tpsErrorDetectionTooLow = -10; // -10% open
	engineConfiguration->tpsErrorDetectionTooHigh = 110; // 110% open

	engineConfiguration->canNbcType = CAN_BUS_NBC_BMW;
	engineConfiguration->canSleepPeriod = 50;
	engineConfiguration->canReadEnabled = true;
	engineConfiguration->canWriteEnabled = false;

	setOperationMode(engineConfiguration, FOUR_STROKE_CAM_SENSOR);
	engineConfiguration->specs.cylindersCount = 4;
	engineConfiguration->specs.displacement = 2;
	/**
	 * By the way http://users.erols.com/srweiss/tableifc.htm has a LOT of data
	 */
	engineConfiguration->injector.flow = 200;

	engineConfiguration->displayMode = DM_HD44780;

	engineConfiguration->logFormat = LF_NATIVE;
	engineConfiguration->directSelfStimulation = false;

	engineConfiguration->trigger.type = TT_TOOTHED_WHEEL_60_2;

	engineConfiguration->HD44780width = 20;
	engineConfiguration->HD44780height = 4;

	engineConfiguration->vRefAdcChannel = EFI_ADC_NONE;
	engineConfiguration->vbattAdcChannel = EFI_ADC_NONE;
	engineConfiguration->clt.adcChannel = EFI_ADC_6;
	engineConfiguration->iat.adcChannel = EFI_ADC_7;
	engineConfiguration->mafAdcChannel = EFI_ADC_NONE;
	engineConfiguration->afr.hwChannel = EFI_ADC_14;

	engineConfiguration->cylinderBore = 87.5;

	setEgoSensor(ES_14Point7_Free PASS_ENGINE_PARAMETER);

	engineConfiguration->globalFuelCorrection = 1;

	engineConfiguration->map.sensor.type = MT_MPX4250;

	engineConfiguration->baroSensor.type = MT_CUSTOM;
	engineConfiguration->baroSensor.valueAt0 = 0;
	engineConfiguration->baroSensor.valueAt5 = 500;

	engineConfiguration->hasMapSensor = true;
	engineConfiguration->hasMafSensor = true;
	engineConfiguration->hasTpsSensor = true;
	engineConfiguration->hasAfrSensor = true;
	engineConfiguration->hasIatSensor = true;
	engineConfiguration->hasCltSensor = true;
	engineConfiguration->hasBaroSensor = false;
	engineConfiguration->isEngineChartEnabled = true;

	engineConfiguration->useOnlyRisingEdgeForTrigger = false;

	boardConfiguration->idle.solenoidFrequency = 200;
	// set_idle_position 50
	boardConfiguration->manIdlePosition = 50;
	engineConfiguration->targetIdleRpm = 1200;
//	engineConfiguration->idleMode = IM_AUTO;
	engineConfiguration->idleMode = IM_MANUAL;

	engineConfiguration->acSwitchAdc = EFI_ADC_NONE;

	engineConfiguration->externalKnockSenseAdc = EFI_ADC_NONE;

	boardConfiguration->useSerialPort = true;
	boardConfiguration->useStepperIdle = false;

	boardConfiguration->idle.stepperDirectionPin = GPIOE_10;
	boardConfiguration->idle.stepperStepPin = GPIOE_12;
	engineConfiguration->stepperEnablePin = GPIOE_14;
	engineConfiguration->idleStepperReactionTime = 10;
	engineConfiguration->idleStepperTotalSteps = 150;

#if EFI_PROD_CODE || defined(__DOXYGEN__)
	engineConfiguration->engineChartSize = 300;
#else
	// need more events for automated test
	engineConfiguration->engineChartSize = 400;
#endif

	engineConfiguration->primingSquirtDurationMs = 5;

	engineConfiguration->isInjectionEnabled = true;
	engineConfiguration->isIgnitionEnabled = true;
	engineConfiguration->isCylinderCleanupEnabled = true;
	engineConfiguration->secondTriggerChannelEnabled = true;

	engineConfiguration->isMapAveragingEnabled = true;
	engineConfiguration->isMilEnabled = true;
	engineConfiguration->isFuelPumpEnabled = true;
	engineConfiguration->isTunerStudioEnabled = true;
	engineConfiguration->isWaveAnalyzerEnabled = true;
	engineConfiguration->isIdleThreadEnabled = true;

	engineConfiguration->debugMode = ALTERNATOR;

	engineConfiguration->acIdleRpmBump = 200;
	engineConfiguration->knockDetectionWindowStart = 35;
	engineConfiguration->knockDetectionWindowEnd = 135;

	engineConfiguration->fuelLevelSensor = EFI_ADC_NONE;
	boardConfiguration->fuelLevelEmptyTankVoltage = 0;
	boardConfiguration->fuelLevelFullTankVoltage = 5;

	engineConfiguration->hipOutputChannel = EFI_ADC_NONE;

	/**
	 * this is RPM. 10000 rpm is only 166Hz, 800 rpm is 13Hz
	 */
	boardConfiguration->triggerSimulatorFrequency = 1200;

	boardConfiguration->triggerErrorPin = GPIO_UNASSIGNED;

	boardConfiguration->max31855spiDevice = SPI_NONE;
	for (int i = 0; i < EGT_CHANNEL_COUNT; i++) {
		boardConfiguration->max31855_cs[i] = GPIO_UNASSIGNED;
	}
	for (int i = 0; i < LE_COMMAND_COUNT; i++) {
		boardConfiguration->fsioPins[i] = GPIO_UNASSIGNED;
		config->le_formulas[i][0] = 0;
		boardConfiguration->fsioDigitalInputs[i] = GPIO_UNASSIGNED;
		engineConfiguration->fsioInputModes[i] = PI_DEFAULT;
	}

	engineConfiguration->communicationPin = GPIOD_15;
	engineConfiguration->runningPin = GPIOD_12;
	setDefaultBasePins(PASS_ENGINE_PARAMETER_F);
	engineConfiguration->binarySerialTxPin = GPIOC_10;
	engineConfiguration->binarySerialRxPin = GPIOC_11;
	engineConfiguration->consoleSerialTxPin = GPIOC_10;
	engineConfiguration->consoleSerialRxPin = GPIOC_11;


	boardConfiguration->triggerSimulatorPins[0] = GPIOD_1;
	boardConfiguration->triggerSimulatorPins[1] = GPIOD_2;
	boardConfiguration->triggerSimulatorPins[2] = GPIO_UNASSIGNED;

	boardConfiguration->triggerSimulatorPinModes[0] = OM_DEFAULT;
	boardConfiguration->triggerSimulatorPinModes[1] = OM_DEFAULT;
	boardConfiguration->triggerSimulatorPinModes[2] = OM_DEFAULT;

	setFrankenstein_01_LCD(boardConfiguration);

	strcpy(config->timingMultiplier, "1");
	strcpy(config->timingAdditive, "0");

	engineConfiguration->hip9011SpiDevice = SPI_DEVICE_2;

	engineConfiguration->isAlternatorControlEnabled = true;

	engineConfiguration->isGpsEnabled = false;
	boardConfiguration->gps_rx_pin = GPIOB_7;
	boardConfiguration->gps_tx_pin = GPIOB_6;

	boardConfiguration->triggerInputPins[0] = GPIOC_6;
	boardConfiguration->triggerInputPins[1] = GPIOA_5;
	boardConfiguration->logicAnalyzerPins[0] = GPIO_UNASSIGNED;
	boardConfiguration->logicAnalyzerPins[1] = GPIO_UNASSIGNED; // GPIOE_5 is a popular option (if available)
	boardConfiguration->logicAnalyzerPins[2] = GPIO_UNASSIGNED;
	boardConfiguration->logicAnalyzerPins[3] = GPIO_UNASSIGNED;
	boardConfiguration->vehicleSpeedSensorInputPin = GPIO_UNASSIGNED;
	engineConfiguration->vehicleSpeedCoef = 1.0f;

	boardConfiguration->logicAnalyzerMode[0] = false;
	boardConfiguration->logicAnalyzerMode[1] = false;

	engineConfiguration->mapErrorDetectionTooLow = 5;
	engineConfiguration->mapErrorDetectionTooHigh = 250;

	boardConfiguration->idleThreadPeriod = 100;
	boardConfiguration->consoleLoopPeriod = 200;
	boardConfiguration->lcdThreadPeriod = 300;
	boardConfiguration->generalPeriodicThreadPeriod = 50;
	boardConfiguration->useLcdScreen = true;

	boardConfiguration->boardTestModeJumperPin = GPIOB_0;

	boardConfiguration->canDeviceMode = CD_USE_CAN2;
	boardConfiguration->canTxPin = GPIOB_6;
	boardConfiguration->canRxPin = GPIOB_12;

	// set this to SPI_DEVICE_3 to enable stimulation
	boardConfiguration->digitalPotentiometerSpiDevice = SPI_NONE;
	boardConfiguration->digitalPotentiometerChipSelect[0] = GPIOD_7;
	boardConfiguration->digitalPotentiometerChipSelect[1] = GPIO_UNASSIGNED;
	boardConfiguration->digitalPotentiometerChipSelect[2] = GPIOD_5;
	boardConfiguration->digitalPotentiometerChipSelect[3] = GPIO_UNASSIGNED;

	boardConfiguration->is_enabled_spi_1 = false;
	boardConfiguration->is_enabled_spi_2 = false;
	boardConfiguration->is_enabled_spi_3 = true;

	boardConfiguration->spi1mosiPin = GPIOB_5;
	boardConfiguration->spi1misoPin = GPIOB_4;
	boardConfiguration->spi1sckPin = GPIOB_3; // please note that this pin is also SWO/SWD - Single Wire debug Output

	boardConfiguration->spi2mosiPin = GPIOB_15;
	boardConfiguration->spi2misoPin = GPIOB_14;
	boardConfiguration->spi2sckPin = GPIOB_13;

	boardConfiguration->spi3mosiPin = GPIOB_5;
	boardConfiguration->spi3misoPin = GPIOB_4;
	boardConfiguration->spi3sckPin = GPIOB_3;

	boardConfiguration->hip9011Gain = 1;

	boardConfiguration->sdCardCsPin = GPIOD_4;
	boardConfiguration->isSdCardEnabled = true;
	boardConfiguration->isFastAdcEnabled = true;
	boardConfiguration->isEngineControlEnabled = true;

	boardConfiguration->isVerboseAlternator = false;

	boardConfiguration->tunerStudioSerialSpeed = TS_DEFAULT_SPEED;
	engineConfiguration->uartConsoleSerialSpeed = 115200;

	engineConfiguration->warmupAfrPid.offset = 1;
	engineConfiguration->warmupAfrThreshold = 60;

	engineConfiguration->engineLoadAccelLength = 6;
	engineConfiguration->engineLoadAccelEnrichmentThreshold = 5; // kPa
	engineConfiguration->engineLoadAccelEnrichmentMultiplier = 2;

	engineConfiguration->tpsAccelLength = 12;
	engineConfiguration->tpsAccelEnrichmentThreshold = 40; // TPS % change, per engine cycle
	engineConfiguration->tpsAccelEnrichmentMultiplier = 0.05;
}

void resetConfigurationExt(Logging * logger, engine_type_e engineType DECLARE_ENGINE_PARAMETER_S) {
	/**
	 * Let's apply global defaults first
	 */
	setDefaultConfiguration(PASS_ENGINE_PARAMETER_F);
#if EFI_SIMULATOR || defined(__DOXYGEN__)
	engineConfiguration->directSelfStimulation = true;
#endif /* */
	engineConfiguration->engineType = engineType;

	/**
	 * And override them with engine-specific defaults
	 */
	switch (engineType) {
	case CUSTOM_ENGINE:
		setCustomEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case ACURA_RSX:
		setAcuraRSX(engineConfiguration);
		break;
#if EFI_SUPPORT_DODGE_NEON || defined(__DOXYGEN__)
	case DODGE_NEON_1995:
		setDodgeNeon1995EngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case DODGE_NEON_2003:
		setDodgeNeonNGCEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case LADA_KALINA:
		setLadaKalina(PASS_ENGINE_PARAMETER_F);
		break;

#endif /* EFI_SUPPORT_DODGE_NEON */
#if EFI_SUPPORT_FORD_ASPIRE || defined(__DOXYGEN__)
	case FORD_ASPIRE_1996:
		setFordAspireEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
#endif /* EFI_SUPPORT_FORD_ASPIRE */
#if EFI_SUPPORT_FORD_FIESTA || defined(__DOXYGEN__)
	case FORD_FIESTA:
		setFordFiestaDefaultEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
#endif /* EFI_SUPPORT_FORD_FIESTA */
#if EFI_SUPPORT_NISSAN_PRIMERA || defined(__DOXYGEN__)
	case NISSAN_PRIMERA:
		setNissanPrimeraEngineConfiguration(engineConfiguration);
		break;
#endif
	case HONDA_ACCORD_CD:
		setHondaAccordConfigurationThreeWires(PASS_ENGINE_PARAMETER_F);
		break;
	case HONDA_ACCORD_CD_TWO_WIRES:
		setHondaAccordConfiguration1_24(PASS_ENGINE_PARAMETER_F);
		break;
	case HONDA_ACCORD_CD_DIP:
		setHondaAccordConfigurationDip(PASS_ENGINE_PARAMETER_F);
		break;
	case MITSU_4G93:
		setMitsubishiConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
#if EFI_SUPPORT_1995_FORD_INLINE_6 || defined(__DOXYGEN__)
	case FORD_INLINE_6_1995:
		setFordInline6(PASS_ENGINE_PARAMETER_F);
		break;
#endif /* EFI_SUPPORT_1995_FORD_INLINE_6 */
	case GY6_139QMB:
		setGy6139qmbDefaultEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case MAZDA_MIATA_NB:
		setMazdaMiataNbEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case MAZDA_323:
		setMazda323EngineConfiguration(engineConfiguration);
		break;
	case MAZDA_626:
		setMazda626EngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case SATURN_ION_2004:
		setSaturnIonEngineConfiguration(engineConfiguration);
		break;
	case SUZUKI_VITARA:
		setSuzukiVitara(PASS_ENGINE_PARAMETER_F);
		break;
	case MINI_COOPER_R50:
		setMiniCooperR50(engineConfiguration);
		break;
	case FORD_ESCORT_GT:
		setFordEscortGt(PASS_ENGINE_PARAMETER_F);
		break;
	case MIATA_1990:
		setMiata1990(PASS_ENGINE_PARAMETER_F);
		break;
	case MIATA_1994_DEVIATOR:
		setMiata1994_d(PASS_ENGINE_PARAMETER_F);
		break;
	case MIATA_1994_SPAGS:
		setMiata1994_s(PASS_ENGINE_PARAMETER_F);
		break;
	case MIATA_1996:
		setMiata1996(PASS_ENGINE_PARAMETER_F);
		break;
	case CITROEN_TU3JP:
		setCitroenBerlingoTU3JPConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case ROVER_V8:
		setRoverv8(PASS_ENGINE_PARAMETER_F);
		break;
	case SUBARU_2003_WRX:
		setSubaru2003Wrx(PASS_ENGINE_PARAMETER_F);
		break;
	case BMW_E34:
		setBmwE34(PASS_ENGINE_PARAMETER_F);
		break;
	case GM_2_2:
		setGm2_2(PASS_ENGINE_PARAMETER_F);
		break;
	case DODGE_RAM:
		setDodgeRam1996(PASS_ENGINE_PARAMETER_F);
		break;
	case DODGE_STRATUS:
		setDodgeStratus(PASS_ENGINE_PARAMETER_F);
		break;
	case VW_ABA:
		setVwAba(PASS_ENGINE_PARAMETER_F);
		break;
	case TEST_ENGINE:
		setTestEngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;
	case SACHS:
		setSachs(PASS_ENGINE_PARAMETER_F);
		break;
	case DAIHATSU:
		setDaihatsu(PASS_ENGINE_PARAMETER_F);
		break;
	case CAMARO_4:
		setCamaro4(PASS_ENGINE_PARAMETER_F);
		break;
	case CHEVY_C20_1973:
		set1973c20(PASS_ENGINE_PARAMETER_F);
		break;
	case TOYOTA_JZS147:
		setToyota_jzs147EngineConfiguration(PASS_ENGINE_PARAMETER_F);
		break;

	default:
		warning(OBD_PCM_Processor_Fault, "Unexpected engine type: %d", engineType);
	}
	applyNonPersistentConfiguration(logger PASS_ENGINE_PARAMETER);
	// todo: eliminate triggerShape.operationMode?
	if (engineConfiguration->operationMode != engine->triggerShape.getOperationMode())
		firmwareError("operationMode mismatch");

#if EFI_TUNER_STUDIO
	syncTunerStudioCopy();
#endif
}

engine_configuration2_s::engine_configuration2_s() {
    injectionEvents   = &injectionEvents0;
    processing = &injectionEvents0;    
}

void applyNonPersistentConfiguration(Logging * logger DECLARE_ENGINE_PARAMETER_S) {
#if EFI_PROD_CODE || defined(__DOXYGEN__)
	efiAssertVoid(getRemainingStack(chThdSelf()) > 256, "apply c");
	scheduleMsg(logger, "applyNonPersistentConfiguration()");
#endif

// todo: this would require 'initThermistors() to re-establish a reference, todo: fix
//	memset(engineConfiguration2, 0, sizeof(engine_configuration2_s));
#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)
	engine->triggerShape.initializeTriggerShape(logger PASS_ENGINE_PARAMETER);
#endif
	if (engine->triggerShape.getSize() == 0) {
		firmwareError("triggerShape size is zero");
		return;
	}
	if (engine->triggerShape.getSize() == 0) {
		firmwareError("shaftPositionEventCount is zero");
		return;
	}
	engine->engineCycleEventCount = engine->triggerShape.getLength();
#if EFI_FSIO || defined(__DOXYGEN__)
	applyFsioConfiguration(PASS_ENGINE_PARAMETER_F);
#endif
}

#if EFI_ENGINE_CONTROL || defined(__DOXYGEN__)

void prepareShapes(DECLARE_ENGINE_PARAMETER_F) {
	engine_configuration2_s *engineConfiguration2 = engine->engineConfiguration2;
	prepareOutputSignals(PASS_ENGINE_PARAMETER_F);

	engineConfiguration2->injectionEvents->addFuelEvents(
			engineConfiguration->crankingInjectionMode PASS_ENGINE_PARAMETER);
}

#endif

float getRpmMultiplier(operation_mode_e mode) {
	if (mode == FOUR_STROKE_CAM_SENSOR) {
		return 0.5;
	} else if (mode == FOUR_STROKE_CRANK_SENSOR) {
		return 1;
	}
	return 1;
}

void setOperationMode(engine_configuration_s *engineConfiguration, operation_mode_e mode) {
	engineConfiguration->operationMode = mode;
}

operation_mode_e getOperationMode(engine_configuration_s const *engineConfiguration) {
	return engineConfiguration->operationMode;
}

void commonFrankensoAnalogInputs(engine_configuration_s *engineConfiguration) {
	/**
	 * VBatt
	 */
	engineConfiguration->vbattAdcChannel = EFI_ADC_14;
}

void setFrankenso0_1_joystick(engine_configuration_s *engineConfiguration) {
	engineConfiguration->isJoystickEnabled = true;
	board_configuration_s *boardConfiguration = &engineConfiguration->bc;
	boardConfiguration->joystickCenterPin = GPIOC_8;
	boardConfiguration->joystickAPin = GPIOD_10;
	boardConfiguration->joystickBPin = GPIO_UNASSIGNED;
	boardConfiguration->joystickCPin = GPIO_UNASSIGNED;
	boardConfiguration->joystickDPin = GPIOD_11;
}

void copyFuelTable(fuel_table_t const source, fuel_table_t destination) {
	for (int loadIndex = 0; loadIndex < FUEL_LOAD_COUNT; loadIndex++) {
		for (int rpmIndex = 0; rpmIndex < FUEL_RPM_COUNT; rpmIndex++) {
			destination[loadIndex][rpmIndex] = source[loadIndex][rpmIndex];
		}
	}
}

void copyTimingTable(ignition_table_t const source, ignition_table_t destination) {
	for (int k = 0; k < IGN_LOAD_COUNT; k++) {
		for (int rpmIndex = 0; rpmIndex < IGN_RPM_COUNT; rpmIndex++) {
			destination[k][rpmIndex] = source[k][rpmIndex];
		}
	}
}

