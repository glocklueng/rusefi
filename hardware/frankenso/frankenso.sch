EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:176122-6
LIBS:art-electro-conn
LIBS:art-electro-conn_2
LIBS:art-electro-ic
LIBS:art-electro-max
LIBS:art-electro-power
LIBS:LMV324IDR
LIBS:logo
LIBS:logo_flipped
LIBS:MAX9926-9927
LIBS:max9939
LIBS:max31855
LIBS:stm32
LIBS:tc4427
LIBS:lm2596
LIBS:mos_p_numbered-pins
LIBS:project_specific_libs
LIBS:hip9011
LIBS:frankenso-cache
EELAYER 27 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 1 10
Title "Frankenso"
Date "3 jul 2014"
Rev ".01"
Comp "rusEFI.com"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 9600 5450 1500 800 
U 52ED7C56
F0 "hi-lo" 50
F1 "hi-lo.sch" 50
F2 "H_IN2" I L 9600 5600 60 
F3 "H_IN4" I L 9600 5800 60 
F4 "H_IN1" I L 9600 5500 60 
F5 "H_IN3" I L 9600 5700 60 
F6 "H_IN6" I L 9600 6000 60 
F7 "H_IN5" I L 9600 5900 60 
F8 "HL1" I R 11100 5500 60 
F9 "HL2" I R 11100 5600 60 
F10 "HL3" I R 11100 5700 60 
F11 "HL4" I R 11100 5800 60 
F12 "HL5" I R 11100 5900 60 
F13 "HL6" I R 11100 6000 60 
F14 "12V" I R 11100 6200 60 
F15 "5V" I L 9600 6200 60 
F16 "GND" I R 11100 6100 60 
$EndSheet
$Sheet
S 5700 3700 1450 1300
U 52A5358C
F0 "adc_amp_divider" 50
F1 "adc_amp_divider.sch" 50
F2 "INP12" I L 5700 4950 60 
F3 "INP11" I L 5700 4850 60 
F4 "INP10" I L 5700 4750 60 
F5 "INP9" I L 5700 4650 60 
F6 "INP8" I L 5700 4550 60 
F7 "INP7" I L 5700 4450 60 
F8 "INP6" I L 5700 4350 60 
F9 "INP5" I L 5700 4250 60 
F10 "INP4" I L 5700 4150 60 
F11 "INP3" I L 5700 4050 60 
F12 "INP2" I L 5700 3950 60 
F13 "INP1" I L 5700 3850 60 
F14 "OUT4" I R 7150 4150 60 
F15 "OUT3" I R 7150 4050 60 
F16 "OUT1" I R 7150 3850 60 
F17 "OUT2" I R 7150 3950 60 
F18 "OUT10" I R 7150 4750 60 
F19 "OUT12" I R 7150 4950 60 
F20 "OUT6" I R 7150 4350 60 
F21 "OUT5" I R 7150 4250 60 
F22 "OUT8" I R 7150 4550 60 
F23 "OUT7" I R 7150 4450 60 
F24 "OUT9" I R 7150 4650 60 
F25 "OUT11" I R 7150 4850 60 
F26 "5V" I L 5700 3750 60 
F27 "GND" I R 7150 3750 60 
$EndSheet
$Sheet
S 9600 7150 1500 450 
U 52DB7A23
F0 "can_brd_1" 50
F1 "can_brd_1.sch" 50
F2 "CANH" I R 11100 7400 60 
F3 "CANL" I R 11100 7500 60 
F4 "3.3V" I L 9600 7200 60 
F5 "GND" I L 9600 7300 60 
F6 "CAN_RX" I L 9600 7400 60 
F7 "CAN_TX" I L 9600 7500 60 
$EndSheet
Text Notes 7300 2950 0    600  ~ 0
rusEfi
$Sheet
S 5700 5200 1450 450 
U 539DA233
F0 "DD_HIP9011" 50
F1 "DD_HIP9011.sch" 50
F2 "GND" I L 5700 5350 60 
F3 "5V" I L 5700 5250 60 
F4 "KNOCK1" I L 5700 5450 60 
F5 "KNOCK2" I L 5700 5550 60 
F6 "SO" I R 7150 5450 60 
F7 "SCK" I R 7150 5350 60 
F8 "CS" I R 7150 5250 60 
F9 "SI" I R 7150 5550 60 
$EndSheet
$Sheet
S 9600 3800 1500 1400
U 52A53383
F0 "inj_12ch" 50
F1 "inj_12ch.sch" 50
F2 "INJ-06_5V" I L 9600 4350 60 
F3 "INJ-10_5V" I L 9600 4750 60 
F4 "INJ-09_5V" I L 9600 4650 60 
F5 "INJ-07_5V" I L 9600 4450 60 
F6 "INJ-05_5V" I L 9600 4250 60 
F7 "INJ-08_5V" I L 9600 4550 60 
F8 "INJ-01_5V" I L 9600 3850 60 
F9 "INJ-02_5V" I L 9600 3950 60 
F10 "INJ-03_5V" I L 9600 4050 60 
F11 "INJ-04_5V" I L 9600 4150 60 
F12 "iGND2" I R 11100 5150 60 
F13 "INJ-05" I R 11100 4250 60 
F14 "INJ-04" I R 11100 4150 60 
F15 "INJ-06" I R 11100 4350 60 
F16 "INJ-07" I R 11100 4450 60 
F17 "INJ-02" I R 11100 3950 60 
F18 "INJ-03" I R 11100 4050 60 
F19 "INJ-01_2" I R 11100 3850 60 
F20 "iGND1" I R 11100 5050 60 
F21 "INJ-08" I R 11100 4550 60 
F22 "INJ-09" I R 11100 4650 60 
F23 "INJ-11" I R 11100 4850 60 
F24 "INJ-10" I R 11100 4750 60 
F25 "INJ-12" I R 11100 4950 60 
F26 "INJ-11_5V" I L 9600 4850 60 
F27 "INJ-12_5V" I L 9600 4950 60 
$EndSheet
$Comp
L TEST W1
U 1 1 539824F9
P 4950 1400
F 0 "W1" V 4950 1400 40  0000 C CNN
F 1 "TEST" H 4950 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 4950 1400 60  0001 C CNN
F 3 "" H 4950 1400 60  0000 C CNN
	1    4950 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W2
U 1 1 5398252F
P 5050 1300
F 0 "W2" V 5050 1300 40  0000 C CNN
F 1 "TEST" H 5050 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 5050 1300 60  0001 C CNN
F 3 "" H 5050 1300 60  0000 C CNN
	1    5050 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W3
U 1 1 53982535
P 5150 1400
F 0 "W3" V 5150 1400 40  0000 C CNN
F 1 "TEST" H 5150 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 5150 1400 60  0001 C CNN
F 3 "" H 5150 1400 60  0000 C CNN
	1    5150 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W4
