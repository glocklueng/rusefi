// this section was generated automatically by ConfigDefinition.jar based on rusefi_config.txt Tue Mar 08 23:31:32 EST 2016
// begin
#ifndef ENGINE_CONFIGURATION_GENERATED_H_
#define ENGINE_CONFIGURATION_GENERATED_H_
#include "rusefi_types.h"
typedef struct {
	/**
	 * offset 0
	 */
	float pFactor;
	/**
	 * offset 4
	 */
	float iFactor;
	/**
	 * offset 8
	 */
	float dFactor;
	/**
	 * Linear addition to PID logic
	 * offset 12
	 */
	float offset;
	/** total size 16*/
} pid_s;

typedef struct {
	/**
	 * Fuel squirt duration while cranking
	 * A number of curves adjust this value according to CLT/IAT/TPS etc
	 * offset 0
	 */
	float baseFuel;
	/**
	 * Cranking mode threshold. Special cranking logic controls fuel and spark while RPM is below this threshold
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
 * @brief Thermistor known values

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
	/** total size 28*/
} thermistor_conf_s;

/**
 * @brief Thermistor curve parameters

*/
typedef struct {
	/**
	 * offset 0
	 */
	float s_h_a;
	/**
	 * offset 4
	 */
	float s_h_b;
	/**
	 * offset 8
	 */
	float s_h_c;
	/** total size 12*/
} thermistor_curve_s;

/**
 * @brief Thermistor curve parameters

*/
typedef struct {
	/**
	 * offset 0
	 */
	thermistor_conf_s config;
	/**
	 * offset 28
	 */
	adc_channel_e adcChannel;
	/** total size 32*/
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
	 * Base injector lag
	 * See also vBatt correction curve
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
	bool customIsSynchronizationNeeded : 1;
	/**
	offset 4 bit 1 */
	bool customNeedSecondTriggerInput : 1;
	/**
	 * This option could be used if your second trigger channel is broken
	offset 4 bit 2 */
	bool useOnlyFirstChannel : 1;
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
	brain_pin_e solenoidPin;
	/**
	 * offset 4
	 */
	pin_output_mode_e solenoidPinMode;
	/**
	 * offset 8
	 */
	int solenoidFrequency;
	/**
	 * offset 12
	 */
	brain_pin_e stepperDirectionPin;
	/**
	 * offset 16
	 */
	brain_pin_e stepperStepPin;
	/** total size 20*/
} idle_hardware_s;

