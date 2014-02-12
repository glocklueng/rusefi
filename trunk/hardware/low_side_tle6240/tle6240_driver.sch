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
LIBS:tle6240
LIBS:project_specific_libs
LIBS:tle6240_driver-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "12 feb 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TLE6240 D2
U 1 1 52F8B8AA
P 5300 2900
F 0 "D2" H 5300 3750 60  0000 C CNN
F 1 "TLE6240" H 5300 1500 60  0000 C CNN
F 2 "~" H 5300 2900 60  0000 C CNN
F 3 "~" H 5300 2900 60  0000 C CNN
	1    5300 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 52F8B8DA
P 4750 4250
F 0 "#PWR01" H 4750 4250 30  0001 C CNN
F 1 "GND" H 4750 4180 30  0001 C CNN
F 2 "" H 4750 4250 60  0000 C CNN
F 3 "" H 4750 4250 60  0000 C CNN
	1    4750 4250
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 52F8B996
P 4200 2350
F 0 "C1" H 4200 2450 40  0000 L CNN
F 1 "C" H 4206 2265 40  0000 L CNN
F 2 "~" H 4238 2200 30  0000 C CNN
F 3 "~" H 4200 2350 60  0000 C CNN
	1    4200 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 52F8B9B3
P 4200 2600
F 0 "#PWR02" H 4200 2600 30  0001 C CNN
F 1 "GND" H 4200 2530 30  0001 C CNN
F 2 "" H 4200 2600 60  0000 C CNN
F 3 "" H 4200 2600 60  0000 C CNN
	1    4200 2600
	1    0    0    -1  
$EndComp
Text Label 5800 2250 0    60   ~ 0
OUT1
Text Label 5800 2350 0    60   ~ 0
OUT2
Text Label 5800 2450 0    60   ~ 0
OUT3
Text Label 5800 2550 0    60   ~ 0
OUT4
Text Label 5800 2650 0    60   ~ 0
OUT5
Text Label 5800 2750 0    60   ~ 0
OUT6
Text Label 5800 2850 0    60   ~ 0
OUT7
Text Label 5800 2950 0    60   ~ 0
OUT8
Text Label 5800 3050 0    60   ~ 0
OUT9
Text Label 5800 3150 0    60   ~ 0
OUT10
Text Label 5800 3250 0    60   ~ 0
OUT11
Text Label 5800 3350 0    60   ~ 0
OUT12
Text Label 5800 3450 0    60   ~ 0
OUT13
Text Label 5800 3550 0    60   ~ 0
OUT14
Text Label 5800 3650 0    60   ~ 0
OUT15
Text Label 5800 3750 0    60   ~ 0
OUT16
Text Label 6450 3350 0    60   ~ 0
OUT9
Text Label 6450 3250 0    60   ~ 0
OUT10
Text Label 6450 3150 0    60   ~ 0
OUT1
Text Label 6450 3050 0    60   ~ 0
OUT2
Text Label 6450 2950 0    60   ~ 0
OUT3
Text Label 6450 2850 0    60   ~ 0
OUT4
Text Label 6450 2750 0    60   ~ 0
OUT11
Text Label 6450 2650 0    60   ~ 0
OUT12
Text Label 6450 2550 0    60   ~ 0
OUT13
Text Label 6450 2450 0    60   ~ 0
OUT14
Text Label 6450 2350 0    60   ~ 0
OUT5
Text Label 6450 2250 0    60   ~ 0
OUT6
Text Label 6450 3750 0    60   ~ 0
OUT7
Text Label 6450 3650 0    60   ~ 0
OUT8
Text Label 6450 3550 0    60   ~ 0
OUT15
Text Label 6450 3450 0    60   ~ 0
OUT16
$Comp
L +5V #PWR03
U 1 1 52F8C522
P 4400 1900
F 0 "#PWR03" H 4400 1990 20  0001 C CNN
F 1 "+5V" H 4400 1990 30  0000 C CNN
F 2 "" H 4400 1900 60  0000 C CNN
F 3 "" H 4400 1900 60  0000 C CNN
	1    4400 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 52F8C942
