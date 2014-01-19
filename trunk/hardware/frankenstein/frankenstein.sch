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
LIBS:LMV324IDR
LIBS:logo
LIBS:logo_flipped
LIBS:project_specific_libs
LIBS:header_10x2
LIBS:art-electro-conn
LIBS:frankenstein-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title ""
Date "19 jan 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 8200 1000 900  400 
U 52A53383
F0 "inj_6ch" 50
F1 "inj_6ch.sch" 50
$EndSheet
$Sheet
S 9800 1800 900  400 
U 52A5358C
F0 "adc_amp_divider" 50
F1 "adc_amp_divider.sch" 50
$EndSheet
$Sheet
S 8200 1800 900  400 
U 52C39F6D
F0 "mmc_usb_1" 50
F1 "mmc_usb_1.sch" 50
$EndSheet
$Comp
L CONN_4X2 P1
U 1 1 52DB4402
P 6400 4600
F 0 "P1" H 6400 4850 50  0000 C CNN
F 1 "CONN_4X2" V 6400 4600 40  0000 C CNN
F 2 "" H 6400 4600 60  0000 C CNN
F 3 "" H 6400 4600 60  0000 C CNN
	1    6400 4600
	1    0    0    -1  
$EndComp
$Comp
L CONN_10X2 P2
U 1 1 52DB4411
P 2950 4400
F 0 "P2" H 2950 4950 60  0000 C CNN
F 1 "CONN_10X2" V 2950 4300 50  0000 C CNN
F 2 "" H 2950 4400 60  0000 C CNN
F 3 "" H 2950 4400 60  0000 C CNN
	1    2950 4400
	1    0    0    -1  
$EndComp
NoConn ~ 6000 4650
NoConn ~ 6000 4550
NoConn ~ 6000 4450
NoConn ~ 6800 4450
NoConn ~ 6800 4550
NoConn ~ 6800 4650
Text Label 6800 4750 0    60   ~ 0
GND
$Comp
L GND #PWR01
U 1 1 52DB443D
P 6950 4900
F 0 "#PWR01" H 6950 4900 30  0001 C CNN
F 1 "GND" H 6950 4830 30  0001 C CNN
F 2 "" H 6950 4900 60  0000 C CNN
F 3 "" H 6950 4900 60  0000 C CNN
	1    6950 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 4750 6950 4750
Wire Wire Line
	6950 4750 6950 4900
Text Label 6000 4750 2    60   ~ 0
GND
NoConn ~ 2550 3950
NoConn ~ 2550 4050
NoConn ~ 2550 4150
NoConn ~ 2550 4250
NoConn ~ 2550 4350
NoConn ~ 2550 4450
NoConn ~ 2550 4650
NoConn ~ 1800 4750
NoConn ~ 3350 4750
NoConn ~ 3350 4650
NoConn ~ 3350 4550
NoConn ~ 3350 4450
NoConn ~ 3350 4350
NoConn ~ 3350 4250
NoConn ~ 3350 4150
NoConn ~ 3350 4050
NoConn ~ 3350 3950
Text Label 3350 4850 0    60   ~ 0
GND
Text Label 2550 4850 2    60   ~ 0
GND
$Comp
L CONN_2 P3
U 1 1 52DB49B9
P 6400 3450
F 0 "P3" V 6350 3450 40  0000 C CNN
F 1 "CONN_2" V 6450 3450 40  0000 C CNN
F 2 "" H 6400 3450 60  0000 C CNN
F 3 "" H 6400 3450 60  0000 C CNN
	1    6400 3450
	1    0    0    -1  
$EndComp
NoConn ~ 6050 3350
NoConn ~ 6050 3550
$Comp
L CONN_5X2 P4
U 1 1 52DB49D4
P 2950 2800
F 0 "P4" H 2950 3100 60  0000 C CNN
F 1 "CONN_5X2" V 2950 2800 50  0000 C CNN
F 2 "" H 2950 2800 60  0000 C CNN
F 3 "" H 2950 2800 60  0000 C CNN
	1    2950 2800
	1    0    0    -1  
$EndComp
NoConn ~ 2550 3000
NoConn ~ 2550 2900
NoConn ~ 2550 2800
NoConn ~ 2550 2700
NoConn ~ 2550 2600
NoConn ~ 3350 2600
NoConn ~ 3350 2700
NoConn ~ 3350 2800
NoConn ~ 3350 2900
NoConn ~ 3350 3000
$Comp
L TEST W1
U 1 1 52DB714B
P 2000 4750
F 0 "W1" H 2000 4810 40  0000 C CNN
F 1 "TEST" H 2000 4680 40  0000 C CNN
F 2 "" H 2000 4750 60  0000 C CNN
F 3 "" H 2000 4750 60  0000 C CNN
	1    2000 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4750 2550 4750
Text Label 2550 4750 2    60   ~ 0
PC6
Text Label 2550 4550 2    60   ~ 0
PA8
$Comp
L TEST W2
U 1 1 52DB716E
P 2000 4550
F 0 "W2" H 2000 4610 40  0000 C CNN
F 1 "TEST" H 2000 4480 40  0000 C CNN
F 2 "" H 2000 4550 60  0000 C CNN
F 3 "" H 2000 4550 60  0000 C CNN
	1    2000 4550
	1    0    0    -1  
$EndComp
NoConn ~ 1800 4550
Wire Wire Line
	2550 4550 2200 4550
$Sheet
S 9800 1050 900  400 
U 52DB7A23
F0 "can_brd_1" 50
F1 "can_brd_1.sch" 50
$EndSheet
$EndSCHEMATC