typedef struct {
	/**
	 * offset 0
	 */
	idle_hardware_s idle;
	/**
	 * value between 0 and 100 used in Manual mode
	 * offset 20
	 */
	float manIdlePosition;
	/**
	 * offset 24
	 */
	brain_pin_e fuelPumpPin;
	/**
	 * offset 28
	 */
	pin_output_mode_e fuelPumpPinMode;
	/**
	 * offset 32
	 */
	brain_pin_e injectionPins[INJECTION_PIN_COUNT];
	/**
	 * offset 80
	 */
	pin_output_mode_e injectionPinMode;
	/**
	 * offset 84
	 */
	brain_pin_e ignitionPins[IGNITION_PIN_COUNT];
	/**
	 * offset 132
	 */
	pin_output_mode_e ignitionPinMode;
	/**
	 * offset 136
	 */
	brain_pin_e malfunctionIndicatorPin;
	/**
	 * offset 140
	 */
	pin_output_mode_e malfunctionIndicatorPinMode;
	/**
	 * offset 144
	 */
	brain_pin_e fanPin;
	/**
	 * offset 148
	 */
	pin_output_mode_e fanPinMode;
	/**
	 * offset 152
	 */
	float mapFrequency0Kpa;
	/**
	 * offset 156
	 */
	float mapFrequency100Kpa;
	/**
	 * some cars have a switch to indicate that clutch pedal is all the way down
	 * offset 160
	 */
	brain_pin_e clutchDownPin;
	/**
	 * offset 164
	 */
	pin_input_mode_e clutchDownPinMode;
	/**
	 * offset 168
	 */
	brain_pin_e alternatorControlPin;
	/**
	 * offset 172
	 */
	pin_output_mode_e alternatorControlPinMode;
	/**
	 * offset 176
	 */
	brain_pin_e HD44780_rs;
	/**
	 * offset 180
	 */
	brain_pin_e HD44780_e;
	/**
	 * offset 184
	 */
	brain_pin_e HD44780_db4;
	/**
	 * offset 188
	 */
	brain_pin_e HD44780_db5;
	/**
	 * offset 192
	 */
	brain_pin_e HD44780_db6;
	/**
	 * offset 196
	 */
	brain_pin_e HD44780_db7;
	/**
	 * offset 200
	 */
	brain_pin_e gps_rx_pin;
	/**
	 * offset 204
	 */
	brain_pin_e gps_tx_pin;
	/**
	 * offset 208
	 */
	int triggerSimulatorFrequency;
	/**
	 * Digital Potentiometer is used by stock ECU stimulation code
	 * offset 212
	 */
	spi_device_e digitalPotentiometerSpiDevice;
	/**
	 * offset 216
	 */
	brain_pin_e digitalPotentiometerChipSelect[DIGIPOT_COUNT];
	/**
	 * offset 232
	 */
	brain_pin_e etbDirectionPin1;
	/**
	 * offset 236
	 */
	brain_pin_e etbDirectionPin2;
	/**
	 * offset 240
	 */
	brain_pin_e etbControlPin1;
	/**
	 * offset 244
	 */
	brain_pin_e etbControlPin2;
	/**
	 * offset 248
	 */
	pin_output_mode_e electronicThrottlePin1Mode;
	/**
	 * offset 252
	 */
	brain_pin_e wboHeaterPin;
	/**
	 * offset 256
	 */
	brain_pin_e wboPumpPin;
	/**
	 * offset 260
	 */
	float fuelLevelEmptyTankVoltage;
	/**
	 * offset 264
	 */
	float fuelLevelFullTankVoltage;
	/**
	 * AFR, WBO, EGO - whatever you like to call it
	 * offset 268
	 */
	ego_sensor_e afr_type;
	/**
	 * offset 272
	 */
	int etbDT;
	/**
	 * offset 276
	 */
	pin_output_mode_e hip9011CsPinMode;
	/**
	 * offset 280
	 */
	brain_pin_e tachOutputPin;
	/**
	 * offset 284
	 */
	pin_output_mode_e tachOutputPinMode;
	/**
	 * offset 288
	 */
	brain_input_pin_e triggerInputPins[3];
	/**
	 * offset 300
	 */
	brain_pin_e mainRelayPin;
	/**
	 * offset 304
	 */
	int idleThreadPeriod;
	/**
	 * offset 308
	 */
	int consoleLoopPeriod;
	/**
	 * offset 312
	 */
	int lcdThreadPeriod;
	/**
	 * offset 316
	 */
	brain_pin_e sdCardCsPin;
	/**
	 * offset 320
	 */
	int generalPeriodicThreadPeriod;
	/**
	 * offset 324
	 */
	uint32_t tunerStudioSerialSpeed;
	/**
	 * offset 328
	 */
	brain_pin_e boardTestModeJumperPin;
	/**
	 * offset 332
	 */
	can_device_mode_e canDeviceMode;
	/**
	 * offset 336
	 */
	brain_pin_e canTxPin;
	/**
	 * offset 340
	 */
	brain_pin_e canRxPin;
	/**
	 * offset 344
	 */
	brain_pin_e triggerSimulatorPins[TRIGGER_SIMULATOR_PIN_COUNT];
	/**
	 * offset 356
	 */
	pin_output_mode_e triggerSimulatorPinModes[TRIGGER_SIMULATOR_PIN_COUNT];
	/**
	 * offset 368
	 */
	brain_pin_e o2heaterPin;
	/**
	 * offset 372
	 */
	pin_output_mode_e o2heaterPinModeTodO;
	/**
	offset 376 bit 0 */
	bool is_enabled_spi_1 : 1;
	/**
	offset 376 bit 1 */
	bool is_enabled_spi_2 : 1;
	/**
	offset 376 bit 2 */
	bool is_enabled_spi_3 : 1;
	/**
	offset 376 bit 3 */
	bool isSdCardEnabled : 1;
	/**
	offset 376 bit 4 */
	bool isFastAdcEnabled : 1;
	/**
	offset 376 bit 5 */
	bool isEngineControlEnabled : 1;
	/**
	offset 376 bit 6 */
	bool isHip9011Enabled : 1;
	/**
	offset 376 bit 7 */
	bool isVerboseAlternator : 1;
	/**
	offset 376 bit 8 */
	bool useSerialPort : 1;
	/**
	offset 376 bit 9 */
	bool useStepperIdle : 1;
	/**
	offset 376 bit 10 */
	bool enabledStep1Limiter : 1;
	/**
	offset 376 bit 11 */
	bool useTpicAdvancedMode : 1;
	/**
	offset 376 bit 12 */
	bool useLcdScreen : 1;
	/**
	offset 376 bit 13 */
	bool startConsoleInBinaryMode : 1;
	/**
	offset 376 bit 14 */
	bool useWarmupPidAfr : 1;
	/**
	offset 376 bit 15 */
	bool onOffAlternatorLogic : 1;
	/**
	 * offset 380
	 */
	brain_input_pin_e logicAnalyzerPins[LOGIC_ANALYZER_CHANNEL_COUNT];
	/**
	 * default or inverted input
	 * offset 396
	 */
	uint8_t logicAnalyzerMode[LOGIC_ANALYZER_CHANNEL_COUNT];
	/**
	 * offset 400
	 */
	int unrealisticRpmThreashold;
	/**
	 * offset 404
	 */
	pin_output_mode_e mainRelayPinMode;
	/**
	 * offset 408
	 */
	brain_pin_e max31855_cs[EGT_CHANNEL_COUNT];
	/**
	 * offset 440
	 */
	spi_device_e max31855spiDevice;
	/**
	 * offset 444
	 */
	brain_pin_e fsioPins[LE_COMMAND_COUNT];
	/**
	 * offset 508
	 */
	pin_output_mode_e gpioPinModes[LE_COMMAND_COUNT];
	/**
	 * offset 572
	 */
	brain_pin_e joystickPins[JOYSTICK_PIN_COUNT];
	/**
	 * This pin is used for debugging - snap a logic analyzer on it and see if it's ever high
	 * offset 592
	 */
	brain_pin_e triggerErrorPin;
	/**
	 * offset 596
	 */
	pin_output_mode_e triggerErrorPinMode;
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
	pin_output_mode_e hip9011IntHoldPinMode;
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
	sensor_chart_e sensorChartMode;
	/**
	 * offset 780
	 */
	maf_sensor_type_e mafSensorType;
	/**
	 * offset 784
	 */
	brain_input_pin_e vehicleSpeedSensorInputPin;
	/**
	 * Some vehicles have a switch to indicate that clutch pedal is all the way up
	 * offset 788
	 */
	brain_pin_e clutchUpPin;
	/**
	 * offset 792
	 */
	pin_input_mode_e clutchUpPinMode;
	/**
	 * These input pins allow us to pull toggle buttons state
	 * offset 796
	 */
	brain_pin_e fsioDigitalInputs[LE_COMMAND_COUNT];
	/**
	 * offset 860
	 */
	brain_input_pin_e frequencyReportingMapInputPin;
	/** total size 864*/
} board_configuration_s;

