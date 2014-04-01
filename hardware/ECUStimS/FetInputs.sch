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
LIBS:ECUStimS
LIBS:ECUStimS-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 5
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
L MOSFET_N Q?
U 1 1 53374089
P 3550 2750
F 0 "Q?" H 3560 2920 60  0000 R CNN
F 1 "MOSFET_N" H 4150 2600 60  0000 R CNN
F 2 "" H 3550 2750 60  0000 C CNN
F 3 "" H 3550 2750 60  0000 C CNN
	1    3550 2750
	1    0    0    -1  
$EndComp
Text HLabel 3900 2500 2    60   Output ~ 0
In1
Text HLabel 3150 3550 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	3650 2950 3650 3550
Wire Wire Line
	3650 3550 3150 3550
Wire Wire Line
	3200 3450 3200 3550
Connection ~ 3200 3550
Wire Wire Line
	3200 2550 3200 2950
$Comp
L R R?
U 1 1 5337409D
P 3200 2300
F 0 "R?" V 3280 2300 40  0000 C CNN
F 1 "10k" V 3207 2301 40  0000 C CNN
F 2 "" V 3130 2300 30  0000 C CNN
F 3 "" H 3200 2300 30  0000 C CNN
	1    3200 2300
	1    0    0    -1  
$EndComp
Text HLabel 3150 1850 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	3150 1850 3200 1850
Wire Wire Line
	3200 1850 3200 2050
Wire Wire Line
	3900 2500 3650 2500
Wire Wire Line
	3650 2450 3650 2550
Wire Wire Line
	2850 2750 3350 2750
Connection ~ 3200 2750
$Comp
L MOSFET_N Q?
U 1 1 53374166
P 3550 4650
F 0 "Q?" H 3560 4820 60  0000 R CNN
F 1 "MOSFET_N" H 4150 4500 60  0000 R CNN
F 2 "" H 3550 4650 60  0000 C CNN
F 3 "" H 3550 4650 60  0000 C CNN
	1    3550 4650
	1    0    0    -1  
$EndComp
Text HLabel 3900 4400 2    60   Output ~ 0
In6
Text HLabel 3150 5450 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	3650 4850 3650 5450
Wire Wire Line
	3650 5450 3150 5450
Wire Wire Line
	3200 5350 3200 5450
Connection ~ 3200 5450
Wire Wire Line
	3200 4450 3200 4850
Text HLabel 3150 3750 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	3150 3750 3200 3750
Wire Wire Line
	3200 3750 3200 3950
Wire Wire Line
	3900 4400 3650 4400
Wire Wire Line
	3650 4350 3650 4450
Wire Wire Line
	2850 4650 3350 4650
Connection ~ 3200 4650
$Comp
L MOSFET_N Q?
U 1 1 53374187
P 5150 2750
F 0 "Q?" H 5160 2920 60  0000 R CNN
F 1 "MOSFET_N" H 5750 2600 60  0000 R CNN
F 2 "" H 5150 2750 60  0000 C CNN
F 3 "" H 5150 2750 60  0000 C CNN
	1    5150 2750
	1    0    0    -1  
$EndComp
Text HLabel 5500 2500 2    60   Output ~ 0
In2
Text HLabel 4750 3550 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	5250 2950 5250 3550
Wire Wire Line
	5250 3550 4750 3550
Wire Wire Line
	4800 3450 4800 3550
Connection ~ 4800 3550
Wire Wire Line
	4800 2550 4800 2950
Text HLabel 4750 1850 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	4750 1850 4800 1850
Wire Wire Line
	4800 1850 4800 2050
Wire Wire Line
	5500 2500 5250 2500
Wire Wire Line
	5250 2450 5250 2550
Wire Wire Line
	4450 2750 4950 2750
Connection ~ 4800 2750
$Comp
L MOSFET_N Q?
U 1 1 533741A8
P 5150 4650
F 0 "Q?" H 5160 4820 60  0000 R CNN
F 1 "MOSFET_N" H 5750 4500 60  0000 R CNN
F 2 "" H 5150 4650 60  0000 C CNN
F 3 "" H 5150 4650 60  0000 C CNN
	1    5150 4650
	1    0    0    -1  