U 1 1 5398253B
P 5250 1300
F 0 "W4" V 5250 1300 40  0000 C CNN
F 1 "TEST" H 5250 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 5250 1300 60  0001 C CNN
F 3 "" H 5250 1300 60  0000 C CNN
	1    5250 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W5
U 1 1 53982541
P 5350 1400
F 0 "W5" V 5350 1400 40  0000 C CNN
F 1 "TEST" H 5350 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 5350 1400 60  0001 C CNN
F 3 "" H 5350 1400 60  0000 C CNN
	1    5350 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W6
U 1 1 53982547
P 5450 1300
F 0 "W6" V 5450 1300 40  0000 C CNN
F 1 "TEST" H 5450 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 5450 1300 60  0001 C CNN
F 3 "" H 5450 1300 60  0000 C CNN
	1    5450 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W7
U 1 1 5398254D
P 5550 1400
F 0 "W7" V 5550 1400 40  0000 C CNN
F 1 "TEST" H 5550 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 5550 1400 60  0001 C CNN
F 3 "" H 5550 1400 60  0000 C CNN
	1    5550 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W8
U 1 1 53982553
P 5650 1300
F 0 "W8" V 5650 1300 40  0000 C CNN
F 1 "TEST" H 5650 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 5650 1300 60  0001 C CNN
F 3 "" H 5650 1300 60  0000 C CNN
	1    5650 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W9
U 1 1 53982559
P 5750 1400
F 0 "W9" V 5750 1400 40  0000 C CNN
F 1 "TEST" H 5750 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 5750 1400 60  0001 C CNN
F 3 "" H 5750 1400 60  0000 C CNN
	1    5750 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W10
U 1 1 5398255F
P 5850 1300
F 0 "W10" V 5850 1300 40  0000 C CNN
F 1 "TEST" H 5850 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 5850 1300 60  0001 C CNN
F 3 "" H 5850 1300 60  0000 C CNN
	1    5850 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W11
U 1 1 53982565
P 5950 1400
F 0 "W11" V 5950 1400 40  0000 C CNN
F 1 "TEST" H 5950 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 5950 1400 60  0001 C CNN
F 3 "" H 5950 1400 60  0000 C CNN
	1    5950 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W12
U 1 1 5398256B
P 6050 1300
F 0 "W12" V 6050 1300 40  0000 C CNN
F 1 "TEST" H 6050 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 6050 1300 60  0001 C CNN
F 3 "" H 6050 1300 60  0000 C CNN
	1    6050 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W13
U 1 1 53982571
P 6150 1400
F 0 "W13" V 6150 1400 40  0000 C CNN
F 1 "TEST" H 6150 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 6150 1400 60  0001 C CNN
F 3 "" H 6150 1400 60  0000 C CNN
	1    6150 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W14
U 1 1 53982577
P 6250 1300
F 0 "W14" V 6250 1300 40  0000 C CNN
F 1 "TEST" H 6250 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 6250 1300 60  0001 C CNN
F 3 "" H 6250 1300 60  0000 C CNN
	1    6250 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W15
U 1 1 5398257D
P 6350 1400
F 0 "W15" V 6350 1400 40  0000 C CNN
F 1 "TEST" H 6350 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 6350 1400 60  0001 C CNN
F 3 "" H 6350 1400 60  0000 C CNN
	1    6350 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W16
U 1 1 53982583
P 6450 1300
F 0 "W16" V 6450 1300 40  0000 C CNN
F 1 "TEST" H 6450 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 6450 1300 60  0001 C CNN
F 3 "" H 6450 1300 60  0000 C CNN
	1    6450 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W17
U 1 1 53982589
P 6550 1400
F 0 "W17" V 6550 1400 40  0000 C CNN
F 1 "TEST" H 6550 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 6550 1400 60  0001 C CNN
F 3 "" H 6550 1400 60  0000 C CNN
	1    6550 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W18
U 1 1 5398258F
P 6650 1300
F 0 "W18" V 6650 1300 40  0000 C CNN
F 1 "TEST" H 6650 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 6650 1300 60  0001 C CNN
F 3 "" H 6650 1300 60  0000 C CNN
	1    6650 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W19
U 1 1 53982595
P 6750 1400
F 0 "W19" V 6750 1400 40  0000 C CNN
F 1 "TEST" H 6750 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 6750 1400 60  0001 C CNN
F 3 "SM0805_jumper" H 6750 1400 60  0001 C CNN
	1    6750 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W20
U 1 1 5398259B
P 6850 1300
F 0 "W20" V 6850 1300 40  0000 C CNN
F 1 "TEST" H 6850 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 6850 1300 60  0001 C CNN
F 3 "" H 6850 1300 60  0000 C CNN
	1    6850 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W21
U 1 1 539825A1
P 6950 1400
F 0 "W21" V 6950 1400 40  0000 C CNN
F 1 "TEST" H 6950 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 6950 1400 60  0001 C CNN
F 3 "" H 6950 1400 60  0000 C CNN
	1    6950 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W22
U 1 1 539825A7
P 7050 1300
F 0 "W22" V 7050 1300 40  0000 C CNN
F 1 "TEST" H 7050 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 7050 1300 60  0001 C CNN
F 3 "" H 7050 1300 60  0000 C CNN
	1    7050 1300
	0    -1   -1   0   
$EndComp
$Comp
L 176122-6_2ND P99
U 1 1 5398DBFC
P 5950 650
F 0 "P99" H 6450 700 50  0000 C CNN
F 1 "176122-6_2ND" H 5450 700 50  0000 C CNN
F 2 "176122-6_2nd" H 6350 800 50  0001 C CNN
F 3 "DOCUMENTATION" H 5450 800 50  0001 C CNN
	1    5950 650 
	1    0    0    -1  
$EndComp
$Comp
L 176122-6_2ND P99
U 2 1 5398DC09
P 8500 650
F 0 "P99" H 9000 700 50  0000 C CNN
F 1 "176122-6_2ND" H 8000 700 50  0000 C CNN
F 2 "176122-6_2nd" H 8900 800 50  0001 C CNN
F 3 "DOCUMENTATION" H 8000 800 50  0001 C CNN
	2    8500 650 
	1    0    0    -1  
$EndComp
$Comp
L 176122-6_2ND P99
U 3 1 5398DC0F
P 11000 650
F 0 "P99" H 11500 700 50  0000 C CNN
F 1 "176122-6_2ND" H 10500 700 50  0000 C CNN
F 2 "176122-6_2nd" H 11400 800 50  0001 C CNN
F 3 "DOCUMENTATION" H 10500 800 50  0001 C CNN
	3    11000 650 
	1    0    0    -1  