typedef struct {
	/**
	 * http://rusefi.com/wiki/index.php?title=Manual:Engine_Type
	 * offset 0
	 */
	engine_type_e engineType;
	/**
	 * Disable engine sniffer above this rpm
	 * offset 4
	 */
	int engineSnifferRpmThreshold;
	/**
	 * offset 8
	 */
	injector_s injector;
	/**
	 * Should the trigger emulator push data right into trigger input, eliminating the need for physical jumper wires?
	 * PS: Funny name, right? :)
	offset 80 bit 0 */
	bool directSelfStimulation : 1;
	/**
	 * todo: extract these two fields into a structure
	 * todo: we need two sets of TPS parameters - modern ETBs have two sensors
	 * offset 84
	 */
	int16_t tpsMin;
	/**
	 * tpsMax value as 10 bit ADC value. Not Voltage!
	 * offset 86
	 */
	int16_t tpsMax;
	/**
	 * TPS error detection, what TPS % value is unrealistically low
	 * offset 88
	 */
	int16_t tpsErrorDetectionTooLow;
	/**
	 * offset 90
	 */
	int16_t tpsErrorDetectionTooHigh;
	/**
	 * offset 92
	 */
	cranking_parameters_s cranking;
	/**
	 * offset 100
	 */
	float primingSquirtDurationMs;
	/**
	 * offset 104
	 */
	float ignitionDwellForCrankingMs;
	/**
	 * While cranking (which causes battery voltage to drop) we can calculate dwell time in shaft
	 * degrees, not in absolute time as in running mode.
	 * offset 108
	 */
	float crankingChargeAngle;
	/**
	 * @see hasMapSensor
	 * @see isMapAveragingEnabled
	 * offset 112
	 */
	MAP_sensor_config_s map;
	/**
	 * todo: merge with channel settings, use full-scale Thermistor here!
	 * offset 256
	 */
	ThermistorConf clt;
	/**
	 * offset 288
	 */
	ThermistorConf iat;
	/**
	 * A secondary Rev limit engaged by the driver to help launch the vehicle faster
	 * offset 320
	 */
	int step1rpm;
	/**
	 * offset 324
	 */
	int step1timing;
	/**
	 * offset 328
	 */
	int hip9011PrescalerAndSDO;
	/**
	 * kHz knock band override
	 * offset 332
	 */
	float knockBandCustom;
	/**
	 * offset 336
	 */
	float sparkDwellBins[DWELL_CURVE_SIZE];
	/**
	 * offset 368
	 */
	float sparkDwell[DWELL_CURVE_SIZE];
	/**
	 * offset 400
	 */
	specs_s specs;
	/**
	 * Cylinder diameter, in mm.
	 * offset 412
	 */
	float cylinderBore;
	/**
	 * Disable sensor sniffer above this rpm
	 * offset 416
	 */
	int sensorSnifferRpmThreshold;
	/**
	 * offset 420
	 */
	int rpmHardLimit;
	/**
	 * This setting controls which algorithm is used for ENGINE LOAD
	 * offset 424
	 */
	engine_load_mode_e algorithm;
	/**
	 * offset 428
	 */
	injection_mode_e crankingInjectionMode;
	/**
	 * offset 432
	 */
	injection_mode_e injectionMode;
	/**
	 * this is about deciding when the injector starts it's squirt
	 * See also injectionPhase map
	 * offset 436
	 */
	angle_t injectionOffset;
	/**
	 * Timing advance while cranking engine
	 * offset 440
	 */
	angle_t crankingTimingAngle;
	/**
	 * offset 444
	 */
	ignition_mode_e ignitionMode;
	/**
	 * this value could be used to offset the whole ignition timing table by a constant
	 * offset 448
	 */
	angle_t ignitionOffset;
	/**
	 * offset 452
	 */
	timing_mode_e timingMode;
	/**
	 * This value is used in 'fixed timing' mode, i.e. constant timing
	 * This mode is useful for instance while adjusting distributor location
	 * offset 456
	 */
	angle_t fixedModeTiming;
	/**
	 * This field is the angle between Top Dead Center (TDC) and the first trigger event.
	 * Knowing this angle allows us to control timing and other angles in reference to TDC.
	 * offset 460
	 */
	angle_t globalTriggerAngleOffset;
	/**
	 * This parameter holds the coefficient of input voltage dividers
	 * offset 464
	 */
	float analogInputDividerCoefficient;
	/**
	 * Battery Voltage input resistor divider coefficient
	 * offset 468
	 */
	float vbattDividerCoeff;
	/**
	 * offset 472
	 */
	adc_channel_e vbattAdcChannel;
	/**
	 * Cooling fan turn-on temperature threshold, in Celsuis
	 * offset 476
	 */
	float fanOnTemperature;
	/**
	 * Cooling fan turn-off temperature threshold, in Celsuis
	 * offset 480
	 */
	float fanOffTemperature;
	/**
	 * offset 484
	 */
	adc_channel_e fuelLevelSensor;
	/**
	 * This coefficient translates vehicle speed input frequency (in Hz) into vehicle speed, km/h
	 * offset 488
	 */
	float vehicleSpeedCoef;
	/**
	 * offset 492
	 */
	can_nbc_e canNbcType;
	/**
	 * CANbus thread period, ms
	 * offset 496
	 */
	int canSleepPeriod;
	/**
	 * offset 500
	 */
	operation_mode_e operationMode;
	/**
	 * offset 504
	 */
	display_mode_e displayMode;
	/**
	 * offset 508
	 */
	log_format_e logFormat;
	/**
	 * offset 512
	 */
	int firmwareVersion;
	/**
	 * offset 516
	 */
	int HD44780width;
	/**
	 * offset 520
	 */
	int HD44780height;
	/**
	 * offset 524
	 */
	adc_channel_e tpsAdcChannel;
	/**
	 * offset 528
	 */
	int overrideCrankingIgnition;
	/**
	 * offset 532
	 */
	int sensorChartFrequency;
	/**
	 * offset 536
	 */
	trigger_config_s trigger;
	/**
	 * offset 564
	 */
	spi_device_e hip9011SpiDevice;
	/**
	 * offset 568
	 */
	float globalFuelCorrection;
	/**
	 * offset 572
	 */
	int16_t pedalPositionMin;
	/**
	 * offset 574
	 */
	int16_t pedalPositionMax;
	/**
	 * maximum total number of degrees to subtract from ignition advance
	 * when knocking
	 * offset 576
	 */
	float maxKnockSubDeg;
	/**
	 * offset 580
	 */
	adc_channel_e mafAdcChannel;
	/**
	 * @see hasAfrSensor
	 * offset 584
	 */
	afr_sensor_s afr;
	/**
	 * offset 604
	 */
	adc_channel_e pedalPositionChannel;
	/**
	 * @see hasBaroSensor
	 * offset 608
	 */
	air_pressure_sensor_config_s baroSensor;
	/**
	 * offset 624
	 */
	board_configuration_s bc;
	/**
	 * @see isMapAveragingEnabled
	offset 1488 bit 0 */
	bool hasMapSensor : 1;
	/**
	offset 1488 bit 1 */
	bool hasIatSensor : 1;
	/**
	offset 1488 bit 2 */
	bool hasBaroSensor : 1;
	/**
	offset 1488 bit 3 */
	bool hasAfrSensor : 1;
	/**
	offset 1488 bit 4 */
	bool useConstantDwellDuringCranking : 1;
	/**
	 * This options enables data for 'engine sniffer' tab in console, which comes at some CPU price
	offset 1488 bit 5 */
	bool isEngineChartEnabled : 1;
	/**
	offset 1488 bit 6 */
	bool isCanEnabled : 1;
	/**
	offset 1488 bit 7 */
	bool hasCltSensor : 1;
	/**
	offset 1488 bit 8 */
	bool canReadEnabled : 1;
	/**
	offset 1488 bit 9 */
	bool canWriteEnabled : 1;
	/**
	offset 1488 bit 10 */
	bool hasVehicleSpeedSensor : 1;
	/**
	offset 1488 bit 11 */
	bool isJoystickEnabled : 1;
	/**
	offset 1488 bit 12 */
	bool isGpsEnabled : 1;
	/**
	offset 1488 bit 13 */
	bool isAlternatorControlEnabled : 1;
	/**
	offset 1488 bit 14 */
	bool hasMafSensor : 1;
	/**
	offset 1488 bit 15 */
	bool hasTpsSensor : 1;
	/**
	offset 1488 bit 16 */
	bool cutFuelOnHardLimit : 1;
	/**
	offset 1488 bit 17 */
	bool cutSparkOnHardLimit : 1;
	/**
	offset 1488 bit 18 */
	bool step1fuelCutEnable : 1;
	/**
	offset 1488 bit 19 */
	bool step1SparkCutEnable : 1;
	/**
	offset 1488 bit 20 */
	bool hasFrequencyReportingMapSensor : 1;
	/**
	 * offset 1492
	 */
	adc_channel_e hipOutputChannel;
	/**
	 * offset 1496
	 */
	idle_mode_e idleMode;
	/**
	offset 1500 bit 0 */
	bool isInjectionEnabled : 1;
	/**
	offset 1500 bit 1 */
	bool isIgnitionEnabled : 1;
	/**
	offset 1500 bit 2 */
	bool isCylinderCleanupEnabled : 1;
	/**
	offset 1500 bit 3 */
	bool secondTriggerChannelEnabled : 1;
	/**
	offset 1500 bit 4 */
	bool needSecondTriggerInputDeprecated : 1;
	/**
	offset 1500 bit 5 */
	bool isMapAveragingEnabled : 1;
	/**
	offset 1500 bit 6 */
	bool isMilEnabled : 1;
	/**
	offset 1500 bit 7 */
	bool isFuelPumpEnabled : 1;
	/**
	offset 1500 bit 8 */
	bool isTunerStudioEnabled : 1;
	/**
	offset 1500 bit 9 */
	bool isWaveAnalyzerEnabled : 1;
	/**
	offset 1500 bit 10 */
	bool isIdleThreadEnabled : 1;
	/**
	offset 1500 bit 11 */
	bool isPrintTriggerSynchDetails : 1;
	/**
	 * Usually if we have no trigger events that means engine is stopped
	 * Unless we are troubleshooting and spinning the engine by hand - this case a longer
	 * delay is needed
	offset 1500 bit 12 */
	bool isManualSpinningMode : 1;
	/**
	 * This is needed if batched injection and individual injector wiring
	offset 1500 bit 13 */
	bool twoWireBatchInjection : 1;
	/**
	 * See #172
	offset 1500 bit 14 */
	bool useOnlyRisingEdgeForTrigger : 1;
	/**
	 * This is needed if batched igniton (waster spark) and individual coil wiring
	offset 1500 bit 15 */
	bool twoWireBatchIgnition : 1;
	/**
	 * offset 1504
	 */
	uint32_t engineChartSize;
	/**
	 * offset 1508
	 */
	int targetIdleRpm;
	/**
	 * A/C button input handled as analog input
	 * offset 1512
	 */
	adc_channel_e acSwitchAdc;
	/**
	 * At what trigger index should some ignition-related math be executed? This is a performance trick to reduce load on synchronization trigger callback.
	 * offset 1516
	 */
	int ignMathCalculateAtIndex;
	/**
	 * offset 1520
	 */
	int16_t acCutoffLowRpm;
	/**
	 * offset 1522
	 */
	int16_t acCutoffHighRpm;
	/**
	 * offset 1524
	 */
	int16_t acIdleRpmBump;
	/**
	 * offset 1526
	 */
	int16_t unusedShort;
	/**
	 * offset 1528
	 */
	adc_channel_e vRefAdcChannel;
	/**
	 * offset 1532
	 */
	float knockDetectionWindowStart;
	/**
	 * offset 1536
	 */
	float knockDetectionWindowEnd;
	/**
	 * offset 1540
	 */
	float idleStepperReactionTime;
	/**
	 * offset 1544
	 */
	float knockVThreshold;
	/**
	 * offset 1548
	 */
	pin_input_mode_e fsioInputModes[LE_COMMAND_COUNT];
	/**
	 * offset 1612
	 */
	adc_channel_e externalKnockSenseAdc;
	/**
	 * offset 1616
	 */
	int unsed2342342[3];
	/**
	 * offset 1628
	 */
	int idleStepperTotalSteps;
	/**
	 * offset 1632
	 */
	brain_pin_e stepperEnablePin;
	/**
	 * offset 1636
	 */
	float noAccelAfterHardLimitPeriodSecs;
	/**
	 * At what trigger index should some MAP-related math be executed? This is a performance trick to reduce load on synchronization trigger callback.
	 * offset 1640
	 */
	int mapAveragingSchedulingAtIndex;
	/**
	 * offset 1644
	 */
	float baroCorrPressureBins[BARO_CORR_SIZE];
	/**
	 * offset 1660
	 */
	float baroCorrRpmBins[BARO_CORR_SIZE];
	/**
	 * offset 1676
	 */
	baro_corr_table_t baroCorrTable;
	/**
	 * offset 1740
	 */
	int spi2SckMode;
	/**
	 * offset 1744
	 */
	int spi2MosiMode;
	/**
	 * offset 1748
	 */
	int spi2MisoMode;
	/**
	 * Cranking fuel correction coefficient based on TPS
	 * offset 1752
	 */
	float crankingTpsCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 1784
	 */
	float crankingTpsBins[CRANKING_CURVE_SIZE];
	/**
	 * offset 1816
	 */
	float tachPulseDuractionMs;
	/**
	 * trigger cycle index at which we start tach pulse (performance consideration)
	 * offset 1820
	 */
	int tachPulseTriggerIndex;
	/**
	 * offset 1824
	 */
	float suckedOffCoef;
	/**
	 * TODO make suckedOffCoef an array by RPM
	 * offset 1828
	 */
	float unused71[7];
	/**
	 * offset 1856
	 */
	float addedToWallCoef;
	/**
	 * TODO make addedToWallCoef an array by RPM
	 * offset 1860
	 */
	float unused72[7];
	/**
	 * kPa value which is too low to be true
	 * offset 1888
	 */
	float mapErrorDetectionTooLow;
	/**
	 * kPa value which is too high to be true
	 * offset 1892
	 */
	float mapErrorDetectionTooHigh;
	/**
	 * RPMs prior to step1rpm point where ignition advance is retarded
	 * offset 1896
	 */
	int step1RpmWindow;
	/**
	 * offset 1900
	 */
	pid_s idleRpmPid;
	/**
	 * offset 1916
	 */
	int idleDT;
	/**
	 * offset 1920
	 */
	idle_control_e idleControl;
	/**
	 * offset 1924
	 */
	brain_pin_e communicationPin;
	/**
	 * offset 1928
	 */
	brain_pin_e runningPin;
	/**
	 * offset 1932
	 */
	brain_pin_e binarySerialTxPin;
	/**
	 * offset 1936
	 */
	brain_pin_e binarySerialRxPin;
	/**
	 * offset 1940
	 */
	brain_pin_e consoleSerialTxPin;
	/**
	 * offset 1944
	 */
	brain_pin_e consoleSerialRxPin;
	/**
	 * Knock sensor output knock detection threshold depending on current RPM
	 * offset 1948
	 */
	float knockNoise[ENGINE_NOISE_CURVE_SIZE];
	/**
	 * offset 1980
	 */
	float knockNoiseRpmBins[ENGINE_NOISE_CURVE_SIZE];
	/**
	 * offset 2012
	 */
	pid_s etb;
	/**
	 * CLT-based target RPM for automatic idle controller
	 * offset 2028
	 */
	float cltIdleRpmBins[CLT_CURVE_SIZE];
	/**
	 * offset 2092
	 */
	float cltIdleRpm[CLT_CURVE_SIZE];
	/**
	 * offset 2156
	 */
	float targetVBatt;
	/**
	 * Turn off alternator output above specified TPS
	 * offset 2160
	 */
	float alternatorOffAboveTps;
	/**
	 * PID dTime
	 * offset 2164
	 */
	int alternatorDT;
	/**
	 * offset 2168
	 */
	pid_s alternatorControl;
	/**
	 * offset 2184
	 */
	int tpsAccelLength;
	/**
	 * offset 2188
	 */
	float tpsAccelEnrichmentThreshold;
	/**
	 * offset 2192
	 */
	float tpsAccelEnrichmentMultiplier;
	/**
	 * offset 2196
	 */
	int engineLoadAccelLength;
	/**
	 * offset 2200
	 */
	float engineLoadDecelEnleanmentThreshold;
	/**
	 * offset 2204
	 */
	float engineLoadDecelEnleanmentMultiplier;
	/**
	 * offset 2208
	 */
	float engineLoadAccelEnrichmentThreshold;
	/**
	 * offset 2212
	 */
	float engineLoadAccelEnrichmentMultiplier;
	/**
	 * offset 2216
	 */
	brain_pin_e fatalErrorPin;
	/**
	 * offset 2220
	 */
	brain_pin_e warninigPin;
	/**
	 * offset 2224
	 */
	brain_pin_e configResetPin;
	/**
	 * offset 2228
	 */
	uint32_t uartConsoleSerialSpeed;
	/**
	 * offset 2232
	 */
	float tpsDecelEnleanmentThreshold;
	/**
	 * offset 2236
	 */
	float tpsDecelEnleanmentMultiplier;
	/**
	 * offset 2240
	 */
	float slowAdcAlpha;
	/**
	 * offset 2244
	 */
	debug_mode_e debugMode;
	/**
	 * offset 2248
	 */
	pid_s warmupAfrPid;
	/**
	 * CLT-based target AFR for PID-based control
	 * offset 2264
	 */
	float warmupTargetAfrBins[WARMUP_TARGET_AFR_SIZE];
	/**
	 * offset 2280
	 */
	float warmupTargetAfr[WARMUP_TARGET_AFR_SIZE];
	/**
	 * offset 2296
	 */
	float warmupAfrThreshold;
	/**
	 * kPa value at which we need to cut fuel and spark, 0 if not enabled
	 * offset 2300
	 */
	float boostCutPressure;
	/**
	 * offset 2304
	 */
	float mapAccelTaper[MAP_ACCEL_TAPER];
	/**
	 * offset 2336
	 */
	int unused[178];
	/** total size 3048*/
} engine_configuration_s;

