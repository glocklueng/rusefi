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
LIBS:vn750ps_e
LIBS:VN5E050AJ_E
LIBS:VN750PS_E-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VN750PS_E Q1
U 1 1 55A7C4D6
P 3750 4400
F 0 "Q1" H 5600 4850 60  0000 C CNN
F 1 "VN750PS_E" H 5600 6050 60  0000 C CNN
F 2 "VN750PS_E_Vertical:VN750PS-E" H 5600 4850 60  0001 C CNN
F 3 "" H 5600 4850 60  0000 C CNN
	1    3750 4400
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 55A7C862
P 6600 3300
F 0 "D1" H 6600 3400 50  0000 C CNN
F 1 "D" H 6600 3200 50  0000 C CNN
F 2 "VN750PS_E_Vertical:US1GHE3" H 6600 3300 60  0001 C CNN
F 3 "" H 6600 3300 60  0000 C CNN
	1    6600 3300
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 55A7C95A
P 4600 3050
F 0 "R1" V 4680 3050 50  0000 C CNN
F 1 "130" V 4600 3050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4530 3050 30  0001 C CNN
F 3 "" H 4600 3050 30  0000 C CNN
	1    4600 3050
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 55A7C9E2
P 4600 3300
F 0 "R2" V 4680 3300 50  0000 C CNN
F 1 "10k" V 4600 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4530 3300 30  0001 C CNN
F 3 "" H 4600 3300 30  0000 C CNN
	1    4600 3300
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 55A7CA15
P 4600 3550
F 0 "R3" V 4680 3550 50  0000 C CNN
F 1 "10k" V 4600 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4530 3550 30  0001 C CNN
F 3 "" H 4600 3550 30  0000 C CNN
	1    4600 3550
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 55A7CA70
P 4600 3750
F 0 "R4" V 4680 3750 50  0000 C CNN
F 1 "10k" V 4600 3750 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4530 3750 30  0001 C CNN
F 3 "" H 4600 3750 30  0000 C CNN
	1    4600 3750
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
P 3550 3150
F 0 "P1" H 3550 3600 50  0000 C CNN
F 1 "CONN_01X08" V 3650 3150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x08" H 3550 3150 60  0001 C CNN
F 3 "" H 3550 3150 60  0000 C CNN
	1    3550 3150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3150 4750 3150
Wire Wire Line
	4750 3150 4750 3050
Wire Wire Line
	4750 3300 4900 3300
Wire Wire Line
	4900 3450 4750 3450
Wire Wire Line
	4750 3450 4750 3750
Wire Wire Line
	6250 3300 6350 3300
Wire Wire Line
	6350 3300 6350 3450
Wire Wire Line
	6250 3450 7000 3450
Connection ~ 6350 3450
Wire Wire Line
	6600 2700 6600 3150
Wire Wire Line
	6250 3150 7000 3150
Wire Wire Line
	6250 3600 6800 3600
Wire Wire Line
	6800 3600 6800 3150
Connection ~ 6600 3150
Connection ~ 6800 3150
Wire Wire Line
	7000 3450 7000 3250
Connection ~ 6600 3450
Wire Wire Line
	4450 3050 4150 3050
Wire Wire Line
	4150 3050 4150 3000
Wire Wire Line
	4000 3100 4000 3300
Wire Wire Line
	4000 3300 4450 3300
Connection ~ 4150 3050
Connection ~ 4750 3550
Wire Wire Line
	3800 3750 4450 3750
Wire Wire Line
	4350 2700 4350 3750
Connection ~ 4350 3750
Wire Wire Line
	3900 3200 3900 3550
Wire Wire Line
	3900 3550 4450 3550
Wire Wire Line
	3750 3300 3800 3300
Wire Wire Line
	3800 3300 3800 3750
Wire Wire Line
	3900 3200 3750 3200
Wire Wire Line
	4000 3100 3750 3100
Wire Wire Line
	4150 3000 3750 3000
$Comp
L +5V #PWR03
U 1 1 55A810DA
P 4350 2700
F 0 "#PWR03" H 4350 2550 50  0001 C CNN
F 1 "+5V" H 4350 2840 50  0000 C CNN
F 2 "" H 4350 2700 60  0000 C CNN
F 3 "" H 4350 2700 60  0000 C CNN
	1    4350 2700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