$EndComp
Text Label 5150 1600 3    60   ~ 0
START-SIG
Text Label 5250 1600 3    60   ~ 0
DIAG
Text Label 4950 1600 3    60   ~ 0
12V-CONST
Text Label 5350 1600 3    60   ~ 0
MUL
Text Label 5950 1600 3    60   ~ 0
DIAG-1K
Text Label 5850 1600 3    60   ~ 0
AC-RELAY
Text Label 6350 1600 3    60   ~ 0
STOP-LIGHT
Text Label 6450 1600 3    60   ~ 0
STEERING-SW
Text Label 6250 1600 3    60   ~ 0
TPS-IDL-SW
Text Label 6550 1600 3    60   ~ 0
AC-SW
Text Label 6650 1600 3    60   ~ 0
COOL-FAN
Text Label 6950 1600 3    60   ~ 0
HEADLIGHT-SW
Text Label 7050 1600 3    60   ~ 0
NEUTRAL-CLUTCH-SW
Text Label 6750 1600 3    60   ~ 0
BLOWER-SW
Text Label 6850 1600 3    60   ~ 0
REAR-DEFROSTER-SW
$Comp
L TEST W27
U 1 1 5398DD62
P 8100 1400
F 0 "W27" V 8100 1400 40  0000 C CNN
F 1 "TEST" H 8100 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 8100 1400 60  0001 C CNN
F 3 "" H 8100 1400 60  0000 C CNN
	1    8100 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W28
U 1 1 5398DD68
P 8200 1300
F 0 "W28" V 8200 1300 40  0000 C CNN
F 1 "TEST" H 8200 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 8200 1300 60  0001 C CNN
F 3 "" H 8200 1300 60  0000 C CNN
	1    8200 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W33
U 1 1 5398DD86
P 8700 1400
F 0 "W33" V 8700 1400 40  0000 C CNN
F 1 "TEST" H 8700 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 8700 1400 60  0001 C CNN
F 3 "" H 8700 1400 60  0000 C CNN
	1    8700 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W34
U 1 1 5398DD8C
P 8800 1300
F 0 "W34" V 8800 1300 40  0000 C CNN
F 1 "TEST" H 8800 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 8800 1300 60  0001 C CNN
F 3 "" H 8800 1300 60  0000 C CNN
	1    8800 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W35
U 1 1 5398DD92
P 8900 1400
F 0 "W35" V 8900 1400 40  0000 C CNN
F 1 "TEST" H 8900 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 8900 1400 60  0001 C CNN
F 3 "" H 8900 1400 60  0000 C CNN
	1    8900 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W36
U 1 1 5398DD98
P 9000 1300
F 0 "W36" V 9000 1300 40  0000 C CNN
F 1 "TEST" H 9000 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 9000 1300 60  0001 C CNN
F 3 "" H 9000 1300 60  0000 C CNN
	1    9000 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W37
U 1 1 5398DD9E
P 9100 1400
F 0 "W37" V 9100 1400 40  0000 C CNN
F 1 "TEST" H 9100 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 9100 1400 60  0001 C CNN
F 3 "" H 9100 1400 60  0000 C CNN
	1    9100 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W38
U 1 1 5398DDA4
P 9200 1300
F 0 "W38" V 9200 1300 40  0000 C CNN
F 1 "TEST" H 9200 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 9200 1300 60  0001 C CNN
F 3 "" H 9200 1300 60  0000 C CNN
	1    9200 1300
	0    -1   -1   0   
$EndComp
Text Label 8600 1600 3    60   ~ 0
2J
Text Label 8500 1600 3    60   ~ 0
2I
Text Label 8200 1600 3    60   ~ 0
2F
Text Label 8100 1600 3    60   ~ 0
2E
Text Label 11400 1600 3    60   ~ 0
3R
$Comp
L TEST W39
U 1 1 5398DDFA
P 9700 1400
F 0 "W39" V 9700 1400 40  0000 C CNN
F 1 "TEST" H 9700 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 9700 1400 60  0001 C CNN
F 3 "" H 9700 1400 60  0000 C CNN
	1    9700 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W40
U 1 1 5398DE00
P 9800 1300
F 0 "W40" V 9800 1300 40  0000 C CNN
F 1 "TEST" H 9800 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 9800 1300 60  0001 C CNN
F 3 "" H 9800 1300 60  0000 C CNN
	1    9800 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W41
U 1 1 5398DE06
P 9900 1400
F 0 "W41" V 9900 1400 40  0000 C CNN
F 1 "TEST" H 9900 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 9900 1400 60  0001 C CNN
F 3 "" H 9900 1400 60  0000 C CNN
	1    9900 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W42
U 1 1 5398DE0C
P 10000 1300
F 0 "W42" V 10000 1300 40  0000 C CNN
F 1 "TEST" H 10000 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 10000 1300 60  0001 C CNN
F 3 "" H 10000 1300 60  0000 C CNN
	1    10000 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W43
U 1 1 5398DE12
P 10100 1400
F 0 "W43" V 10100 1400 40  0000 C CNN
F 1 "TEST" H 10100 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 10100 1400 60  0001 C CNN
F 3 "" H 10100 1400 60  0000 C CNN
	1    10100 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W44
U 1 1 5398DE18
P 10200 1300
F 0 "W44" V 10200 1300 40  0000 C CNN
F 1 "TEST" H 10200 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 10200 1300 60  0001 C CNN
F 3 "" H 10200 1300 60  0000 C CNN
	1    10200 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W45
U 1 1 5398DE1E
P 10300 1400
F 0 "W45" V 10300 1400 40  0000 C CNN
F 1 "TEST" H 10300 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 10300 1400 60  0001 C CNN
F 3 "" H 10300 1400 60  0000 C CNN
	1    10300 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W46
U 1 1 5398DE24
P 10400 1300
F 0 "W46" V 10400 1300 40  0000 C CNN
F 1 "TEST" H 10400 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 10400 1300 60  0001 C CNN
F 3 "" H 10400 1300 60  0000 C CNN
	1    10400 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W47
U 1 1 5398DE2A
P 10500 1400
F 0 "W47" V 10500 1400 40  0000 C CNN
F 1 "TEST" H 10500 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 10500 1400 60  0001 C CNN
F 3 "" H 10500 1400 60  0000 C CNN
	1    10500 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W48
U 1 1 5398DE30
P 10600 1300
F 0 "W48" V 10600 1300 40  0000 C CNN
F 1 "TEST" H 10600 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 10600 1300 60  0001 C CNN
F 3 "" H 10600 1300 60  0000 C CNN
	1    10600 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W49
U 1 1 5398DE36
P 10700 1400
F 0 "W49" V 10700 1400 40  0000 C CNN
F 1 "TEST" H 10700 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 10700 1400 60  0001 C CNN
F 3 "" H 10700 1400 60  0000 C CNN
	1    10700 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W50