P 3850 3150
F 0 "#PWR04" H 3850 3150 30  0001 C CNN
F 1 "GND" H 3850 3080 30  0001 C CNN
F 2 "" H 3850 3150 60  0000 C CNN
F 3 "" H 3850 3150 60  0000 C CNN
	1    3850 3150
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR05
U 1 1 52F8C983
P 3850 3250
F 0 "#PWR05" H 3850 3340 20  0001 C CNN
F 1 "+5V" V 3850 3350 30  0000 C CNN
F 2 "" H 3850 3250 60  0000 C CNN
F 3 "" H 3850 3250 60  0000 C CNN
	1    3850 3250
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 52F8D9F4
P 4000 2000
F 0 "D1" H 4000 2100 50  0000 C CNN
F 1 "LED" H 4000 1900 50  0000 C CNN
F 2 "~" H 4000 2000 60  0000 C CNN
F 3 "~" H 4000 2000 60  0000 C CNN
	1    4000 2000
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 52F8DA08
P 3500 2000
F 0 "R1" V 3580 2000 40  0000 C CNN
F 1 "R" V 3507 2001 40  0000 C CNN
F 2 "~" V 3430 2000 30  0000 C CNN
F 3 "~" H 3500 2000 30  0000 C CNN
	1    3500 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 4150 4750 4150
Wire Wire Line
	4750 3850 4750 4250
Wire Wire Line
	4850 4050 4750 4050
Connection ~ 4750 4150
Wire Wire Line
	4850 3950 4750 3950
Connection ~ 4750 4050
Wire Wire Line
	4850 3850 4750 3850
Connection ~ 4750 3950
Wire Wire Line
	4850 2250 4650 2250
Wire Wire Line
	4650 2250 4650 2000
Wire Wire Line
	4200 2600 4200 2550
Wire Wire Line
	5750 2250 5850 2250
Wire Wire Line
	5750 2350 5850 2350
Wire Wire Line
	5750 2450 5850 2450
Wire Wire Line
	5750 2550 5850 2550
Wire Wire Line
	5750 2650 5850 2650
Wire Wire Line
	5750 2750 5850 2750
Wire Wire Line
	5750 2850 5850 2850
Wire Wire Line
	5750 2950 5850 2950
Wire Wire Line
	5750 3050 5850 3050
Wire Wire Line
	5750 3150 5850 3150
Wire Wire Line
	5750 3250 5850 3250
Wire Wire Line
	5750 3350 5850 3350
Wire Wire Line
	5750 3450 5850 3450
Wire Wire Line
	5750 3550 5850 3550
Wire Wire Line
	5750 3650 5850 3650
Wire Wire Line
	5750 3750 5850 3750
Wire Wire Line
	6550 3350 6450 3350
Wire Wire Line
	6550 3250 6450 3250
Wire Wire Line
	6550 3150 6450 3150
Wire Wire Line
	6550 3050 6450 3050
Wire Wire Line
	6550 2950 6450 2950
Wire Wire Line
	6550 2850 6450 2850
Wire Wire Line
	6550 2750 6450 2750
Wire Wire Line
	6550 2650 6450 2650
Wire Wire Line
	6550 2550 6450 2550
Wire Wire Line
	6550 2450 6450 2450
Wire Wire Line
	6550 2350 6450 2350
Wire Wire Line
	6550 2250 6450 2250
Wire Wire Line
	6550 3750 6450 3750
Wire Wire Line
	6550 3650 6450 3650
Wire Wire Line
	6550 3550 6450 3550
Wire Wire Line
	6550 3450 6450 3450
Wire Wire Line
	4500 2350 4850 2350
Wire Wire Line
	4850 2450 4700 2450
Wire Wire Line
	4850 2550 4700 2550
Wire Wire Line
	4850 2650 4700 2650
Wire Wire Line
	4850 2750 4700 2750
Wire Wire Line
	4850 2850 4700 2850
Wire Wire Line
	4850 2950 4700 2950
Wire Wire Line
	4850 3050 4700 3050
Wire Wire Line
	4850 3150 4700 3150
Wire Wire Line
	4850 3250 4700 3250
Wire Wire Line
	4850 3350 4700 3350
Wire Wire Line
	4850 3450 4700 3450
Wire Wire Line
	4850 3550 4700 3550
Wire Wire Line
	4850 3650 4700 3650
Wire Wire Line
	4850 3750 4700 3750
Wire Wire Line
	3750 3450 3850 3450
Wire Wire Line
	3750 3550 3850 3550
Wire Wire Line
	3750 3650 3850 3650
