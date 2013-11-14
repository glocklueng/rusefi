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
LIBS:HALL_PICKUP-cache
EELAYER 27 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Hall Pickup"
Date "14 nov 2013"
Rev "A"
Comp "RUSEFI.com"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L OP275 U4
U 2 1 524B8379
P 4400 3650
F 0 "U4" H 4400 3800 60  0000 L CNN
F 1 "OP2340" H 4400 3500 60  0000 L CNN
F 2 "" H 4400 3650 60  0000 C CNN
F 3 "" H 4400 3650 60  0000 C CNN
	2    4400 3650
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR026
U 1 1 524B838B
P 4300 3100
F 0 "#PWR026" H 4300 3200 30  0001 C CNN
F 1 "VCC" H 4300 3200 30  0000 C CNN
F 2 "" H 4300 3100 60  0000 C CNN
F 3 "" H 4300 3100 60  0000 C CNN
	1    4300 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 524B8391
P 4300 3950
F 0 "#PWR027" H 4300 3950 30  0001 C CNN
F 1 "GND" H 4300 3880 30  0001 C CNN
F 2 "" H 4300 3950 60  0000 C CNN
F 3 "" H 4300 3950 60  0000 C CNN
	1    4300 3950
	1    0    0    -1  
$EndComp
Text Label 5350 3650 2    60   ~ 0
MCU PIN
$Comp
L GND #PWR029
U 1 1 524B83B9
P 4900 4650
F 0 "#PWR029" H 4900 4650 30  0001 C CNN
F 1 "GND" H 4900 4580 30  0001 C CNN
F 2 "" H 4900 4650 60  0000 C CNN
F 3 "" H 4900 4650 60  0000 C CNN
	1    4900 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3650 4750 4100
Wire Wire Line
	4300 3100 4300 3350
Wire Wire Line
	4750 4100 3850 4100
Wire Wire Line
	3850 4100 3850 3750
Wire Wire Line
	3850 3750 4050 3750
Wire Wire Line
	4050 3550 3550 3550
Wire Wire Line
	4900 3650 5350 3650
$Comp
L CONN_1 PC6
U 1 1 52842320
P 5500 3650
F 0 "PC6" H 5580 3650 40  0000 L CNN
F 1 "CONN_1" H 5500 3705 30  0001 C CNN
F 2 "" H 5500 3650 60  0000 C CNN
F 3 "" H 5500 3650 60  0000 C CNN
	1    5500 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 HALL
U 1 1 5284232F
P 3400 3550
F 0 "HALL" H 3480 3550 40  0000 L CNN
F 1 "CONN_1" H 3400 3605 30  0001 C CNN
F 2 "" H 3400 3550 60  0000 C CNN
F 3 "" H 3400 3550 60  0000 C CNN
	1    3400 3550
	-1   0    0    1   
$EndComp
Text Label 3550 3550 0    60   ~ 0
ENGINE
$Comp
L R R1
U 1 1 52842356
P 4900 3900
F 0 "R1" H 4980 3900 40  0000 C CNN
F 1 "1K" V 4907 3901 40  0000 C CNN
F 2 "~" V 4830 3900 30  0000 C CNN
F 3 "~" H 4900 3900 30  0000 C CNN
	1    4900 3900
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5284235E
P 4900 4350
F 0 "D1" H 4900 4450 50  0000 C CNN
F 1 "LED" H 4900 4250 50  0000 C CNN
F 2 "~" H 4900 4350 60  0000 C CNN
F 3 "~" H 4900 4350 60  0000 C CNN
	1    4900 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 4550 4900 4650
Wire Wire Line
	4750 3650 4900 3650
Text Label 4300 3150 0    60   ~ 0
+5v
Connection ~ 4900 3650
Text Label 3550 3650 0    60   ~ 0
HARNESS
$EndSCHEMATC