U 1 1 5398DE3C
P 10800 1300
F 0 "W50" V 10800 1300 40  0000 C CNN
F 1 "TEST" H 10800 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 10800 1300 60  0001 C CNN
F 3 "" H 10800 1300 60  0000 C CNN
	1    10800 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W51
U 1 1 5398DE42
P 10900 1400
F 0 "W51" V 10900 1400 40  0000 C CNN
F 1 "TEST" H 10900 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 10900 1400 60  0001 C CNN
F 3 "" H 10900 1400 60  0000 C CNN
	1    10900 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W52
U 1 1 5398DE48
P 11000 1300
F 0 "W52" V 11000 1300 40  0000 C CNN
F 1 "TEST" H 11000 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 11000 1300 60  0001 C CNN
F 3 "" H 11000 1300 60  0000 C CNN
	1    11000 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W53
U 1 1 5398DE4E
P 11100 1400
F 0 "W53" V 11100 1400 40  0000 C CNN
F 1 "TEST" H 11100 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 11100 1400 60  0001 C CNN
F 3 "" H 11100 1400 60  0000 C CNN
	1    11100 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W54
U 1 1 5398DE54
P 11200 1300
F 0 "W54" V 11200 1300 40  0000 C CNN
F 1 "TEST" H 11200 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 11200 1300 60  0001 C CNN
F 3 "" H 11200 1300 60  0000 C CNN
	1    11200 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W55
U 1 1 5398DE5A
P 11300 1400
F 0 "W55" V 11300 1400 40  0000 C CNN
F 1 "TEST" H 11300 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 11300 1400 60  0001 C CNN
F 3 "" H 11300 1400 60  0000 C CNN
	1    11300 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W56
U 1 1 5398DE60
P 11400 1300
F 0 "W56" V 11400 1300 40  0000 C CNN
F 1 "TEST" H 11400 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 11400 1300 60  0001 C CNN
F 3 "" H 11400 1300 60  0000 C CNN
	1    11400 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W57
U 1 1 5398DE66
P 11500 1400
F 0 "W57" V 11500 1400 40  0000 C CNN
F 1 "TEST" H 11500 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 11500 1400 60  0001 C CNN
F 3 "" H 11500 1400 60  0000 C CNN
	1    11500 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W58
U 1 1 5398DE6C
P 11600 1300
F 0 "W58" V 11600 1300 40  0000 C CNN
F 1 "TEST" H 11600 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 11600 1300 60  0001 C CNN
F 3 "" H 11600 1300 60  0000 C CNN
	1    11600 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W59
U 1 1 5398DE72
P 11700 1400
F 0 "W59" V 11700 1400 40  0000 C CNN
F 1 "TEST" H 11700 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 11700 1400 60  0001 C CNN
F 3 "" H 11700 1400 60  0000 C CNN
	1    11700 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W60
U 1 1 5398DE78
P 11800 1300
F 0 "W60" V 11800 1300 40  0000 C CNN
F 1 "TEST" H 11800 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 11800 1300 60  0001 C CNN
F 3 "" H 11800 1300 60  0000 C CNN
	1    11800 1300
	0    -1   -1   0   
$EndComp
Text Label 9900 1600 3    60   ~ 0
CPU-GND
Text Label 10000 1600 3    60   ~ 0
INPUT-GND
Text Label 9800 1600 3    60   ~ 0
OUTPUT-GND
$Comp
L TEST W61
U 1 1 5398DEAA
P 11900 1400
F 0 "W61" V 11900 1400 40  0000 C CNN
F 1 "TEST" H 11900 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 11900 1400 60  0001 C CNN
F 3 "" H 11900 1400 60  0000 C CNN
	1    11900 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W62
U 1 1 5398DEB0
P 12000 1300
F 0 "W62" V 12000 1300 40  0000 C CNN
F 1 "TEST" H 12000 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 12000 1300 60  0001 C CNN
F 3 "" H 12000 1300 60  0000 C CNN
	1    12000 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W63
U 1 1 5398DEB6
P 12100 1400
F 0 "W63" V 12100 1400 40  0000 C CNN
F 1 "TEST" H 12100 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 12100 1400 60  0001 C CNN
F 3 "" H 12100 1400 60  0000 C CNN
	1    12100 1400
	0    -1   -1   0   
$EndComp
$Comp
L TEST W64
U 1 1 5398DEBC
P 12200 1300
F 0 "W64" V 12200 1300 40  0000 C CNN
F 1 "TEST" H 12200 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 12200 1300 60  0001 C CNN
F 3 "" H 12200 1300 60  0000 C CNN
	1    12200 1300
	0    -1   -1   0   
$EndComp
$Comp
L DISPLAY_BL S1
U 1 1 539A66AE
P 12100 8550
F 0 "S1" H 11050 9300 60  0000 C CNN
F 1 "DISPLAY_BL" H 12350 7800 60  0000 C CNN
F 2 "DISPLAY_4x20_BL" H 12100 8550 60  0001 C CNN
F 3 "~" H 12100 8550 60  0000 C CNN
	1    12100 8550
	1    0    0    -1  
$EndComp
Text Label 11500 1600 3    60   ~ 0
INJ-05
Text Label 11600 1600 3    60   ~ 0
INJ-06
Text Label 11700 1600 3    60   ~ 0
INJ-07
Text Label 10700 1600 3    60   ~ 0
5V
Text Label 11800 1600 3    60   ~ 0
INJ-08
Text Label 11900 1600 3    60   ~ 0
INJ-09
Text Label 12000 1600 3    60   ~ 0
INJ-10
Text Label 12100 1600 3    60   ~ 0
INJ-11
Text Label 12200 1600 3    60   ~ 0
INJ-12
Text Label 11100 1600 3    60   ~ 0
AN3-HARN
Text Label 10800 1600 3    60   ~ 0
AN6-HARN
Text Label 11300 1600 3    60   ~ 0
AN1-HARN
Text Label 11200 1600 3    60   ~ 0
AN2-HARN
Text Label 5050 1600 3    60   ~ 0
12V-SWITCH
NoConn ~ 10300 8800
NoConn ~ 10300 8700
NoConn ~ 10300 8600
NoConn ~ 10300 8500
Text Label 10300 7900 2    60   ~ 0
GND
Text Label 10300 8300 2    60   ~ 0
GND
Text Label 10300 8900 2    60   ~ 0
HD44780_D4
Text Label 10300 9000 2    60   ~ 0
HD44780_D5
Text Label 10300 9100 2    60   ~ 0
HD44780_D6
Text Label 10300 9200 2    60   ~ 0
HD44780_D7
Text Label 10300 8200 2    60   ~ 0
HD44780_RS
Text Label 10300 8400 2    60   ~ 0
HD44780_CS
$Comp
L TEST JP01
U 1 1 539C78D5
P 9550 8000
F 0 "JP01" V 9550 8000 40  0000 C CNN
F 1 "TEST" H 9550 7930 40  0001 C CNN
F 2 "SM0805_jumper" H 9550 8000 60  0001 C CNN
F 3 "" H 9550 8000 60  0000 C CNN
	1    9550 8000
	-1   0    0    1   