Wire Wire Line
	3750 3850 3850 3850
Wire Wire Line
	3750 3950 3850 3950
Wire Wire Line
	3750 4050 3850 4050
Wire Wire Line
	2950 3450 2850 3450
Wire Wire Line
	2950 3550 2850 3550
Wire Wire Line
	2950 3650 2850 3650
Wire Wire Line
	2950 3750 2850 3750
Wire Wire Line
	2950 3950 2850 3950
Wire Wire Line
	2950 4050 2850 4050
Connection ~ 4200 2000
Wire Wire Line
	3800 2000 3750 2000
$Comp
L GND #PWR06
U 1 1 52F8DC80
P 3200 2050
F 0 "#PWR06" H 3200 2050 30  0001 C CNN
F 1 "GND" H 3200 1980 30  0001 C CNN
F 2 "" H 3200 2050 60  0000 C CNN
F 3 "" H 3200 2050 60  0000 C CNN
	1    3200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2000 3200 2000
Wire Wire Line
	3200 2000 3200 2050
Text Label 4700 2350 0    60   ~ 0
Reset
Text Label 4700 2450 0    60   ~ 0
PRG
Text Label 4700 2550 0    60   ~ 0
Fault
Text Label 4700 2650 0    60   ~ 0
CS
Text Label 4700 2750 0    60   ~ 0
SO
Text Label 4700 2850 0    60   ~ 0
SCLK
Text Label 4700 2950 0    60   ~ 0
SI
Text Label 4700 3050 0    60   ~ 0
IN1
Text Label 4700 3150 0    60   ~ 0
IN2
Text Label 4700 3250 0    60   ~ 0
IN3
Text Label 4700 3350 0    60   ~ 0
IN4
Text Label 4700 3450 0    60   ~ 0
IN9
Text Label 4700 3550 0    60   ~ 0
IN10
Text Label 4700 3650 0    60   ~ 0
IN11
Text Label 4700 3750 0    60   ~ 0
IN12
Text Label 3850 3950 0    60   ~ 0
IN11
Text Label 3600 4450 0    60   ~ 0
SCLK
Text Label 3850 3850 0    60   ~ 0
IN10
Text Label 3850 3750 0    60   ~ 0
IN9
Text Label 3850 3650 0    60   ~ 0
IN1
Text Label 2850 3950 0    60   ~ 0
IN3
Text Label 2850 4050 0    60   ~ 0
IN4
Text Label 2850 3850 0    60   ~ 0
CS
Text Label 3600 4350 0    60   ~ 0
Reset
Text Label 4150 4700 0    60   ~ 0
PRG
Text Label 3450 2450 0    60   ~ 0
Fault
$Comp
L CONN_3 K1
U 1 1 52F9CFE5
P 4750 4700
F 0 "K1" V 4700 4700 50  0000 C CNN
F 1 "CONN_3" V 4800 4700 40  0000 C CNN
F 2 "" H 4750 4700 60  0000 C CNN
F 3 "" H 4750 4700 60  0000 C CNN
	1    4750 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4600 4400 4550
Wire Wire Line
	4400 4800 4400 4850
$Comp
L +5V #PWR07
U 1 1 52F9D105
P 4400 4550
F 0 "#PWR07" H 4400 4640 20  0001 C CNN
F 1 "+5V" H 4400 4640 30  0000 C CNN
F 2 "" H 4400 4550 60  0000 C CNN
F 3 "" H 4400 4550 60  0000 C CNN
	1    4400 4550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 52F9D114
P 4400 4850
F 0 "#PWR08" H 4400 4850 30  0001 C CNN
F 1 "GND" H 4400 4780 30  0001 C CNN
F 2 "" H 4400 4850 60  0000 C CNN
F 3 "" H 4400 4850 60  0000 C CNN
	1    4400 4850
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 52F9D123
P 2600 2450
F 0 "D3" H 2600 2550 50  0000 C CNN
F 1 "LED" H 2600 2350 50  0000 C CNN
F 2 "~" H 2600 2450 60  0000 C CNN
F 3 "~" H 2600 2450 60  0000 C CNN
	1    2600 2450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 52F9D13C
P 3150 2450
F 0 "R2" V 3230 2450 40  0000 C CNN
F 1 "R" V 3157 2451 40  0000 C CNN
F 2 "~" V 3080 2450 30  0000 C CNN
F 3 "~" H 3150 2450 30  0000 C CNN
	1    3150 2450
	0    -1   -1   0   
