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
LIBS:update
LIBS:vn750ps_e
LIBS:VN750PS_E-cache
LIBS:176122-6
LIBS:art-electro-conn
LIBS:art-electro-conn_2
LIBS:art-electro-ic
LIBS:art-electro-max
LIBS:art-electro-power
LIBS:art-electro-stm32
LIBS:cj125
LIBS:crystal(mc306)
LIBS:ECUStimS
LIBS:itead_hc-0X_bluetooth
LIBS:joystick_SKRHAAE010
LIBS:lm2596
LIBS:LMV324IDR
LIBS:logo
LIBS:logo_flipped
LIBS:MAX9926-9927
LIBS:max9939
LIBS:max31855
LIBS:mos_n_numbered-pins
LIBS:mos_p_numbered-pins
LIBS:rn-41
LIBS:skqucaa010_joystick
LIBS:slc_oem
LIBS:STM32F050Fx
LIBS:STM32F407IGT6
LIBS:tc4427
LIBS:tle6240
LIBS:TLE6244
LIBS:vnd5e025aktr
LIBS:VN750PS_E-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "6 jan 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R1
U 1 1 55A7C95A
P 4550 3050
F 0 "R1" V 4630 3050 50  0000 C CNN
F 1 "130" V 4550 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4480 3050 30  0001 C CNN
F 3 "" H 4550 3050 30  0000 C CNN
	1    4550 3050
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 55A7C9E2
P 4550 3300
F 0 "R2" V 4630 3300 50  0000 C CNN
F 1 "10k" V 4550 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4480 3300 30  0001 C CNN
F 3 "" H 4550 3300 30  0000 C CNN
	1    4550 3300
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 55A7CA15
P 4550 3550
F 0 "R3" V 4630 3550 50  0000 C CNN
F 1 "10k" V 4550 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4480 3550 30  0001 C CNN
F 3 "" H 4550 3550 30  0000 C CNN
	1    4550 3550
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 55A7CA70
P 4550 3750
F 0 "R4" V 4630 3750 50  0000 C CNN
F 1 "10k" V 4550 3750 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4480 3750 30  0001 C CNN
F 3 "" H 4550 3750 30  0000 C CNN
	1    4550 3750
	0    -1   -1   0   
$EndComp
$Comp
L +12V #PWR01
U 1 1 55A7CAF7
P 6600 2700
F 0 "#PWR01" H 6600 2550 50  0001 C CNN
F 1 "+12V" H 6600 2840 50  0000 C CNN
F 2 "" H 6600 2700 60  0000 C CNN
F 3 "" H 6600 2700 60  0000 C CNN
	1    6600 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 55A7CB37
P 4150 3050
F 0 "#PWR02" H 4150 2800 50  0001 C CNN
F 1 "GND" H 4150 2900 50  0000 C CNN
F 2 "" H 4150 3050 60  0000 C CNN
F 3 "" H 4150 3050 60  0000 C CNN
	1    4150 3050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X02 P2
U 1 1 55A7CFB7
P 7200 3200
F 0 "P2" H 7200 3350 50  0000 C CNN
F 1 "CONN_01X02" V 7300 3200 50  0000 C CNN
F 2 "VN750PS_E_Vertical:Pin_Header_Straight_25x02" H 7200 3200 60  0001 C CNN
F 3 "" H 7200 3200 60  0000 C CNN
	1    7200 3200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P1
U 1 1 55A7E2A2
P 3450 3150
F 0 "P1" H 3450 3600 50  0000 C CNN
F 1 "CONN_01X08" V 3550 3150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x08" H 3450 3150 60  0001 C CNN
F 3 "" H 3450 3150 60  0000 C CNN
	1    3450 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6250 3300 6350 3300
Wire Wire Line
	6350 3300 6350 3450
Wire Wire Line
	6250 3450 7000 3450
Connection ~ 6350 3450
Wire Wire Line
	6250 3600 6800 3600
Wire Wire Line
	7000 3450 7000 3250
Wire Wire Line
	4150 3050 4150 3000
Wire Wire Line
	4000 3100 4000 3300
Connection ~ 4150 3050
Wire Wire Line
	3900 3200 3900 3550
Wire Wire Line
	3650 3300 3800 3300
Wire Wire Line
	3800 2700 3800 3750
Wire Wire Line
	3650 3200 3900 3200
Wire Wire Line
	3650 3100 4000 3100
Wire Wire Line
	3650 3000 4300 3000
$Comp
L +5V #PWR03
U 1 1 55A810DA
P 3800 2700
F 0 "#PWR03" H 3800 2550 50  0001 C CNN
F 1 "+5V" H 3800 2840 50  0000 C CNN
F 2 "" H 3800 2700 60  0000 C CNN
F 3 "" H 3800 2700 60  0000 C CNN
	1    3800 2700
	1    0    0    -1  
$EndComp
$Comp
L DIODE 1N4448W
U 1 1 568C8BE1
P 6600 3200
F 0 "1N4448W" H 6600 3300 40  0000 C CNN
F 1 "DIODE" H 6600 3100 40  0000 C CNN
F 2 "~" H 6600 3200 60  0000 C CNN
F 3 "~" H 6600 3200 60  0000 C CNN
	1    6600 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 3400 6600 3450
Connection ~ 6600 3450
Wire Wire Line
	6800 3600 6800 3450
Connection ~ 6800 3450
Wire Wire Line
	6250 3150 6250 3000
Wire Wire Line
	6250 3000 7000 3000
Wire Wire Line
	7000 3000 7000 3150
Connection ~ 6600 3000
Wire Wire Line
	6600 2700 6600 3000
$Comp
L VN750PS_E Q1
U 1 1 55A7C4D6
P 3750 4400
F 0 "Q1" H 5600 4850 60  0000 C CNN
F 1 "VN750PS_E" H 5600 6050 60  0000 C CNN
F 2 "VN750PS-E" H 5600 4850 60  0001 C CNN
F 3 "" H 5600 4850 60  0000 C CNN
	1    3750 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3750 4300 3750
Wire Wire Line
	3900 3550 4300 3550
Wire Wire Line
	4800 3550 4900 3550
Wire Wire Line
	4900 3550 4900 3450
Wire Wire Line
	4800 3300 4900 3300
Wire Wire Line
	4800 3050 4900 3050
Wire Wire Line
	4900 3050 4900 3150
Wire Wire Line
	4300 3000 4300 3050
Connection ~ 4150 3000
Wire Wire Line
	4000 3300 4300 3300
Wire Wire Line
	4800 3750 4800 3550
Connection ~ 3800 3300
$EndSCHEMATC
