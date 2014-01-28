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
Date "28 jan 2014"
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
NoConn ~ 2550 4650
NoConn ~ 3350 4750
NoConn ~ 3350 4650
NoConn ~ 3350 4550
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
P 2950 3650
F 0 "P54" H 2950 3950 60  0000 C CNN
F 1 "CONN_5X2" V 2950 3650 50  0000 C CNN
F 2 "" H 2950 3650 60  0000 C CNN
F 3 "" H 2950 3650 60  0000 C CNN
	1    2950 3650
	1    0    0    -1  
$EndComp
NoConn ~ 2550 3650
NoConn ~ 2550 3550
NoConn ~ 2550 3450
NoConn ~ 3350 3450
NoConn ~ 3350 3550
NoConn ~ 3350 3650
NoConn ~ 3350 3750
NoConn ~ 3350 3850
Wire Wire Line
	5250 4650 6000 4650
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
NoConn ~ 2550 4750
Text Label 3350 4350 0    60   ~ 0
PD8
Text Label 3350 4250 0    60   ~ 0
PB14
Wire Wire Line
	3900 4150 3350 4150
Text Label 3600 4150 0    60   ~ 0
PB12
$Comp
L JUMPER JP52
U 1 1 52E33BA4
P 5350 4450
F 0 "JP52" H 5350 4600 60  0000 C CNN
F 1 "JUMPER" H 5350 4370 40  0000 C CNN
F 2 "~" H 5350 4450 60  0000 C CNN
F 3 "~" H 5350 4450 60  0000 C CNN
	1    5350 4450
	1    0    0    -1  
$EndComp
Text Label 6000 4450 2    60   ~ 0
PA8
Text Label 6800 4650 0    60   ~ 0
PC7
Text Label 6800 4550 0    60   ~ 0
PC9
Text Label 2550 4550 2    60   ~ 0
PD11
Text Label 2550 4450 2    60   ~ 0
PD9
Text Label 2550 4350 2    60   ~ 0
PB15
Text Label 2550 4250 2    60   ~ 0
PB13
Text Label 2550 4150 2    60   ~ 0
PB11
Text Label 2550 4050 2    60   ~ 0
PE15
Text Label 2550 3950 2    60   ~ 0
PE13
Text Label 3350 3950 0    60   ~ 0
PE14
Text Label 3350 4050 0    60   ~ 0
PB10
$Comp
L CONN_6 P56
U 1 1 52E349DA
P 1200 4600
F 0 "P56" V 1150 4600 60  0000 C CNN
F 1 "CONN_6" V 1250 4600 60  0000 C CNN
F 2 "" H 1200 4600 60  0000 C CNN
F 3 "" H 1200 4600 60  0000 C CNN
	1    1200 4600
	-1   0    0    1   
$EndComp
$Comp
L CONN_6 P57
U 1 1 52E349FD
P 1200 4000
F 0 "P57" V 1150 4000 60  0000 C CNN
F 1 "CONN_6" V 1250 4000 60  0000 C CNN
F 2 "" H 1200 4000 60  0000 C CNN
F 3 "" H 1200 4000 60  0000 C CNN
	1    1200 4000
	-1   0    0    1   
$EndComp
Text Label 1550 4850 0    60   ~ 0
GND
Text Label 1550 4750 0    60   ~ 0
PD10
Wire Wire Line
	2550 4550 1550 4550
Wire Wire Line
	2550 4450 1550 4450
Wire Wire Line
	2550 4350 1550 4350
Wire Wire Line
	2550 4250 1550 4250
Wire Wire Line
	2550 4150 1550 4150
Wire Wire Line
	2550 4050 1550 4050
Wire Wire Line
	2550 3950 1550 3950
