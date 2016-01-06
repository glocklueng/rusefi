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
LIBS:ion-cache
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
L LM7805 U2
U 1 1 568C25DD
P 3450 4250
F 0 "U2" H 3600 4054 50  0000 C CNN
F 1 "LM7805" H 3450 4450 50  0000 C CNN
F 2 "TO_SOT_Packages_THT:TO-220_Neutral123_Vertical" H 3450 4250 50  0001 C CNN
F 3 "" H 3450 4250 50  0000 C CNN
	1    3450 4250
	1    0    0    -1  
$EndComp
$Comp
L D D10
U 1 1 568C2844
P 3050 4050
F 0 "D10" H 3050 4150 50  0000 C CNN
F 1 "UF4007" H 3050 3950 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 3050 4050 50  0001 C CNN
F 3 "" H 3050 4050 50  0000 C CNN
	1    3050 4050
	0    -1   -1   0   
$EndComp
$Comp
L CP C5
U 1 1 568C2B54
P 3050 4350
F 0 "C5" H 3075 4450 50  0000 L CNN
F 1 "47uF 25V" H 3075 4250 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L25_P5" H 3088 4200 50  0001 C CNN
F 3 "" H 3050 4350 50  0000 C CNN
	1    3050 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3050 4500 3450 4500
Wire Wire Line
	3050 3750 3050 3900
$Comp
L C C1
U 1 1 568C2D52
P 3150 5050
F 0 "C1" H 3175 5150 50  0000 L CNN
F 1 "0.1uF" H 3175 4950 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 3188 4900 50  0001 C CNN
F 3 "" H 3150 5050 50  0000 C CNN
	1    3150 5050
	1    0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 568C2DBB
P 2900 5050
F 0 "D2" H 2900 5150 50  0000 C CNN
F 1 "UF4007" H 2900 4950 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 2900 5050 50  0001 C CNN
F 3 "" H 2900 5050 50  0000 C CNN
	1    2900 5050
	0    1    1    0   
$EndComp
$Comp
L D D1
U 1 1 568C2E50
P 2650 4850
F 0 "D1" H 2650 4950 50  0000 C CNN
F 1 "UF4007" H 2650 4750 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 2650 4850 50  0001 C CNN
F 3 "" H 2650 4850 50  0000 C CNN
	1    2650 4850
	1    0    0    1   
$EndComp
Wire Wire Line
	2800 4850 3550 4850
Wire Wire Line
	2900 4850 2900 4900
Wire Wire Line
	3150 4850 3150 4900
Connection ~ 2900 4850
Wire Wire Line
	2900 5200 3650 5200
Connection ~ 3450 5200
Connection ~ 3150 5200
$Comp
L R R5
U 1 1 568C2F2B
P 3700 4850
F 0 "R5" V 3780 4850 50  0000 C CNN
F 1 "1k" V 3700 4850 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3630 4850 50  0001 C CNN
F 3 "" H 3700 4850 50  0000 C CNN
	1    3700 4850
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 568C2FE6
P 3900 4600
F 0 "R4" V 3980 4600 50  0000 C CNN
F 1 "10k" V 3900 4600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3830 4600 50  0001 C CNN
F 3 "" H 3900 4600 50  0000 C CNN
	1    3900 4600
	1    0    0    -1  
$EndComp
Connection ~ 3150 4850
Wire Wire Line
	3850 4850 4000 4850
Wire Wire Line
	3900 4850 3900 4750
Wire Wire Line
	3900 4450 3900 4200
Wire Wire Line
	3850 4200 6250 4200
$Comp
L MPSA92 Q2
U 1 1 568CDE39
P 4200 4850
F 0 "Q2" H 4400 4925 50  0000 L CNN
F 1 "MPSA92" H 4400 4850 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 4400 4775 50  0000 L CIN
F 3 "" H 4200 4850 50  0000 L CNN
	1    4200 4850
	1    0    0    1   
$EndComp
Wire Wire Line
	4300 4200 4300 4650
Connection ~ 3900 4200
Connection ~ 3900 4850
$Comp
L R R3
U 1 1 568CDED4
P 4500 5100
F 0 "R3" V 4580 5100 50  0000 C CNN
F 1 "3.9k" V 4500 5100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4430 5100 50  0001 C CNN
F 3 "" H 4500 5100 50  0000 C CNN
	1    4500 5100
	0    1    1    0   
