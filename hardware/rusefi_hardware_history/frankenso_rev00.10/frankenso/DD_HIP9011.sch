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
LIBS:rn-41
LIBS:skqucaa010_joystick
LIBS:itead_hc-0X_bluetooth
LIBS:frankenso-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 14
Title "Frankenso"
Date "11 jul 2014"
Rev ".01"
Comp "rusEFI.com"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L HIP9011 D161
U 1 1 52928107
P 5250 4450
F 0 "D161" H 5100 5150 60  0000 C CNN
F 1 "HIP9011" H 5250 5050 60  0000 C CNN
F 2 "SO20L" H 5250 5050 60  0001 C CNN
F 3 "" H 5250 5050 60  0000 C CNN
	1    5250 4450
	1    0    0    -1  
$EndComp
$Comp
L C C162
U 1 1 529286C7
P 2700 2400
F 0 "C162" H 2700 2500 40  0000 L CNN
F 1 "47n" H 2706 2315 40  0000 L CNN
F 2 "SM1206" H 2738 2250 30  0001 C CNN
F 3 "~" H 2700 2400 60  0000 C CNN
	1    2700 2400
	0    -1   -1   0   
$EndComp
$Comp
L R R161
U 1 1 529286D6
P 2300 2650
F 0 "R161" V 2380 2650 40  0000 C CNN
F 1 "1M" V 2307 2651 40  0000 C CNN
F 2 "SM1206" V 2230 2650 30  0001 C CNN
F 3 "~" H 2300 2650 30  0000 C CNN
	1    2300 2650
	1    0    0    -1  
$EndComp
$Comp
L R R162
U 1 1 529287C2
P 2300 3400
F 0 "R162" V 2380 3400 40  0000 C CNN
F 1 "1M" V 2307 3401 40  0000 C CNN
F 2 "SM1206" V 2230 3400 30  0001 C CNN
F 3 "~" H 2300 3400 30  0000 C CNN
	1    2300 3400
	1    0    0    -1  
$EndComp
$Comp
L C C163
U 1 1 52928818
P 2750 3150
F 0 "C163" H 2750 3250 40  0000 L CNN
F 1 "47n" H 2756 3065 40  0000 L CNN
F 2 "SM1206" H 2788 3000 30  0001 C CNN
F 3 "~" H 2750 3150 60  0000 C CNN
	1    2750 3150
	0    -1   -1   0   
$EndComp
$Comp
L R R163
U 1 1 52928849
P 3250 2400
F 0 "R163" V 3330 2400 40  0000 C CNN
F 1 "10k" V 3257 2401 40  0000 C CNN
F 2 "SM1206" V 3180 2400 30  0001 C CNN
F 3 "~" H 3250 2400 30  0000 C CNN
	1    3250 2400
	0    -1   -1   0   
$EndComp
$Comp
L R R164
U 1 1 52928858
P 3300 3150
F 0 "R164" V 3380 3150 40  0000 C CNN
F 1 "10k" V 3307 3151 40  0000 C CNN
F 2 "SM1206" V 3230 3150 30  0001 C CNN
F 3 "~" H 3300 3150 30  0000 C CNN
	1    3300 3150
	0    -1   -1   0   
$EndComp
$Comp
L R R167
U 1 1 52928876
P 6200 4250
F 0 "R167" V 6280 4250 40  0000 C CNN
F 1 "68k" V 6207 4251 40  0000 C CNN
F 2 "SM1206" V 6130 4250 30  0001 C CNN
F 3 "~" H 6200 4250 30  0000 C CNN
	1    6200 4250
	0    -1   -1   0   
$EndComp
$Comp
L R R168
U 1 1 52928885
P 6200 4350
F 0 "R168" V 6280 4350 40  0000 C CNN
F 1 "68k" V 6207 4351 40  0000 C CNN
F 2 "SM1206" V 6130 4350 30  0001 C CNN
F 3 "~" H 6200 4350 30  0000 C CNN
	1    6200 4350
	0    -1   1    0   
$EndComp
$Comp
L C C165
U 1 1 52928976
P 4050 4250
F 0 "C165" H 4050 4350 40  0000 L CNN
F 1 "100n" H 4056 4165 40  0000 L CNN
F 2 "SM1206" H 4088 4100 30  0001 C CNN
F 3 "~" H 4050 4250 60  0000 C CNN
	1    4050 4250
	1    0    0    -1  
$EndComp
$Comp
L R R166
U 1 1 52928EAF
P 4650 5500
F 0 "R166" V 4730 5500 40  0000 C CNN
F 1 "1M" V 4657 5501 40  0000 C CNN
F 2 "SM1206" V 4580 5500 30  0001 C CNN
F 3 "~" H 4650 5500 30  0000 C CNN
	1    4650 5500
	1    0    0    -1  
$EndComp
$Comp
L C C166
U 1 1 52928F04
P 5450 5200
F 0 "C166" H 5450 5300 40  0000 L CNN
F 1 "20pF" H 5456 5115 40  0000 L CNN
F 2 "SM0805" H 5488 5050 30  0001 C CNN
F 3 "~" H 5450 5200 60  0000 C CNN
	1    5450 5200
	0    -1   -1   0   