$EndComp
Text HLabel 5500 4400 2    60   Output ~ 0
In7
Text HLabel 4750 5450 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	5250 4850 5250 5450
Wire Wire Line
	5250 5450 4750 5450
Wire Wire Line
	4800 5350 4800 5450
Connection ~ 4800 5450
Wire Wire Line
	4800 4450 4800 4850
Text HLabel 4750 3750 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	4750 3750 4800 3750
Wire Wire Line
	4800 3750 4800 3950
Wire Wire Line
	5500 4400 5250 4400
Wire Wire Line
	5250 4350 5250 4450
Wire Wire Line
	4450 4650 4950 4650
Connection ~ 4800 4650
$Comp
L MOSFET_N Q?
U 1 1 533741C9
P 6750 2750
F 0 "Q?" H 6760 2920 60  0000 R CNN
F 1 "MOSFET_N" H 7350 2600 60  0000 R CNN
F 2 "" H 6750 2750 60  0000 C CNN
F 3 "" H 6750 2750 60  0000 C CNN
	1    6750 2750
	1    0    0    -1  
$EndComp
Text HLabel 7100 2500 2    60   Output ~ 0
In3
Text HLabel 6350 3550 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	6850 2950 6850 3550
Wire Wire Line
	6850 3550 6350 3550
Wire Wire Line
	6400 3450 6400 3550
Connection ~ 6400 3550
Wire Wire Line
	6400 2550 6400 2950
Text HLabel 6350 1850 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	6350 1850 6400 1850
Wire Wire Line
	6400 1850 6400 2050
Wire Wire Line
	7100 2500 6850 2500
Wire Wire Line
	6850 2450 6850 2550
Wire Wire Line
	6050 2750 6550 2750
Connection ~ 6400 2750
$Comp
L MOSFET_N Q?
U 1 1 533741EA
P 6750 4650
F 0 "Q?" H 6760 4820 60  0000 R CNN
F 1 "MOSFET_N" H 7350 4500 60  0000 R CNN
F 2 "" H 6750 4650 60  0000 C CNN
F 3 "" H 6750 4650 60  0000 C CNN
	1    6750 4650
	1    0    0    -1  
$EndComp
Text HLabel 7100 4400 2    60   Output ~ 0
In8
Text HLabel 6350 5450 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	6850 4850 6850 5450
Wire Wire Line
	6850 5450 6350 5450
Wire Wire Line
	6400 5350 6400 5450
Connection ~ 6400 5450
Wire Wire Line
	6400 4450 6400 4850
Text HLabel 6350 3750 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	6350 3750 6400 3750
Wire Wire Line
	6400 3750 6400 3950
Wire Wire Line
	7100 4400 6850 4400
Wire Wire Line
	6850 4350 6850 4450
Wire Wire Line
	6050 4650 6550 4650
Connection ~ 6400 4650
$Comp
L MOSFET_N Q?
U 1 1 5337420B
P 8350 2750
F 0 "Q?" H 8360 2920 60  0000 R CNN
F 1 "MOSFET_N" H 8950 2600 60  0000 R CNN
F 2 "" H 8350 2750 60  0000 C CNN
F 3 "" H 8350 2750 60  0000 C CNN
	1    8350 2750
	1    0    0    -1  
$EndComp
Text HLabel 8700 2500 2    60   Output ~ 0
In4
Text HLabel 7950 3550 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	8450 2950 8450 3550
Wire Wire Line
	8450 3550 7950 3550
Wire Wire Line
	8000 3450 8000 3550
Connection ~ 8000 3550
Wire Wire Line
	8000 2550 8000 2950
Text HLabel 7950 1850 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	7950 1850 8000 1850
Wire Wire Line
	8000 1850 8000 2050
Wire Wire Line
	8700 2500 8450 2500
Wire Wire Line
	8450 2450 8450 2550
Wire Wire Line
	7650 2750 8150 2750