$EndComp
Text Label 10300 8000 2    60   ~ 0
HD44780_VCC
Text Notes 11750 7600 0    60   ~ 0
The JP1 jumper is needed because we cannot feed the screen via USB - we\nwould need to disconnect it while the board is on a bench
$Comp
L TEST JP02
U 1 1 539C7A79
P 1000 9550
F 0 "JP02" V 1000 9550 40  0000 C CNN
F 1 "TEST" H 1000 9480 40  0001 C CNN
F 2 "SIL-2" H 1000 9550 60  0001 C CNN
F 3 "" H 1000 9550 60  0000 C CNN
	1    1000 9550
	-1   0    0    1   
$EndComp
Text Notes 850  9400 0    60   ~ 0
These two jumpers are here to accomodate stm32f4discovery
$Comp
L TEST JP03
U 1 1 539C7A95
P 1000 9700
F 0 "JP03" V 1000 9700 40  0000 C CNN
F 1 "TEST" H 1000 9630 40  0001 C CNN
F 2 "SIL-2" H 1000 9700 60  0001 C CNN
F 3 "" H 1000 9700 60  0000 C CNN
	1    1000 9700
	-1   0    0    1   
$EndComp
Text Label 9350 8000 2    60   ~ 0
5V
Text Label 9700 1600 3    60   ~ 0
GND
Text Label 10100 1600 3    60   ~ 0
AN11-HARN
Text Label 10300 1600 3    60   ~ 0
AN9-HARN
Text Label 1200 9700 0    60   ~ 0
GND
Text Label 1200 9550 0    60   ~ 0
GND
Text Label 800  9550 2    60   ~ 0
GND
Text Label 800  9700 2    60   ~ 0
GND
$Comp
L GND #PWR01
U 1 1 539C90CE
P 13600 9000
F 0 "#PWR01" H 13600 9000 30  0001 C CNN
F 1 "GND" H 13600 8930 30  0001 C CNN
F 2 "" H 13600 9000 60  0000 C CNN
F 3 "" H 13600 9000 60  0000 C CNN
	1    13600 9000
	1    0    0    -1  
$EndComp
Text Label 13600 8850 1    60   ~ 0
GND
Text Label 13600 8450 1    60   ~ 0
HD44780_VCC
$Comp
L R R99
U 1 1 539C9170
P 9550 8100
F 0 "R99" V 9550 8050 40  0000 C CNN
F 1 "2K" V 9550 8200 40  0000 C CNN
F 2 "SM0805" V 9480 8100 30  0001 C CNN
F 3 "~" H 9550 8100 30  0000 C CNN
	1    9550 8100
	0    -1   -1   0   
$EndComp
Text Label 9300 8100 2    60   ~ 0
GND
Text Label 5550 1600 3    60   ~ 0
HL3
Text Label 5450 1600 3    60   ~ 0
HL1
Text Label 5650 1600 3    60   ~ 0
HL2
Text Label 6150 1600 3    60   ~ 0
HL4
Text Label 5750 1600 3    60   ~ 0
HL5
Text Label 6050 1600 3    60   ~ 0
HL6
Text Label 9000 1600 3    60   ~ 0
INJ-03
Text Label 11000 1600 3    60   ~ 0
AN4-HARN
Text Label 10900 1600 3    60   ~ 0
AN5-HARN
Text Label 10600 1600 3    60   ~ 0
AN8-HARN
Text Label 10500 1600 3    60   ~ 0
AN7-HARN
Text Label 8900 1600 3    60   ~ 0
INJ-04
Text Label 9100 1600 3    60   ~ 0
INJ-02
Text Label 9200 1600 3    60   ~ 0
INJ-01_2
Text Label 8700 1600 3    60   ~ 0
CANH
Text Label 8800 1600 3    60   ~ 0
CANL
Text Label 8400 1600 3    60   ~ 0
KNOCK-INPUT-2
$Comp
L TEST TEST2
U 1 1 539DA1B1
P 1200 10400
F 0 "TEST2" V 1200 10400 40  0000 C CNN
F 1 "TEST" H 1200 10330 40  0001 C CNN
F 2 "SIL-2" H 1200 10400 60  0001 C CNN
F 3 "" H 1200 10400 60  0000 C CNN
	1    1200 10400
	-1   0    0    1   