$EndComp
$Comp
L BC547 Q1
U 1 1 568CDF31
P 4950 5100
F 0 "Q1" H 5150 5175 50  0000 L CNN
F 1 "BC547" H 5150 5100 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 5150 5025 50  0000 L CIN
F 3 "" H 4950 5100 50  0000 L CNN
	1    4950 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5100 4300 5100
Wire Wire Line
	4300 5100 4300 5050
Wire Wire Line
	4650 5100 4750 5100
$Comp
L R R2
U 1 1 568CDFD4
P 4850 5350
F 0 "R2" V 4930 5350 50  0000 C CNN
F 1 "2k" V 4850 5350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4780 5350 50  0001 C CNN
F 3 "" H 4850 5350 50  0000 C CNN
	1    4850 5350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 5100 4700 5350
Connection ~ 4700 5100
Wire Wire Line
	5000 5350 5050 5350
Wire Wire Line
	5050 5300 5050 5450
Wire Wire Line
	3650 5450 9050 5450
Wire Wire Line
	3650 5200 3650 5450
Connection ~ 5050 5350
$Comp
L CP C4
U 1 1 568CE566
P 5400 4400
F 0 "C4" H 5425 4500 50  0000 L CNN
F 1 "4.7uF 16V" H 5425 4300 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L25_P5" H 5438 4250 50  0001 C CNN
F 3 "" H 5400 4400 50  0000 C CNN
	1    5400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4200 5400 4250
Connection ~ 4300 4200
Wire Wire Line
	5400 5450 5400 4550
Connection ~ 5050 5450
$Comp
L C C2
U 1 1 568D0063
P 6050 5250
F 0 "C2" H 6075 5350 50  0000 L CNN
F 1 "1uF" H 6075 5150 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Disc_D7.5_P5" H 6088 5100 50  0001 C CNN
F 3 "" H 6050 5250 50  0000 C CNN
	1    6050 5250
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 568D00BA
P 6250 5250
F 0 "R1" V 6330 5250 50  0000 C CNN
F 1 "51k" V 6250 5250 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6180 5250 50  0001 C CNN
F 3 "" H 6250 5250 50  0000 C CNN
	1    6250 5250
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 568D00F7
P 6250 4850
F 0 "R6" V 6330 4850 50  0000 C CNN
F 1 "51k" V 6250 4850 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6180 4850 50  0001 C CNN
F 3 "" H 6250 4850 50  0000 C CNN
	1    6250 4850
	1    0    0    -1  
$EndComp
$Comp
L LM2903 U1
U 1 1 568D0156
P 6750 5100
F 0 "U1" H 6900 5250 50  0000 C CNN
F 1 "LM2904" H 7000 4950 50  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 6750 5100 50  0001 C CNN
F 3 "" H 6750 5100 50  0000 C CNN
	1    6750 5100
	1    0    0    -1  
$EndComp
$Comp
L LM2903 U1
U 2 1 568D0548
P 7750 5100
F 0 "U1" H 7900 5250 50  0000 C CNN
F 1 "LM2904" H 8000 4950 50  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 7750 5100 50  0001 C CNN
F 3 "" H 7750 5100 50  0000 C CNN
	2    7750 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5000 6250 5100
Wire Wire Line
	6050 5100 6050 5050
Wire Wire Line
	6050 5050 6350 5050
Connection ~ 6250 5050
Wire Wire Line
	6450 5000 6350 5000
Wire Wire Line
	6350 5000 6350 5050
Wire Wire Line
	6050 5450 6050 5400
Connection ~ 5400 5450
Wire Wire Line
	6250 5450 6250 5400
Connection ~ 6050 5450
Connection ~ 6250 5450
Wire Wire Line
	6450 5200 6400 5200
Wire Wire Line
	7150 5100 7050 5100
Wire Wire Line
	7150 5000 7450 5000
Connection ~ 7150 5100
$Comp
L R R9
U 1 1 568D20B4
P 7150 4800
F 0 "R9" V 7230 4800 50  0000 C CNN
F 1 "4.7k" V 7150 4800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7080 4800 50  0001 C CNN
F 3 "" H 7150 4800 50  0000 C CNN
	1    7150 4800
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 568D2117
P 7350 4800
F 0 "R7" V 7430 4800 50  0000 C CNN
F 1 "51k" V 7350 4800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7280 4800 50  0001 C CNN
F 3 "" H 7350 4800 50  0000 C CNN
	1    7350 4800
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 568D259A
P 7950 5350
F 0 "R8" V 8030 5350 50  0000 C CNN
F 1 "51k" V 7950 5350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7880 5350 50  0001 C CNN
F 3 "" H 7950 5350 50  0000 C CNN
	1    7950 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	7450 5200 7350 5200