Connection ~ 8000 2750
$Comp
L MOSFET_N Q?
U 1 1 5337422C
P 8350 4650
F 0 "Q?" H 8360 4820 60  0000 R CNN
F 1 "MOSFET_N" H 8950 4500 60  0000 R CNN
F 2 "" H 8350 4650 60  0000 C CNN
F 3 "" H 8350 4650 60  0000 C CNN
	1    8350 4650
	1    0    0    -1  
$EndComp
Text HLabel 8700 4400 2    60   Output ~ 0
In9
Text HLabel 7950 5450 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	8450 4850 8450 5450
Wire Wire Line
	8450 5450 7950 5450
Wire Wire Line
	8000 5350 8000 5450
Connection ~ 8000 5450
Wire Wire Line
	8000 4450 8000 4850
Text HLabel 7950 3750 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	7950 3750 8000 3750
Wire Wire Line
	8000 3750 8000 3950
Wire Wire Line
	8700 4400 8450 4400
Wire Wire Line
	8450 4350 8450 4450
Wire Wire Line
	7650 4650 8150 4650
Connection ~ 8000 4650
$Comp
L MOSFET_N Q?
U 1 1 5337424D
P 9950 2750
F 0 "Q?" H 9960 2920 60  0000 R CNN
F 1 "MOSFET_N" H 10550 2600 60  0000 R CNN
F 2 "" H 9950 2750 60  0000 C CNN
F 3 "" H 9950 2750 60  0000 C CNN
	1    9950 2750
	1    0    0    -1  
$EndComp
Text HLabel 10300 2500 2    60   Output ~ 0
In5
Text HLabel 9550 3550 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	10050 2950 10050 3550
Wire Wire Line
	10050 3550 9550 3550
Wire Wire Line
	9600 3450 9600 3550
Connection ~ 9600 3550
Wire Wire Line
	9600 2550 9600 2950
Text HLabel 9550 1850 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	9550 1850 9600 1850
Wire Wire Line
	9600 1850 9600 2050
Wire Wire Line
	10300 2500 10050 2500
Wire Wire Line
	10050 2450 10050 2550
Wire Wire Line
	9250 2750 9750 2750
Connection ~ 9600 2750
$Comp
L MOSFET_N Q?
U 1 1 5337426E
P 9950 4650
F 0 "Q?" H 9960 4820 60  0000 R CNN
F 1 "MOSFET_N" H 10550 4500 60  0000 R CNN
F 2 "" H 9950 4650 60  0000 C CNN
F 3 "" H 9950 4650 60  0000 C CNN
	1    9950 4650
	1    0    0    -1  
$EndComp
Text HLabel 10300 4400 2    60   Output ~ 0
In10
Text HLabel 9550 5450 0    60   UnSpc ~ 0
Gnd
Wire Wire Line
	10050 4850 10050 5450
Wire Wire Line
	10050 5450 9550 5450
Wire Wire Line
	9600 5350 9600 5450
Connection ~ 9600 5450
Wire Wire Line
	9600 4450 9600 4850
Text HLabel 9550 3750 0    60   UnSpc ~ 0
Ex_p
Wire Wire Line
	9550 3750 9600 3750
Wire Wire Line
	9600 3750 9600 3950
Wire Wire Line
	10300 4400 10050 4400
Wire Wire Line
	10050 4350 10050 4450
Wire Wire Line
	9250 4650 9750 4650
Connection ~ 9600 4650
Text HLabel 10100 3750 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	10100 3750 10050 3750
Wire Wire Line
	10050 3750 10050 3850
Text HLabel 3700 1850 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	3700 1850 3650 1850
Wire Wire Line
	3650 1850 3650 1950
Text HLabel 5300 1850 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	5300 1850 5250 1850
Wire Wire Line
	5250 1850 5250 1950
Text HLabel 6900 1850 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	6900 1850 6850 1850
Wire Wire Line
	6850 1850 6850 1950
Text HLabel 8500 1850 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	8500 1850 8450 1850
Wire Wire Line
	8450 1850 8450 1950
Text HLabel 10100 1850 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	10100 1850 10050 1850
Wire Wire Line
	10050 1850 10050 1950