$EndComp
Text Label 650  10400 0    60   ~ 0
CRANK
Text Label 1550 10400 0    60   ~ 0
CAM
Text Label 8000 1600 3    60   ~ 0
CAM+
Text Label 7900 1600 3    60   ~ 0
CAM-
Text Label 7700 1600 3    60   ~ 0
CRK2-
Text Label 7800 1600 3    60   ~ 0
CRK2+
Text Notes 800  10050 0    60   ~ 0
That's alternative signal OUTPUT - these traces should be routable to PC6 and PA5 via jumpers. \nAleternative to W212 and W212 routung of op-amps ch 11 and ch 12
$Sheet
S 5700 5850 1450 750 
U 52C39F6D
F0 "mmc_usb_1" 50
F1 "mmc_usb_1.sch" 50
F2 "SPI_MOSI" I R 7150 6200 60 
F3 "SPI_SCK" I R 7150 6000 60 
F4 "CS_SD_MODULE" I R 7150 5900 60 
F5 "USART_RX" I R 7150 6400 60 
F6 "USART_TX" I R 7150 6500 60 
F7 "SPI_MISO" I R 7150 6100 60 
F8 "5V" I L 5700 5900 60 
F9 "3.3V" I L 5700 6000 60 
F10 "GND" I L 5700 6100 60 
$EndSheet
Text Label 7750 3300 2    60   ~ 0
GND
Text Label 9000 3200 0    60   ~ 0
5V
Text Label 9000 3650 0    60   ~ 0
5V
Text Label 7750 3650 2    60   ~ 0
5V
Text Label 7750 3750 2    60   ~ 0
GND
Text Label 11100 5050 0    60   ~ 0
GND
Text Label 11100 5150 0    60   ~ 0
GND
Text Label 9000 3750 0    60   ~ 0
3.3V
Text Label 9600 7200 2    60   ~ 0
3.3V
Text Label 9600 7300 2    60   ~ 0
GND
Text Label 5700 3750 2    60   ~ 0
5V
Text Label 7150 3750 0    60   ~ 0
GND
Text Label 5700 5250 2    60   ~ 0
5V
Text Label 5700 5900 2    60   ~ 0
5V
Text Label 5700 5350 2    60   ~ 0
GND
Text Label 5700 6100 2    60   ~ 0
GND
Text Label 11100 6100 0    60   ~ 0
GND
Text Label 5700 6000 2    60   ~ 0
3.3V
Text Label 11100 3850 0    60   ~ 0
INJ-01_2
Text Label 11100 3950 0    60   ~ 0
INJ-02
Text Label 11100 4050 0    60   ~ 0
INJ-03
Text Label 11100 4150 0    60   ~ 0
INJ-04
Text Label 11100 4250 0    60   ~ 0
INJ-05
Text Label 11100 4350 0    60   ~ 0
INJ-06
Text Label 11100 4450 0    60   ~ 0
INJ-07
Text Label 11100 4550 0    60   ~ 0
INJ-08
Text Label 11100 4650 0    60   ~ 0
INJ-09
Text Label 5700 3850 2    60   ~ 0
AN1-HARN
Text Label 5700 3950 2    60   ~ 0
AN2-HARN
Text Label 5700 4150 2    60   ~ 0
AN4-HARN
Text Label 5700 4050 2    60   ~ 0
AN3-HARN
Text Label 5700 4850 2    60   ~ 0
AN11-HARN
Text Label 5700 4950 2    60   ~ 0
AN12-HARN
Text Label 5700 4350 2    60   ~ 0
AN6-HARN
Text Label 5700 4450 2    60   ~ 0
AN7-HARN
Text Label 5700 4650 2    60   ~ 0
AN9-HARN
Text Label 5700 4750 2    60   ~ 0
AN10-HARN
Text Label 11100 4750 0    60   ~ 0
INJ-10
Text Label 11100 4850 0    60   ~ 0
INJ-11
Text Label 11100 4950 0    60   ~ 0
INJ-12
Text Label 5700 4250 2    60   ~ 0
AN5-HARN
Text Label 5700 4550 2    60   ~ 0
AN8-HARN
Text Label 7150 5350 0    60   ~ 0
SCK-2
Text Label 7150 5550 0    60   ~ 0
SI-2
Text Label 7150 5450 0    60   ~ 0
SO-2
Text Label 7150 5900 0    60   ~ 0
CS_SD
Text Label 7150 6000 0    60   ~ 0
SCK
Text Label 7150 6100 0    60   ~ 0
SI
Text Label 7150 6200 0    60   ~ 0
SO
Text Label 7150 6400 0    60   ~ 0
USART_RX
Text Label 7150 6500 0    60   ~ 0
USART_TX
Text Label 5700 5450 2    60   ~ 0
KNOCK-INPUT-1
Text Label 5700 5550 2    60   ~ 0
KNOCK-INPUT-2
Text Label 11100 5500 0    60   ~ 0
HL1
Text Label 11100 5600 0    60   ~ 0
HL2
Text Label 11100 5700 0    60   ~ 0
HL3
Text Label 11100 5800 0    60   ~ 0
HL4
Text Label 11100 5900 0    60   ~ 0
HL5
Text Label 11100 6000 0    60   ~ 0
HL6
Text Label 11100 6200 0    60   ~ 0
12V-SWITCH
Text Label 9600 6200 2    60   ~ 0
5V
Text Label 11100 7400 0    60   ~ 0
CANH
Text Label 11100 7500 0    60   ~ 0
CANL
Text Label 11100 6600 0    60   ~ 0
CRK2+
Text Label 11100 6500 0    60   ~ 0
CRK2-
Text Label 11100 6850 0    60   ~ 0
CAM+
Text Label 11100 6750 0    60   ~ 0
CAM-
Text Label 7750 3200 2    60   ~ 0
12V-SWITCH
Text Label 9600 6600 2    60   ~ 0
5V
Text Label 9600 6700 2    60   ~ 0
GND
$Sheet
S 9600 6450 1500 500 
U 52DC5D44
F0 "cps_vrs_io_1" 50
F1 "cps_vrs_io_1.sch" 50
F2 "CAM+" I R 11100 6850 60 
F3 "CAM-" I R 11100 6750 60 
F4 "CRK2-" I R 11100 6500 60 
F5 "CRK2+" I R 11100 6600 60 
F6 "CAM" I L 9600 6800 60 
F7 "CRANK" I L 9600 6500 60 
F8 "GND" I L 9600 6700 60 
F9 "5V" I L 9600 6600 60 
$EndSheet
Text Label 7150 5250 0    60   ~ 0
5V
$Sheet
S 7750 3150 1250 200 
U 539DA32A
F0 "PWR_buck_12V_switcher" 50
F1 "PWR_buck_12V_switcher.sch" 50
F2 "Vin" I L 7750 3200 60 
F3 "GND" I L 7750 3300 60 
F4 "5V-REG" I R 9000 3200 60 
$EndSheet
Text Notes 4100 4750 0    250  ~ 0
2
Text Notes 4100 5500 0    250  ~ 0
1
Text Notes 4100 6350 0    250  ~ 0
3
Text Notes 11800 4550 0    250  ~ 0
4
Text Notes 11900 5950 0    250  ~ 0
6
Text Notes 11850 6850 0    250  ~ 0
1
Text Notes 11900 7450 0    250  ~ 0
4
Text Label 9600 6500 2    60   ~ 0
CRANK
Text Label 9600 6800 2    60   ~ 0
CAM
NoConn ~ 5150 1600
NoConn ~ 5250 1600
NoConn ~ 5350 1600
NoConn ~ 5850 1600
NoConn ~ 5950 1600
NoConn ~ 6250 1600
NoConn ~ 6350 1600
NoConn ~ 6450 1600
NoConn ~ 6550 1600
NoConn ~ 6650 1600
NoConn ~ 6750 1600
NoConn ~ 6850 1600
NoConn ~ 6950 1600
NoConn ~ 7050 1600
NoConn ~ 4950 1600
Wire Wire Line
	4950 1000 4950 1200
Wire Wire Line
	5050 900  5050 1100
Wire Wire Line
	5150 1000 5150 1200
Wire Wire Line
	5250 900  5250 1100
Wire Wire Line
	5350 1000 5350 1200
Wire Wire Line
	5450 900  5450 1100
Wire Wire Line
	5550 1000 5550 1200
Wire Wire Line
	5650 900  5650 1100
Wire Wire Line
	5750 1000 5750 1200
Wire Wire Line
	5850 900  5850 1100
Wire Wire Line
	5950 1000 5950 1200
Wire Wire Line
	6050 900  6050 1100
Wire Wire Line
	6150 1000 6150 1200
Wire Wire Line
	6250 900  6250 1100
Wire Wire Line
	6350 1000 6350 1200
Wire Wire Line
	6450 900  6450 1100
Wire Wire Line
	6550 1000 6550 1200
Wire Wire Line
	6650 900  6650 1100
