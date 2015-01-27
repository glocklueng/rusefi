#include "rusefi_types.h"

typedef struct {
	/**
	 * offset 0
	 */
	float baseFuel;
	/**
	 * This value controls what RPM values we consider 'cranking' (any RPM below 'crankingRpm')
	 * Anything above 'crankingRpm' would be 'running'
	 * offset 4
	 */
	int16_t rpm;
	/**
	 * need 4 byte alignment
	 * offset 6
	 */
	uint8_t alignmentFill[2];
	/** total size 8*/
} cranking_parameters_s;

typedef struct {
	/**
	 * kPa value at zero volts
	 * offset 0
	 */
	float valueAt0;
	/**
	 * kPa value at 5 volts
	 * offset 4
	 */
	float valueAt5;
	/**
	 * offset 8
	 */
	air_pressure_sensor_type_e type;
	/**
	 * offset 12
	 */
	adc_channel_e hwChannel;
	/** total size 16*/
} air_pressure_sensor_config_s;

/**
 * @brief MAP averaging configuration

 */
typedef struct {
	/**
	 * offset 0
	 */
	float samplingAngleBins[MAP_ANGLE_SIZE];
	/**
	 * @brief MAP averaging sampling start angle, by RPM
	 * offset 32
	 */
	float samplingAngle[MAP_ANGLE_SIZE];
	/**
	 * offset 64
	 */
	float samplingWindowBins[MAP_WINDOW_SIZE];
	/**
	 * @brief MAP averaging angle duration, by RPM
	 * offset 96
	 */
	float samplingWindow[MAP_WINDOW_SIZE];
	/**
	 * offset 128
	 */
	air_pressure_sensor_config_s sensor;
	/** total size 144*/
} MAP_sensor_config_s;

/**
 * @brief Thermistor curve parameters

 */
typedef struct {
	/**
	 * these values are in Celcuus
	 * offset 0
	 */
	float tempC_1;
	/**
	 * offset 4
	 */
	float tempC_2;
	/**
	 * offset 8
	 */
	float tempC_3;
	/**
	 * offset 12
	 */
	float resistance_1;
	/**
	 * offset 16
	 */
	float resistance_2;
	/**
	 * offset 20
	 */
	float resistance_3;
	/**
	 * offset 24
	 */
	float bias_resistor;
	/**
	 * offset 28
	 */
	float s_h_a;
	/**
	 * offset 32
	 */
	float s_h_b;
	/**
	 * offset 36
	 */
	float s_h_c;
	/** total size 40*/
} ThermistorConf;


/**
 * @brief Trigger wheel(s) configuration

 */
typedef struct {
	/**
	 * offset 0
	 */
	trigger_type_e type;
	/**
	 * offset 4
	 */
	int customIsSynchronizationNeeded;
	/**
	 * offset 8
	 */
	int customTotalToothCount;
	/**
	 * offset 12
	 */
	int customSkippedToothCount;
	/**
	 * offset 16
	 */
	float customSyncRatioFrom;
	/**
	 * offset 20
	 */
	float customSyncRatioTo;
	/**
	 * offset 24
	 */
	int customUseRiseEdge;
	/** total size 28*/
} trigger_config_s;

typedef struct {
	/**
	 * offset 0
	*/
	adc_channel_e afrAdcChannel;
	/**
	 * offset 4
	*/
	float v1;
	/**
	 * offset 8
	*/
	float value1;
	/**
	 * offset 12
	*/
	float v2;
	/**
	 * offset 16
	*/
	float value2;
/** total size 20*/
} afr_sensor_s;