$EndComp
$Comp
L C C167
U 1 1 52928F18
P 5450 5800
F 0 "C167" H 5450 5900 40  0000 L CNN
F 1 "20pF" H 5456 5715 40  0000 L CNN
F 2 "SM0805" H 5488 5650 30  0001 C CNN
F 3 "~" H 5450 5800 60  0000 C CNN
	1    5450 5800
	0    -1   -1   0   
$EndComp
$Comp
L C C168
U 1 1 529299B0
P 4300 3750
F 0 "C168" H 4300 3850 40  0000 L CNN
F 1 "22n" H 4306 3665 40  0000 L CNN
F 2 "SM1206" H 4338 3600 30  0001 C CNN
F 3 "~" H 4300 3750 60  0000 C CNN
	1    4300 3750
	1    0    0    -1  
$EndComp
NoConn ~ 4650 4450
NoConn ~ 4650 4550
Wire Wire Line
	2300 2900 2050 2900
Wire Wire Line
	2050 2900 2050 2600
Wire Wire Line
	2050 2400 2500 2400
Wire Wire Line
	2300 3650 2050 3650
Wire Wire Line
	2050 3650 2050 3350
Wire Wire Line
	2050 3150 2550 3150
Connection ~ 2300 3150
Connection ~ 2300 2400
Wire Wire Line
	2900 2400 3000 2400
Wire Wire Line
	2950 3150 3050 3150
Wire Wire Line
	5850 4250 5950 4250
Wire Wire Line
	5850 4350 5950 4350
Wire Wire Line
	5850 4450 6450 4450
Wire Wire Line
	6450 4450 6450 4350
Wire Wire Line
	6450 3150 6450 4250
Wire Wire Line
	6450 4150 5850 4150
Wire Wire Line
	3550 3150 6450 3150
Connection ~ 6450 4150
Wire Wire Line
	3500 2400 6550 2400
Wire Wire Line
	6550 2400 6550 4350
Wire Wire Line
	6550 4350 6450 4350
Connection ~ 6450 4350
Wire Wire Line
	3950 4050 4650 4050
Wire Wire Line
	4650 4150 4300 4150
Wire Wire Line
	4300 4450 4300 3950
Connection ~ 4050 4050
Connection ~ 4050 4450
Wire Wire Line
	4500 4250 4650 4250
Wire Wire Line
	4500 3550 4500 4250
Wire Wire Line
	5900 3550 5900 4550
Wire Wire Line
	5900 4050 5850 4050
Wire Wire Line
	5900 4550 5850 4550
Connection ~ 5900 4050
Wire Wire Line
	4650 5200 5250 5200
Wire Wire Line
	4650 4950 4650 5250
Connection ~ 5000 5200
Wire Wire Line
	4550 5800 5250 5800
Wire Wire Line
	4650 5800 4650 5750
Connection ~ 5000 5800
Wire Wire Line
	5650 5200 5700 5200
Wire Wire Line
	5700 5200 5700 5800
Connection ~ 4650 5200
Wire Wire Line
	4550 5800 4550 4850
Wire Wire Line
	4550 4850 4650 4850
Connection ~ 4650 5800
Wire Wire Line
	4300 3550 5900 3550
Connection ~ 4500 3550
Connection ~ 4300 4150
Wire Wire Line
	4650 4650 4200 4650
Wire Wire Line
	4650 4750 4200 4750
Wire Wire Line
	5850 4650 6200 4650
Wire Wire Line
	5850 4750 6200 4750
Wire Wire Line
	5850 4850 6200 4850
Wire Wire Line
	5850 4950 6200 4950
Text Label 6200 4650 0    60   ~ 0
TEST
Wire Wire Line
	4650 4350 4350 4350
Text Label 4350 4350 0    60   ~ 0
INTOUT
$Comp
L R R170
U 1 1 52A255C1
P 7350 3600
F 0 "R170" V 7430 3600 40  0000 C CNN
F 1 "1K" V 7357 3601 40  0000 C CNN
F 2 "SM1206" V 7280 3600 30  0001 C CNN
F 3 "~" H 7350 3600 30  0000 C CNN
	1    7350 3600
	1    0    0    -1  
$EndComp
$Comp
L R R171
U 1 1 52A255D0
P 7500 3600
F 0 "R171" V 7580 3600 40  0000 C CNN
F 1 "1K" V 7507 3601 40  0000 C CNN
F 2 "SM0805_jumper" V 7430 3600 30  0001 C CNN
F 3 "~" H 7500 3600 30  0000 C CNN
	1    7500 3600
	1    0    0    -1  
$EndComp
$Comp
L R R172
U 1 1 52A255DF
P 7650 3600
F 0 "R172" V 7730 3600 40  0000 C CNN
F 1 "1K" V 7657 3601 40  0000 C CNN
F 2 "SM1206" V 7580 3600 30  0001 C CNN
F 3 "~" H 7650 3600 30  0000 C CNN
	1    7650 3600
	1    0    0    -1  