Wire Wire Line
	6750 1000 6750 1200
Wire Wire Line
	6850 900  6850 1100
Wire Wire Line
	6950 1000 6950 1200
Wire Wire Line
	7050 900  7050 1100
Wire Wire Line
	7700 1000 7700 1600
Wire Wire Line
	7800 900  7800 1600
Wire Wire Line
	7900 1000 7900 1600
Wire Wire Line
	8000 900  8000 1600
Wire Wire Line
	8100 1000 8100 1200
Wire Wire Line
	8200 900  8200 1100
Wire Wire Line
	8300 1000 8300 1200
Wire Wire Line
	8400 900  8400 1100
Wire Wire Line
	8500 1000 8500 1200
Wire Wire Line
	8600 900  8600 1100
Wire Wire Line
	8700 1000 8700 1200
Wire Wire Line
	8800 900  8800 1100
Wire Wire Line
	8900 1000 8900 1200
Wire Wire Line
	9000 900  9000 1100
Wire Wire Line
	9100 1000 9100 1200
Wire Wire Line
	9200 900  9200 1100
Wire Wire Line
	9700 1000 9700 1200
Wire Wire Line
	9800 900  9800 1100
Wire Wire Line
	9900 1000 9900 1200
Wire Wire Line
	10000 900  10000 1100
Wire Wire Line
	10100 1000 10100 1200
Wire Wire Line
	10200 900  10200 1100
Wire Wire Line
	10300 1000 10300 1200
Wire Wire Line
	10400 900  10400 1100
Wire Wire Line
	10500 1000 10500 1200
Wire Wire Line
	10600 900  10600 1100
Wire Wire Line
	10700 1000 10700 1200
Wire Wire Line
	10800 900  10800 1100
Wire Wire Line
	10900 1000 10900 1200
Wire Wire Line
	11000 900  11000 1100
Wire Wire Line
	11100 1000 11100 1200
Wire Wire Line
	11200 900  11200 1100
Wire Wire Line
	11300 1000 11300 1200
Wire Wire Line
	11400 900  11400 1100
Wire Wire Line
	11500 1000 11500 1200
Wire Wire Line
	11600 900  11600 1100
Wire Wire Line
	11700 1000 11700 1200
Wire Wire Line
	11800 900  11800 1100
Wire Wire Line
	11900 1000 11900 1200
Wire Wire Line
	12000 900  12000 1100
Wire Wire Line
	12100 1000 12100 1200
Wire Wire Line
	12200 900  12200 1100
Wire Wire Line
	9750 8000 10300 8000
Wire Wire Line
	13600 8850 13600 9000
Wire Wire Line
	10300 8100 9800 8100
Wire Wire Line
	650  10400 1000 10400
Wire Wire Line
	1900 10400 1400 10400
Wire Wire Line
	9800 1600 9800 1500
Wire Wire Line
	10000 1600 10000 1500
Wire Wire Line
	10200 1600 10200 1500
Wire Wire Line
	10400 1600 10400 1500
Wire Wire Line
	10600 1600 10600 1500
Wire Wire Line
	10800 1600 10800 1500
Wire Wire Line
	11000 1600 11000 1500
Wire Wire Line
	11200 1600 11200 1500
Wire Wire Line
	11400 1600 11400 1500
Wire Wire Line
	11600 1600 11600 1500
Wire Wire Line
	11800 1600 11800 1500
Wire Wire Line
	12000 1600 12000 1500
Wire Wire Line
	12200 1600 12200 1500
Wire Wire Line
	5050 1600 5050 1500
Wire Wire Line
	5250 1600 5250 1500
Wire Wire Line
	5450 1600 5450 1500
Wire Wire Line
	5650 1600 5650 1500
Wire Wire Line
	5850 1600 5850 1500
Wire Wire Line
	6050 1600 6050 1500
Wire Wire Line
	6250 1600 6250 1500
Wire Wire Line
	6450 1600 6450 1500
Wire Wire Line
	6650 1600 6650 1500
Wire Wire Line
	6850 1600 6850 1500
Wire Wire Line
	7050 1600 7050 1500
Wire Wire Line
	8200 1600 8200 1500
Wire Wire Line
	8800 1600 8800 1500
Wire Wire Line
	9000 1600 9000 1500
Wire Wire Line
	9200 1600 9200 1500
Wire Wire Line
	9700 1600 10000 1600
Connection ~ 9900 1600
Connection ~ 9800 1600
Wire Wire Line
	9000 6800 9600 6800
Wire Wire Line
	9000 3850 9600 3850
Wire Wire Line
	9000 6500 9600 6500
Wire Wire Line
	9000 7400 9600 7400
Wire Wire Line
	9000 7500 9600 7500
Wire Wire Line
	9000 4350 9600 4350
Wire Wire Line
	9000 4450 9600 4450
Wire Wire Line
	9000 4550 9600 4550
Wire Wire Line
	9000 4650 9600 4650
Wire Wire Line
	9000 3950 9600 3950
Wire Wire Line
	9000 4050 9600 4050
Wire Wire Line
	9000 4150 9600 4150
Wire Wire Line
	9000 4250 9600 4250
Wire Wire Line
	9000 4750 9600 4750
Wire Wire Line
	9000 4850 9600 4850
Wire Wire Line
	9000 4950 9600 4950
Wire Wire Line
	7150 4150 7750 4150
Wire Wire Line
	7150 4250 7750 4250
Wire Wire Line
	7150 4350 7750 4350
Wire Wire Line
	7150 4450 7750 4450
Wire Wire Line
	7150 3850 7750 3850
Wire Wire Line
	7150 3950 7750 3950
Wire Wire Line
	7150 4050 7750 4050
Wire Wire Line
	7150 4950 7750 4950
Wire Wire Line
	7150 4550 7750 4550
Wire Wire Line
	7150 4650 7750 4650
Wire Wire Line
	7150 4750 7750 4750
Wire Wire Line
	7150 4850 7750 4850
Wire Wire Line
	7150 6400 7750 6400
Wire Wire Line
	7150 6500 7750 6500
Wire Wire Line
	7150 5900 7750 5900
Wire Wire Line
	7150 6000 7750 6000
Wire Wire Line
	7150 6100 7750 6100
Wire Wire Line
	7150 6200 7750 6200
Wire Wire Line
	9000 5700 9600 5700
Wire Wire Line
	9000 5800 9600 5800
Wire Wire Line
	9000 5900 9600 5900
Wire Wire Line
	9000 6000 9600 6000
Wire Wire Line
	9000 5500 9600 5500
Wire Wire Line
	9000 5600 9600 5600
Wire Wire Line
	7150 5350 7750 5350
Wire Wire Line
	7150 5450 7750 5450
Wire Wire Line
	7150 5550 7750 5550