Text HLabel 3700 3750 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	3700 3750 3650 3750
Wire Wire Line
	3650 3750 3650 3850
Text HLabel 5300 3750 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	5300 3750 5250 3750
Wire Wire Line
	5250 3750 5250 3850
Text HLabel 6900 3750 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	6900 3750 6850 3750
Wire Wire Line
	6850 3750 6850 3850
Text HLabel 8500 3750 2    60   UnSpc ~ 0
3.3V
Wire Wire Line
	8500 3750 8450 3750
Wire Wire Line
	8450 3750 8450 3850
Connection ~ 3650 4400
Connection ~ 5250 4400
Connection ~ 6850 4400
Connection ~ 8450 4400
Connection ~ 10050 4400
Connection ~ 3650 2500
Connection ~ 5250 2500
Connection ~ 8450 2500
Connection ~ 10050 2500
Connection ~ 6850 2500
$Comp
L R R?
U 1 1 5338461F
P 3650 2200
F 0 "R?" V 3730 2200 40  0000 C CNN
F 1 "10k" V 3657 2201 40  0000 C CNN
F 2 "" V 3580 2200 30  0000 C CNN
F 3 "" H 3650 2200 30  0000 C CNN
	1    3650 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338462A
P 3200 3200
F 0 "R?" V 3280 3200 40  0000 C CNN
F 1 "10k" V 3207 3201 40  0000 C CNN
F 2 "" V 3130 3200 30  0000 C CNN
F 3 "" H 3200 3200 30  0000 C CNN
	1    3200 3200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384635
P 4800 2300
F 0 "R?" V 4880 2300 40  0000 C CNN
F 1 "10k" V 4807 2301 40  0000 C CNN
F 2 "" V 4730 2300 30  0000 C CNN
F 3 "" H 4800 2300 30  0000 C CNN
	1    4800 2300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384640
P 5250 2200
F 0 "R?" V 5330 2200 40  0000 C CNN
F 1 "10k" V 5257 2201 40  0000 C CNN
F 2 "" V 5180 2200 30  0000 C CNN
F 3 "" H 5250 2200 30  0000 C CNN
	1    5250 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338464B
P 4800 3200
F 0 "R?" V 4880 3200 40  0000 C CNN
F 1 "10k" V 4807 3201 40  0000 C CNN
F 2 "" V 4730 3200 30  0000 C CNN
F 3 "" H 4800 3200 30  0000 C CNN
	1    4800 3200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384656
P 6400 2300
F 0 "R?" V 6480 2300 40  0000 C CNN
F 1 "10k" V 6407 2301 40  0000 C CNN
F 2 "" V 6330 2300 30  0000 C CNN
F 3 "" H 6400 2300 30  0000 C CNN
	1    6400 2300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384661
P 6850 2200
F 0 "R?" V 6930 2200 40  0000 C CNN
F 1 "10k" V 6857 2201 40  0000 C CNN
F 2 "" V 6780 2200 30  0000 C CNN
F 3 "" H 6850 2200 30  0000 C CNN
	1    6850 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338466C
P 6400 3200
F 0 "R?" V 6480 3200 40  0000 C CNN
F 1 "10k" V 6407 3201 40  0000 C CNN
F 2 "" V 6330 3200 30  0000 C CNN
F 3 "" H 6400 3200 30  0000 C CNN
	1    6400 3200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384677
P 8000 2300
F 0 "R?" V 8080 2300 40  0000 C CNN
F 1 "10k" V 8007 2301 40  0000 C CNN
F 2 "" V 7930 2300 30  0000 C CNN
F 3 "" H 8000 2300 30  0000 C CNN
	1    8000 2300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384682
P 8450 2200
F 0 "R?" V 8530 2200 40  0000 C CNN
F 1 "10k" V 8457 2201 40  0000 C CNN
F 2 "" V 8380 2200 30  0000 C CNN
F 3 "" H 8450 2200 30  0000 C CNN
	1    8450 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338468D