typedef struct {
	/**
	 * offset 0
	 */
	engine_configuration_s engineConfiguration;
	/**
	 * offset 3048
	 */
	le_formula_t le_formulas[LE_COMMAND_COUNT];
	/**
	 * offset 6248
	 */
	le_formula_t timingMultiplier;
	/**
	 * offset 6448
	 */
	le_formula_t timingAdditive;
	/**
	 * offset 6648
	 */
	float cltFuelCorrBins[CLT_CURVE_SIZE];
	/**
	 * offset 6712
	 */
	float cltFuelCorr[CLT_CURVE_SIZE];
	/**
	 * offset 6776
	 */
	float iatFuelCorrBins[IAT_CURVE_SIZE];
	/**
	 * offset 6840
	 */
	float iatFuelCorr[IAT_CURVE_SIZE];
	/**
	 * offset 6904
	 */
	float crankingFuelCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 6936
	 */
	float crankingFuelBins[CRANKING_CURVE_SIZE];
	/**
	 * offset 6968
	 */
	float crankingCycleCoef[CRANKING_CURVE_SIZE];
	/**
	 * offset 7000
	 */
	float crankingCycleBins[CRANKING_CURVE_SIZE];
	/**
	 * CLT-based adjustment for simple manual idle controller
	 * offset 7032
	 */
	float cltIdleCorrBins[CLT_CURVE_SIZE];
	/**
	 * offset 7096
	 */
	float cltIdleCorr[CLT_CURVE_SIZE];
	/**
	 * kg/hour value.
	 * By the way 2.081989116 kg/h = 1 ft�/m
	 * offset 7160
	 */
	float mafDecoding[MAF_DECODING_COUNT];
	/**
	 * offset 8184
	 */
	float mafDecodingBins[MAF_DECODING_COUNT];
	/**
	 * offset 9208
	 */
	angle_table_t ignitionIatCorrTable;
	/**
	 * offset 10232
	 */
	float ignitionIatCorrLoadBins[IGN_LOAD_COUNT];
	/**
	 * offset 10296
	 */
	float ignitionIatCorrRpmBins[IGN_RPM_COUNT];
	/**
	 * offset 10360
	 */
	angle_table_t injectionPhase;
	/**
	 * offset 11384
	 */
	float injPhaseLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 11448
	 */
	float injPhaseRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 11512
	 */
	fuel_table_t fuelTable;
	/**
	 * offset 12536
	 */
	float fuelLoadBins[FUEL_LOAD_COUNT];
	/**
	 * RPM is float and not integer in order to use unified methods for interpolation
	 * offset 12600
	 */
	float fuelRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 12664
	 */
	ignition_table_t ignitionTable;
	/**
	 * offset 13688
	 */
	float ignitionLoadBins[IGN_LOAD_COUNT];
	/**
	 * offset 13752
	 */
	float ignitionRpmBins[IGN_RPM_COUNT];
	/**
	 * offset 13816
	 */
	ve_table_t veTable;
	/**
	 * offset 14840
	 */
	float veLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 14904
	 */
	float veRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 14968
	 */
	afr_table_t afrTable;
	/**
	 * offset 15992
	 */
	float afrLoadBins[FUEL_LOAD_COUNT];
	/**
	 * offset 16056
	 */
	float afrRpmBins[FUEL_RPM_COUNT];
	/**
	 * offset 16120
	 */
	tps_tps_table_t tpsTpsAccelTable;
	/**
	 * offset 16376
	 */
	float tpsTpsAccelFromRpmBins[TPS_TPS_ACCEL_TABLE];
	/**
	 * RPM is float and not integer in order to use unified methods for interpolation
	 * offset 16408
	 */
	float tpsTpsAccelToRpmBins[TPS_TPS_ACCEL_TABLE];
	/**
	 * offset 16440
	 */
	fsio_table_8x8_t fsioTable1;
	/**
	 * offset 16696
	 */
	float fsioTable1LoadBins[FSIO_TABLE_8];
	/**
	 * RPM is float and not integer in order to use unified methods for interpolation
	 * offset 16728
	 */
	float fsioTable1RpmBins[FSIO_TABLE_8];
	/**
	 * offset 16760
	 */
	fsio_table_8x8_t fsioTable2;
	/**
	 * offset 17016
	 */
	float fsioTable2LoadBins[FSIO_TABLE_8];
	/**
	 * RPM is float and not integer in order to use unified methods for interpolation
	 * offset 17048
	 */
	float fsioTable2RpmBins[FSIO_TABLE_8];
	/** total size 17080*/
} persistent_config_s;

#endif
// end
// this section was generated automatically by ConfigDefinition.jar based on rusefi_config.txt Tue Mar 08 23:31:32 EST 2016
