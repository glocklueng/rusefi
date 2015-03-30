// this section was generated by config_definition.jar on Sun Mar 29 18:29:28 EDT 2015
// begin
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

typedef struct {
	/**
	 * cc/min, cubic centimeter per minute
	 * By the way, g/s = 0.125997881 * (lb/hr)
	 * g/s = 0.125997881 * (cc/min)/10.5
	 * g/s = 0.0119997981 * cc/min
	 * offset 0
	 */
	float flow;
	/**
	 * offset 4
	 */
	float lag;
	/**
	 * offset 8
	 */
	float battLagCorrBins[VBAT_INJECTOR_CURVE_SIZE];
	/**
	 * offset 40
	 */
	float battLagCorr[VBAT_INJECTOR_CURVE_SIZE];
	/** total size 72*/
} injector_s;

typedef struct {
	/**
	 * Engine displacement, in liters
	 * see also cylindersCount
	 * offset 0
	 */
	float displacement;
	/**
	 * offset 4
	 */
	cylinders_count_t cylindersCount;
	/**
	 * offset 8
	 */
	firing_order_e firingOrder;
	/** total size 12*/
} specs_s;

/**
 * @brief Trigger wheel(s) configuration

*/
typedef struct {
	/**
	 * offset 0
	 */
	trigger_type_e type;
	/**
	offset 4 bit 0 */
	bool_t customIsSynchronizationNeeded : 1;
	/**
	offset 4 bit 1 */
	bool_t customNeedSecondTriggerInput : 1;
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
	bool32_t customUseRiseEdge;
	/** total size 28*/
} trigger_config_s;

typedef struct {
	/**
	 * offset 0
	 */
	adc_channel_e hwChannel;
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
	brain_input_pin_e triggerInputPins[3];
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
	int anotherUnused;
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
	/**
	offset 372 bit 0 */
	bool_t is_enabled_spi_1 : 1;
	/**
	offset 372 bit 1 */
	bool_t is_enabled_spi_2 : 1;
	/**
	offset 372 bit 2 */
	bool_t is_enabled_spi_3 : 1;
	/**
	offset 372 bit 3 */
	bool_t isSdCardEnabled : 1;
	/**
	offset 372 bit 4 */
	bool_t isFastAdcEnabled : 1;
	/**
	offset 372 bit 5 */
	bool_t isEngineControlEnabled : 1;
	/**
	offset 372 bit 6 */
	bool_t isHip9011Enabled : 1;
	/**
	offset 372 bit 7 */
	bool_t isVerboseAlternator : 1;
	/**
	offset 372 bit 8 */
	bool_t useSerialPort : 1;
	/**
	offset 372 bit 9 */
	bool_t useStepperSerial : 1;
	/**
	 * offset 376
	 */
	brain_input_pin_e logicAnalyzerPins[LOGIC_ANALYZER_CHANNEL_COUNT];
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
	brain_pin_e max31855_cs[EGT_CHANNEL_COUNT];
	/**
	 * offset 436
	 */
	spi_device_e max31855spiDevice;
	/**
	 * offset 440
	 */
	brain_pin_e fsioPins[LE_COMMAND_COUNT];
	/**
	 * offset 504
	 */
	pin_output_mode_e gpioPinModes[LE_COMMAND_COUNT];
	/**
	 * offset 568
	 */
	brain_pin_e joystickPins[JOYSTICK_PIN_COUNT];
	/**
	 * This pin is used for debugging - snap a logic analyzer on it and see if it's ever high
	 * offset 588
	 */
	brain_pin_e triggerErrorPin;
	/**
	 * offset 592
	 */
	pin_output_mode_e triggerErrorPinMode;
	/**
	 * value between 0 and 1
	 * offset 596
	 */
	float idleSolenoidPwm;
	/**
	 * offset 600
	 */
	brain_pin_e acRelayPin;
	/**
	 * offset 604
	 */
	pin_output_mode_e acRelayPinMode;
	/**
	 * offset 608
	 */
	fsio_pwm_freq_t fsioFrequency[LE_COMMAND_COUNT];
	/**
	 * offset 640
	 */
	brain_pin_e hip9011CsPin;
	/**
	 * offset 644
	 */
	brain_pin_e hip9011IntHoldPin;
	/**
	 * offset 648
	 */
	brain_pin_e hip9011OutPin;
	/**
	 * offset 652
	 */
	fsio_setting_t fsio_setting[LE_COMMAND_COUNT];
	/**
	 * offset 716
	 */
	brain_pin_e spi1mosiPin;
	/**
	 * offset 720
	 */
	brain_pin_e spi1misoPin;
	/**
	 * offset 724
	 */
	brain_pin_e spi1sckPin;
	/**
	 * offset 728
	 */
	brain_pin_e spi2mosiPin;
	/**
	 * offset 732
	 */
	brain_pin_e spi2misoPin;
	/**
	 * offset 736
	 */
	brain_pin_e spi2sckPin;
	/**
	 * offset 740
	 */
	brain_pin_e spi3mosiPin;
	/**
	 * offset 744
	 */
	brain_pin_e spi3misoPin;
	/**
	 * offset 748
	 */
	brain_pin_e spi3sckPin;
	/**
	 * offset 752
	 */
	float hip9011Gain;
	/**
	 * offset 756
	 */
	brain_pin_e joystickCenterPin;
	/**
	 * offset 760
	 */
	brain_pin_e joystickAPin;
	/**
	 * offset 764
	 */
	brain_pin_e joystickBPin;
	/**
	 * offset 768
	 */
	brain_pin_e joystickCPin;
	/**
	 * offset 772
	 */
	brain_pin_e joystickDPin;
	/**
	 * offset 776
	 */
	analog_chart_e analogChartMode;
	/**
	 * offset 780
	 */
	maf_sensor_type_e mafSensorType;
	/**
	 * offset 784
	 */
	brain_pin_e idleStepperDirection;
	/**
	 * offset 788
	 */
	brain_pin_e idleStepperStep;
	/**
	 * offset 792
	 */
	int unusedbs[3];
	/**
	 * offset 804
	 */
	le_formula_t le_formulas[LE_COMMAND_COUNT];
	/** total size 4004*/
} board_configuration_s;