Wire Wire Line
	10300 8900 9000 8900
Wire Wire Line
	10300 9000 9000 9000
Wire Wire Line
	10300 9100 9000 9100
Wire Wire Line
	10300 9200 9000 9200
Wire Wire Line
	10300 8400 9000 8400
Wire Wire Line
	10300 8200 9000 8200
Wire Wire Line
	8600 1600 8600 1500
$Comp
L TEST W32
U 1 1 5398DD80
P 8600 1300
F 0 "W32" V 8600 1300 40  0000 C CNN
F 1 "TEST" H 8600 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 8600 1300 60  0001 C CNN
F 3 "" H 8600 1300 60  0000 C CNN
	1    8600 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W31
U 1 1 5398DD7A
P 8500 1400
F 0 "W31" V 8500 1400 40  0000 C CNN
F 1 "TEST" H 8500 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 8500 1400 60  0001 C CNN
F 3 "" H 8500 1400 60  0000 C CNN
	1    8500 1400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8400 1600 8400 1500
$Comp
L TEST W30
U 1 1 5398DD74
P 8400 1300
F 0 "W30" V 8400 1300 40  0000 C CNN
F 1 "TEST" H 8400 1230 40  0001 C CNN
F 2 "SM0805_jumper" H 8400 1300 60  0001 C CNN
F 3 "" H 8400 1300 60  0000 C CNN
	1    8400 1300
	0    -1   -1   0   
$EndComp
$Comp
L TEST W29
U 1 1 5398DD6E
P 8300 1400
F 0 "W29" V 8300 1400 40  0000 C CNN
F 1 "TEST" H 8300 1330 40  0001 C CNN
F 2 "SM0805_jumper" H 8300 1400 60  0001 C CNN
F 3 "" H 8300 1400 60  0000 C CNN
	1    8300 1400
	0    -1   -1   0   
$EndComp
Text Label 10400 1600 3    60   ~ 0
AN10-HARN
Text Label 10200 1600 3    60   ~ 0
AN12-HARN
Text Label 8300 1600 3    60   ~ 0
KNOCK-INPUT-1
NoConn ~ 8100 1600
NoConn ~ 8200 1600
NoConn ~ 8500 1600
NoConn ~ 8600 1600
$Sheet
S 7750 3550 1250 6550
U 53A0541A
F0 "stm32f407_board" 50
F1 "stm32f407_board.sch" 50
F2 "VDD" I L 7750 3650 60 
F3 "PC1" I L 7750 3950 60 
F4 "PC3" I L 7750 4150 60 
F5 "PA1" I L 7750 4350 60 
F6 "PA3" I L 7750 4550 60 
F7 "PA5" I L 7750 4750 60 
F8 "PA7" I L 7750 4950 60 
F9 "PC5" I L 7750 8000 60 
F10 "PB1" I L 7750 7100 60 
F11 "PE7" I L 7750 9800 60 
F12 "PE9" I R 9000 9100 60 
F13 "PE11" I R 9000 9200 60 
F14 "PE13" I R 9000 8400 60 
F15 "PE15" I R 9000 10000 60 
F16 "PB11" I L 7750 7500 60 
F17 "PB13" I L 7750 5350 60 
F18 "PB15" I L 7750 5550 60 
F19 "PD9" I L 7750 9200 60 
F20 "PD11" I L 7750 9400 60 
F21 "PD13" I L 7750 9500 60 
F22 "PD15" I L 7750 9700 60 
F23 "NRST" I R 9000 9700 60 
F24 "PC0" I L 7750 7900 60 
F25 "PC2" I L 7750 3850 60 
F26 "PA0" I L 7750 4050 60 
F27 "PA2" I L 7750 4250 60 
F28 "PA4" I L 7750 4450 60 
F29 "PA6" I L 7750 4650 60 
F30 "PC4" I L 7750 4850 60 
F31 "PB0" I L 7750 7000 60 
F32 "PE8" I R 9000 5700 60 
F33 "PE10" I R 9000 5500 60 
F34 "PE12" I R 9000 9000 60 
F35 "PE14" I R 9000 5800 60 
F36 "PB10" I L 7750 7400 60 
F37 "PB12" I R 9000 5600 60 
F38 "PB14" I L 7750 5450 60 
F39 "PD8" I L 7750 9100 60 
F40 "PD10" I L 7750 9300 60 
F41 "PD12" I R 9000 7400 60 
F42 "PD14" I L 7750 9600 60 
F43 "NC" I R 9000 9500 60 
F44 "5V" I R 9000 3650 60 
F45 "3.3V" I R 9000 3750 60 
F46 "PE6" I R 9000 4050 60 
F47 "PE4" I R 9000 4250 60 
F48 "PE2" I R 9000 4450 60 
F49 "PE0" I R 9000 4650 60 
F50 "PB8" I R 9000 4850 60 
F51 "BOOT0" I R 9000 9600 60 
F52 "PB6" I R 9000 7500 60 
F53 "PB4" I L 7750 6100 60 
F54 "PD7" I L 7750 9000 60 
F55 "PD5" I L 7750 8800 60 
F56 "PD3" I L 7750 8700 60 
F57 "PD1" I L 7750 8500 60 
F58 "PC12" I R 9000 8200 60 
F59 "PC10" I L 7750 6400 60 
F60 "PA14" I L 7750 6800 60 
F61 "PA8" I R 9000 6500 60 
F62 "PC8" I L 7750 8200 60 
F63 "PC6" I R 9000 6800 60 
F64 "PC13" I R 9000 4150 60 
F65 "PE5" I R 9000 4350 60 
F66 "PE3" I R 9000 4550 60 
F67 "PE1" I R 9000 4750 60 
F68 "PB9" I R 9000 4950 60 
F69 "PB7" I L 7750 7300 60 
F70 "PB5" I L 7750 6200 60 
F71 "PB3" I L 7750 6000 60 
F72 "PD6" I L 7750 8900 60 
F73 "PD4" I L 7750 5900 60 
F74 "PD2" I L 7750 8600 60 
F75 "PD0" I L 7750 8400 60 
F76 "PC11" I L 7750 6500 60 
F77 "PA15" I L 7750 6900 60 
F78 "PA13" I L 7750 6700 60 
F79 "PC9" I R 9000 5900 60 
F80 "PC7" I L 7750 8100 60 
F81 "GND" I L 7750 3750 60 
F82 "PB2-NC" I L 7750 7200 60 
F83 "NC-PA10" I R 9000 8900 60 
F84 "NC-PA9" I R 9000 6000 60 
F85 "NC-PC14" I R 9000 3850 60 
F86 "NC-PH0" I R 9000 9800 60 
F87 "NC-PC15" I R 9000 3950 60 
F88 "NC-PH1" I R 9000 9900 60 
$EndSheet
$EndSCHEMATC