P 8000 3200
F 0 "R?" V 8080 3200 40  0000 C CNN
F 1 "10k" V 8007 3201 40  0000 C CNN
F 2 "" V 7930 3200 30  0000 C CNN
F 3 "" H 8000 3200 30  0000 C CNN
	1    8000 3200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384698
P 9600 2300
F 0 "R?" V 9680 2300 40  0000 C CNN
F 1 "10k" V 9607 2301 40  0000 C CNN
F 2 "" V 9530 2300 30  0000 C CNN
F 3 "" H 9600 2300 30  0000 C CNN
	1    9600 2300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846A3
P 10050 2200
F 0 "R?" V 10130 2200 40  0000 C CNN
F 1 "10k" V 10057 2201 40  0000 C CNN
F 2 "" V 9980 2200 30  0000 C CNN
F 3 "" H 10050 2200 30  0000 C CNN
	1    10050 2200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846AE
P 9600 3200
F 0 "R?" V 9680 3200 40  0000 C CNN
F 1 "10k" V 9607 3201 40  0000 C CNN
F 2 "" V 9530 3200 30  0000 C CNN
F 3 "" H 9600 3200 30  0000 C CNN
	1    9600 3200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846B9
P 3200 4200
F 0 "R?" V 3280 4200 40  0000 C CNN
F 1 "10k" V 3207 4201 40  0000 C CNN
F 2 "" V 3130 4200 30  0000 C CNN
F 3 "" H 3200 4200 30  0000 C CNN
	1    3200 4200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846CE
P 3650 4100
F 0 "R?" V 3730 4100 40  0000 C CNN
F 1 "10k" V 3657 4101 40  0000 C CNN
F 2 "" V 3580 4100 30  0000 C CNN
F 3 "" H 3650 4100 30  0000 C CNN
	1    3650 4100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846D9
P 3200 5100
F 0 "R?" V 3280 5100 40  0000 C CNN
F 1 "10k" V 3207 5101 40  0000 C CNN
F 2 "" V 3130 5100 30  0000 C CNN
F 3 "" H 3200 5100 30  0000 C CNN
	1    3200 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846E4
P 4800 4200
F 0 "R?" V 4880 4200 40  0000 C CNN
F 1 "10k" V 4807 4201 40  0000 C CNN
F 2 "" V 4730 4200 30  0000 C CNN
F 3 "" H 4800 4200 30  0000 C CNN
	1    4800 4200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846EF
P 4800 5100
F 0 "R?" V 4880 5100 40  0000 C CNN
F 1 "10k" V 4807 5101 40  0000 C CNN
F 2 "" V 4730 5100 30  0000 C CNN
F 3 "" H 4800 5100 30  0000 C CNN
	1    4800 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 533846FA
P 5250 4100
F 0 "R?" V 5330 4100 40  0000 C CNN
F 1 "10k" V 5257 4101 40  0000 C CNN
F 2 "" V 5180 4100 30  0000 C CNN
F 3 "" H 5250 4100 30  0000 C CNN
	1    5250 4100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384705
P 6400 4200
F 0 "R?" V 6480 4200 40  0000 C CNN
F 1 "10k" V 6407 4201 40  0000 C CNN
F 2 "" V 6330 4200 30  0000 C CNN
F 3 "" H 6400 4200 30  0000 C CNN
	1    6400 4200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384710
P 6400 5100
F 0 "R?" V 6480 5100 40  0000 C CNN
F 1 "10k" V 6407 5101 40  0000 C CNN
F 2 "" V 6330 5100 30  0000 C CNN
F 3 "" H 6400 5100 30  0000 C CNN
	1    6400 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338471B
P 6850 4100
F 0 "R?" V 6930 4100 40  0000 C CNN
F 1 "10k" V 6857 4101 40  0000 C CNN
F 2 "" V 6780 4100 30  0000 C CNN
F 3 "" H 6850 4100 30  0000 C CNN
	1    6850 4100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384726
P 8000 4200
F 0 "R?" V 8080 4200 40  0000 C CNN
F 1 "10k" V 8007 4201 40  0000 C CNN
F 2 "" V 7930 4200 30  0000 C CNN
F 3 "" H 8000 4200 30  0000 C CNN
	1    8000 4200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384731