$EndComp
$Comp
L R R173
U 1 1 52A255EE
P 7800 3600
F 0 "R173" V 7880 3600 40  0000 C CNN
F 1 "1K" V 7807 3601 40  0000 C CNN
F 2 "SM1206" V 7730 3600 30  0001 C CNN
F 3 "~" H 7800 3600 30  0000 C CNN
	1    7800 3600
	1    0    0    -1  
$EndComp
$Comp
L R R174
U 1 1 52A255FD
P 7950 3600
F 0 "R174" V 8030 3600 40  0000 C CNN
F 1 "1K" V 7957 3601 40  0000 C CNN
F 2 "SM1206" V 7880 3600 30  0001 C CNN
F 3 "~" H 7950 3600 30  0000 C CNN
	1    7950 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3350 7950 3350
Connection ~ 7800 3350
Connection ~ 7650 3350
Connection ~ 7500 3350
Wire Wire Line
	7350 3350 7350 3000
Text Label 7350 3100 0    60   ~ 0
5V
Text Label 7350 3850 3    60   ~ 0
INT/HLD
Text Label 7500 3850 3    60   ~ 0
CS
Text Label 7650 3850 3    60   ~ 0
TEST
Text Label 7800 3850 3    60   ~ 0
SCK
Text Label 7950 3850 3    60   ~ 0
SI
Wire Wire Line
	5700 5800 5650 5800
Text Label 5700 5500 0    60   ~ 0
GND
Text Notes 1600 1700 0    118  ~ 0
DD_HIP9011 ver.2\nRusEfi.com
$Comp
L R R175
U 1 1 52A2E159
P 8400 3450
F 0 "R175" V 8480 3450 40  0000 C CNN
F 1 "10k" V 8407 3451 40  0000 C CNN
F 2 "SM1206" V 8330 3450 30  0001 C CNN
F 3 "~" H 8400 3450 30  0000 C CNN
	1    8400 3450
	1    0    0    -1  
$EndComp
$Comp
L R R176
U 1 1 52A2E168
P 8400 3950
F 0 "R176" V 8480 3950 40  0000 C CNN
F 1 "10k" V 8407 3951 40  0000 C CNN
F 2 "SM1206" V 8330 3950 30  0001 C CNN
F 3 "~" H 8400 3950 30  0000 C CNN
	1    8400 3950
	1    0    0    -1  
$EndComp
Text Label 8400 4200 0    60   ~ 0
GND
Text Label 8400 3200 0    60   ~ 0
INTOUT
$Comp
L CONN_2 P165
U 1 1 52AEADCD
P 8000 5450
F 0 "P165" V 7950 5450 40  0000 C CNN
F 1 "CONN_2" V 8050 5450 40  0000 C CNN
F 2 "PIN_ARRAY_2X1" H 8000 5450 60  0001 C CNN
F 3 "" H 8000 5450 60  0000 C CNN
	1    8000 5450
	-1   0    0    1   
$EndComp
Text Label 8350 5350 0    60   ~ 0
INT/HLD
Text Label 8350 5550 0    60   ~ 0
TEST
$Comp
L CONN_2 P166
U 1 1 52AEAE96
P 8000 5850
F 0 "P166" V 7950 5850 40  0000 C CNN
F 1 "CONN_2" V 8050 5850 40  0000 C CNN
F 2 "PIN_ARRAY_2X1" H 8000 5850 60  0001 C CNN
F 3 "" H 8000 5850 60  0000 C CNN
	1    8000 5850
	-1   0    0    1   
$EndComp
Text Label 8350 5750 0    60   ~ 0
OUT
Text Label 8350 5950 0    60   ~ 0
GND
$Comp
L CRYSTAL X161
U 1 1 538954BF
P 5000 5500
F 0 "X161" H 5000 5650 60  0000 C CNN
F 1 "CRYSTAL" H 5000 5350 60  0000 C CNN
F 2 "Q_49U3HMS" H 5000 5500 60  0001 C CNN
F 3 "~" H 5000 5500 60  0000 C CNN
	1    5000 5500
	0    -1   -1   0   
$EndComp
Text HLabel 4050 4450 0    60   Input ~ 0
GND
Text HLabel 4050 4050 1    60   Input ~ 0
5V
Wire Wire Line
	4300 4450 4050 4450
Text HLabel 2050 2400 0    60   Input ~ 0
KNOCK1
Text HLabel 2300 2900 2    60   Input ~ 0
GND
Text HLabel 2050 3150 0    60   Input ~ 0
KNOCK2
Text HLabel 2300 3650 2    60   Input ~ 0
GND
Text HLabel 6200 4750 2    60   Input ~ 0
SCK
Text HLabel 6200 4850 2    60   Input ~ 0
SI
Text HLabel 6200 4950 2    60   Input ~ 0
SO
Text HLabel 4200 4750 0    60   Input ~ 0
CS
Text HLabel 4200 4650 0    60   Input ~ 0
INT/HLD
Text HLabel 8400 3700 0    60   Input ~ 0
OUT
$EndSCHEMATC
