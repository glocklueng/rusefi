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
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "11 feb 2014"
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
L CONN_2 P2
U 1 1 52F8B91D
P 3150 2100
F 0 "P2" V 3100 2100 40  0000 C CNN
F 1 "CONN_2" V 3200 2100 40  0000 C CNN
F 2 "" H 3150 2100 60  0000 C CNN
F 3 "" H 3150 2100 60  0000 C CNN
	1    3150 2100
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 52F8B962
P 3550 2300
F 0 "#PWR02" H 3550 2300 30  0001 C CNN
F 1 "GND" H 3550 2230 30  0001 C CNN
F 2 "" H 3550 2300 60  0000 C CNN
F 3 "" H 3550 2300 60  0000 C CNN
	1    3550 2300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 52F8B996
P 4400 2350
F 0 "C1" H 4400 2450 40  0000 L CNN
F 1 "C" H 4406 2265 40  0000 L CNN
F 2 "~" H 4438 2200 30  0000 C CNN
F 3 "~" H 4400 2350 60  0000 C CNN
	1    4400 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 52F8B9B3
P 4400 2600
F 0 "#PWR03" H 4400 2600 30  0001 C CNN
F 1 "GND" H 4400 2530 30  0001 C CNN
F 2 "" H 4400 2600 60  0000 C CNN
F 3 "" H 4400 2600 60  0000 C CNN
	1    4400 2600
	1    0    0    -1  
$EndComp
$Comp
L CONN_10X2 P1
U 1 1 52F8BA09
P 3000 3850
F 0 "P1" H 3000 4400 60  0000 C CNN
F 1 "CONN_10X2" V 3000 3750 50  0000 C CNN
F 2 "" H 3000 3850 60  0000 C CNN
F 3 "" H 3000 3850 60  0000 C CNN
	1    3000 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P3
U 1 1 52F8BA27
P 7600 2400
F 0 "P3" V 7550 2400 50  0000 C CNN
F 1 "CONN_4" V 7650 2400 50  0000 C CNN
F 2 "" H 7600 2400 60  0000 C CNN
F 3 "" H 7600 2400 60  0000 C CNN
	1    7600 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P4
U 1 1 52F8BA36
P 7600 2900
F 0 "P4" V 7550 2900 50  0000 C CNN
F 1 "CONN_4" V 7650 2900 50  0000 C CNN
F 2 "" H 7600 2900 60  0000 C CNN
F 3 "" H 7600 2900 60  0000 C CNN
	1    7600 2900
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P5
U 1 1 52F8BA45
P 7600 3400
F 0 "P5" V 7550 3400 50  0000 C CNN
F 1 "CONN_4" V 7650 3400 50  0000 C CNN
F 2 "" H 7600 3400 60  0000 C CNN
F 3 "" H 7600 3400 60  0000 C CNN
	1    7600 3400
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P6
U 1 1 52F8BA54
P 7600 3900
F 0 "P6" V 7550 3900 50  0000 C CNN
F 1 "CONN_4" V 7650 3900 50  0000 C CNN
F 2 "" H 7600 3900 60  0000 C CNN
F 3 "" H 7600 3900 60  0000 C CNN
	1    7600 3900
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
Text Label 7150 2250 0    60   ~ 0
OUT9
Text Label 7150 2350 0    60   ~ 0
OUT10
Text Label 7150 2450 0    60   ~ 0
OUT1
Text Label 7150 2550 0    60   ~ 0
OUT2
Text Label 7150 2750 0    60   ~ 0
OUT3
Text Label 7150 2850 0    60   ~ 0
OUT4
Text Label 7150 2950 0    60   ~ 0
OUT11
Text Label 7150 3050 0    60   ~ 0
OUT12
Text Label 7150 3250 0    60   ~ 0
OUT13
Text Label 7150 3350 0    60   ~ 0
OUT14
Text Label 7150 3450 0    60   ~ 0
OUT5
Text Label 7150 3550 0    60   ~ 0
OUT6
Text Label 7150 3750 0    60   ~ 0
OUT7
Text Label 7150 3850 0    60   ~ 0
OUT8
Text Label 7150 3950 0    60   ~ 0
OUT15
Text Label 7150 4050 0    60   ~ 0
OUT16
$Comp
L +5V #PWR04
U 1 1 52F8C522
P 4400 1900
F 0 "#PWR04" H 4400 1990 20  0001 C CNN
F 1 "+5V" H 4400 1990 30  0000 C CNN
F 2 "" H 4400 1900 60  0000 C CNN
F 3 "" H 4400 1900 60  0000 C CNN
	1    4400 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 52F8C942