P 8450 4100
F 0 "R?" V 8530 4100 40  0000 C CNN
F 1 "10k" V 8457 4101 40  0000 C CNN
F 2 "" V 8380 4100 30  0000 C CNN
F 3 "" H 8450 4100 30  0000 C CNN
	1    8450 4100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338473C
P 8000 5100
F 0 "R?" V 8080 5100 40  0000 C CNN
F 1 "10k" V 8007 5101 40  0000 C CNN
F 2 "" V 7930 5100 30  0000 C CNN
F 3 "" H 8000 5100 30  0000 C CNN
	1    8000 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384747
P 9600 4200
F 0 "R?" V 9680 4200 40  0000 C CNN
F 1 "10k" V 9607 4201 40  0000 C CNN
F 2 "" V 9530 4200 30  0000 C CNN
F 3 "" H 9600 4200 30  0000 C CNN
	1    9600 4200
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 53384752
P 9600 5100
F 0 "R?" V 9680 5100 40  0000 C CNN
F 1 "10k" V 9607 5101 40  0000 C CNN
F 2 "" V 9530 5100 30  0000 C CNN
F 3 "" H 9600 5100 30  0000 C CNN
	1    9600 5100
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5338475D
P 10050 4100
F 0 "R?" V 10130 4100 40  0000 C CNN
F 1 "10k" V 10057 4101 40  0000 C CNN
F 2 "" V 9980 4100 30  0000 C CNN
F 3 "" H 10050 4100 30  0000 C CNN
	1    10050 4100
	1    0    0    -1  
$EndComp
$Comp
L CONN_12 P?
U 1 1 53389EA5
P 1250 3600
F 0 "P?" V 1200 3600 60  0000 C CNN
F 1 "CONN_12" V 1300 3600 60  0000 C CNN
F 2 "" H 1250 3600 60  0000 C CNN
F 3 "" H 1250 3600 60  0000 C CNN
	1    1250 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1600 3050 2050 3050
Wire Wire Line
	1600 3150 1950 3150
Wire Wire Line
	1600 3250 1950 3250
Wire Wire Line
	1600 3350 1950 3350
Wire Wire Line
	1600 3450 1950 3450
Wire Wire Line
	1600 3550 1950 3550
Wire Wire Line
	1600 3650 1950 3650
Wire Wire Line
	1600 3750 1950 3750
Wire Wire Line
	1600 3850 1950 3850
Wire Wire Line
	1600 3950 1950 3950
Wire Wire Line
	1600 4050 1950 4050
Wire Wire Line
	1600 4150 2050 4150
Text Label 1800 4050 0    60   ~ 0
IN1
Text Label 1800 3950 0    60   ~ 0
IN2
Text Label 1800 3850 0    60   ~ 0
IN3
Text Label 1800 3750 0    60   ~ 0
IN4
Text Label 1800 3650 0    60   ~ 0
IN5
Text Label 1800 3550 0    60   ~ 0
IN6
Text Label 1800 3450 0    60   ~ 0
IN7
Text Label 1800 3350 0    60   ~ 0
IN8
Text Label 1800 3250 0    60   ~ 0
IN9
Text Label 1800 3150 0    60   ~ 0
IN10
Text Label 2900 2750 0    60   ~ 0
IN1
Text Label 4500 2750 0    60   ~ 0
IN2
Text Label 6100 2750 0    60   ~ 0
IN3
Text Label 7700 2750 0    60   ~ 0
IN4
Text Label 9300 2750 0    60   ~ 0
IN5
Text Label 2900 4650 0    60   ~ 0
IN6
Text Label 4500 4650 0    60   ~ 0
IN7
Text Label 6100 4650 0    60   ~ 0
IN8
Text Label 7700 4650 0    60   ~ 0
IN9
Text Label 9300 4650 0    60   ~ 0
IN10
Text HLabel 2050 3050 2    60   UnSpc ~ 0
Gnd
Text HLabel 2050 4150 2    60   UnSpc ~ 0
Gnd
$EndSCHEMATC