typedef struct {
	/**
	 * offset 0
	*/
	brain_pin_e idleValvePin;
	/**
	 * offset 4
	*/
	pin_output_mode_e idleValvePinMode;
	/**
	 * offset 8
	*/
	brain_pin_e fuelPumpPin;
	/**
	 * offset 12
	*/
	pin_output_mode_e fuelPumpPinMode;
	/**
	 * offset 16
	*/
	brain_pin_e injectionPins[INJECTION_PIN_COUNT];
	/**
	 * offset 64
	*/
	pin_output_mode_e injectionPinMode;
	/**
	 * offset 68
	*/
	brain_pin_e ignitionPins[IGNITION_PIN_COUNT];
	/**
	 * offset 116
	*/
	pin_output_mode_e ignitionPinMode;
	/**
	 * offset 120
	*/
	brain_pin_e malfunctionIndicatorPin;
	/**
	 * offset 124
	*/
	pin_output_mode_e malfunctionIndicatorPinMode;
	/**
	 * offset 128
	*/
	brain_pin_e fanPin;
	/**
	 * offset 132
	*/
	pin_output_mode_e fanPinMode;
	/**
	 * offset 136
	*/
	brain_pin_e electronicThrottlePin1;
	/**
	 * offset 140
	*/
	pin_output_mode_e electronicThrottlePin1Mode;
	/**
	 * some cars have a switch to indicate that clutch pedal is all the way down
	 * offset 144
	*/
	brain_pin_e clutchDownPin;
	/**
	 * offset 148
	*/
	pin_input_mode_e clutchDownPinMode;
	/**
	 * offset 152
	*/
	brain_pin_e alternatorControlPin;
	/**
	 * offset 156
	*/
	pin_output_mode_e alternatorControlPinMode;
	/**
	 * offset 160
	*/
	brain_pin_e HD44780_rs;
	/**
	 * offset 164
	*/
	brain_pin_e HD44780_e;
	/**
	 * offset 168
	*/
	brain_pin_e HD44780_db4;
	/**
	 * offset 172
	*/
	brain_pin_e HD44780_db5;
	/**
	 * offset 176
	*/
	brain_pin_e HD44780_db6;
	/**
	 * offset 180
	*/
	brain_pin_e HD44780_db7;
	/**
	 * offset 184
	*/
	brain_pin_e gps_rx_pin;
	/**
	 * offset 188
	*/
	brain_pin_e gps_tx_pin;
	/**
	 * offset 192
	*/
	int idleSolenoidFrequency;
	/**
	 * offset 196
	*/
	int triggerSimulatorFrequency;
	/**
	 * Digital Potentiometer is used by stock ECU stimulation code
	 * offset 200
	*/
	spi_device_e digitalPotentiometerSpiDevice;
	/**
	 * offset 204
	*/
	brain_pin_e digitalPotentiometerChipSelect[DIGIPOT_COUNT];
	/**
	 * offset 220
	*/
	adc_channel_mode_e adcHwChannelEnabled[HW_MAX_ADC_INDEX];
	/**
	 * offset 284
	*/
	brain_pin_e triggerInputPins[3];
	/**
	 * offset 296
	*/
	brain_pin_e mainRelayPin;
	/**
	 * offset 300
	*/
	int idleThreadPeriod;
	/**
	 * offset 304
	*/
	int consoleLoopPeriod;
	/**
	 * offset 308
	*/
	int lcdThreadPeriod;
	/**
	 * offset 312
	*/
	int tunerStudioThreadPeriod;
	/**
	 * offset 316
	*/
	int generalPeriodicThreadPeriod;
	/**
	 * offset 320
	*/
	uint32_t tunerStudioSerialSpeed;
	/**
	 * offset 324
	*/
	brain_pin_e boardTestModeJumperPin;
	/**
	 * offset 328
	*/
	can_device_mode_e canDeviceMode;
	/**
	 * offset 332
	*/
	brain_pin_e canTxPin;
	/**
	 * offset 336
	*/
	brain_pin_e canRxPin;
	/**
	 * offset 340
	*/
	brain_pin_e triggerSimulatorPins[TRIGGER_SIMULATOR_PIN_COUNT];
	/**
	 * offset 352
	*/
	pin_output_mode_e triggerSimulatorPinModes[TRIGGER_SIMULATOR_PIN_COUNT];
	/**
	 * offset 364
	*/
	brain_pin_e o2heaterPin;
	/**
	 * offset 368
	*/
	pin_output_mode_e o2heaterPinModeTodO;

	/** offset 372 bit 0 */
	uint32_t is_enabled_spi_1 : 1;
	/** offset 372 bit 1 */
	uint32_t is_enabled_spi_2 : 1;
	/** offset 372 bit 2 */
	uint32_t is_enabled_spi_3 : 1;
	/** offset 372 bit 3 */
	uint32_t isSdCardEnabled : 1;
	/** offset 372 bit 4 */
	uint32_t isFastAdcEnabled : 1;
	/** offset 372 bit 5 */
	uint32_t isEngineControlEnabled : 1;
	/** offset 372 bit 6 */
	uint32_t isHip9011Enabled : 1;
	/**
	 * offset 376
	*/
	brain_pin_e logicAnalyzerPins[LOGIC_ANALYZER_CHANNEL_COUNT];
	/**
	 * default or inverted input
	 * offset 392
	*/
	uint8_t logicAnalyzerMode[LOGIC_ANALYZER_CHANNEL_COUNT];
	/**
	 * offset 396
	*/
	int unrealisticRpmThreashold;
	/**
	 * offset 400
	*/
	pin_output_mode_e mainRelayPinMode;
	/**
	 * offset 404
	*/
	egt_cs_array_t max31855_cs;
	/**
	 * offset 408
	*/
	spi_device_e max31855spiDevice;
	/**
	 * offset 412
	*/
	brain_pin_e fsioPins[LE_COMMAND_COUNT];
	/**
	 * offset 476
	*/
	pin_output_mode_e gpioPinModes[LE_COMMAND_COUNT];
	/**
	 * offset 540
	*/
	brain_pin_e joystickPins[JOYSTICK_PIN_COUNT];
	/**
	 * This pin is used for debugging - snap a logic analyzer on it and see if it's ever high
	 * offset 560
	*/
	brain_pin_e triggerErrorPin;
	/**
	 * offset 564
	*/
	pin_output_mode_e triggerErrorPinMode;
	/**
	 * value between 0 and 1
	 * offset 568
	*/
	float idleSolenoidPwm;
	/**
	 * offset 572
	*/
	brain_pin_e acRelayPin;
	/**
	 * offset 576
	*/
	pin_output_mode_e acRelayPinMode;
	/**
	 * offset 580
	*/
	int16_t fsioFrequency[LE_COMMAND_COUNT];
	/**
	 * offset 612
	*/
	brain_pin_e hip9011CsPin;
	/**
	 * offset 616
	*/
	brain_pin_e hip9011IntHoldPin;
	/**
	 * offset 620
	*/
	brain_pin_e hip9011OutPin;
	/**
	 * offset 624
	*/
	float fsio_setting[LE_COMMAND_COUNT];
	/**
	 * offset 688
	*/
	brain_pin_e spi1mosiPin;
	/**
	 * offset 692
	*/
	brain_pin_e spi1misoPin;
	/**
	 * offset 696
	*/
	brain_pin_e spi1sckPin;
	/**
	 * offset 700
	*/
	brain_pin_e spi2mosiPin;
	/**
	 * offset 704
	*/
	brain_pin_e spi2misoPin;
	/**
	 * offset 708
	*/
	brain_pin_e spi2sckPin;
	/**
	 * offset 712
	*/
	brain_pin_e spi3mosiPin;
	/**
	 * offset 716
	*/
	brain_pin_e spi3misoPin;
	/**
	 * offset 720
	*/
	brain_pin_e spi3sckPin;
	/**
	 * offset 724
	*/
	float hip9011Gain;
	/**
	 * offset 728
	*/
	brain_pin_e joystickCenterPin;
	/**
	 * offset 732
	*/
	brain_pin_e joystickAPin;
	/**
	 * offset 736
	*/
	brain_pin_e joystickBPin;
	/**
	 * offset 740
	*/
	brain_pin_e joystickCPin;
	/**
	 * offset 744
	*/
	brain_pin_e joystickDPin;
	/**
	 * offset 748
	*/
	analog_chart_e analogChartMode;
	/**
	 * offset 752
	*/
	int unusedbs[6];
	/**
	 * offset 776
	*/
	le_formula_t le_formulas[LE_COMMAND_COUNT];
	/** total size 3976*/
} board_configuration_s;