$EndComp
$Comp
L +5V #PWR09
U 1 1 52F9D205
P 2350 2450
F 0 "#PWR09" H 2350 2540 20  0001 C CNN
F 1 "+5V" H 2350 2540 30  0000 C CNN
F 2 "" H 2350 2450 60  0000 C CNN
F 3 "" H 2350 2450 60  0000 C CNN
	1    2350 2450
	0    -1   -1   0   
$EndComp
Text Notes 4600 4950 0    60   ~ 0
Jumper
$Comp
L CONN_10X2 P1
U 1 1 52F8BA09
P 3350 3600
F 0 "P1" H 3350 4150 60  0000 C CNN
F 1 "CONN_10X2" V 3350 3500 50  0000 C CNN
F 2 "" H 3350 3600 60  0000 C CNN
F 3 "" H 3350 3600 60  0000 C CNN
	1    3350 3600
	1    0    0    -1  
$EndComp
Text Label 2500 4450 0    60   ~ 0
SO
Text Label 2500 4350 0    60   ~ 0
SI
Text Label 3850 3550 0    60   ~ 0
IN2
Text Label 3850 4050 0    60   ~ 0
IN12
$Comp
L CONN_3 K2
U 1 1 52FB13F1
P 2150 3250
F 0 "K2" V 2100 3250 50  0000 C CNN
F 1 "CONN_3" V 2200 3250 40  0000 C CNN
F 2 "" H 2150 3250 60  0000 C CNN
F 3 "" H 2150 3250 60  0000 C CNN
	1    2150 3250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2500 3150 3850 3150
Wire Wire Line
	2500 3250 2600 3250
Wire Wire Line
	2600 3250 2600 3350
Wire Wire Line
	2650 3250 3850 3250
Wire Wire Line
	2650 3250 2650 3400
Wire Wire Line
	2650 3400 2500 3400
Wire Wire Line
	2500 3400 2500 3350
Connection ~ 2950 3150
Connection ~ 2950 3250
Wire Wire Line
	2600 3350 3750 3350
Connection ~ 2950 3350
Connection ~ 3750 3150
Connection ~ 3750 3250
Wire Wire Line
	4400 4700 4150 4700
Wire Wire Line
	4650 2000 4200 2000
$Comp
L CONN_16 P2
U 1 1 52FB1B2B
P 6900 3000
F 0 "P2" H 6900 3950 70  0000 C CNN
F 1 "CONN_16" V 6900 3000 50  0000 C CNN
F 2 "~" H 6900 3000 60  0000 C CNN
F 3 "~" H 6900 3000 60  0000 C CNN
	1    6900 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3750 3850 3750
Wire Wire Line
	2950 3850 2850 3850
$Comp
L CONN_2X2 P3
U 1 1 52FB2102
P 3050 4400
F 0 "P3" H 3050 4550 50  0000 C CNN
F 1 "CONN_2X2" H 3060 4270 40  0000 C CNN
F 2 "" H 3050 4400 60  0000 C CNN
F 3 "" H 3050 4400 60  0000 C CNN
	1    3050 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 4350 3600 4350
Wire Wire Line
	3450 4450 3600 4450
Wire Wire Line
	2650 4350 2500 4350
Wire Wire Line
	2650 4450 2500 4450
Wire Wire Line
	4200 2000 4200 2150
$Comp
L R R3
U 1 1 52FB23F7
P 4400 2250
F 0 "R3" V 4480 2250 40  0000 C CNN
F 1 "R" V 4407 2251 40  0000 C CNN
F 2 "~" V 4330 2250 30  0000 C CNN
F 3 "~" H 4400 2250 30  0000 C CNN
	1    4400 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1900 4400 2000
Connection ~ 4400 2000
Wire Wire Line
	4400 2500 4500 2500
Wire Wire Line
	4500 2500 4500 2350
Text Label 2750 3350 0    60   ~ 0
+3.3V
Text Label 2750 3250 0    60   ~ 0
+5V
Text Label 2800 3150 0    60   ~ 0
GND
Wire Wire Line
	2900 2450 2800 2450
Wire Wire Line
	2400 2450 2350 2450
Wire Wire Line
	3400 2450 3450 2450
$EndSCHEMATC