Wire Wire Line
	7350 4950 7350 5350
Wire Wire Line
	7350 5350 7800 5350
Connection ~ 7350 5200
Wire Wire Line
	8100 5350 8200 5350
Wire Wire Line
	8200 5350 8200 5100
Wire Wire Line
	8050 5100 8300 5100
Connection ~ 7150 5000
Wire Wire Line
	7150 4650 7150 4600
Wire Wire Line
	5050 4600 7350 4600
Wire Wire Line
	5050 4600 5050 4900
Wire Wire Line
	7350 4600 7350 4650
Connection ~ 7150 4600
Wire Wire Line
	6250 4200 6250 4700
Connection ~ 5400 4200
Wire Wire Line
	6650 4800 6650 4550
Wire Wire Line
	6250 4550 7650 4550
Connection ~ 6250 4550
Wire Wire Line
	7650 4550 7650 4800
Connection ~ 6650 4550
Connection ~ 3050 4200
Connection ~ 3450 4500
Text GLabel 8300 5100 2    60   Input ~ 0
to_SoundCard
Connection ~ 8200 5100
Text GLabel 2450 4750 1    60   Input ~ 0
ignition_signal_from_ECU
Wire Wire Line
	2500 4850 2450 4850
$Comp
L ZENER D5
U 1 1 568DBC81
P 5900 3900
F 0 "D5" H 5900 4000 50  0000 C CNN
F 1 "1.5KE200A" H 5900 3800 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-201AD_Horizontal_RM15" H 5900 3900 50  0001 C CNN
F 3 "" H 5900 3900 50  0000 C CNN
	1    5900 3900
	0    1    1    0   
$EndComp
$Comp
L ZENER D4
U 1 1 568DBE04
P 5900 3400
F 0 "D4" H 5900 3500 50  0000 C CNN
F 1 "1.5KE200A" H 5900 3300 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-201AD_Horizontal_RM15" H 5900 3400 50  0001 C CNN
F 3 "" H 5900 3400 50  0000 C CNN
	1    5900 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	5900 3600 5900 3700
Wire Wire Line
	5900 4100 5900 5450
Connection ~ 5900 5450
$Comp
L R R13
U 1 1 568DD833
P 6450 4300
F 0 "R13" V 6530 4300 50  0000 C CNN
F 1 "68k" V 6450 4300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6380 4300 50  0001 C CNN
F 3 "" H 6450 4300 50  0000 C CNN
	1    6450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4450 6450 4600
Connection ~ 6450 4600
$Comp
L D D3
U 1 1 568DDA16
P 6100 3150
F 0 "D3" H 6100 3250 50  0000 C CNN
F 1 "UF4007" H 6100 3050 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 6100 3150 50  0001 C CNN
F 3 "" H 6100 3150 50  0000 C CNN
	1    6100 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3150 5900 3150
Wire Wire Line
	5900 3100 5900 3200
$Comp
L R R12
U 1 1 568DDB9C
P 6450 3150
F 0 "R12" V 6530 3150 50  0000 C CNN
F 1 "180k" V 6450 3150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 6380 3150 50  0001 C CNN
F 3 "" H 6450 3150 50  0000 C CNN
	1    6450 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 3150 6250 3150
$Comp
L MPSA92 Q5
U 1 1 568DE429
P 6750 4000
F 0 "Q5" H 6950 4075 50  0000 L CNN
F 1 "MPSA92" H 6950 4000 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 6950 3925 50  0000 L CIN
F 3 "" H 6750 4000 50  0000 L CNN
	1    6750 4000
	0    -1   1    0   
$EndComp
$Comp
L MPSA92 Q4
U 1 1 568DE4B6
P 7250 4000
F 0 "Q4" H 7450 4075 50  0000 L CNN
F 1 "MPSA92" H 7450 4000 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 7450 3925 50  0000 L CIN
F 3 "" H 7250 4000 50  0000 L CNN
	1    7250 4000
	0    -1   1    0   
$EndComp
$Comp
L MPSA92 Q3
U 1 1 568DE52F
P 7250 3250
F 0 "Q3" H 7450 3325 50  0000 L CNN
F 1 "MPSA92" H 7450 3250 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Inline_Narrow_Oval" H 7450 3175 50  0000 L CIN
F 3 "" H 7250 3250 50  0000 L CNN
	1    7250 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7050 3150 6600 3150
