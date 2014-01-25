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
LIBS:frankenstein_foundation-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "25 jan 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_4X2 P51
U 1 1 52DB4402
P 6400 4600
F 0 "P51" H 6400 4850 50  0000 C CNN
F 1 "CONN_4X2" V 6400 4600 40  0000 C CNN
F 2 "" H 6400 4600 60  0000 C CNN
F 3 "" H 6400 4600 60  0000 C CNN
	1    6400 4600
	1    0    0    -1  
$EndComp
$Comp
L CONN_10X2 P52
U 1 1 52DB4411
P 2950 4400
F 0 "P52" H 2950 4950 60  0000 C CNN
F 1 "CONN_10X2" V 2950 4300 50  0000 C CNN
F 2 "" H 2950 4400 60  0000 C CNN
F 3 "" H 2950 4400 60  0000 C CNN
	1    2950 4400
	1    0    0    -1  
$EndComp
NoConn ~ 6000 4550
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
NoConn ~ 3350 4750
NoConn ~ 3350 4650
NoConn ~ 3350 4550
NoConn ~ 3350 4350
NoConn ~ 3350 4250
NoConn ~ 3350 4050
NoConn ~ 3350 3950
Text Label 3350 4850 0    60   ~ 0
GND
Text Label 2550 4850 2    60   ~ 0
GND
$Comp
L CONN_2 P53
U 1 1 52DB49B9
P 6400 3450
F 0 "P53" V 6350 3450 40  0000 C CNN
F 1 "CONN_2" V 6450 3450 40  0000 C CNN
F 2 "" H 6400 3450 60  0000 C CNN
F 3 "" H 6400 3450 60  0000 C CNN
	1    6400 3450
	1    0    0    -1  
$EndComp
NoConn ~ 6050 3350
NoConn ~ 6050 3550
$Comp
L CONN_5X2 P54
U 1 1 52DB49D4
P 2950 2800
F 0 "P54" H 2950 3100 60  0000 C CNN
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
Wire Wire Line
	5250 4650 6000 4650
Text Label 6000 4650 2    60   ~ 0
CAM
Wire Wire Line
	6000 4450 5650 4450
Text Label 3350 4750 0    60   ~ 0
NC
Text Label 3350 4650 0    60   ~ 0
PD14
Text Label 3350 4550 0    60   ~ 0
PD12
Text Label 3350 4450 0    60   ~ 0
PD10
Wire Wire Line
	3800 4450 3350 4450
NoConn ~ 3800 4450
NoConn ~ 2550 4750
NoConn ~ 2550 4550
Text Label 3350 4350 0    60   ~ 0
PD8
Text Label 3350 4250 0    60   ~ 0
PB14
Wire Wire Line
	4000 4150 3350 4150
Text GLabel 4600 3200 2    60   Input ~ 0
CAN_RX
Wire Wire Line
	4600 3200 4600 4150
Text Label 4600 3650 0    60   ~ 0
CAN_RX
Text Label 3600 4150 0    60   ~ 0
CAN_RX
$Comp
L JUMPER JP1
U 1 1 52E33BA4
P 5350 4450
F 0 "JP1" H 5350 4600 60  0000 C CNN
F 1 "JUMPER" H 5350 4370 40  0000 C CNN
F 2 "~" H 5350 4450 60  0000 C CNN
F 3 "~" H 5350 4450 60  0000 C CNN
	1    5350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4450 5050 4450
$Comp
L JUMPER JP2
U 1 1 52E34097
P 4950 4650
F 0 "JP2" H 4950 4800 60  0000 C CNN
F 1 "JUMPER" H 4950 4570 40  0000 C CNN
F 2 "~" H 4950 4650 60  0000 C CNN
F 3 "~" H 4950 4650 60  0000 C CNN
	1    4950 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4650 4650 4650
Text Label 6000 4450 2    60   ~ 0
CRANK
$Comp
L JUMPER JP3
U 1 1 52E340C3
P 4300 4150
F 0 "JP3" H 4300 4300 60  0000 C CNN
F 1 "JUMPER" H 4300 4070 40  0000 C CNN
F 2 "~" H 4300 4150 60  0000 C CNN
F 3 "~" H 4300 4150 60  0000 C CNN
	1    4300 4150
	1    0    0    -1  
$EndComp
Text Label 6800 4650 0    60   ~ 0
PC7
Text Label 6800 4550 0    60   ~ 0
PC9
$Comp
L CONN_2 P55
U 1 1 52E34759
P 7900 4350
F 0 "P55" V 7850 4350 40  0000 C CNN
F 1 "CONN_2" V 7950 4350 40  0000 C CNN
F 2 "" H 7900 4350 60  0000 C CNN
F 3 "" H 7900 4350 60  0000 C CNN
	1    7900 4350
	-1   0    0    1   
$EndComp
Text Label 8250 4250 0    60   ~ 0
PC9
Text Label 8250 4450 0    60   ~ 0
PC7
$EndSCHEMATC