P 2500 3500
F 0 "#PWR05" H 2500 3500 30  0001 C CNN
F 1 "GND" H 2500 3430 30  0001 C CNN
F 2 "" H 2500 3500 60  0000 C CNN
F 3 "" H 2500 3500 60  0000 C CNN
	1    2500 3500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR06
U 1 1 52F8C983
P 3400 3350
F 0 "#PWR06" H 3400 3440 20  0001 C CNN
F 1 "+5V" H 3400 3440 30  0000 C CNN
F 2 "" H 3400 3350 60  0000 C CNN
F 3 "" H 3400 3350 60  0000 C CNN
	1    3400 3350
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 52F8D9F4
P 4000 2450
F 0 "D1" H 4000 2550 50  0000 C CNN
F 1 "LED" H 4000 2350 50  0000 C CNN
F 2 "~" H 4000 2450 60  0000 C CNN
F 3 "~" H 4000 2450 60  0000 C CNN
	1    4000 2450
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 52F8DA08
P 3500 2450
F 0 "R1" V 3580 2450 40  0000 C CNN
F 1 "R" V 3507 2451 40  0000 C CNN
F 2 "~" V 3430 2450 30  0000 C CNN
F 3 "~" H 3500 2450 30  0000 C CNN
	1    3500 2450
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
	3500 2200 3550 2200
Wire Wire Line
	3550 2200 3550 2300
Wire Wire Line
	4850 2250 4650 2250
Wire Wire Line
	4650 2250 4650 2000
Wire Wire Line
	4650 2000 3500 2000
Wire Wire Line
	4400 2600 4400 2550
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
	7250 2250 7150 2250
Wire Wire Line
	7250 2350 7150 2350
Wire Wire Line
	7250 2450 7150 2450
Wire Wire Line
	7250 2550 7150 2550
Wire Wire Line
	7250 2750 7150 2750
Wire Wire Line
	7250 2850 7150 2850
Wire Wire Line
	7250 2950 7150 2950
Wire Wire Line
	7250 3050 7150 3050
Wire Wire Line
	7250 3250 7150 3250
Wire Wire Line
	7250 3350 7150 3350
Wire Wire Line
	7250 3450 7150 3450
Wire Wire Line
	7250 3550 7150 3550
Wire Wire Line
	7250 3750 7150 3750
Wire Wire Line
	7250 3850 7150 3850
Wire Wire Line
	7250 3950 7150 3950
Wire Wire Line
	7250 4050 7150 4050
Connection ~ 3400 3400
Wire Wire Line
	3400 3400 3400 3350
Wire Wire Line
	2500 3500 3400 3500
Connection ~ 2600 3500
Wire Wire Line
	4850 2350 4700 2350
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
	3400 3600 3500 3600
Wire Wire Line
	3400 3700 3500 3700
Wire Wire Line
	3400 3800 3500 3800
Wire Wire Line
	3400 3900 3500 3900
Wire Wire Line
	3400 4000 4000 4000
Wire Wire Line
	3400 4100 3500 4100
Wire Wire Line
	3400 4200 3500 4200
Wire Wire Line
	3400 4300 3500 4300
Wire Wire Line
	2600 3600 2500 3600
Wire Wire Line
	2600 3700 2500 3700
Wire Wire Line
	2600 3800 2500 3800
Wire Wire Line
	2600 3900 2500 3900
Wire Wire Line
	2600 4000 2500 4000
Wire Wire Line
	2400 4100 2600 4100
Wire Wire Line
	2600 4200 2500 4200
Wire Wire Line
	2600 4300 2500 4300