Wire Wire Line
	6750 3800 6750 3150
Connection ~ 6750 3150
Wire Wire Line
	7250 3450 7250 3800
Wire Wire Line
	7050 4100 6950 4100
Wire Wire Line
	7000 4100 7000 3700
Wire Wire Line
	7000 3700 7250 3700
Connection ~ 7250 3700
Connection ~ 7000 4100
Wire Wire Line
	6550 4100 6450 4100
Wire Wire Line
	6450 4100 6450 4150
$Comp
L R R11
U 1 1 568DE885
P 7650 3150
F 0 "R11" V 7730 3150 50  0000 C CNN
F 1 "560" V 7650 3150 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7580 3150 50  0001 C CNN
F 3 "" H 7650 3150 50  0000 C CNN
	1    7650 3150
	0    1    1    0   
$EndComp
$Comp
L R R10
U 1 1 568DE930
P 7650 4100
F 0 "R10" V 7730 4100 50  0000 C CNN
F 1 "560" V 7650 4100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 7580 4100 50  0001 C CNN
F 3 "" H 7650 4100 50  0000 C CNN
	1    7650 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	7500 3150 7450 3150
Wire Wire Line
	7500 4100 7450 4100
Wire Wire Line
	7800 3150 7900 3150
Wire Wire Line
	7850 3150 7850 4100
Wire Wire Line
	7800 4100 7900 4100
$Comp
L ZENER D6
U 1 1 568E0D43
P 8100 3150
F 0 "D6" H 8100 3250 50  0000 C CNN
F 1 "1N4740A" H 8100 3050 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 8100 3150 50  0001 C CNN
F 3 "" H 8100 3150 50  0000 C CNN
	1    8100 3150
	-1   0    0    1   
$EndComp
$Comp
L ZENER D7
U 1 1 568E0FC2
P 8550 3150
F 0 "D7" H 8550 3250 50  0000 C CNN
F 1 "1N4740A" H 8550 3050 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 8550 3150 50  0001 C CNN
F 3 "" H 8550 3150 50  0000 C CNN
	1    8550 3150
	-1   0    0    1   
$EndComp
$Comp
L ZENER D8
U 1 1 568E101F
P 9000 3150
F 0 "D8" H 9000 3250 50  0000 C CNN
F 1 "1N4740A" H 9000 3050 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 9000 3150 50  0001 C CNN
F 3 "" H 9000 3150 50  0000 C CNN
	1    9000 3150
	-1   0    0    1   
$EndComp
$Comp
L CP C3
U 1 1 568E10A6
P 8050 4100
F 0 "C3" H 8075 4200 50  0000 L CNN
F 1 "2.2uF 350V" H 8075 4000 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D12.5_L25_P5" H 8088 3950 50  0001 C CNN
F 3 "" H 8050 4100 50  0000 C CNN
	1    8050 4100
	0    -1   -1   0   
$EndComp
Connection ~ 7850 3150
Wire Wire Line
	8350 3150 8300 3150
Wire Wire Line
	8800 3150 8750 3150
Connection ~ 7850 4100
Wire Wire Line
	9050 5450 9050 4100
Wire Wire Line
	8200 4100 9250 4100
$Comp
L R R14
U 1 1 568E1DEF
P 9250 3350
F 0 "R14" V 9330 3350 50  0000 C CNN
F 1 "33k" V 9250 3350 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM20mm" V 9180 3350 50  0001 C CNN
F 3 "" H 9250 3350 50  0000 C CNN
	1    9250 3350
	-1   0    0    1   
$EndComp
$Comp
L R R15
U 1 1 568E1E82
P 9250 3900
F 0 "R15" V 9330 3900 50  0000 C CNN
F 1 "1M" V 9250 3900 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM20mm" V 9180 3900 50  0001 C CNN
F 3 "" H 9250 3900 50  0000 C CNN
	1    9250 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	9200 3150 9250 3150
Wire Wire Line
	9250 3150 9250 3200
Wire Wire Line
	9250 3500 9250 3750
Wire Wire Line
	9250 4100 9250 4050
Connection ~ 9050 4100
$Comp
L D D9
U 1 1 568E21E0
P 9450 3600
F 0 "D9" H 9450 3700 50  0000 C CNN
F 1 "UF4007" H 9450 3500 50  0000 C CNN
F 2 "Diodes_ThroughHole:Diode_DO-41_SOD81_Horizontal_RM10" H 9450 3600 50  0001 C CNN
F 3 "" H 9450 3600 50  0000 C CNN
	1    9450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3600 9250 3600
