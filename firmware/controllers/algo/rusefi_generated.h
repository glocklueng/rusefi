#define LE_COMMAND_LENGTH 200
#define TS_FILE_VERSION 20150522
#define MAP_ANGLE_SIZE 8
#define MAP_WINDOW_SIZE 8
#define CLT_CURVE_SIZE 16
#define IAT_CURVE_SIZE 16
#define VBAT_INJECTOR_CURVE_SIZE 8
#define DWELL_CURVE_SIZE 8
#define CRANKING_CURVE_SIZE 8
#define IGN_LOAD_COUNT 16
#define IGN_RPM_COUNT 16
#define INJECTION_PIN_COUNT 12
#define IGNITION_PIN_COUNT 12
#define EGT_CHANNEL_COUNT 8
#define JOYSTICK_PIN_COUNT 5
#define DIGIPOT_COUNT 4
#define HW_MAX_ADC_INDEX 16
#define TRIGGER_SIMULATOR_PIN_COUNT 3
#define LOGIC_ANALYZER_CHANNEL_COUNT 4
#define LE_COMMAND_COUNT 16
#define FUEL_RPM_COUNT 16
#define FUEL_LOAD_COUNT 16
#define BARO_CORR_SIZE 4
#define MAF_DECODING_COUNT 256
#define engineConfiguration_offset 0
#define engineConfiguration_offset_hex 0
#define engineType_offset 0
#define engineType_offset_hex 0
#define headerMagicValue_offset 4
#define headerMagicValue_offset_hex 4
#define injector_offset 8
#define injector_offset_hex 8
#define injector_flow_offset 8
#define injector_flow_offset_hex 8
#define injector_lag_offset 12
#define injector_battLagCorrBins_offset 16
#define injector_battLagCorrBins_offset_hex 10
#define injector_battLagCorr_offset 48
#define injector_battLagCorr_offset_hex 30
#define directSelfStimulation_offset 80
#define directSelfStimulation_offset_hex 50
#define tpsMin_offset 84
#define tpsMin_offset_hex 54
#define tpsMax_offset 86
#define tpsMax_offset_hex 56
#define tpsErrorLowValue_offset 88
#define tpsErrorLowValue_offset_hex 58
#define tpsErrorHighValue_offset 90
#define cranking_offset 92
#define cranking_baseFuel_offset 92
#define cranking_rpm_offset 96
#define cranking_rpm_offset_hex 60
#define cranking_alignmentFill_offset 98
#define cranking_alignmentFill_offset_hex 62
#define primingSquirtDurationMs_offset 100
#define primingSquirtDurationMs_offset_hex 64
#define ignitionDwellForCrankingMs_offset 104
#define ignitionDwellForCrankingMs_offset_hex 68
#define crankingChargeAngle_offset 108
#define map_offset 112
#define map_offset_hex 70
#define map_samplingAngleBins_offset 112
#define map_samplingAngleBins_offset_hex 70
#define map_samplingAngle_offset 144
#define map_samplingAngle_offset_hex 90
#define map_samplingWindowBins_offset 176
#define map_samplingWindow_offset 208
#define map_sensor_offset 240
#define map_sensor_valueAt0_offset 240
#define map_sensor_valueAt5_offset 244
#define map_sensor_type_offset 248
#define map_sensor_hwChannel_offset 252
#define clt_offset 256
#define clt_offset_hex 100
#define clt_config_offset 256
#define clt_config_offset_hex 100
#define clt_tempC_1_offset 256
#define clt_tempC_1_offset_hex 100
#define clt_tempC_2_offset 260
#define clt_tempC_2_offset_hex 104
#define clt_tempC_3_offset 264
#define clt_tempC_3_offset_hex 108
#define clt_resistance_1_offset 268
#define clt_resistance_2_offset 272
#define clt_resistance_2_offset_hex 110
#define clt_resistance_3_offset 276
#define clt_resistance_3_offset_hex 114
#define clt_bias_resistor_offset 280
#define clt_bias_resistor_offset_hex 118
#define clt_adcChannel_offset 284
#define iat_offset 288
#define iat_offset_hex 120
#define iat_config_offset 288
#define iat_config_offset_hex 120
#define iat_tempC_1_offset 288
#define iat_tempC_1_offset_hex 120
#define iat_tempC_2_offset 292
#define iat_tempC_2_offset_hex 124
#define iat_tempC_3_offset 296
#define iat_tempC_3_offset_hex 128
#define iat_resistance_1_offset 300
#define iat_resistance_2_offset 304
#define iat_resistance_2_offset_hex 130
#define iat_resistance_3_offset 308
#define iat_resistance_3_offset_hex 134
#define iat_bias_resistor_offset 312
#define iat_bias_resistor_offset_hex 138
#define iat_adcChannel_offset 316
#define step1rpm_offset 320
#define step1rpm_offset_hex 140
#define step1timing_offset 324
#define step1timing_offset_hex 144
#define hip9011PrescalerAndSDO_offset 328
#define hip9011PrescalerAndSDO_offset_hex 148
#define knockBandCustom_offset 332
#define sparkDwellBins_offset 336
#define sparkDwellBins_offset_hex 150
#define sparkDwell_offset 368
#define sparkDwell_offset_hex 170
#define specs_offset 400
#define specs_offset_hex 190
#define displacement_offset 400
#define displacement_offset_hex 190
#define cylindersCount_offset 404
#define cylindersCount_offset_hex 194
#define firingOrder_offset 408
#define firingOrder_offset_hex 198
#define cylinderBore_offset 412
#define engineCycle_offset 416
#define rpmHardLimit_offset 420
#define algorithm_offset 424
#define crankingInjectionMode_offset 428
#define injectionMode_offset 432
#define injectionAngle_offset 436
#define crankingTimingAngle_offset 440
#define ignitionMode_offset 444
#define ignitionBaseAngle_offset 448
#define timingMode_offset 452
#define fixedModeTiming_offset 456
#define globalTriggerAngleOffset_offset 460
#define analogInputDividerCoefficient_offset 464
#define vbattDividerCoeff_offset 468
#define vbattAdcChannel_offset 472
#define fanOnTemperature_offset 476
#define fanOffTemperature_offset 480
#define ususedBla_offset 484
#define vehicleSpeedCoef_offset 488
#define canNbcType_offset 492
#define canSleepPeriod_offset 496
#define operationMode_offset 500
#define displayMode_offset 504
#define logFormat_offset 508
#define firmwareVersion_offset 512
#define firmwareVersion_offset_hex 200
#define HD44780width_offset 516
#define HD44780width_offset_hex 204
#define HD44780height_offset 520
#define HD44780height_offset_hex 208
#define tpsAdcChannel_offset 524
#define overrideCrankingIgnition_offset 528
#define overrideCrankingIgnition_offset_hex 210
#define sensorChartFrequency_offset 532
#define sensorChartFrequency_offset_hex 214
#define trigger_offset 536
#define trigger_offset_hex 218
#define trigger_type_offset 536
#define trigger_type_offset_hex 218
#define trigger_customIsSynchronizationNeeded_offset 540
#define trigger_customNeedSecondTriggerInput_offset 540
#define trigger_customTotalToothCount_offset 544
#define trigger_customTotalToothCount_offset_hex 220
#define trigger_customSkippedToothCount_offset 548
#define trigger_customSkippedToothCount_offset_hex 224
#define trigger_customSyncRatioFrom_offset 552
#define trigger_customSyncRatioFrom_offset_hex 228
#define trigger_customSyncRatioTo_offset 556
#define trigger_customUseRiseEdge_offset 560
#define trigger_customUseRiseEdge_offset_hex 230
#define hip9011SpiDevice_offset 564
#define hip9011SpiDevice_offset_hex 234
#define globalFuelCorrection_offset 568
#define globalFuelCorrection_offset_hex 238
#define pedalPositionMin_offset 572
#define pedalPositionMax_offset 574
#define unused12_offset 576
#define unused12_offset_hex 240
#define mafAdcChannel_offset 580
#define mafAdcChannel_offset_hex 244
#define afr_offset 584
#define afr_offset_hex 248
#define afr_hwChannel_offset 584
#define afr_hwChannel_offset_hex 248
#define afr_v1_offset 588
#define afr_value1_offset 592
#define afr_value1_offset_hex 250
#define afr_v2_offset 596
#define afr_v2_offset_hex 254
#define afr_value2_offset 600
#define afr_value2_offset_hex 258
#define pedalPositionChannel_offset 604
#define baroSensor_offset 608
#define baroSensor_offset_hex 260
#define baroSensor_valueAt0_offset 608
#define baroSensor_valueAt0_offset_hex 260
#define baroSensor_valueAt5_offset 612
#define baroSensor_valueAt5_offset_hex 264
#define baroSensor_type_offset 616
#define baroSensor_type_offset_hex 268
#define baroSensor_hwChannel_offset 620
#define bc_offset 624
#define bc_offset_hex 270
#define idle_offset 624
#define idle_offset_hex 270
#define idle_solenoidPin_offset 624
#define idle_solenoidPin_offset_hex 270
#define idle_solenoidPinMode_offset 628
#define idle_solenoidPinMode_offset_hex 274
#define idle_solenoidFrequency_offset 632
#define idle_solenoidFrequency_offset_hex 278
#define idle_stepperDirectionPin_offset 636
#define idle_stepperStepPin_offset 640
#define idle_stepperStepPin_offset_hex 280
#define idlePosition_offset 644
#define idlePosition_offset_hex 284
#define fuelPumpPin_offset 648
#define fuelPumpPin_offset_hex 288
#define fuelPumpPinMode_offset 652
#define injectionPins1_offset 656
#define injectionPins1_offset_hex 290
#define injectionPins2_offset 660
#define injectionPins2_offset_hex 294
#define injectionPins3_offset 664
#define injectionPins3_offset_hex 298
#define injectionPins4_offset 668
#define injectionPins5_offset 672
#define injectionPins6_offset 676
#define injectionPins7_offset 680
#define injectionPins8_offset 684
#define injectionPins9_offset 688
#define injectionPins10_offset 692
#define injectionPins11_offset 696
#define injectionPins12_offset 700
#define injectionPinMode_offset 704
#define ignitionPins1_offset 708
#define ignitionPins2_offset 712
#define ignitionPins3_offset 716
#define ignitionPins4_offset 720
#define ignitionPins5_offset 724
#define ignitionPins6_offset 728
#define ignitionPins7_offset 732
#define ignitionPins8_offset 736
#define ignitionPins9_offset 740
#define ignitionPins10_offset 744
#define ignitionPins11_offset 748
#define ignitionPins12_offset 752
#define ignitionPinMode_offset 756
#define malfunctionIndicatorPin_offset 760
#define malfunctionIndicatorPinMode_offset 764
#define fanPin_offset 768
#define fanPin_offset_hex 300
#define fanPinMode_offset 772
#define fanPinMode_offset_hex 304
#define unuseddddd1_offset 776
#define unuseddddd1_offset_hex 308
#define unuseddddd2_offset 780
#define clutchDownPin_offset 784
#define clutchDownPin_offset_hex 310
#define clutchDownPinMode_offset 788
#define clutchDownPinMode_offset_hex 314
#define alternatorControlPin_offset 792
#define alternatorControlPin_offset_hex 318
#define alternatorControlPinMode_offset 796
#define HD44780_rs_offset 800
#define HD44780_rs_offset_hex 320
#define HD44780_e_offset 804
#define HD44780_e_offset_hex 324
#define HD44780_db4_offset 808
#define HD44780_db4_offset_hex 328
#define HD44780_db5_offset 812
#define HD44780_db6_offset 816
#define HD44780_db6_offset_hex 330
#define HD44780_db7_offset 820
#define HD44780_db7_offset_hex 334
#define gps_rx_pin_offset 824
#define gps_rx_pin_offset_hex 338
#define gps_tx_pin_offset 828
#define triggerSimulatorFrequency_offset 832
#define triggerSimulatorFrequency_offset_hex 340
#define digitalPotentiometerSpiDevice_offset 836
#define digitalPotentiometerSpiDevice_offset_hex 344
#define digitalPotentiometerChipSelect1_offset 840
#define digitalPotentiometerChipSelect1_offset_hex 348
#define digitalPotentiometerChipSelect2_offset 844
#define digitalPotentiometerChipSelect3_offset 848
#define digitalPotentiometerChipSelect3_offset_hex 350
#define digitalPotentiometerChipSelect4_offset 852
#define digitalPotentiometerChipSelect4_offset_hex 354
#define etbDirectionPin1_offset 856
#define etbDirectionPin1_offset_hex 358
#define etbDirectionPin2_offset 860
#define etbControlPin1_offset 864
#define etbControlPin1_offset_hex 360
#define etbControlPin2_offset 868
#define etbControlPin2_offset_hex 364
#define electronicThrottlePin1Mode_offset 872
#define electronicThrottlePin1Mode_offset_hex 368
#define etbPFactor_offset 876
#define etbIFactor_offset 880
#define etbIFactor_offset_hex 370
#define unusedADC_offset 884
#define unusedADC_offset_hex 374
#define triggerInputPins1_offset 920
#define triggerInputPins1_offset_hex 398
#define triggerInputPins2_offset 924
#define triggerInputPins3_offset 928
#define mainRelayPin_offset 932
#define idleThreadPeriod_offset 936
#define consoleLoopPeriod_offset 940
#define lcdThreadPeriod_offset 944
#define sdCardCsPin_offset 948
#define generalPeriodicThreadPeriod_offset 952
#define tunerStudioSerialSpeed_offset 956
#define boardTestModeJumperPin_offset 960
#define canDeviceMode_offset 964
#define canTxPin_offset 968
#define canRxPin_offset 972
#define triggerSimulatorPins1_offset 976
#define triggerSimulatorPins2_offset 980
#define triggerSimulatorPins3_offset 984
#define triggerSimulatorPinModes1_offset 988
#define triggerSimulatorPinModes2_offset 992
#define triggerSimulatorPinModes3_offset 996
#define o2heaterPin_offset 1000
#define o2heaterPinModeTodO_offset 1004
#define is_enabled_spi_1_offset 1008
#define is_enabled_spi_2_offset 1008
#define is_enabled_spi_3_offset 1008
#define isSdCardEnabled_offset 1008
#define isFastAdcEnabled_offset 1008
#define isEngineControlEnabled_offset 1008
#define isHip9011Enabled_offset 1008
#define isVerboseAlternator_offset 1008
#define useSerialPort_offset 1008
#define useStepperIdle_offset 1008
#define enabledStep1Limiter_offset 1008
#define logicAnalyzerPins1_offset 1012
#define logicAnalyzerPins2_offset 1016
#define logicAnalyzerPins3_offset 1020
#define logicAnalyzerPins4_offset 1024
#define logicAnalyzerPins4_offset_hex 400
#define logicAnalyzerMode_offset 1028
#define logicAnalyzerMode_offset_hex 404
#define unrealisticRpmThreashold_offset 1032
#define unrealisticRpmThreashold_offset_hex 408
#define mainRelayPinMode_offset 1036
#define max31855_cs1_offset 1040
#define max31855_cs1_offset_hex 410
#define max31855_cs2_offset 1044
#define max31855_cs2_offset_hex 414
#define max31855_cs3_offset 1048
#define max31855_cs3_offset_hex 418
#define max31855_cs4_offset 1052
#define max31855_cs5_offset 1056
#define max31855_cs5_offset_hex 420
#define max31855_cs6_offset 1060
#define max31855_cs6_offset_hex 424
#define max31855_cs7_offset 1064
#define max31855_cs7_offset_hex 428
#define max31855_cs8_offset 1068
#define max31855spiDevice_offset 1072
#define max31855spiDevice_offset_hex 430
#define fsioPins1_offset 1076
#define fsioPins1_offset_hex 434
#define fsioPins2_offset 1080
#define fsioPins2_offset_hex 438
#define fsioPins3_offset 1084
#define fsioPins4_offset 1088
#define fsioPins4_offset_hex 440
#define fsioPins5_offset 1092
#define fsioPins5_offset_hex 444
#define fsioPins6_offset 1096
#define fsioPins6_offset_hex 448
#define fsioPins7_offset 1100
#define fsioPins8_offset 1104
#define fsioPins8_offset_hex 450
#define fsioPins9_offset 1108
#define fsioPins9_offset_hex 454
#define fsioPins10_offset 1112
#define fsioPins10_offset_hex 458
#define fsioPins11_offset 1116
#define fsioPins12_offset 1120
#define fsioPins12_offset_hex 460
#define fsioPins13_offset 1124
#define fsioPins13_offset_hex 464
#define fsioPins14_offset 1128
#define fsioPins14_offset_hex 468
#define fsioPins15_offset 1132
#define fsioPins16_offset 1136
#define fsioPins16_offset_hex 470
#define gpioPinModes1_offset 1140
#define gpioPinModes1_offset_hex 474
#define gpioPinModes2_offset 1144
#define gpioPinModes2_offset_hex 478
#define gpioPinModes3_offset 1148
#define gpioPinModes4_offset 1152
#define gpioPinModes4_offset_hex 480
#define gpioPinModes5_offset 1156
#define gpioPinModes5_offset_hex 484
#define gpioPinModes6_offset 1160
#define gpioPinModes6_offset_hex 488
#define gpioPinModes7_offset 1164
#define gpioPinModes8_offset 1168
#define gpioPinModes8_offset_hex 490
#define gpioPinModes9_offset 1172
#define gpioPinModes9_offset_hex 494
#define gpioPinModes10_offset 1176
#define gpioPinModes10_offset_hex 498
#define gpioPinModes11_offset 1180
#define gpioPinModes12_offset 1184
#define gpioPinModes13_offset 1188
#define gpioPinModes14_offset 1192
#define gpioPinModes15_offset 1196
#define gpioPinModes16_offset 1200
#define joystickPins1_offset 1204
#define joystickPins2_offset 1208
#define joystickPins3_offset 1212
#define joystickPins4_offset 1216
#define joystickPins5_offset 1220
#define triggerErrorPin_offset 1224
#define triggerErrorPinMode_offset 1228
#define acRelayPin_offset 1232
#define acRelayPinMode_offset 1236
#define fsioFrequency1_offset 1240
#define fsioFrequency2_offset 1242
#define fsioFrequency3_offset 1244
#define fsioFrequency4_offset 1246
#define fsioFrequency5_offset 1248
#define fsioFrequency6_offset 1250
#define fsioFrequency7_offset 1252
#define fsioFrequency8_offset 1254
#define fsioFrequency9_offset 1256
#define fsioFrequency10_offset 1258
#define fsioFrequency11_offset 1260
#define fsioFrequency12_offset 1262
#define fsioFrequency13_offset 1264
#define fsioFrequency14_offset 1266
#define fsioFrequency15_offset 1268
#define fsioFrequency16_offset 1270
#define hip9011CsPin_offset 1272
#define hip9011IntHoldPin_offset 1276
#define unused113234_offset 1280
#define unused113234_offset_hex 500
#define fsio_setting1_offset 1284
#define fsio_setting1_offset_hex 504
#define fsio_setting2_offset 1288
#define fsio_setting2_offset_hex 508
#define fsio_setting3_offset 1292
#define fsio_setting4_offset 1296
#define fsio_setting4_offset_hex 510
#define fsio_setting5_offset 1300
#define fsio_setting5_offset_hex 514
#define fsio_setting6_offset 1304
#define fsio_setting6_offset_hex 518
#define fsio_setting7_offset 1308
#define fsio_setting8_offset 1312
#define fsio_setting8_offset_hex 520
#define fsio_setting9_offset 1316
#define fsio_setting9_offset_hex 524
#define fsio_setting10_offset 1320
#define fsio_setting10_offset_hex 528
#define fsio_setting11_offset 1324
#define fsio_setting12_offset 1328
#define fsio_setting12_offset_hex 530
#define fsio_setting13_offset 1332
#define fsio_setting13_offset_hex 534
#define fsio_setting14_offset 1336
#define fsio_setting14_offset_hex 538
#define fsio_setting15_offset 1340
#define fsio_setting16_offset 1344
#define fsio_setting16_offset_hex 540
#define spi1mosiPin_offset 1348
#define spi1mosiPin_offset_hex 544
#define spi1misoPin_offset 1352
#define spi1misoPin_offset_hex 548
#define spi1sckPin_offset 1356
#define spi2mosiPin_offset 1360
#define spi2mosiPin_offset_hex 550
#define spi2misoPin_offset 1364
#define spi2misoPin_offset_hex 554
#define spi2sckPin_offset 1368
#define spi2sckPin_offset_hex 558
#define spi3mosiPin_offset 1372
#define spi3misoPin_offset 1376
#define spi3misoPin_offset_hex 560
#define spi3sckPin_offset 1380
#define spi3sckPin_offset_hex 564
#define hip9011Gain_offset 1384
#define hip9011Gain_offset_hex 568
#define joystickCenterPin_offset 1388
#define joystickAPin_offset 1392
#define joystickAPin_offset_hex 570
#define joystickBPin_offset 1396
#define joystickBPin_offset_hex 574
#define joystickCPin_offset 1400
#define joystickCPin_offset_hex 578
#define joystickDPin_offset 1404
#define sensorChartMode_offset 1408
#define sensorChartMode_offset_hex 580
#define mafSensorType_offset 1412
#define mafSensorType_offset_hex 584
#define vehicleSpeedSensorInputPin_offset 1416
#define vehicleSpeedSensorInputPin_offset_hex 588
#define clutchUpPin_offset 1420
#define clutchUpPinMode_offset 1424
#define clutchUpPinMode_offset_hex 590
#define fsioDigitalInputs1_offset 1428
#define fsioDigitalInputs1_offset_hex 594
#define fsioDigitalInputs2_offset 1432
#define fsioDigitalInputs2_offset_hex 598
#define fsioDigitalInputs3_offset 1436
#define fsioDigitalInputs4_offset 1440
#define fsioDigitalInputs5_offset 1444
#define fsioDigitalInputs6_offset 1448
#define fsioDigitalInputs7_offset 1452
#define fsioDigitalInputs8_offset 1456
#define fsioDigitalInputs9_offset 1460
#define fsioDigitalInputs10_offset 1464
#define fsioDigitalInputs11_offset 1468
#define fsioDigitalInputs12_offset 1472
#define fsioDigitalInputs13_offset 1476
#define fsioDigitalInputs14_offset 1480
#define fsioDigitalInputs15_offset 1484
#define fsioDigitalInputs16_offset 1488
#define frequencyReportingMapInputPin_offset 1492
#define hasMapSensor_offset 1496
#define hasIatSensor_offset 1496
#define hasBaroSensor_offset 1496
#define hasAfrSensor_offset 1496
#define useConstantDwellDuringCranking_offset 1496
#define isEngineChartEnabled_offset 1496
#define isCanEnabled_offset 1496
#define hasCltSensor_offset 1496
#define canReadEnabled_offset 1496
#define canWriteEnabled_offset 1496
#define hasVehicleSpeedSensor_offset 1496
#define isJoystickEnabled_offset 1496
#define isGpsEnabled_offset 1496
#define isAlternatorControlEnabled_offset 1496
#define hasMafSensor_offset 1496
#define hasTpsSensor_offset 1496
#define cutFuelOnHardLimit_offset 1496
#define cutSparkOnHardLimit_offset 1496
#define hasFrequencyReportingMapSensor_offset 1496
#define hipOutputChannel_offset 1500
#define idleMode_offset 1504
#define isInjectionEnabled_offset 1508
#define isIgnitionEnabled_offset 1508
#define isCylinderCleanupEnabled_offset 1508
#define secondTriggerChannelEnabled_offset 1508
#define needSecondTriggerInputDeprecated_offset 1508
#define isMapAveragingEnabled_offset 1508
#define isMilEnabled_offset 1508
#define isFuelPumpEnabled_offset 1508
#define isTunerStudioEnabled_offset 1508
#define isWaveAnalyzerEnabled_offset 1508
#define isIdleThreadEnabled_offset 1508
#define isPrintTriggerSynchDetails_offset 1508
#define isManualSpinningMode_offset 1508
#define twoWireBatch_offset 1508
#define useOnlyFrontForTrigger_offset 1508
#define engineChartSize_offset 1512
#define targetIdleRpm_offset 1516
#define acSwitchAdc_offset 1520
#define ignMathCalculateAtIndex_offset 1524
#define acCutoffLowRpm_offset 1528
#define acCutoffHighRpm_offset 1530
#define acIdleRpmBump_offset 1532
#define unusedShort_offset 1534
#define vRefAdcChannel_offset 1536
#define vRefAdcChannel_offset_hex 600
#define knockDetectionWindowStart_offset 1540
#define knockDetectionWindowStart_offset_hex 604
#define knockDetectionWindowEnd_offset 1544
#define knockDetectionWindowEnd_offset_hex 608
#define idleStepperReactionTime_offset 1548
#define hipThreshold_offset 1552
#define hipThreshold_offset_hex 610
#define fsioInputModes1_offset 1556
#define fsioInputModes1_offset_hex 614
#define fsioInputModes2_offset 1560
#define fsioInputModes2_offset_hex 618
#define fsioInputModes3_offset 1564
#define fsioInputModes4_offset 1568
#define fsioInputModes4_offset_hex 620
#define fsioInputModes5_offset 1572
#define fsioInputModes5_offset_hex 624
#define fsioInputModes6_offset 1576
#define fsioInputModes6_offset_hex 628
#define fsioInputModes7_offset 1580
#define fsioInputModes8_offset 1584
#define fsioInputModes8_offset_hex 630
#define fsioInputModes9_offset 1588
#define fsioInputModes9_offset_hex 634
#define fsioInputModes10_offset 1592
#define fsioInputModes10_offset_hex 638
#define fsioInputModes11_offset 1596
#define fsioInputModes12_offset 1600
#define fsioInputModes12_offset_hex 640
#define fsioInputModes13_offset 1604
#define fsioInputModes13_offset_hex 644
#define fsioInputModes14_offset 1608
#define fsioInputModes14_offset_hex 648
#define fsioInputModes15_offset 1612
#define fsioInputModes16_offset 1616
#define fsioInputModes16_offset_hex 650
#define externalKnockSenseAdc_offset 1620
#define externalKnockSenseAdc_offset_hex 654
#define unsed2342342_offset 1624
#define unsed2342342_offset_hex 658
#define idleStepperTotalSteps_offset 1636
#define idleStepperTotalSteps_offset_hex 664
#define stepperEnablePin_offset 1640
#define stepperEnablePin_offset_hex 668
#define noAccelAfterHardLimitPeriodSecs_offset 1644
#define mapAveragingSchedulingAtIndex_offset 1648
#define mapAveragingSchedulingAtIndex_offset_hex 670
#define baroCorrPressureBins_offset 1652
#define baroCorrPressureBins_offset_hex 674
#define baroCorrRpmBins_offset 1668
#define baroCorrRpmBins_offset_hex 684
#define baroCorrTable_offset 1684
#define baroCorrTable_offset_hex 694
#define unused3_offset 1748
#define targetVBatt_offset 2156
#define alternatorOffAboveTps_offset 2160
#define alternatorOffAboveTps_offset_hex 870
#define alternatorDT_offset 2164
#define alternatorDT_offset_hex 874
#define alternatorOffset_offset 2168
#define alternatorOffset_offset_hex 878
#define alternatorControlPFactor_offset 2172
#define alternatorControlIFactor_offset 2176
#define alternatorControlIFactor_offset_hex 880
#define alternatorControlDFactor_offset 2180
#define alternatorControlDFactor_offset_hex 884
#define tpsAccelLength_offset 2184
#define tpsAccelLength_offset_hex 888
#define tpsAccelEnrichmentThreshold_offset 2188
#define tpsAccelEnrichmentMultiplier_offset 2192
#define tpsAccelEnrichmentMultiplier_offset_hex 890
#define mapAccelLength_offset 2196
#define mapAccelLength_offset_hex 894
#define decelEnrichmentThreshold_offset 2200
#define decelEnrichmentThreshold_offset_hex 898
#define decelEnrichmentMultiplier_offset 2204
#define mapAccelEnrichmentThreshold_offset 2208
#define mapAccelEnrichmentMultiplier_offset 2212
#define le_formulas1_offset 2216
#define le_formulas2_offset 2416
#define le_formulas2_offset_hex 970
#define le_formulas3_offset 2616
#define le_formulas4_offset 2816
#define le_formulas5_offset 3016
#define le_formulas6_offset 3216
#define le_formulas7_offset 3416
#define le_formulas8_offset 3616
#define le_formulas9_offset 3816
#define le_formulas10_offset 4016
#define le_formulas11_offset 4216
#define le_formulas11_offset_hex 1078
#define le_formulas12_offset 4416
#define le_formulas12_offset_hex 1140
#define le_formulas13_offset 4616
#define le_formulas13_offset_hex 1208
#define le_formulas14_offset 4816
#define le_formulas15_offset 5016
#define le_formulas15_offset_hex 1398
#define le_formulas16_offset 5216
#define le_formulas16_offset_hex 1460
#define timingMultiplier_offset 5416
#define timingMultiplier_offset_hex 1528
#define timingAdditive_offset 5616
#define cltFuelCorrBins_offset 5816
#define cltFuelCorr_offset 5880
#define iatFuelCorrBins_offset 5944
#define iatFuelCorrBins_offset_hex 1738
#define iatFuelCorr_offset 6008
#define iatFuelCorr_offset_hex 1778
#define crankingFuelCoef_offset 6072
#define crankingFuelBins_offset 6104
#define crankingCycleCoef_offset 6136
#define crankingCycleBins_offset 6168
#define crankingCycleBins_offset_hex 1818
#define cltIdleCorrBins_offset 6200
#define cltIdleCorrBins_offset_hex 1838
#define cltIdleCorr_offset 6264
#define cltIdleCorr_offset_hex 1878
#define mafDecoding_offset 6328
#define mafDecodingBins_offset 7352
#define ignitionIatCorrTable_offset 8376
#define ignitionIatCorrLoadBins_offset 9400
#define ignitionIatCorrRpmBins_offset 9464
#define injectionPhase_offset 9528
#define injectionPhase_offset_hex 2538
#define injPhaseLoadBins_offset 10552
#define injPhaseLoadBins_offset_hex 2938
#define injPhaseRpmBins_offset 10616
#define injPhaseRpmBins_offset_hex 2978
#define fuelTable_offset 10680
#define fuelLoadBins_offset 11704
#define fuelRpmBins_offset 11768
#define ignitionTable_offset 11832
#define ignitionLoadBins_offset 12856
#define ignitionLoadBins_offset_hex 3238
#define ignitionRpmBins_offset 12920
#define ignitionRpmBins_offset_hex 3278
#define veTable_offset 12984
#define veLoadBins_offset 14008
#define veRpmBins_offset 14072
#define afrTable_offset 14136
#define afrTable_offset_hex 3738
#define afrLoadBins_offset 15160
#define afrRpmBins_offset 15224
#define TOTAL_CONFIG_SIZE 15288