Wire Wire Line
	4400 1900 4400 2150
Connection ~ 4400 2000
Wire Wire Line
	3800 2450 3750 2450
Wire Wire Line
	4200 2450 4200 2000
Connection ~ 4200 2000
$Comp
L GND #PWR07
U 1 1 52F8DC80
P 3200 2500
F 0 "#PWR07" H 3200 2500 30  0001 C CNN
F 1 "GND" H 3200 2430 30  0001 C CNN
F 2 "" H 3200 2500 60  0000 C CNN
F 3 "" H 3200 2500 60  0000 C CNN
	1    3200 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2450 3200 2450
Wire Wire Line
	3200 2450 3200 2500
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
Wire Wire Line
	3400 3400 2600 3400
Text Label 2500 3600 0    60   ~ 0
IN12
Text Label 3500 3600 0    60   ~ 0
IN11
Text Label 2500 3800 0    60   ~ 0
SI
Text Label 3500 3800 0    60   ~ 0
SCLK
Text Label 2500 3900 0    60   ~ 0
SO
Text Label 2500 4300 0    60   ~ 0
IN10
Text Label 3500 4300 0    60   ~ 0
IN9
Text Label 3500 3700 0    60   ~ 0
IN1
Text Label 2500 3700 0    60   ~ 0
IN2
Text Label 3500 4200 0    60   ~ 0
IN3
Text Label 2500 4200 0    60   ~ 0
IN4
Text Label 3500 3900 0    60   ~ 0
CS
Text Label 2500 4000 0    60   ~ 0
Reset
Text Label 3500 4000 0    60   ~ 0
PRG
Text Label 2500 4100 0    60   ~ 0
Fault
$Comp
L CONN_3 K1
U 1 1 52F9CFE5
P 4350 4000
F 0 "K1" V 4300 4000 50  0000 C CNN
F 1 "CONN_3" V 4400 4000 40  0000 C CNN
F 2 "" H 4350 4000 60  0000 C CNN
F 3 "" H 4350 4000 60  0000 C CNN
	1    4350 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3900 4000 3850
Wire Wire Line
	4000 4100 4000 4150
$Comp
L +5V #PWR08
U 1 1 52F9D105
P 4000 3850
F 0 "#PWR08" H 4000 3940 20  0001 C CNN
F 1 "+5V" H 4000 3940 30  0000 C CNN
F 2 "" H 4000 3850 60  0000 C CNN
F 3 "" H 4000 3850 60  0000 C CNN
	1    4000 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 52F9D114
P 4000 4150
F 0 "#PWR09" H 4000 4150 30  0001 C CNN
F 1 "GND" H 4000 4080 30  0001 C CNN
F 2 "" H 4000 4150 60  0000 C CNN
F 3 "" H 4000 4150 60  0000 C CNN
	1    4000 4150
	1    0    0    -1  
$EndComp
$Comp
L LED D3
U 1 1 52F9D123
P 2200 4100
F 0 "D3" H 2200 4200 50  0000 C CNN
F 1 "LED" H 2200 4000 50  0000 C CNN
F 2 "~" H 2200 4100 60  0000 C CNN
F 3 "~" H 2200 4100 60  0000 C CNN
	1    2200 4100
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 52F9D13C
P 1950 3800
F 0 "R2" V 2030 3800 40  0000 C CNN
F 1 "R" V 1957 3801 40  0000 C CNN
F 2 "~" V 1880 3800 30  0000 C CNN
F 3 "~" H 1950 3800 30  0000 C CNN
	1    1950 3800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2000 4100 1950 4100
Wire Wire Line
	1950 4100 1950 4050
$Comp
L +5V #PWR010
U 1 1 52F9D205
P 1950 3500
F 0 "#PWR010" H 1950 3590 20  0001 C CNN
F 1 "+5V" H 1950 3590 30  0000 C CNN
F 2 "" H 1950 3500 60  0000 C CNN
F 3 "" H 1950 3500 60  0000 C CNN
	1    1950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 3550 1950 3500
Text Notes 4200 4250 0    60   ~ 0
Jumper
$EndSCHEMATC