Connection ~ 9250 3600
Text GLabel 9650 3600 2    60   Input ~ 0
+300V
Wire Wire Line
	9650 3600 9600 3600
Text GLabel 5750 3100 0    60   Input ~ 0
to_coil_HV
Wire Wire Line
	5750 3100 5900 3100
Connection ~ 5900 3150
$Comp
L CONN_01X01 P2
U 1 1 568EA7F5
P 1250 5900
F 0 "P2" H 1250 6000 50  0000 C CNN
F 1 "CONN_01X01" V 1350 5900 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2-5mm" H 1250 5900 50  0000 C CNN
F 3 "" H 1250 5900 50  0000 C CNN
	1    1250 5900
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X01 P3
U 1 1 568EA9C2
P 1250 6450
F 0 "P3" H 1250 6550 50  0000 C CNN
F 1 "CONN_01X01" V 1350 6450 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2-5mm" H 1250 6450 50  0000 C CNN
F 3 "" H 1250 6450 50  0000 C CNN
	1    1250 6450
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X01 P4
U 1 1 568EAA5B
P 1250 7000
F 0 "P4" H 1250 7100 50  0000 C CNN
F 1 "CONN_01X01" V 1350 7000 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_3mm" H 1250 7000 50  0000 C CNN
F 3 "" H 1250 7000 50  0000 C CNN
	1    1250 7000
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X01 P1
U 1 1 568EAB11
P 1250 5350
F 0 "P1" H 1250 5450 50  0000 C CNN
F 1 "CONN_01X01" V 1350 5350 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2-5mm" H 1250 5350 50  0000 C CNN
F 3 "" H 1250 5350 50  0000 C CNN
	1    1250 5350
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X01 P5
U 1 1 568EAFBB
P 1250 7550
F 0 "P5" H 1250 7650 50  0000 C CNN
F 1 "CONN_01X01" V 1350 7550 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2-5mm" H 1250 7550 50  0000 C CNN
F 3 "" H 1250 7550 50  0000 C CNN
	1    1250 7550
	-1   0    0    -1  
$EndComp
Text GLabel 1550 7550 2    60   Input ~ 0
ignition_signal_from_ECU
Wire Wire Line
	1550 7550 1450 7550
Text GLabel 1550 7000 2    60   Input ~ 0
to_coil_HV
Wire Wire Line
	1550 7000 1450 7000
Text GLabel 1550 6450 2    60   Input ~ 0
to_SoundCard
Wire Wire Line
	1550 6450 1450 6450
Text GLabel 1550 5900 2    60   Input ~ 0
+300V
Wire Wire Line
	1550 5900 1450 5900
Wire Wire Line
	2450 4850 2450 4750
$Comp
L CONN_01X01 P0
U 1 1 568EF97B
P 1250 4800
F 0 "P0" H 1250 4900 50  0000 C CNN
F 1 "CONN_01X01" V 1350 4800 50  0000 C CNN
F 2 "Mounting_Holes:MountingHole_2-5mm" H 1250 4800 50  0000 C CNN
F 3 "" H 1250 4800 50  0000 C CNN
	1    1250 4800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3450 4500 3450 5350
Text GLabel 3350 5350 0    60   Input ~ 0
GND
Wire Wire Line
	3450 5350 3350 5350
Text GLabel 1550 5350 2    60   Input ~ 0
GND
Text GLabel 1550 4800 2    60   Input ~ 0
+12V
Text GLabel 3050 3750 1    60   Input ~ 0
+12V
Wire Wire Line
	1550 4800 1450 4800
Wire Wire Line
	1550 5350 1450 5350
Wire Wire Line
	7650 5400 7650 5550
Connection ~ 7650 5450
$Comp
L Earth #PWR01
U 1 1 568F0E8F
P 7650 5550
F 0 "#PWR01" H 7650 5300 50  0001 C CNN
F 1 "Earth" H 7650 5400 50  0001 C CNN
F 2 "" H 7650 5550 50  0000 C CNN
F 3 "" H 7650 5550 50  0000 C CNN
	1    7650 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 4950 7150 5350
Wire Wire Line
	7150 5350 6400 5350
Wire Wire Line
	6400 5350 6400 5200
Wire Wire Line
	6650 5400 6650 5450
Connection ~ 6650 5450
$EndSCHEMATC