typedef struct {
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
	injector_s injector;
	/**
	 * offset 80
	 */
	float cltFuelCorrBins[CLT_CURVE_SIZE];
	/**
	 * offset 144
	 */
	float cltFuelCorr[CLT_CURVE_SIZE];
	/**
	 * offset 208
	 */
	float iatFuelCorrBins[IAT_CURVE_SIZE];
	/**
	 * offset 272
	 */
	float iatFuelCorr[IAT_CURVE_SIZE];
	/**
	 * Should the trigger emulator push data right into trigger input, eliminating the need for physical jumper wires?
	 * PS: Funny name, right? :)
	 * todo: make this a bit on some bit field
	 * offset 336
	 */
	int16_t directSelfStimulation;
	/**
	 * todo: extract these two fields into a structure
	 * todo: we need two sets of TPS parameters - modern ETBs have two sensors
	 * offset 338
	 */
	int16_t tpsMin;
	/**
	 * tpsMax value as 10 bit ADC value. Not Voltage!
	 * offset 340
	 */
	int16_t tpsMax;
	/**
	 * offset 342
	 */
	uint16_t unused334;
	/**
	 * todo: finish implementation. These values are used for TPS disconnect detection
	 * offset 344
	 */
	int16_t tpsErrorLowValue;
	/**
	 * offset 346
	 */
	int16_t tpsErrorHighValue;
	/**
	 * offset 348
	 */
	float primingSquirtDurationMs;
	/**
	 * 360 for two-stroke
	 * 720 for four-stroke
	 * offset 352
	 */
	int engineCycle;
	/**
	 * offset 356
	 */
	cranking_parameters_s cranking;
	/**
	 * @see hasMapSensor
	 * @see isMapAveragingEnabled
	 * offset 364
	 */
	MAP_sensor_config_s map;
	/**
	 * todo: merge with channel settings, use full-scale Thermistor here!
	 * offset 508
	 */
	ThermistorConf clt;
	/**
	 * offset 548
	 */
	ThermistorConf iat;
	/**
	 * offset 588
	 */
	float sparkDwellBins[DWELL_COUNT];
	/**
	 * offset 620
	 */
	float sparkDwell[DWELL_COUNT];
	/**
	 * this value could be used to offset the whole ignition timing table by a constant
	 * offset 652
	 */
	float ignitionBaseAngle;
	/**
	 * While cranking (which causes battery voltage to drop) we can calculate dwell time in shaft
	 * degrees, not in absolute time as in running mode.
	 * offset 656
	 */
	float crankingChargeAngle;
	/**
	 * offset 660
	 */
	timing_mode_e timingMode;
	/**
	 * This value is used in 'fixed timing' mode, i.e. constant timing
	 * This mode is useful for instance while adjusting distributor location
	 * offset 664
	 */
	float fixedModeTiming;
	/**
	 * offset 668
	 */
	specs_s specs;
	/**
	 * offset 680
	 */
	int rpmHardLimit;
	/**
	 * offset 684
	 */
	injection_mode_e crankingInjectionMode;
	/**
	 * offset 688
	 */
	injection_mode_e injectionMode;
	/**
	 * This field is the angle between Top Dead Center (TDC) and the first trigger event.
	 * Knowing this angle allows us to control timing and other angles in reference to TDC.
	 * offset 692
	 */
	float globalTriggerAngleOffset;
	/**
	 * This parameter holds the coefficient of input voltage dividers
	 * offset 696
	 */
	float analogInputDividerCoefficient;
	/**
	 * This setting controls which algorithm is used for ENGINE LOAD
	 * offset 700
	 */
	engine_load_mode_e algorithm;
	/**
	 * offset 704
	 */
	float vbattDividerCoeff;
	/**
	 * Cooling fan turn-on temperature threshold, in Celsuis
	 * offset 708
	 */
	float fanOnTemperature;
	/**
	 * Cooling fan turn-off temperature threshold, in Celsuis
	 * offset 712
	 */
	float fanOffTemperature;
	/**
	 * offset 716
	 */
	brain_pin_e vehicleSpeedSensorInputPin;
	/**
	 * This coefficient translates vehicle speed input frequency (in Hz) into vehicle speed, km/h
	 * offset 720
	 */
	float vehicleSpeedCoef;
	/**
	 * offset 724
	 */
	can_nbc_e canNbcType;
	/**
	 * offset 728
	 */
	int canSleepPeriod;
	/**
	 * offset 732
	 */
	ignition_mode_e ignitionMode;
	/**
	 * offset 736
	 */
	operation_mode_e operationMode;
	/**
	 * offset 740
	 */
	display_mode_e displayMode;
	/**
	 * offset 744
	 */
	log_format_e logFormat;
	/**
	 * offset 748
	 */
	int firmwareVersion;
	/**
	 * offset 752
	 */
	int HD44780width;
	/**
	 * offset 756
	 */
	int HD44780height;
	/**
	 * offset 760
	 */
	adc_channel_e tpsAdcChannel;
	/**
	 * offset 764
	 */
	int overrideCrankingIgnition;
	/**
	 * offset 768
	 */
	int analogChartFrequency;
	/**
	 * offset 772
	 */
	trigger_config_s trigger;
	/**
	 * offset 800
	 */
	spi_device_e hip9011SpiDevice;
	/**
	 * offset 804
	 */
	adc_channel_e vbattAdcChannel;
	/**
	 * offset 808
	 */
	float globalFuelCorrection;
	/**
	 * todo: merge with channel settings, use full-scale Thermistor!
	 * offset 812
	 */
	adc_channel_e cltAdcChannel;
	/**
	 * offset 816
	 */
	adc_channel_e iatAdcChannel;
	/**
	 * offset 820
	 */
	adc_channel_e mafAdcChannel;
	/**
	 * @see hasAfrSensor
	 * offset 824
	 */
	afr_sensor_s afr;
	/**
	 * this is about deciding when the injector starts it's squirt
	 * offset 844
	 */
	float injectionAngle;
	/**
	 * offset 848
	 */
	float crankingTimingAngle;
	/**
	 * offset 852
	 */
	float diffLoadEnrichmentCoef;
	/**
	 * @see hasBaroSensor
	 * offset 856
	 */
	air_pressure_sensor_config_s baroSensor;
	/**
	 * offset 872
	 */
	board_configuration_s bc;
	/**
	 * @see isMapAveragingEnabled
	offset 4876 bit 0 */
	bool_t hasMapSensor : 1;
	/**
	offset 4876 bit 1 */
	bool_t hasIatSensor : 1;
	/**
	offset 4876 bit 2 */
	bool_t hasBaroSensor : 1;
	/**
	offset 4876 bit 3 */
	bool_t hasAfrSensor : 1;
	/**
	offset 4876 bit 4 */
	bool_t useConstantDwellDuringCranking : 1;
	/**
	offset 4876 bit 5 */
	bool_t isDigitalChartEnabled : 1;
	/**
	offset 4876 bit 6 */
	bool_t isCanEnabled : 1;
	/**
	offset 4876 bit 7 */
	bool_t hasCltSensor : 1;
	/**
	offset 4876 bit 8 */
	bool_t canReadEnabled : 1;
	/**
	offset 4876 bit 9 */
	bool_t canWriteEnabled : 1;
	/**
	offset 4876 bit 10 */
	bool_t hasVehicleSpeedSensor : 1;
	/**
	offset 4876 bit 11 */
	bool_t isJoystickEnabled : 1;
	/**
	offset 4876 bit 12 */
	bool_t isGpsEnabled : 1;
	/**
	offset 4876 bit 13 */
	bool_t isAlternatorControlEnabled : 1;
	/**
	offset 4876 bit 14 */
	bool_t hasMafSensor : 1;
	/**
	offset 4876 bit 15 */
	bool_t hasTpsSensor : 1;
	/**
	 * offset 4880
	 */
	adc_channel_e hipOutputChannel;
	/**
	 * offset 4884
	 */
	idle_mode_e idleMode;
	/**
	offset 4888 bit 0 */
	bool_t isInjectionEnabled : 1;
	/**
	offset 4888 bit 1 */
	bool_t isIgnitionEnabled : 1;
	/**
	offset 4888 bit 2 */
	bool_t isCylinderCleanupEnabled : 1;
	/**
	offset 4888 bit 3 */
	bool_t secondTriggerChannelEnabled : 1;
	/**
	offset 4888 bit 4 */
	bool_t needSecondTriggerInputDeprecated : 1;
	/**
	offset 4888 bit 5 */
	bool_t isMapAveragingEnabled : 1;
	/**
	offset 4888 bit 6 */
	bool_t isMilEnabled : 1;
	/**
	offset 4888 bit 7 */
	bool_t isFuelPumpEnabled : 1;
	/**
	offset 4888 bit 8 */
	bool_t isTunerStudioEnabled : 1;
	/**
	offset 4888 bit 9 */
	bool_t isWaveAnalyzerEnabled : 1;
	/**
	offset 4888 bit 10 */
	bool_t isIdleThreadEnabled : 1;
	/**
	offset 4888 bit 11 */
	bool_t isPrintTriggerSynchDetails : 1;
	/**
	 * Usually if we have no trigger events that means engine is stopped
	 * Unless we are troubleshooting and spinning the engine by hand - this case a longer
	 * delay is needed
	offset 4888 bit 12 */
	bool_t isManualSpinningMode : 1;
	/**
	offset 4888 bit 13 */
	bool_t twoWireBatch : 1;
	/**
	 * offset 4892
	 */
	uint32_t digitalChartSize;
	/**
	 * offset 4896
	 */
	float crankingFuelCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 4928
	 */
	float crankingFuelBins[CRANKING_CURVE_SIZE];
	/**
	 * offset 4960
	 */
	float crankingCycleCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 4992
	 */
	float crankingCycleBins[CRANKING_CURVE_SIZE];
	/**
	 * offset 5024
	 */
	float ignitionDwellForCrankingMs;
	/**
	 * offset 5028
	 */
	int targetIdleRpm;
	/**
	 * A/C button input handled as analog input
	 * offset 5032
	 */
	adc_channel_e acSwitchAdc;
	/**
	 * offset 5036
	 */
	int ignMathCalculateAtIndex;
	/**
	 * offset 5040
	 */
	int16_t acCutoffLowRpm;
	/**
	 * offset 5042
	 */
	int16_t acCutoffHighRpm;
	/**
	 * offset 5044
	 */
	int16_t acIdleRpmBump;
	/**
	 * offset 5046
	 */
	int16_t unusedShort;
	/**
	 * offset 5048
	 */
	adc_channel_e vRefAdcChannel;
	/**
	 * offset 5052
	 */
	float knockDetectionWindowStart;
	/**
	 * offset 5056
	 */
	float knockDetectionWindowEnd;
	/**
	 * Cylinder diameter, in mm.
	 * offset 5060
	 */
	float cylinderBore;
	/**
	 * Some vehicles have a switch to indicate that clutch pedal is all the way up
	 * offset 5064
	 */
	brain_pin_e clutchUpPin;
	/**
	 * offset 5068
	 */
	pin_input_mode_e clutchUpPinMode;
	/**
	 * offset 5072
	 */
	float hipThreshold;
	/**
	 * offset 5076
	 */
	brain_pin_e fsioInputs[LE_COMMAND_COUNT];
	/**
	 * offset 5140
	 */
	pin_input_mode_e fsioInputModes[LE_COMMAND_COUNT];
	/**
	 * offset 5204
	 */
	adc_channel_e externalKnockSenseAdc;
	/**
	 * offset 5208
	 */
	float alternatorControlPFactor;
	/**
	 * offset 5212
	 */
	float alternatorControlIFactor;
	/**
	 * offset 5216
	 */
	float alternatorControlDFactor;
	/**
	 * offset 5220
	 */
	int unused3[140];
	/**
	 * offset 5780
	 */
	int accelLength;
	/**
	 * offset 5784
	 */
	float decelEnrichmentThreshold;
	/**
	 * offset 5788
	 */
	float decelEnrichmentMultiplier;
	/**
	 * offset 5792
	 */
	float accelEnrichmentThreshold;
	/**
	 * offset 5796
	 */
	float accelEnrichmentMultiplier;
	/**
	 * offset 5800
	 */
	le_formula_t timingMultiplier;
	/**
	 * offset 6000
	 */
	le_formula_t timingAdditive;
	/**
	 * kg/hour value.
	 * By the way 2.081989116 kg/h = 1 ft�/m
	 * offset 6200
	 */
	float mafDecoding[MAF_DECODING_COUNT];
	/**
	 * offset 7224
	 */
	float mafDecodingBins[MAF_DECODING_COUNT];
	/**
	 * offset 8248
	 */
	fuel_table_t fuelTable;
	/**
	 * offset 9272
	 */
	float fuelLoadBins[FUEL_LOAD_COUNT];
	/**
	 * RPM is float and not integer in order to use unified methods for interpolation
	 * offset 9336
	 */
	float fuelRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 9400
	 */
	ignition_table_t ignitionTable;
	/**
	 * offset 10424
	 */
	float ignitionLoadBins[IGN_LOAD_COUNT];
	/**
	 * offset 10488
	 */
	float ignitionRpmBins[IGN_RPM_COUNT];
	/**
	 * offset 10552
	 */
	ve_table_t veTable;
	/**
	 * offset 11576
	 */
	float veLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 11640
	 */
	float veRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 11704
	 */
	afr_table_t afrTable;
	/**
	 * offset 12728
	 */
	float afrLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 12792
	 */
	float afrRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 12856
	 */
	fuel_table_t injectionPhase;
	/**
	 * offset 13880
	 */
	float injPhaseLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 13944
	 */
	float injPhaseRpmBins[FUEL_RPM_COUNT];
	/** total size 14008*/
} engine_configuration_s;

// end
// this section was generated by config_definition.jar on Sun Mar 29 18:29:28 EDT 2015
