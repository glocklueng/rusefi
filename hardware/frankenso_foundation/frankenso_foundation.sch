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
LIBS:logo
LIBS:logo_flipped
LIBS:frankenso_foundation-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "6 jun 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 0176122-06 P99
U 1 1 5389F085
P 2150 3000
F 0 "P99" H 2150 2900 50  0000 C CNN
F 1 "0176122-06" H 2150 3100 50  0000 C CNN
F 2 "MODULE" H 2150 2650 50  0001 C CNN
F 3 "DOCUMENTATION" H 2150 2750 50  0001 C CNN
	1    2150 3000
	-1   0    0    1   
$EndComp
$Comp
L TEST W1
U 1 1 5391DCE5
P 3300 3750
F 0 "W1" H 3300 3810 40  0000 C CNN
F 1 "TEST" H 3300 3680 40  0000 C CNN
F 2 "" H 3300 3750 60  0000 C CNN
F 3 "" H 3300 3750 60  0000 C CNN
	1    3300 3750
	1    0    0    -1  
$EndComp
$Comp
L TEST W2
U 1 1 5391DCFC
P 3600 3650
F 0 "W2" H 3600 3710 40  0000 C CNN
F 1 "TEST" H 3600 3580 40  0000 C CNN
F 2 "" H 3600 3650 60  0000 C CNN
F 3 "" H 3600 3650 60  0000 C CNN
	1    3600 3650
	1    0    0    -1  
$EndComp
$Comp
L TEST W3
U 1 1 5391DD02
P 3850 3550
F 0 "W3" H 3850 3610 40  0000 C CNN
F 1 "TEST" H 3850 3480 40  0000 C CNN
F 2 "" H 3850 3550 60  0000 C CNN
F 3 "" H 3850 3550 60  0000 C CNN
	1    3850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3750 2900 3750
Wire Wire Line
	2900 3650 3400 3650
Wire Wire Line
	3650 3550 2900 3550
Wire Wire Line
	5250 3550 4050 3550
Text Label 4300 3750 0    60   ~ 0
INJ-12
Text Label 4300 3650 0    60   ~ 0
INJ-11
Text Label 4300 3550 0    60   ~ 0
INJ-10
$Comp
L CONN_8 P_VOID3
U 1 1 5391EE9B
P 5600 3400
F 0 "P_VOID3" V 5550 3400 60  0000 C CNN
F 1 "CONN_8" V 5650 3400 60  0000 C CNN
F 2 "" H 5600 3400 60  0000 C CNN
F 3 "" H 5600 3400 60  0000 C CNN
	1    5600 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3650 5250 3650
Wire Wire Line
	3500 3750 5250 3750
$EndSCHEMATC