Text Label 1550 4650 0    60   ~ 0
PD8
Text Label 1550 5200 0    60   ~ 0
PB14
Text Label 1550 5300 0    60   ~ 0
PB10
Text Label 2550 3850 2    60   ~ 0
PE11
Text Label 2550 3750 2    60   ~ 0
PE9
Text Label 2550 3650 2    60   ~ 0
PE7
$Comp
L CONN_6 P58
U 1 1 52E3E69E
P 1200 5450
F 0 "P58" V 1150 5450 60  0000 C CNN
F 1 "CONN_6" V 1250 5450 60  0000 C CNN
F 2 "" H 1200 5450 60  0000 C CNN
F 3 "" H 1200 5450 60  0000 C CNN
	1    1200 5450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2550 3850 1550 3850
Wire Wire Line
	1550 3750 2550 3750
Text Label 5050 4450 2    60   ~ 0
CRANK
Text Label 5750 4650 2    60   ~ 0
PC6
Text Label 4500 4150 0    60   ~ 0
CAN_RX
$Comp
L CONN_6 P_VOID1
U 1 1 52E444C3
P 4400 6150
F 0 "P_VOID1" V 4350 6150 60  0000 C CNN
F 1 "CONN_6" V 4450 6150 60  0000 C CNN
F 2 "" H 4400 6150 60  0000 C CNN
F 3 "" H 4400 6150 60  0000 C CNN
	1    4400 6150
	-1   0    0    1   
$EndComp
Text Label 4650 4650 2    60   ~ 0
CAM
Text Label 4750 5900 0    60   ~ 0
CAM
NoConn ~ 1550 5700
NoConn ~ 1550 5600
NoConn ~ 1550 5500
NoConn ~ 1550 5400
NoConn ~ 4750 6400
NoConn ~ 4750 6300
$Comp
L JUMPER JP53
U 1 1 52E445CA
P 4950 4650
F 0 "JP53" H 4950 4800 60  0000 C CNN
F 1 "JUMPER" H 4950 4570 40  0000 C CNN
F 2 "~" H 4950 4650 60  0000 C CNN
F 3 "~" H 4950 4650 60  0000 C CNN
	1    4950 4650
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP51
U 1 1 52E445DC
P 4200 4150
F 0 "JP51" H 4200 4300 60  0000 C CNN
F 1 "JUMPER" H 4200 4070 40  0000 C CNN
F 2 "~" H 4200 4150 60  0000 C CNN
F 3 "~" H 4200 4150 60  0000 C CNN
	1    4200 4150
	1    0    0    -1  
$EndComp
Text Label 4750 6000 0    60   ~ 0
CAN_RX
Text Notes 3400 5550 0    60   ~ 0
The purpose of this VOID connector is to trick KiCad\ninto assigning proper net name to the jumper pad\nwhich would not happen if the pad is unconnected
Text Label 4750 6100 0    60   ~ 0
CRANK
$Comp
L CONN_6 P55
U 1 1 52E474FE
P 7500 5500
F 0 "P55" V 7450 5500 60  0000 C CNN
F 1 "CONN_6" V 7550 5500 60  0000 C CNN
F 2 "" H 7500 5500 60  0000 C CNN
F 3 "" H 7500 5500 60  0000 C CNN
	1    7500 5500
	-1   0    0    1   
$EndComp
Text Label 7850 5450 0    60   ~ 0
GND
Text Label 7850 5550 0    60   ~ 0
PC7
Text Label 7850 5650 0    60   ~ 0
PC9
NoConn ~ 7850 5250
Text Label 7850 5350 0    60   ~ 0
GND
NoConn ~ 7850 5750
$Comp
L CONN_1 P610
U 1 1 52E831CD
P 5650 6200
F 0 "P610" H 5730 6200 40  0000 L CNN
F 1 "CONN_1" H 5650 6255 30  0001 C CNN
F 2 "" H 5650 6200 60  0000 C CNN
F 3 "" H 5650 6200 60  0000 C CNN
	1    5650 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 6200 4750 6200
Text Label 5200 6200 0    60   ~ 0
VP
$EndSCHEMATC