typedef struct {
	// this section was generated by config_definition.jar on Thu Jan 15 15:59:00 EST 2015
	// begin
	/**
	 * http://rusefi.com/wiki/index.php?title=Manual:Engine_Type
	 * offset 0
	*/
	engine_type_e engineType;
	/**
	 * this magic number is used to make sure that what we read from Flash is in fact some configuration
	 * offset 4
	*/
	int headerMagicValue;
	/**
	 * offset 8
	*/
	float battInjectorLagCorrBins[VBAT_INJECTOR_CURVE_SIZE];
	/**
	 * offset 40
	*/
	float battInjectorLagCorr[VBAT_INJECTOR_CURVE_SIZE];
	/**
	 * offset 72
	*/
	float cltFuelCorrBins[CLT_CURVE_SIZE];
	/**
	 * offset 136
	*/
	float cltFuelCorr[CLT_CURVE_SIZE];
	/**
	 * offset 200
	*/
	float iatFuelCorrBins[IAT_CURVE_SIZE];
	/**
	 * offset 264
	*/
	float iatFuelCorr[IAT_CURVE_SIZE];
	/**
	 * Should the trigger emulator push data right into trigger input, eliminating the need for physical jumper wires?
	 * PS: Funny name, right? :)
	 * todo: make this a bit on some bit field
	 * offset 328
	*/
	int16_t directSelfStimulation;
	/**
	 * todo: extract these two fields into a structure
	 * todo: we need two sets of TPS parameters - modern ETBs have to sensors
	 * offset 330
	*/
	int16_t tpsMin;
	/**
	 * tpsMax value as 10 bit ADC value. Not Voltage!
	 * offset 332
	*/
	int16_t tpsMax;
	/**
	 * offset 334
	*/
	uint16_t unused334;

	/**
	 * todo: finish implementation. These values are used for TPS disconnect detection
	 * offset 336
	*/
	int16_t tpsErrorLowValue;
	/**
	 * offset 338
	*/
	int16_t tpsErrorHighValue;
	/**
	 * offset 340
	*/
	float primingSquirtDurationMs;
	/**
	 * 360 for two-stroke
	 * 720 for four-stroke
	 * offset 344
	*/
	int engineCycle;

	/**
	 * offset 348
	*/
	cranking_parameters_s cranking;
	/**
	 * @see hasMapSensor
	 * @see isMapAveragingEnabled
	 * offset 356
	*/
	MAP_sensor_config_s map;

	/**
	 * todo: merge with channel settings, use full-scale Thermistor here!
	 * offset 500
	*/
	ThermistorConf clt;
	/**
	 * offset 540
	*/
	ThermistorConf iat;
	/**
	 * offset 580
	*/
	float sparkDwellBins[DWELL_COUNT];
	/**
	 * offset 612
	*/
	float sparkDwell[DWELL_COUNT];
	/**
	 * offset 644
	*/
	float ignitionLoadBins[IGN_LOAD_COUNT];
	/**
	 * offset 708
	*/
	float ignitionRpmBins[IGN_RPM_COUNT];
	/**
	 * this value could be used to offset the whole ignition timing table by a constant
	 * offset 772
	*/
	float ignitionBaseAngle;
	/**
	 * While cranking (which causes battery voltage to drop) we can calculate dwell time in shaft
	 * degrees, not in absolute time as in running mode.
	 * offset 776
	*/
	float crankingChargeAngle;
	/**
	 * offset 780
	*/
	timing_mode_e timingMode;
	/**
	 * This value is used in 'fixed timing' mode, i.e. constant timing
	 * This mode is useful for instance while adjusting distributor location
	 * offset 784
	*/
	float fixedModeTiming;
	/**
	 * offset 788
	*/
	float injectorLag;
	/**
	 * offset 792
	*/
	float fuelLoadBins[FUEL_LOAD_COUNT];
	/**
	 * RPM is float and not integer in order to use unified methods for interpolation
	 * offset 856
	*/
	float fuelRpmBins[FUEL_RPM_COUNT];
	/**
	 * Engine displacement, in liters
	 * see also cylindersCount
	 * offset 920
	*/
	float displacement;
	/**
	 * offset 924
	*/
	int rpmHardLimit;
	/**
	 * offset 928
	*/
	injection_mode_e crankingInjectionMode;
	/**
	 * offset 932
	*/
	injection_mode_e injectionMode;
	/**
	 * This field is the angle between Top Dead Center (TDC) and the first trigger event.
	 * Knowing this angle allows us to control timing and other angles in reference to TDC.
	 * offset 936
	*/
	float globalTriggerAngleOffset;
	/**
	 * This parameter holds the coefficient of input voltage dividers
	 * offset 940
	*/
	float analogInputDividerCoefficient;
	/**
	 * This setting controls which algorithm is used for ENGINE LOAD
	 * offset 944
	*/
	engine_load_mode_e algorithm;
	/**
	 * offset 948
	*/
	float vbattDividerCoeff;
	/**
	 * Cooling fan turn-on temperature threshold, in Celsuis
	 * offset 952
	*/
	float fanOnTemperature;
	/**
	 * Cooling fan turn-off temperature threshold, in Celsuis
	 * offset 956
	*/
	float fanOffTemperature;
	/**
	 * offset 960
	*/
	brain_pin_e vehicleSpeedSensorInputPin;
	/**
	 * This coefficient translates vehicle speed input frequency (in Hz) into vehicle speed, km/h
	 * offset 964
	*/
	float vehicleSpeedCoef;
	/**
	 * offset 968
	*/
	can_nbc_e canNbcType;
	/**
	 * offset 972
	*/
	int canSleepPeriod;
	/**
	 * offset 976
	*/
	int cylindersCount;
	/**
	 * offset 980
	*/
	ignition_mode_e ignitionMode;
	/**
	 * offset 984
	*/
	firing_order_e firingOrder;
	/**
	 * todo: refactor this, see operation_mode_e
	 * offset 988
	*/
	float rpmMultiplier;
	/**
	 * offset 992
	*/
	display_mode_e displayMode;
	/**
	 * offset 996
	*/
	log_format_e logFormat;
	/**
	 * offset 1000
	*/
	int firmwareVersion;
	/**
	 * offset 1004
	*/
	int HD44780width;
	/**
	 * offset 1008
	*/
	int HD44780height;
	/**
	 * offset 1012
	*/
	adc_channel_e tpsAdcChannel;
	/**
	 * offset 1016
	*/
	int overrideCrankingIgnition;
	/**
	 * offset 1020
	*/
	int analogChartFrequency;
	/**
	 * offset 1024
	*/
	trigger_config_s trigger;
	/**
	 * offset 1052
	*/
	spi_device_e hip9011SpiDevice;
	/**
	 * offset 1056
	*/
	adc_channel_e vbattAdcChannel;
	/**
	 * offset 1060
	*/
	float globalFuelCorrection;
	/**
	 * todo: merge with channel settings, use full-scale Thermistor!
	 * offset 1064
	*/
	adc_channel_e cltAdcChannel;
	/**
	 * offset 1068
	*/
	adc_channel_e iatAdcChannel;
	/**
	 * offset 1072
	*/
	adc_channel_e mafAdcChannel;
	/**
	 * @see hasAfrSensor
	 * offset 1076
	*/
	afr_sensor_s afrSensor;
	/**
	 * this is about deciding when the injector starts it's squirt
	 * offset 1096
	*/
	float injectionAngle;
	/**
	 * offset 1100
	*/
	float crankingTimingAngle;
	/**
	 * offset 1104
	*/
	float diffLoadEnrichmentCoef;
	/**
	 * @see hasBaroSensor
	 * offset 1108
	*/
	air_pressure_sensor_config_s baroSensor;
	/**
	 * offset 1124
	*/
	float veLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 1188
	*/
	float veRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 1252
	*/
	float afrLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 1316
	*/
	float afrRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 1380
	*/
	fuel_table_t fuelTable;
	/**
	 * offset 2404
	*/
	ignition_table_t ignitionTable;
	/**
	 * offset 3428
	*/
	fuel_table_t veTable;
	/**
	 * offset 4452
	*/
	fuel_table_t afrTable;

	board_configuration_s bc;

	// offset 6280 ????
	/**
	 * @see isMapAveragingEnabled
	 */
	/** offset 9480 bit 0 */
	bool_t hasMapSensor : 1;
	/** offset 9480 bit 1 */
	bool_t hasIatSensor : 1;
	/** offset 9480 bit 2 */
	bool_t hasBaroSensor : 1;
	/** offset 9480 bit 3 */
	bool_t hasAfrSensor : 1;
	/** offset 9480 bit 4 */
	bool_t useConstantDwellDuringCranking : 1;
	/** offset 9480 bit 5 */
	bool_t isDigitalChartEnabled : 1;
	/** offset 9480 bit 6 */
	bool_t isCanEnabled : 1;
	/** offset 9480 bit 7 */
	bool_t hasCltSensor : 1;
	/** offset 9480 bit 8 */
	bool_t canReadEnabled : 1;
	/** offset 9480 bit 9 */
	bool_t canWriteEnabled : 1;
	/** offset 9480 bit 10 */
	bool_t hasVehicleSpeedSensor : 1;
	/** offset 9480 bit 11 */
	bool_t isJoystickEnabled : 1;
	/** offset 9480 bit 12 */
	bool_t isGpsEnabled : 1;
	/** offset 9480 bit 13 */
	bool_t hasMafSensor : 1;
	/** offset 9480 bit 14 */
	bool_t hasTpsSensor : 1;

	/**
	 * offset 6284 ???
	 */
	adc_channel_e hipOutputChannel;

	/**
	 * offset 9488
	*/
	idle_mode_e idleMode;
	/** offset 9492 bit 0 */
	bool_t isInjectionEnabled : 1;
	/** offset 9492 bit 1 */
	bool_t isIgnitionEnabled : 1;
	/** offset 9492 bit 2 */
	bool_t isCylinderCleanupEnabled : 1;
	/** offset 9492 bit 3 */
	bool_t secondTriggerChannelEnabled : 1;
	/** offset 9492 bit 4 */
	bool_t needSecondTriggerInput : 1;
	/** offset 9492 bit 5 */
	bool_t isMapAveragingEnabled : 1;
	/** offset 9492 bit 6 */
	bool_t isMilEnabled : 1;
	/** offset 9492 bit 7 */
	bool_t isFuelPumpEnabled : 1;
	/** offset 9492 bit 8 */
	bool_t isTunerStudioEnabled : 1;
	/** offset 9492 bit 9 */
	bool_t isWaveAnalyzerEnabled : 1;
	/** offset 9492 bit 10 */
	bool_t isIdleThreadEnabled : 1;
	/** offset 9492 bit 11 */
	bool_t isPrintTriggerSynchDetails : 1;
	/**
	 * Usually if we have no trigger events that means engine is stopped
	 * Unless we are troubleshooting and spinning the engine by hand - this case a longer
	 * delay is needed
	 */
	bool isManualSpinningMode : 1; // bit 11

	/**
	 * offset 9496
	*/
	uint32_t digitalChartSize;
	/**
	 * cc/min, cubic centimeter per minute
	 * By the way, g/s = 0.125997881 * (lb/hr)
	 * g/s = 0.125997881 * (cc/min)/10.5
	 * g/s = 0.0119997981 * cc/min
	 * offset 9500
	*/
	float injectorFlow;
	/**
	 * offset 9504
	*/
	float crankingFuelCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 9536
	*/
	float crankingFuelBins[CRANKING_CURVE_SIZE];
	/**
	 * offset 9568
	*/
	float crankingCycleCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 9600
	*/
	float crankingCycleBins[CRANKING_CURVE_SIZE];
	/**
	 * offset 9632
	*/
	float ignitionDwellForCrankingMs;
	/**
	 * offset 9636
	*/
	int targetIdleRpm;
	/**
	 * A/C button input handled as analog input
	 * offset 9640
	*/
	adc_channel_e acSwitchAdc;
	/**
	 * offset 9644
	*/
	int ignMathCalculateAtIndex;
	/**
	 * offset 9648
	*/
	int16_t acCutoffLowRpm;
	/**
	 * offset 9650
	*/
	int16_t acCutoffHighRpm;
	/**
	 * offset 9652
	*/
	int16_t acIdleRpmBump;
	/**
	 * offset 9654
	*/
	int16_t unusedShort;
	/**
	 * offset 9656
	*/
	adc_channel_e vRefAdcChannel;
	/**
	 * offset 9660
	*/
	float knockDetectionWindowStart;
	/**
	 * offset 9664
	*/
	float knockDetectionWindowEnd;
	/**
	 * Cylinder diameter, in mm.
	 * offset 9668
	*/
	float cylinderBore;
	/**
	 * Some vehicles have a switch to indicate that clutch pedal is all the way up
	 * offset 9672
	*/
	brain_pin_e clutchUpPin;
	/**
	 * offset 9676
	*/
	pin_input_mode_e clutchUpPinMode;
	/**
	 * offset 9680
	*/
	float hipThreshold;
	/**
	 * offset 9684
	*/
	brain_pin_e fsioInputs[LE_COMMAND_COUNT];
	/**
	 * offset 9748
	*/
	pin_input_mode_e fsioInputModes[LE_COMMAND_COUNT];
	/**
	 * offset 9812
	*/
	int unused3[149];
	/**
	 * offset 10408
	*/
	le_formula_t timingMultiplier;
	/**
	 * offset 10608
	*/
	le_formula_t timingAdditive;
	/**
	 * offset 10808
	*/
	fuel_table_t injectionPhase;
} engine_configuration_s;
