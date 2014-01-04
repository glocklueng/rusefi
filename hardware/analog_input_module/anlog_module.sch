EESchema Schematic File Version 2
LIBS:project_specific_libs
LIBS:power
LIBS:device
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
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:contrib
LIBS:anlog_module-cache
EELAYER 27 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "rusefi analog module"
Date "3 jan 2014"
Rev "A-1"
Comp "http://rusefi.com"
Comment1 "analog interface for rusefi"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	3950 3850 3250 3850
Wire Wire Line
	3050 4850 3050 4150
Connection ~ 2700 3850
Connection ~ 2700 4850
Wire Wire Line
	2700 4800 2700 4850
Wire Notes Line
	1750 4350 1250 4350
Wire Notes Line
	1000 4350 650  4350
Wire Notes Line
	1250 2150 1750 2150
Wire Notes Line
	650  2150 1000 2150
Wire Notes Line
	650  3150 1000 3150
Wire Notes Line
	1250 3150 1750 3150
Wire Notes Line
	3650 3050 4050 3050
Connection ~ 2750 2550
Wire Wire Line
	3250 2550 3250 2350
Wire Wire Line
	1900 2550 2750 2550
Wire Wire Line
	1900 1650 2750 1650
Connection ~ 2750 2150
Connection ~ 2750 3550
Connection ~ 2150 2550
Connection ~ 2150 3550
Connection ~ 2150 1500
Connection ~ 2150 1100
Connection ~ 1900 1100
Wire Wire Line
	1900 1100 1900 1000
Connection ~ 1900 1500
Connection ~ 1900 2550
Connection ~ 1900 3550
Wire Wire Line
	1900 2150 1900 2050
Connection ~ 1900 2150
Wire Wire Line
	1850 2150 2200 2150
Connection ~ 2150 2150
Wire Wire Line
	1900 3150 1900 3100
Connection ~ 1900 3150
Wire Wire Line
	1850 3150 2200 3150
Connection ~ 2150 3150
Connection ~ 2750 1100
Connection ~ 2750 3150
Wire Wire Line
	1900 600  2750 600 
Wire Wire Line
	3250 1500 3250 1300
Connection ~ 2750 1500
Wire Wire Line
	3250 3550 3250 3250
Wire Wire Line
	1900 3550 2750 3550
Wire Notes Line
	3650 3150 3950 3150
Wire Notes Line
	3950 3150 3900 3100
Wire Notes Line
	3900 3100 3900 3200
Wire Notes Line
	3900 3200 3950 3150
Wire Notes Line
	3650 3250 4050 3250
Wire Notes Line
	4050 3250 4050 3225
Wire Notes Line
	4050 3225 4025 3200
Wire Notes Line
	4025 3200 4075 3175
Wire Notes Line
	4075 3175 4025 3150
Wire Notes Line
	4025 3150 4075 3125
Wire Notes Line
	4075 3125 4025 3100
Wire Notes Line
	4025 3100 4050 3075
Wire Notes Line
	4050 3075 4050 3050
Wire Notes Line
	4050 2175 4050 2150
Wire Notes Line
	4050 2175 4025 2200
Wire Notes Line
	4025 2200 4075 2225
Wire Notes Line
	4075 2225 4025 2250
Wire Notes Line
	4025 2250 4075 2275
Wire Notes Line
	4075 2275 4025 2300
Wire Notes Line
	4025 2300 4050 2325
Wire Notes Line
	4050 2325 4050 2350
Wire Notes Line
	4050 2350 3650 2350
Wire Notes Line
	4050 2150 3650 2150
Wire Notes Line
	3650 1100 4050 1100
Wire Notes Line
	3650 1300 4050 1300
Wire Notes Line
	4050 1300 4050 1275
Wire Notes Line
	4050 1275 4025 1250
Wire Notes Line
	4025 1250 4075 1225
Wire Notes Line
	4075 1225 4025 1200
Wire Notes Line
	4025 1200 4075 1175
Wire Notes Line
	4075 1175 4025 1150
Wire Notes Line
	4025 1150 4050 1125
Wire Notes Line
	4050 1125 4050 1100
Wire Wire Line
	1850 1100 2200 1100
Wire Wire Line
	1850 4350 2150 4350
Wire Wire Line
	2700 4350 2700 4400
Wire Notes Line
	1750 1100 650  1100
Wire Wire Line
	2150 3850 2850 3850
Wire Wire Line
	3050 4150 3450 4150
Wire Wire Line
	2150 4850 3050 4850
Text Label 2750 3850 2    60   ~ 0
12V-SENSE
$Comp
L MOS_PRO Q3
U 1 1 510443CC
P 3050 3950
F 0 "Q3" H 3050 4140 60  0000 R CNN
F 1 "MOS_PRO" H 3050 3770 60  0000 R CNN
F 2 "SOT23" H 3050 3950 60  0001 C CNN
F 3 "" H 3050 3950 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 3050 3950 60  0001 C CNN "MFG,MFG#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 3050 3950 60  0001 C CNN "VEND1,VEND1#"
	1    3050 3950
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR4
U 1 1 50E01CC8
P 2700 4850
F 0 "#PWR4" H 2700 4850 30  0001 C CNN
F 1 "GND" H 2700 4780 30  0001 C CNN
F 2 "" H 2700 4850 60  0001 C CNN
F 3 "" H 2700 4850 60  0001 C CNN
	1    2700 4850
	1    0    0    -1  
$EndComp
Text Notes 600  600  0    60   ~ 0
STM DISCOVERY F4\ndev board
Text Notes 4500 4100 0    60   ~ 0
Battery - post
Text Notes 4500 3900 0    60   ~ 0
Battery + post
$Comp
L R R11
U 1 1 50BBF105
P 2700 4100
F 0 "R11" V 2780 4100 50  0000 C CNN
F 1 "2.2k" V 2700 4100 50  0000 C CNN
F 2 "Sm0805" V 1130 2600 60  0001 C CNN
F 3 "" H 2700 4100 60  0001 C CNN
F 4 "vishay,CRCW08052K21FKEA" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-2.21KCCT-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    2700 4100
	-1   0    0    1   
$EndComp
Text Notes 3850 1425 0    30   ~ 0
TYP range 1k, to 10k.
Text Notes 3775 2450 0    30   ~ 0
TYP range 1k, to 10k.
Text Notes 4200 3200 0    60   ~ 0
Throttle Position Sensor
Text Notes 4150 2300 0    60   ~ 0
CooLanT temperature
Text Notes 4150 1250 0    60   ~ 0
Intake Air Temperature
$Comp
L LED D9
U 1 1 50BBE19F
P 2700 4600
F 0 "D9" H 2700 4700 50  0000 C CNN
F 1 "LED" H 2700 4500 50  0000 C CNN
F 2 "LED-0805" H 2700 4600 60  0001 C CNN
F 3 "" H 2700 4600 60  0001 C CNN
	1    2700 4600
	0    1    1    0   
$EndComp
Text Notes 650  4350 0    60   ~ 0
???
$Comp
L CONN_2 P4
U 1 1 50BBDFEF
P 4300 3950
F 0 "P4" V 4250 3950 40  0000 C CNN
F 1 "BAT" V 4350 3950 40  0000 C CNN
F 2 "Phoenix_edge_3.5mm_2pos" V 1930 2600 60  0001 C CNN
F 3 "" H 4300 3950 60  0001 C CNN
F 4 "Phoenix,1893685" V 1930 2600 60  0001 C CNN "mfg,mfg#"
F 5 "MOUSER,651-1893685" V 1930 2600 60  0001 C CNN "vend1,vend1#"
	1    4300 3950
	1    0    0    1   
$EndComp
Text Notes 650  1100 0    60   ~ 0
???
Text Notes 650  2150 0    60   ~ 0
???
Text Notes 650  3150 0    60   ~ 0
???
Text Label 2050 4350 2    60   ~ 0
bat
$Comp
L CONN_3 P3
U 1 1 50BBDBDB
P 3600 3150
F 0 "P3" V 3550 3150 50  0000 C CNN
F 1 "TPS" V 3650 3150 40  0000 C CNN
F 2 "Phoenix_edge_3.5mm_3pos" V 1230 2700 60  0001 C CNN
F 3 "" H 3600 3150 60  0001 C CNN
F 4 "Phoenix,1893698" V 1230 2700 60  0001 C CNN "mfg,mfg#"
F 5 "MOUSER,651-1893698" V 1230 2700 60  0001 C CNN "vend1,vend1#"
	1    3600 3150
	1    0    0    1   
$EndComp
$Comp
L CONN_2 P2
U 1 1 50BBDBCC
P 3600 2250
F 0 "P2" V 3550 2250 40  0000 C CNN
F 1 "CLT" V 3650 2250 40  0000 C CNN
F 2 "Phoenix_edge_3.5mm_2pos" V 1230 2650 60  0001 C CNN
F 3 "" H 3600 2250 60  0001 C CNN
F 4 "Phoenix,1893685" V 1230 2650 60  0001 C CNN "mfg,mfg#"
F 5 "MOUSER,651-1893685" V 1230 2650 60  0001 C CNN "vend1,vend1#"
	1    3600 2250
	1    0    0    1   
$EndComp
$Comp
L CONN_2 P1
U 1 1 50BBDBC1
P 3600 1200
F 0 "P1" V 3550 1200 40  0000 C CNN
F 1 "IAT" V 3650 1200 40  0000 C CNN
F 2 "Phoenix_edge_3.5mm_2pos" V 1230 2600 60  0001 C CNN
F 3 "" H 3600 1200 60  0001 C CNN
F 4 "Phoenix,1893685" V 1230 2600 60  0001 C CNN "mfg,mfg#"
F 5 "MOUSER,651-1893685" V 1230 2600 60  0001 C CNN "vend1,vend1#"
	1    3600 1200
	1    0    0    1   
$EndComp
Text Label 2750 3150 0    60   ~ 0
tps
Text Label 1950 3150 0    60   ~ 0
tps-p
Text Label 1950 2700 0    60   ~ 0
3.3V_AN_protected
Text Label 1950 1650 0    60   ~ 0
3.3V_AN_protected
Text Label 2750 1100 0    60   ~ 0
iat
Text Label 2750 2150 0    60   ~ 0
clt
Text Label 1950 2150 0    60   ~ 0
clt-p
Text Notes 3350 3400 0    30   ~ 0
TYP TPS wiper ranges from 1k, to 10k.
$Comp
L DIODE D6
U 1 1 4E980172
P 1900 3350
F 0 "D6" H 1900 3450 40  0000 C CNN
F 1 "L-AN-D" H 1900 3250 40  0000 C CNN
F 2 "SOD-123" V 1130 2700 60  0001 C CNN
F 3 "" H 1900 3350 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" V 1130 2700 60  0001 C CNN "mfg,mfg#"
F 5 "digi,BAT54T1GOSCT-ND" V 1130 2700 60  0001 C CNN "vend1,vend1#"
	1    1900 3350
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D4
U 1 1 4E980163
P 1900 2350
F 0 "D4" H 1900 2450 40  0000 C CNN
F 1 "L-AN-D" H 1900 2250 40  0000 C CNN
F 2 "SOD-123" V 1130 2650 60  0001 C CNN
F 3 "" H 1900 2350 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" V 1130 2650 60  0001 C CNN "mfg,mfg#"
F 5 "digi,BAT54T1GOSCT-ND" V 1130 2650 60  0001 C CNN "vend1,vend1#"
	1    1900 2350
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D2
U 1 1 4E98013C
P 1900 1300
F 0 "D2" H 1900 1400 40  0000 C CNN
F 1 "L-AN-D" H 1900 1200 40  0000 C CNN
F 2 "SOD-123" V 1130 2600 60  0001 C CNN
F 3 "" H 1900 1300 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "digi,BAT54T1GOSCT-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    1900 1300
	0    -1   -1   0   
$EndComp
Text Label 3900 3850 2    60   ~ 0
12V-BATmA
$Comp
L C C3
U 1 1 4E4821E9
P 2150 3350
F 0 "C3" H 2200 3450 50  0000 L CNN
F 1 ".01uf" H 2200 3250 50  0000 L CNN
F 2 "SM0805" V 830 350 60  0001 C CNN
F 3 "" H 2150 3350 60  0001 C CNN
F 4 "avx,08055C103JAT2A " V 830 350 60  0001 C CNN "mfg,mfg#"
F 5 "newark,96M1408" V 830 350 60  0001 C CNN "vend1,vend1#"
F 6 "" V 830 350 60  0001 C CNN "Field6"
F 7 "" V 830 350 60  0001 C CNN "Field7"
F 8 "50v" V 830 350 60  0001 C CNN "V"
F 9 "10%" V 830 350 60  0001 C CNN "tol"
F 10 "ceramic" V 830 350 60  0001 C CNN "construct"
F 11 "other,more,stuff" V 830 350 60  0001 C CNN "misc"
	1    2150 3350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 4E4821DE
P 2150 2350
F 0 "C2" H 2200 2450 50  0000 L CNN
F 1 ".01uf" H 2200 2250 50  0000 L CNN
F 2 "SM0805" V 830 2300 60  0001 C CNN
F 3 "" H 2150 2350 60  0001 C CNN
F 4 "avx,08055C103JAT2A " V 830 2300 60  0001 C CNN "mfg,mfg#"
F 5 "newark,96M1408" V 830 2300 60  0001 C CNN "vend1,vend1#"
F 6 "" V 830 2300 60  0001 C CNN "Field6"
F 7 "" V 830 2300 60  0001 C CNN "Field7"
F 8 "50v" V 830 2300 60  0001 C CNN "V"
F 9 "10%" V 830 2300 60  0001 C CNN "tol"
F 10 "ceramic" V 830 2300 60  0001 C CNN "construct"
F 11 "other,more,stuff" V 830 2300 60  0001 C CNN "misc"
	1    2150 2350
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 4E482103
P 2750 3350
F 0 "C6" H 2800 3450 50  0000 L CNN
F 1 "0.1uF" H 2800 3250 50  0000 L CNN
F 2 "SM0805" V 1130 2700 60  0001 C CNN
F 3 "" H 2750 3350 60  0001 C CNN
F 4 "AVX,08055C104KAT2A" V 1130 2700 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,478-1395-1-ND" V 1130 2700 60  0001 C CNN "vend1,vend1#"
	1    2750 3350
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 4E4820FA
P 2750 2350
F 0 "C5" H 2800 2450 50  0000 L CNN
F 1 "0.1uF" H 2800 2250 50  0000 L CNN
F 2 "SM0805" V 1130 2650 60  0001 C CNN
F 3 "" H 2750 2350 60  0001 C CNN
F 4 "AVX,08055C104KAT2A" V 1130 2650 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,478-1395-1-ND" V 1130 2650 60  0001 C CNN "vend1,vend1#"
	1    2750 2350
	1    0    0    -1  
$EndComp
$Comp
L DIODE D5
U 1 1 4E4819ED
P 1900 2900
F 0 "D5" H 1900 3000 40  0000 C CNN
F 1 "H-AN-D" H 1900 2800 40  0000 C CNN
F 2 "SOD-123" V 1130 2700 60  0001 C CNN
F 3 "" H 1900 2900 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" V 1130 2700 60  0001 C CNN "mfg,mfg#"
F 5 "digi,BAT54T1GOSCT-ND" V 1130 2700 60  0001 C CNN "vend1,vend1#"
	1    1900 2900
	0    -1   -1   0   
$EndComp
$Comp
L DIODE D3
U 1 1 4E4819E6
P 1900 1850
F 0 "D3" H 1900 1950 40  0000 C CNN
F 1 "H-AN-D" H 1900 1750 40  0000 C CNN
F 2 "SOD-123" V 1130 2650 60  0001 C CNN
F 3 "" H 1900 1850 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" V 1130 2650 60  0001 C CNN "mfg,mfg#"
F 5 "digi,BAT54T1GOSCT-ND" V 1130 2650 60  0001 C CNN "vend1,vend1#"
	1    1900 1850
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 4E47FD9B
P 2750 1900
F 0 "R13" V 2830 1900 50  0000 C CNN
F 1 "2K4" V 2750 1900 50  0000 C CNN
F 2 "SM0805" V 830 2300 60  0001 C CNN
F 3 "" H 2750 1900 60  0001 C CNN
F 4 "vishay,TNPW08052K49BEEA" V 830 2300 60  0001 C CNN "mfg,mfg#"
F 5 "newark,05R1646" V 830 2300 60  0001 C CNN "vend1,vend1#"
F 6 "" V 830 2300 60  0001 C CNN "Field6"
F 7 "" V 830 2300 60  0001 C CNN "Field7"
F 8 "125mW" V 830 2300 60  0001 C CNN "w"
F 9 ".1%" V 830 2300 60  0001 C CNN "tolerance"
F 10 "thin film" V 830 2300 60  0001 C CNN "construct"
F 11 "other,more,stuff" V 830 2300 60  0001 C CNN "misc"
	1    2750 1900
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 4E47FC8B
P 2450 3150
F 0 "R10" V 2530 3150 50  0000 C CNN
F 1 "2.2k" V 2450 3150 50  0000 C CNN
F 2 "Sm0805" V 1130 2700 60  0001 C CNN
F 3 "" H 2450 3150 60  0001 C CNN
F 4 "vishay,CRCW08052K21FKEA" V 1130 2700 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-2.21KCCT-ND" V 1130 2700 60  0001 C CNN "vend1,vend1#"
	1    2450 3150
	0    -1   -1   0   
$EndComp
$Comp
L R R9
U 1 1 4E47FC7E
P 2450 2150
F 0 "R9" V 2530 2150 50  0000 C CNN
F 1 "2.2k" V 2450 2150 50  0000 C CNN
F 2 "Sm0805" V 1130 2650 60  0001 C CNN
F 3 "" H 2450 2150 60  0001 C CNN
F 4 "vishay,CRCW08052K21FKEA" V 1130 2650 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-2.21KCCT-ND" V 1130 2650 60  0001 C CNN "vend1,vend1#"
	1    2450 2150
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 4E467DF0
P 2450 1100
F 0 "R8" V 2530 1100 50  0000 C CNN
F 1 "2.2k" V 2450 1100 50  0000 C CNN
F 2 "Sm0805" V 1130 2600 60  0001 C CNN
F 3 "" H 2450 1100 60  0001 C CNN
F 4 "vishay,CRCW08052K21FKEA" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-2.21KCCT-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    2450 1100
	0    -1   -1   0   
$EndComp
Text Label 2400 3550 0    60   ~ 0
AN_GND
Text Label 2400 2550 0    60   ~ 0
AN_GND
Text Label 2400 1500 0    60   ~ 0
AN_GND
$Comp
L R R12
U 1 1 4E3DE392
P 2750 850
F 0 "R12" V 2830 850 50  0000 C CNN
F 1 "2K4" V 2750 850 50  0000 C CNN
F 2 "SM0805" V 830 2250 60  0001 C CNN
F 3 "" H 2750 850 60  0001 C CNN
F 4 "vishay,TNPW08052K49BEEA" V 830 2250 60  0001 C CNN "mfg,mfg#"
F 5 "newark,05R1646" V 830 2250 60  0001 C CNN "vend1,vend1#"
F 6 "" V 830 2250 60  0001 C CNN "Field6"
F 7 "" V 830 2250 60  0001 C CNN "Field7"
F 8 "125mW" V 830 2250 60  0001 C CNN "w"
F 9 ".1%" V 830 2250 60  0001 C CNN "tolerance"
F 10 "thin film" V 830 2250 60  0001 C CNN "construct"
F 11 "other,more,stuff" V 830 2250 60  0001 C CNN "misc"
	1    2750 850 
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 4E3DE357
P 2750 1300
F 0 "C4" H 2800 1400 50  0000 L CNN
F 1 "0.1uF" H 2800 1200 50  0000 L CNN
F 2 "SM0805" V 1130 2600 60  0001 C CNN
F 3 "" H 2750 1300 60  0001 C CNN
F 4 "AVX,08055C104KAT2A" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,478-1395-1-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    2750 1300
	1    0    0    -1  
$EndComp
Text Label 2600 4850 2    60   ~ 0
AN_GND
Text Label 1950 600  0    60   ~ 0
3.3V_AN_protected
Text Notes 4200 3750 0    60   ~ 0
BATTERY SENSOR
Text Label 1950 1100 0    60   ~ 0
iat-p
$Comp
L R R5
U 1 1 4890FC9B
P 2150 4600
F 0 "R5" V 2230 4600 50  0000 C CNN
F 1 "10k" V 2150 4600 50  0000 C CNN
F 2 "SM0805" V 1130 2600 60  0001 C CNN
F 3 "" H 2150 4600 60  0001 C CNN
F 4 "BOURNS,CR0805-FX-1002ELF" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "digi,CR0805-FX-1002ELFCT-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    2150 4600
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4890FC93
P 2150 4100
F 0 "R4" V 2230 4100 50  0000 C CNN
F 1 "39k" V 2150 4100 50  0000 C CNN
F 2 "SM0805" V -1470 -100 60  0001 C CNN
F 3 "" H 2150 4100 60  0001 C CNN
F 4 "vishay,CRCW080539K0FKEA" V -1470 -100 60  0001 C CNN "mfg,mfg#"
F 5 "newark,53K0197" V -1470 -100 60  0001 C CNN "vend1,vend1#"
F 6 "" V -1470 -100 60  0001 C CNN "Field6"
F 7 "" V -1470 -100 60  0001 C CNN "Field7"
F 8 ".125w" V -1470 -100 60  0001 C CNN "W"
F 9 "1%" V -1470 -100 60  0001 C CNN "tol"
F 10 "thick film" V -1470 -100 60  0001 C CNN "construct"
F 11 "other,more,stuff" V -1470 -100 60  0001 C CNN "misc"
	1    2150 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 4E467DF5
P 1900 3550
F 0 "#PWR3" H 1900 3550 30  0001 C CNN
F 1 "GND" H 1900 3480 30  0001 C CNN
F 2 "" H 1900 3550 60  0001 C CNN
F 3 "" H 1900 3550 60  0001 C CNN
	1    1900 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 489597B8
P 1900 2550
F 0 "#PWR2" H 1900 2550 30  0001 C CNN
F 1 "GND" H 1900 2480 30  0001 C CNN
F 2 "" H 1900 2550 60  0001 C CNN
F 3 "" H 1900 2550 60  0001 C CNN
	1    1900 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 4E467DED
P 1900 1500
F 0 "#PWR1" H 1900 1500 30  0001 C CNN
F 1 "GND" H 1900 1430 30  0001 C CNN
F 2 "" H 1900 1500 60  0001 C CNN
F 3 "" H 1900 1500 60  0001 C CNN
	1    1900 1500
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4E467DE8
P 2150 1300
F 0 "C1" H 2200 1400 50  0000 L CNN
F 1 ".01uf" H 2200 1200 50  0000 L CNN
F 2 "SM0805" V 830 2250 60  0001 C CNN
F 3 "" H 2150 1300 60  0001 C CNN
F 4 "avx,08055C103JAT2A " V 830 2250 60  0001 C CNN "mfg,mfg#"
F 5 "newark,96M1408" V 830 2250 60  0001 C CNN "vend1,vend1#"
F 6 "" V 830 2250 60  0001 C CNN "Field6"
F 7 "" V 830 2250 60  0001 C CNN "Field7"
F 8 "50v" V 830 2250 60  0001 C CNN "V"
F 9 "10%" V 830 2250 60  0001 C CNN "tol"
F 10 "ceramic" V 830 2250 60  0001 C CNN "construct"
F 11 "other,more,stuff" V 830 2250 60  0001 C CNN "misc"
	1    2150 1300
	1    0    0    -1  
$EndComp
$Comp
L DIODE D1
U 1 1 4E467DE6
P 1900 800
F 0 "D1" H 1900 900 40  0000 C CNN
F 1 "H-AN-D" H 1900 700 40  0000 C CNN
F 2 "SOD-123" V 1130 2600 60  0001 C CNN
F 3 "" H 1900 800 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "digi,BAT54T1GOSCT-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    1900 800 
	0    -1   -1   0   
$EndComp
Connection ~ -4675 3450
$Comp
L MOS_PRO Q8
U 1 1 50D6F30C
P 8250 1200
F 0 "Q8" H 8250 1390 60  0000 R CNN
F 1 "MOS_PRO" H 8250 1020 60  0001 R CNN
F 2 "SOT23" H 8250 1200 60  0001 C CNN
F 3 "" H 8250 1200 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 8250 1200 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 8250 1200 60  0001 C CNN "vend1,vend1#"
	1    8250 1200
	-1   0    0    1   
$EndComp
$Comp
L POT RV4
U 1 1 52877F58
P 8900 1200
F 0 "RV4" H 8900 1100 50  0000 C CNN
F 1 "500R" H 8900 1200 50  0000 C CNN
F 2 "POT_TC33X-2" H 8900 1200 60  0001 C CNN
F 3 "~" H 8900 1200 60  0000 C CNN
F 4 "Bourns,TC33X-2-501E" H 8900 1200 60  0001 C CNN "mfg,mfg#"
F 5 "newark,60H9655" H 8900 1200 60  0001 C CNN "vend1,vend1#"
	1    8900 1200
	0    -1   -1   0   
$EndComp
$Comp
L MOS_PRO Q9
U 1 1 52877F67
P 9200 1050
F 0 "Q9" H 9200 1240 60  0000 R CNN
F 1 "MOS_PRO" H 9200 870 60  0001 R CNN
F 2 "SOT23" H 9200 1050 60  0001 C CNN
F 3 "" H 9200 1050 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 9200 1050 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 9200 1050 60  0001 C CNN "vend1,vend1#"
	1    9200 1050
	0    1    -1   0   
$EndComp
$Comp
L VREF D15
U 1 1 52879EF4
P 8900 1550
F 0 "D15" H 8900 1650 40  0000 C CNN
F 1 "VREF" H 8900 1450 30  0000 C CNN
F 2 "SOT323" H 8900 1550 60  0001 C CNN
F 3 "~" H 8900 1550 60  0000 C CNN
F 4 "Analog,ADR5044BRTZ-R2" H 8900 1550 60  0001 C CNN "mfg,mfg#"
F 5 "digi,ADR5044BRTZ-R2" H 8900 1550 60  0001 C CNN "vend1,vend1#"
	1    8900 1550
	0    -1   -1   0   
$EndComp
$Comp
L CONN_1 P9
U 1 1 5287A62B
P 9350 1650
F 0 "P9" H 9430 1650 40  0000 L CNN
F 1 "CONN_1" H 9350 1705 30  0001 C CNN
F 2 "SIL-1" H 9350 1650 60  0001 C CNN
F 3 "" H 9350 1650 60  0000 C CNN
	1    9350 1650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR8
U 1 1 5287A84F
P 9200 1700
F 0 "#PWR8" H 9200 1700 30  0001 C CNN
F 1 "GND" H 9200 1630 30  0001 C CNN
F 2 "" H 9200 1700 60  0000 C CNN
F 3 "" H 9200 1700 60  0000 C CNN
	1    9200 1700
	1    0    0    -1  
$EndComp
Connection ~ 8150 750 
Wire Wire Line
	8900 950  9000 950 
Wire Wire Line
	9200 1250 9200 1700
Connection ~ 9200 1650
Connection ~ 8900 1650
Wire Wire Line
	8150 1400 8150 1650
Wire Wire Line
	8150 750  8150 1000
Wire Wire Line
	8450 1200 8750 1200
Text Label 9500 950  0    60   ~ 0
MCU_3.3V
Wire Wire Line
	9400 950  9500 950 
Text Label 8400 1650 2    60   ~ 0
GND
$Comp
L DIODE D14
U 1 1 5287AEA9
P 8500 1000
F 0 "D14" H 8500 1100 40  0000 C CNN
F 1 "DIODE" H 8500 900 40  0001 C CNN
F 2 "SOD-123" H 8500 1000 60  0001 C CNN
F 3 "SOD-123" H 8500 1000 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" H 8500 1000 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,SS0520-7-F" H 8500 1000 60  0001 C CNN "vend1,vend1#"
F 6 "digi,BAT54T1GOSCT-ND" H 8500 1000 60  0001 C CNN "vend2,vend2"
	1    8500 1000
	0    1    1    0   
$EndComp
Connection ~ 8500 1200
Wire Wire Line
	8500 800  8500 750 
Connection ~ 8500 750 
Text Label 7300 750  0    60   ~ 0
3.3V_AN
Text Notes 8100 1800 0    60   ~ 0
Passed up to 5V shunts \nto GND to keep under \n5.3V max.\nadjust P1, for ?? volts which \nwill limit the protection to 5.3V
$Comp
L FUSE F4
U 1 1 52932969
P 3000 3550
F 0 "F4" H 3100 3600 40  0000 C CNN
F 1 ".5A" H 2900 3500 40  0000 C CNN
F 2 "SM1206" H 3000 3550 60  0001 C CNN
F 3 "~" H 3000 3550 60  0000 C CNN
F 4 "-,-" H 3000 3550 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 3000 3550 60  0001 C CNN "Vend1,Vend1#"
	1    3000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1650 9200 1650
$Comp
L CONN_1 P8
U 1 1 52C6BE24
P 8500 1350
F 0 "P8" H 8580 1350 40  0000 L CNN
F 1 "CONN_1" H 8500 1405 30  0001 C CNN
F 2 "SIL-1" H 8500 1350 60  0001 C CNN
F 3 "" H 8500 1350 60  0000 C CNN
	1    8500 1350
	0    1    1    0   
$EndComp
$Comp
L FUSE F3
U 1 1 52C6BE48
P 3000 2550
F 0 "F3" H 3100 2600 40  0000 C CNN
F 1 ".5A" H 2900 2500 40  0000 C CNN
F 2 "SM1206" H 3000 2550 60  0001 C CNN
F 3 "~" H 3000 2550 60  0000 C CNN
F 4 "-,-" H 3000 2550 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 3000 2550 60  0001 C CNN "Vend1,Vend1#"
	1    3000 2550
	1    0    0    -1  
$EndComp
$Comp
L FUSE F2
U 1 1 52C6BE50
P 3000 1500
F 0 "F2" H 3100 1550 40  0000 C CNN
F 1 ".5A" H 2900 1450 40  0000 C CNN
F 2 "SM1206" H 3000 1500 60  0001 C CNN
F 3 "~" H 3000 1500 60  0000 C CNN
F 4 "-,-" H 3000 1500 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 3000 1500 60  0001 C CNN "Vend1,Vend1#"
	1    3000 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1100 3250 1100
Wire Wire Line
	2700 2150 3250 2150
Wire Wire Line
	2700 3150 3250 3150
Wire Wire Line
	1900 2700 3250 2700
$Comp
L FUSE F5
U 1 1 52C6C81B
P 3700 4150
F 0 "F5" H 3800 4200 40  0000 C CNN
F 1 ".5A" H 3600 4100 40  0000 C CNN
F 2 "SM1206" H 3700 4150 60  0001 C CNN
F 3 "~" H 3700 4150 60  0000 C CNN
F 4 "-,-" H 3700 4150 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 3700 4150 60  0001 C CNN "Vend1,Vend1#"
	1    3700 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4050 3950 4150
Wire Wire Line
	1900 1500 2750 1500
$Comp
L FUSE F8
U 1 1 52C6CCB9
P 7900 750
F 0 "F8" H 8000 800 40  0000 C CNN
F 1 ".5A" H 7800 700 40  0000 C CNN
F 2 "SM1206" H 7900 750 60  0001 C CNN
F 3 "~" H 7900 750 60  0000 C CNN
F 4 "-,-" H 7900 750 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 7900 750 60  0001 C CNN "Vend1,Vend1#"
	1    7900 750 
	1    0    0    -1  
$EndComp
Text Label 8150 750  0    60   ~ 0
3.3V_AN_protected
Wire Wire Line
	8500 750  8150 750 
$Comp
L C C9
U 1 1 50FBE02E
P 4500 5900
F 0 "C9" H 4310 6000 50  0000 L CNN
F 1 "1uF" H 4250 5800 50  0000 L CNN
F 2 "SM0805" V -10170 4675 60  0001 C CNN
F 3 "" H 4500 5900 60  0001 C CNN
F 4 "YAGEO,CC0805KKX7R8BB105" V -10170 4675 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,CC0805KKX7R8BB105" V -10170 4675 60  0001 C CNN "vend1,vend1#"
	1    4500 5900
	0    -1   1    0   
$EndComp
$Comp
L MOS_PRO Q1
U 1 1 52C6E214
P 2050 7000
F 0 "Q1" H 2050 7190 60  0000 R CNN
F 1 "MOS_PRO" H 2050 6820 60  0001 R CNN
F 2 "SOT23" H 2050 7000 60  0001 C CNN
F 3 "" H 2050 7000 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 2050 7000 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 2050 7000 60  0001 C CNN "vend1,vend1#"
	1    2050 7000
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 4AD9C75B
P 1450 7200
F 0 "R1" V 1530 7200 50  0000 C CNN
F 1 "10k" V 1450 7200 50  0000 C CNN
F 2 "SM0603" V -12720 7975 60  0001 C CNN
F 3 "" H 1450 7200 60  0001 C CNN
F 4 "Yageo,RC0603FR-0710KL" V -12720 7975 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0011240p1" V -12720 7975 60  0001 C CNN "vend1,vend1#"
	1    1450 7200
	-1   0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 52C6E215
P 2450 7000
F 0 "RV1" H 2450 6900 50  0000 C CNN
F 1 "500R" H 2450 7000 50  0000 C CNN
F 2 "POT_TC33X-2" H 2450 7000 60  0001 C CNN
F 3 "~" H 2450 7000 60  0000 C CNN
F 4 "Bourns,TC33X-2-501E" H 2450 7000 60  0001 C CNN "mfg,mfg#"
F 5 "newark,60H9655" H 2450 7000 60  0001 C CNN "vend1,vend1#"
	1    2450 7000
	0    -1   -1   0   
$EndComp
$Comp
L MOS_PRO Q2
U 1 1 52C6E216
P 2700 6850
F 0 "Q2" H 2700 7040 60  0000 R CNN
F 1 "MOS_PRO" H 2700 6670 60  0001 R CNN
F 2 "SOT23" H 2700 6850 60  0001 C CNN
F 3 "" H 2700 6850 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 2700 6850 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 2700 6850 60  0001 C CNN "vend1,vend1#"
	1    2700 6850
	0    1    -1   0   
$EndComp
$Comp
L R R2
U 1 1 52877F97
P 1700 5900
F 0 "R2" V 1780 5900 50  0000 C CNN
F 1 "243k" V 1700 5900 50  0000 C CNN
F 2 "SM0805" V -12470 6675 60  0001 C CNN
F 3 "" H 1700 5900 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -12470 6675 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -12470 6675 60  0001 C CNN "vend1,vend1#"
	1    1700 5900
	0    1    -1   0   
$EndComp
$Comp
L VREF D8
U 1 1 52C6E217
P 2450 7350
F 0 "D8" H 2450 7450 40  0000 C CNN
F 1 "VREF" H 2450 7250 30  0000 C CNN
F 2 "SOT323" H 2450 7350 60  0001 C CNN
F 3 "~" H 2450 7350 60  0000 C CNN
F 4 "Analog,ADR5044BRTZ-R2" H 2450 7350 60  0001 C CNN "mfg,mfg#"
F 5 "digi,ADR5044BRTZ-R2" H 2450 7350 60  0001 C CNN "vend1,vend1#"
	1    2450 7350
	0    -1   -1   0   
$EndComp
$Comp
L MCP6G01T-E/OT U1
U 1 1 5287A5E4
P 4400 6550
F 0 "U1" H 4350 6550 70  0000 C CNN
F 1 "MCP6G0_" H 4800 6300 70  0000 C CNN
F 2 "MSOP_8" H 4400 6550 60  0001 C CNN
F 3 "" H 4400 6550 60  0000 C CNN
F 4 "microchip,MCP6G01T-E/OT" H 4400 6550 60  0001 C CNN "mfg,mfg#"
F 5 "digi,MCP6G01T-E/OT" H 4400 6550 60  0001 C CNN "vend1,vend1#"
	1    4400 6550
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P6
U 1 1 52C6E218
P 5650 7450
F 0 "P6" H 5730 7450 40  0000 L CNN
F 1 "CONN_1" H 5650 7505 30  0001 C CNN
F 2 "SIL-1" H 5650 7450 60  0001 C CNN
F 3 "" H 5650 7450 60  0000 C CNN
	1    5650 7450
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P5
U 1 1 5287A631
P 5650 6550
F 0 "P5" H 5730 6550 40  0000 L CNN
F 1 "CONN_1" H 5650 6605 30  0001 C CNN
F 2 "SIL-1" H 5650 6550 60  0001 C CNN
F 3 "" H 5650 6550 60  0000 C CNN
	1    5650 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 7450 4300 6850
Wire Wire Line
	4500 6850 4500 7200
Wire Wire Line
	1450 7450 5500 7450
$Comp
L GND #PWR5
U 1 1 52C6E219
P 4600 7500
F 0 "#PWR5" H 4600 7500 30  0001 C CNN
F 1 "GND" H 4600 7430 30  0001 C CNN
F 2 "" H 4600 7500 60  0000 C CNN
F 3 "" H 4600 7500 60  0000 C CNN
	1    4600 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 7450 4600 7500
Wire Wire Line
	1450 6250 1450 6950
Connection ~ 1950 6550
Wire Wire Line
	2450 6750 2500 6750
Connection ~ 4300 7450
$Comp
L R R16
U 1 1 5287A8C9
P 5050 6550
F 0 "R16" V 5130 6550 50  0000 C CNN
F 1 "150R" V 5050 6550 50  0000 C CNN
F 2 "SM0805" V -9120 7325 60  0001 C CNN
F 3 "" H 5050 6550 60  0001 C CNN
F 4 "bourns,CR0805-FX-1500ELF" V -9120 7325 60  0001 C CNN "mfg,mfg#"
F 5 "digi,CR0805-FX-1500ELFCT-ND" V -9120 7325 60  0001 C CNN "vend1,vend1#"
	1    5050 6550
	0    1    -1   0   
$EndComp
Connection ~ 1950 7450
Wire Wire Line
	1950 7200 1950 7450
Connection ~ 1450 6550
Wire Wire Line
	1950 6550 1950 6800
Wire Wire Line
	2250 7000 2300 7000
Connection ~ 4300 5900
Connection ~ 4300 6250
$Comp
L GND #PWR6
U 1 1 5287AA37
P 4700 6300
F 0 "#PWR6" H 4700 6300 30  0001 C CNN
F 1 "GND" H 4700 6230 30  0001 C CNN
F 2 "" H 4700 6300 60  0000 C CNN
F 3 "" H 4700 6300 60  0000 C CNN
	1    4700 6300
	-1   0    0    -1  
$EndComp
Text Label 4300 6250 1    60   ~ 0
MCU_3.3V
Text Label 2900 6750 0    60   ~ 0
MCU_3.3V
Text Label 4600 6950 0    60   ~ 0
MCU_3.3V
Text Label 5300 6550 0    60   ~ 0
Vmcu_1
Wire Wire Line
	5300 6550 5500 6550
Text Label 5500 7450 2    60   ~ 0
GND
$Comp
L DIODE D7
U 1 1 52C6E21A
P 2250 6800
F 0 "D7" H 2250 6900 40  0000 C CNN
F 1 "DIODE" H 2250 6700 40  0001 C CNN
F 2 "SOD-123" H 2250 6800 60  0001 C CNN
F 3 "SOD-123" H 2250 6800 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" H 2250 6800 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,SS0520-7-F" H 2250 6800 60  0001 C CNN "vend1,vend1#"
F 6 "digi,BAT54T1GOSCT-ND" H 2250 6800 60  0001 C CNN "vend2,vend2"
	1    2250 6800
	0    1    1    0   
$EndComp
Connection ~ 2250 7000
Wire Wire Line
	2250 6600 2250 6550
Connection ~ 2250 6550
Text Label 2600 6550 0    60   ~ 0
signal_1
Text Notes 4750 7150 0    60   ~ 0
GAIN 50\nGAIN 1 (no jumper)\nGAIN 10
Wire Notes Line
	1850 6400 1850 7500
Wire Notes Line
	1850 7500 4150 7500
Wire Notes Line
	3050 5450 3050 7500
Wire Notes Line
	3050 6400 1850 6400
Text Notes 1850 7600 0    60   ~ 0
Passed up to 3.3V shunts \nto GND when over 3.3V to \nkeep signal under 3.6V max.
Connection ~ 4600 7450
Wire Wire Line
	4300 5900 4300 6250
Text Notes 1500 5500 0    60   ~ 0
Front end divider.\nWhen connected to term 3\na 500V input is limited 5V \nat the next stage\n\n
Text Notes 3200 5300 0    60   ~ 0
Selectable Gain Amplifier SGA\ndigitally controlled gain of 50X, 10X or 1X
$Comp
L CONN_3 K1
U 1 1 5287F15B
P 950 6550
F 0 "K1" V 900 6550 50  0000 C CNN
F 1 "CONN_3" V 1000 6550 40  0000 C CNN
F 2 "bornier3" H 950 6550 60  0001 C CNN
F 3 "" H 950 6550 60  0000 C CNN
F 4 "Weidmuller,1760500000" V 950 6550 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,347008p1" V 950 6550 60  0001 C CNN "vend1,vend1#"
	1    950  6550
	-1   0    0    1   
$EndComp
Text Label 1300 6400 1    60   ~ 0
input_500Vmax_1
Text Label 2250 6100 2    60   ~ 0
input_250Vmax_1
Text Label 1450 6450 3    60   ~ 0
input_5Vmax_1
Text Notes 11150 6600 0    60   ~ 0
If 500V input is on pin 3 this will results in 5V on the signal node (100:1). If U1 is set to 1X gain, output = 5V.\nIf 5V on pin 3 results in .05V on the signal node. If U1 is set to 50X gain, output = 2.5V.\nThis can be handy if you are sniffing an automotive ignition signal, that can spike up to 400 to 500V. \n\nIf 250V input is on pin 2, this will result in 5V on the signal node (50:1). If U1 is set to 1X gain, output = 5V. \nIf 50V input is on pin 2, this will result in 1V on the signal node (50:1). If U1 is set to 1X gain, output = 1V. \nIf 25V input is on pin 2, this will result in 1/2V on the signal node (50:1). If U1 is set to 10X gain, output = 5V.\nIf 5V input is on pin 2, this will result in 1/10V on the signal node (50:1). If U1 is set to 50X gain, output = 5V.  \nThis is good for sniffing fuel injectors that might spike to 40 to 70V. \n\nIf 5V input is on pin 1, this will result in 5V on the signal node (1:1). If U1 is set to 1X gain, output = 5V. \nIf 1V input is on pin 1, this will result in 5V on the signal node (1:1). If U1 is set to 10X gain, output = 5V. \nIf .1V input is on pin 1, this will result in 5V on the signal node (1:1). If U1 is set to 50X gain, output = 5V. \nThis is good for signals you know will be 5V or less, including very small signals. \n\nSallenkey LPF 10kHz\nhttp://sim.okawa-denshi.jp/en/OPstool.php
$Comp
L C C10
U 1 1 5288D9F3
P 4500 6250
F 0 "C10" H 4310 6350 50  0000 L CNN
F 1 "1uF" H 4250 6150 50  0000 L CNN
F 2 "SM0805" V -10170 5025 60  0001 C CNN
F 3 "" H 4500 6250 60  0001 C CNN
F 4 "YAGEO,CC0805KKX7R8BB105" V -10170 5025 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,CC0805KKX7R8BB105" V -10170 5025 60  0001 C CNN "vend1,vend1#"
	1    4500 6250
	0    -1   1    0   
$EndComp
$Comp
L R R7
U 1 1 52908526
P 2200 6250
F 0 "R7" V 2280 6250 50  0000 C CNN
F 1 "243k" V 2200 6250 50  0000 C CNN
F 2 "SM0805" V -11970 7025 60  0001 C CNN
F 3 "" H 2200 6250 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -11970 7025 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -11970 7025 60  0001 C CNN "vend1,vend1#"
	1    2200 6250
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 52908557
P 1700 6250
F 0 "R3" V 1780 6250 50  0000 C CNN
F 1 "243k" V 1700 6250 50  0000 C CNN
F 2 "SM0805" V -12470 7025 60  0001 C CNN
F 3 "" H 1700 6250 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -12470 7025 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -12470 7025 60  0001 C CNN "vend1,vend1#"
	1    1700 6250
	0    -1   1    0   
$EndComp
$Comp
L R R6
U 1 1 5290855F
P 2200 5900
F 0 "R6" V 2280 5900 50  0000 C CNN
F 1 "243k" V 2200 5900 50  0000 C CNN
F 2 "SM0805" V -11970 6675 60  0001 C CNN
F 3 "" H 2200 5900 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -11970 6675 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -11970 6675 60  0001 C CNN "vend1,vend1#"
	1    2200 5900
	0    1    -1   0   
$EndComp
$Comp
L R R15
U 1 1 52909041
P 3750 6550
F 0 "R15" V 3830 6550 50  0000 C CNN
F 1 "4.7k" V 3750 6550 50  0000 C CNN
F 2 "SM0603" V -10420 7325 60  0001 C CNN
F 3 "" H 3750 6550 60  0001 C CNN
F 4 "Yageo,RC0603JR-074K7L" V -10420 7325 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0010030p1" V -10420 7325 60  0001 C CNN "vend1,vend1#"
	1    3750 6550
	0    1    -1   0   
$EndComp
$Comp
L R R14
U 1 1 529090DB
P 3250 6550
F 0 "R14" V 3330 6550 50  0000 C CNN
F 1 "4.7k" V 3250 6550 50  0000 C CNN
F 2 "SM0603" V -10920 7325 60  0001 C CNN
F 3 "" H 3250 6550 60  0001 C CNN
F 4 "Yageo,RC0603JR-074K7L" V -10920 7325 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0010030p1" V -10920 7325 60  0001 C CNN "vend1,vend1#"
	1    3250 6550
	0    1    -1   0   
$EndComp
Wire Wire Line
	4700 5900 4700 6300
Connection ~ 4700 6250
$Comp
L C C8
U 1 1 52909177
P 4000 6750
F 0 "C8" H 3810 6850 50  0000 L CNN
F 1 "4.7nF" H 3750 6650 50  0000 L CNN
F 2 "SM0603" V -10670 5525 60  0001 C CNN
F 3 "" H 4000 6750 60  0001 C CNN
F 4 "Yageo,CC0603KRX7R9BB472" V -10670 5525 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,0100850p1" V -10670 5525 60  0001 C CNN "vend1,vend1#"
	1    4000 6750
	1    0    0    1   
$EndComp
$Comp
L C C7
U 1 1 529091EA
P 3700 5600
F 0 "C7" H 3510 5700 50  0000 L CNN
F 1 "4.7nF" H 3450 5500 50  0000 L CNN
F 2 "SM0603" V -10970 4375 60  0001 C CNN
F 3 "" H 3700 5600 60  0001 C CNN
F 4 "Yageo,CC0603KRX7R9BB472" V -10970 4375 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,0100850p1" V -10970 4375 60  0001 C CNN "vend1,vend1#"
	1    3700 5600
	0    1    -1   0   
$EndComp
Wire Wire Line
	3900 5600 4800 5600
Wire Wire Line
	4800 5600 4800 6550
Wire Wire Line
	3500 5600 3500 6550
Wire Wire Line
	4000 6950 4000 7450
Connection ~ 4000 7450
Wire Notes Line
	4150 7500 4150 5450
Wire Notes Line
	4150 5450 3050 5450
Text Notes 3350 7600 0    60   ~ 0
Sallenkey 10kHz
$Comp
L FUSE F1
U 1 1 52C6E21B
P 1700 6550
F 0 "F1" H 1800 6600 40  0000 C CNN
F 1 ".5A" H 1600 6500 40  0000 C CNN
F 2 "SM1206" H 1700 6550 60  0001 C CNN
F 3 "~" H 1700 6550 60  0000 C CNN
F 4 "-,-" H 1700 6550 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 1700 6550 60  0001 C CNN "Vend1,Vend1#"
	1    1700 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6550 3000 6550
$Comp
L JUMPER3 JP1
U 1 1 528790A1
P 4600 7200
F 0 "JP1" H 4650 7100 40  0000 L CNN
F 1 "JUMPER3" H 4600 7300 40  0001 C CNN
F 2 "SIL-3" H 4600 7200 60  0001 C CNN
F 3 "~" H 4600 7200 60  0000 C CNN
F 4 "-,-" H 4600 7200 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,3460810p1" H 4600 7200 60  0001 C CNN "vend1,vend1#"
	1    4600 7200
	0    1    1    0   
$EndComp
Wire Wire Line
	1300 6650 1450 6650
Connection ~ 1450 6650
Wire Wire Line
	2450 5900 2450 6250
Wire Wire Line
	2450 6100 1350 6100
Wire Wire Line
	1350 6100 1350 6550
Wire Wire Line
	1350 6550 1300 6550
Connection ~ 2450 6100
Wire Wire Line
	1300 6450 1300 6450
Wire Wire Line
	1300 6450 1300 5900
Wire Wire Line
	1300 5900 1450 5900
Wire Wire Line
	2700 7050 2700 7450
Connection ~ 2450 7450
Connection ~ 2700 7450
$Comp
L C C17
U 1 1 52C6DFF7
P 9200 5150
F 0 "C17" H 9010 5250 50  0000 L CNN
F 1 "1uF" H 8950 5050 50  0000 L CNN
F 2 "SM0805" V -5470 3925 60  0001 C CNN
F 3 "" H 9200 5150 60  0001 C CNN
F 4 "YAGEO,CC0805KKX7R8BB105" V -5470 3925 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,CC0805KKX7R8BB105" V -5470 3925 60  0001 C CNN "vend1,vend1#"
	1    9200 5150
	0    -1   1    0   
$EndComp
$Comp
L MOS_PRO Q5
U 1 1 52C6DFFF
P 6750 6250
F 0 "Q5" H 6750 6440 60  0000 R CNN
F 1 "MOS_PRO" H 6750 6070 60  0001 R CNN
F 2 "SOT23" H 6750 6250 60  0001 C CNN
F 3 "" H 6750 6250 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 6750 6250 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 6750 6250 60  0001 C CNN "vend1,vend1#"
	1    6750 6250
	-1   0    0    1   
$EndComp
$Comp
L R R18
U 1 1 52C6E007
P 6150 6450
F 0 "R18" V 6230 6450 50  0000 C CNN
F 1 "10k" V 6150 6450 50  0000 C CNN
F 2 "SM0603" V -8020 7225 60  0001 C CNN
F 3 "" H 6150 6450 60  0001 C CNN
F 4 "Yageo,RC0603FR-0710KL" V -8020 7225 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0011240p1" V -8020 7225 60  0001 C CNN "vend1,vend1#"
	1    6150 6450
	-1   0    0    -1  
$EndComp
$Comp
L POT RV3
U 1 1 52C6E00F
P 7150 6250
F 0 "RV3" H 7150 6150 50  0000 C CNN
F 1 "500R" H 7150 6250 50  0000 C CNN
F 2 "POT_TC33X-2" H 7150 6250 60  0001 C CNN
F 3 "~" H 7150 6250 60  0000 C CNN
F 4 "Bourns,TC33X-2-501E" H 7150 6250 60  0001 C CNN "mfg,mfg#"
F 5 "newark,60H9655" H 7150 6250 60  0001 C CNN "vend1,vend1#"
	1    7150 6250
	0    -1   -1   0   
$EndComp
$Comp
L MOS_PRO Q7
U 1 1 52C6E017
P 7400 6100
F 0 "Q7" H 7400 6290 60  0000 R CNN
F 1 "MOS_PRO" H 7400 5920 60  0001 R CNN
F 2 "SOT23" H 7400 6100 60  0001 C CNN
F 3 "" H 7400 6100 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 7400 6100 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 7400 6100 60  0001 C CNN "vend1,vend1#"
	1    7400 6100
	0    1    -1   0   
$EndComp
$Comp
L R R21
U 1 1 52C6E01F
P 6400 5150
F 0 "R21" V 6480 5150 50  0000 C CNN
F 1 "243k" V 6400 5150 50  0000 C CNN
F 2 "SM0805" V -7770 5925 60  0001 C CNN
F 3 "" H 6400 5150 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7770 5925 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7770 5925 60  0001 C CNN "vend1,vend1#"
	1    6400 5150
	0    1    -1   0   
$EndComp
$Comp
L VREF D13
U 1 1 52C6E027
P 7150 6600
F 0 "D13" H 7150 6700 40  0000 C CNN
F 1 "VREF" H 7150 6500 30  0000 C CNN
F 2 "SOT323" H 7150 6600 60  0001 C CNN
F 3 "~" H 7150 6600 60  0000 C CNN
F 4 "Analog,ADR5044BRTZ-R2" H 7150 6600 60  0001 C CNN "mfg,mfg#"
F 5 "digi,ADR5044BRTZ-R2" H 7150 6600 60  0001 C CNN "vend1,vend1#"
	1    7150 6600
	0    -1   -1   0   
$EndComp
$Comp
L MCP6G01T-E/OT U3
U 1 1 52C6E02F
P 9100 5800
F 0 "U3" H 9050 5800 70  0000 C CNN
F 1 "MCP6G0_" H 9500 5550 70  0000 C CNN
F 2 "MSOP_8" H 9100 5800 60  0001 C CNN
F 3 "" H 9100 5800 60  0000 C CNN
F 4 "microchip,MCP6G01T-E/OT" H 9100 5800 60  0001 C CNN "mfg,mfg#"
F 5 "digi,MCP6G01T-E/OT" H 9100 5800 60  0001 C CNN "vend1,vend1#"
	1    9100 5800
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P13
U 1 1 52C6E03B
P 10350 6700
F 0 "P13" H 10430 6700 40  0000 L CNN
F 1 "CONN_1" H 10350 6755 30  0001 C CNN
F 2 "SIL-1" H 10350 6700 60  0001 C CNN
F 3 "" H 10350 6700 60  0000 C CNN
	1    10350 6700
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P12
U 1 1 52C6E041
P 10350 5800
F 0 "P12" H 10430 5800 40  0000 L CNN
F 1 "CONN_1" H 10350 5855 30  0001 C CNN
F 2 "SIL-1" H 10350 5800 60  0001 C CNN
F 3 "" H 10350 5800 60  0000 C CNN
	1    10350 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 6700 9000 6100
Wire Wire Line
	9200 6100 9200 6450
Wire Wire Line
	6150 6700 10200 6700
$Comp
L GND #PWR10
U 1 1 52C6E050
P 9300 6750
F 0 "#PWR10" H 9300 6750 30  0001 C CNN
F 1 "GND" H 9300 6680 30  0001 C CNN
F 2 "" H 9300 6750 60  0000 C CNN
F 3 "" H 9300 6750 60  0000 C CNN
	1    9300 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 6700 9300 6750
Wire Wire Line
	6150 5500 6150 6200
Connection ~ 6650 5800
Wire Wire Line
	7150 6000 7200 6000
Connection ~ 9000 6700
$Comp
L R R32
U 1 1 52C6E05F
P 9750 5800
F 0 "R32" V 9830 5800 50  0000 C CNN
F 1 "150R" V 9750 5800 50  0000 C CNN
F 2 "SM0805" V -4420 6575 60  0001 C CNN
F 3 "" H 9750 5800 60  0001 C CNN
F 4 "bourns,CR0805-FX-1500ELF" V -4420 6575 60  0001 C CNN "mfg,mfg#"
F 5 "digi,CR0805-FX-1500ELFCT-ND" V -4420 6575 60  0001 C CNN "vend1,vend1#"
	1    9750 5800
	0    1    -1   0   
$EndComp
Connection ~ 6650 6700
Wire Wire Line
	6650 6450 6650 6700
Connection ~ 6150 5800
Wire Wire Line
	6650 5800 6650 6050
Wire Wire Line
	6950 6250 7000 6250
Connection ~ 9000 5150
Connection ~ 9000 5500
$Comp
L GND #PWR12
U 1 1 52C6E06C
P 9400 5550
F 0 "#PWR12" H 9400 5550 30  0001 C CNN
F 1 "GND" H 9400 5480 30  0001 C CNN
F 2 "" H 9400 5550 60  0000 C CNN
F 3 "" H 9400 5550 60  0000 C CNN
	1    9400 5550
	-1   0    0    -1  
$EndComp
Text Label 9000 5500 1    60   ~ 0
MCU_3.3V
Text Label 7600 6000 0    60   ~ 0
MCU_3.3V
Text Label 9300 6200 0    60   ~ 0
MCU_3.3V
Text Label 10000 5800 0    60   ~ 0
Vmcu_2
Wire Wire Line
	10000 5800 10200 5800
Text Label 10200 6700 2    60   ~ 0
GND
$Comp
L DIODE D11
U 1 1 52C6E07B
P 6950 6050
F 0 "D11" H 6950 6150 40  0000 C CNN
F 1 "DIODE" H 6950 5950 40  0001 C CNN
F 2 "SOD-123" H 6950 6050 60  0001 C CNN
F 3 "SOD-123" H 6950 6050 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" H 6950 6050 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,SS0520-7-F" H 6950 6050 60  0001 C CNN "vend1,vend1#"
F 6 "digi,BAT54T1GOSCT-ND" H 6950 6050 60  0001 C CNN "vend2,vend2"
	1    6950 6050
	0    1    1    0   
$EndComp
Connection ~ 6950 6250
Wire Wire Line
	6950 5850 6950 5800
Connection ~ 6950 5800
Text Label 7300 5800 0    60   ~ 0
signal_2
Wire Notes Line
	6550 5650 6550 6750
Wire Notes Line
	6550 6750 8850 6750
Wire Notes Line
	7750 4700 7750 6750
Wire Notes Line
	7750 5650 6550 5650
Connection ~ 9300 6700
Wire Wire Line
	9000 5150 9000 5500
$Comp
L CONN_3 K3
U 1 1 52C6E091
P 5650 5800
F 0 "K3" V 5600 5800 50  0000 C CNN
F 1 "CONN_3" V 5700 5800 40  0000 C CNN
F 2 "bornier3" H 5650 5800 60  0001 C CNN
F 3 "" H 5650 5800 60  0000 C CNN
F 4 "Weidmuller,1760500000" V 5650 5800 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,347008p1" V 5650 5800 60  0001 C CNN "vend1,vend1#"
	1    5650 5800
	-1   0    0    1   
$EndComp
Text Label 6000 5650 1    60   ~ 0
input_500Vmax_2
Text Label 6950 5350 2    60   ~ 0
input_250Vmax_2
Text Label 6150 5700 3    60   ~ 0
input_5Vmax_2
$Comp
L C C18
U 1 1 52C6E09D
P 9200 5500
F 0 "C18" H 9010 5600 50  0000 L CNN
F 1 "1uF" H 8950 5400 50  0000 L CNN
F 2 "SM0805" V -5470 4275 60  0001 C CNN
F 3 "" H 9200 5500 60  0001 C CNN
F 4 "YAGEO,CC0805KKX7R8BB105" V -5470 4275 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,CC0805KKX7R8BB105" V -5470 4275 60  0001 C CNN "vend1,vend1#"
	1    9200 5500
	0    -1   1    0   
$EndComp
$Comp
L R R26
U 1 1 52C6E0A5
P 6900 5500
F 0 "R26" V 6980 5500 50  0000 C CNN
F 1 "243k" V 6900 5500 50  0000 C CNN
F 2 "SM0805" V -7270 6275 60  0001 C CNN
F 3 "" H 6900 5500 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7270 6275 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7270 6275 60  0001 C CNN "vend1,vend1#"
	1    6900 5500
	0    -1   -1   0   
$EndComp
$Comp
L R R22
U 1 1 52C6E0AD
P 6400 5500
F 0 "R22" V 6480 5500 50  0000 C CNN
F 1 "243k" V 6400 5500 50  0000 C CNN
F 2 "SM0805" V -7770 6275 60  0001 C CNN
F 3 "" H 6400 5500 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7770 6275 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7770 6275 60  0001 C CNN "vend1,vend1#"
	1    6400 5500
	0    -1   1    0   
$EndComp
$Comp
L R R25
U 1 1 52C6E0B5
P 6900 5150
F 0 "R25" V 6980 5150 50  0000 C CNN
F 1 "243k" V 6900 5150 50  0000 C CNN
F 2 "SM0805" V -7270 5925 60  0001 C CNN
F 3 "" H 6900 5150 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7270 5925 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7270 5925 60  0001 C CNN "vend1,vend1#"
	1    6900 5150
	0    1    -1   0   
$EndComp
$Comp
L R R30
U 1 1 52C6E0BD
P 8450 5800
F 0 "R30" V 8530 5800 50  0000 C CNN
F 1 "4.7k" V 8450 5800 50  0000 C CNN
F 2 "SM0603" V -5720 6575 60  0001 C CNN
F 3 "" H 8450 5800 60  0001 C CNN
F 4 "Yageo,RC0603JR-074K7L" V -5720 6575 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0010030p1" V -5720 6575 60  0001 C CNN "vend1,vend1#"
	1    8450 5800
	0    1    -1   0   
$EndComp
$Comp
L R R28
U 1 1 52C6E0C5
P 7950 5800
F 0 "R28" V 8030 5800 50  0000 C CNN
F 1 "4.7k" V 7950 5800 50  0000 C CNN
F 2 "SM0603" V -6220 6575 60  0001 C CNN
F 3 "" H 7950 5800 60  0001 C CNN
F 4 "Yageo,RC0603JR-074K7L" V -6220 6575 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0010030p1" V -6220 6575 60  0001 C CNN "vend1,vend1#"
	1    7950 5800
	0    1    -1   0   
$EndComp
Wire Wire Line
	9400 5150 9400 5550
Connection ~ 9400 5500
$Comp
L C C14
U 1 1 52C6E0D0
P 8700 6000
F 0 "C14" H 8510 6100 50  0000 L CNN
F 1 "4.7nF" H 8450 5900 50  0000 L CNN
F 2 "SM0603" V -5970 4775 60  0001 C CNN
F 3 "" H 8700 6000 60  0001 C CNN
F 4 "Yageo,CC0603KRX7R9BB472" V -5970 4775 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,0100850p1" V -5970 4775 60  0001 C CNN "vend1,vend1#"
	1    8700 6000
	1    0    0    1   
$EndComp
$Comp
L C C12
U 1 1 52C6E0D8
P 8400 4850
F 0 "C12" H 8210 4950 50  0000 L CNN
F 1 "4.7nF" H 8150 4750 50  0000 L CNN
F 2 "SM0603" V -6270 3625 60  0001 C CNN
F 3 "" H 8400 4850 60  0001 C CNN
F 4 "Yageo,CC0603KRX7R9BB472" V -6270 3625 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,0100850p1" V -6270 3625 60  0001 C CNN "vend1,vend1#"
	1    8400 4850
	0    1    -1   0   
$EndComp
Wire Wire Line
	8600 4850 9500 4850
Wire Wire Line
	9500 4850 9500 5800
Wire Wire Line
	8200 4850 8200 5800
Wire Wire Line
	8700 6200 8700 6700
Connection ~ 8700 6700
Wire Notes Line
	8850 6750 8850 4700
Wire Notes Line
	8850 4700 7750 4700
$Comp
L FUSE F7
U 1 1 52C6E0EC
P 6400 5800
F 0 "F7" H 6500 5850 40  0000 C CNN
F 1 ".5A" H 6300 5750 40  0000 C CNN
F 2 "SM1206" H 6400 5800 60  0001 C CNN
F 3 "~" H 6400 5800 60  0000 C CNN
F 4 "-,-" H 6400 5800 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 6400 5800 60  0001 C CNN "Vend1,Vend1#"
	1    6400 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 5800 7700 5800
$Comp
L JUMPER3 JP3
U 1 1 52C6E0F6
P 9300 6450
F 0 "JP3" H 9350 6350 40  0000 L CNN
F 1 "JUMPER3" H 9300 6550 40  0001 C CNN
F 2 "SIL-3" H 9300 6450 60  0001 C CNN
F 3 "~" H 9300 6450 60  0000 C CNN
F 4 "-,-" H 9300 6450 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,3460810p1" H 9300 6450 60  0001 C CNN "vend1,vend1#"
	1    9300 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 5900 6150 5900
Connection ~ 6150 5900
Wire Wire Line
	7150 5150 7150 5500
Wire Wire Line
	7150 5350 6050 5350
Wire Wire Line
	6050 5350 6050 5800
Wire Wire Line
	6050 5800 6000 5800
Connection ~ 7150 5350
Wire Wire Line
	6000 5700 6000 5700
Wire Wire Line
	6000 5700 6000 5150
Wire Wire Line
	6000 5150 6150 5150
Wire Wire Line
	7400 6300 7400 6700
Connection ~ 7150 6700
Connection ~ 7400 6700
$Comp
L C C15
U 1 1 52C6E10C
P 9200 2800
F 0 "C15" H 9010 2900 50  0000 L CNN
F 1 "1uF" H 8950 2700 50  0000 L CNN
F 2 "SM0805" V -5470 1575 60  0001 C CNN
F 3 "" H 9200 2800 60  0001 C CNN
F 4 "YAGEO,CC0805KKX7R8BB105" V -5470 1575 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,CC0805KKX7R8BB105" V -5470 1575 60  0001 C CNN "vend1,vend1#"
	1    9200 2800
	0    -1   1    0   
$EndComp
$Comp
L MOS_PRO Q4
U 1 1 52C6E114
P 6750 3900
F 0 "Q4" H 6750 4090 60  0000 R CNN
F 1 "MOS_PRO" H 6750 3720 60  0001 R CNN
F 2 "SOT23" H 6750 3900 60  0001 C CNN
F 3 "" H 6750 3900 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 6750 3900 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 6750 3900 60  0001 C CNN "vend1,vend1#"
	1    6750 3900
	-1   0    0    1   
$EndComp
$Comp
L R R17
U 1 1 52C6E11C
P 6150 4100
F 0 "R17" V 6230 4100 50  0000 C CNN
F 1 "10k" V 6150 4100 50  0000 C CNN
F 2 "SM0603" V -8020 4875 60  0001 C CNN
F 3 "" H 6150 4100 60  0001 C CNN
F 4 "Yageo,RC0603FR-0710KL" V -8020 4875 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0011240p1" V -8020 4875 60  0001 C CNN "vend1,vend1#"
	1    6150 4100
	-1   0    0    -1  
$EndComp
$Comp
L POT RV2
U 1 1 52C6E124
P 7150 3900
F 0 "RV2" H 7150 3800 50  0000 C CNN
F 1 "500R" H 7150 3900 50  0000 C CNN
F 2 "POT_TC33X-2" H 7150 3900 60  0001 C CNN
F 3 "~" H 7150 3900 60  0000 C CNN
F 4 "Bourns,TC33X-2-501E" H 7150 3900 60  0001 C CNN "mfg,mfg#"
F 5 "newark,60H9655" H 7150 3900 60  0001 C CNN "vend1,vend1#"
	1    7150 3900
	0    -1   -1   0   
$EndComp
$Comp
L MOS_PRO Q6
U 1 1 52C6E12C
P 7400 3750
F 0 "Q6" H 7400 3940 60  0000 R CNN
F 1 "MOS_PRO" H 7400 3570 60  0001 R CNN
F 2 "SOT23" H 7400 3750 60  0001 C CNN
F 3 "" H 7400 3750 60  0001 C CNN
F 4 "onsemi,NTR1P02T1" H 7400 3750 60  0001 C CNN "mfg,mfg#"
F 5 "digi,NTR1P02T1GOSCT-ND" H 7400 3750 60  0001 C CNN "vend1,vend1#"
	1    7400 3750
	0    1    -1   0   
$EndComp
$Comp
L R R19
U 1 1 52C6E134
P 6400 2800
F 0 "R19" V 6480 2800 50  0000 C CNN
F 1 "243k" V 6400 2800 50  0000 C CNN
F 2 "SM0805" V -7770 3575 60  0001 C CNN
F 3 "" H 6400 2800 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7770 3575 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7770 3575 60  0001 C CNN "vend1,vend1#"
	1    6400 2800
	0    1    -1   0   
$EndComp
$Comp
L VREF D12
U 1 1 52C6E13C
P 7150 4250
F 0 "D12" H 7150 4350 40  0000 C CNN
F 1 "VREF" H 7150 4150 30  0000 C CNN
F 2 "SOT323" H 7150 4250 60  0001 C CNN
F 3 "~" H 7150 4250 60  0000 C CNN
F 4 "Analog,ADR5044BRTZ-R2" H 7150 4250 60  0001 C CNN "mfg,mfg#"
F 5 "digi,ADR5044BRTZ-R2" H 7150 4250 60  0001 C CNN "vend1,vend1#"
	1    7150 4250
	0    -1   -1   0   
$EndComp
$Comp
L MCP6G01T-E/OT U2
U 1 1 52C6E144
P 9100 3450
F 0 "U2" H 9050 3450 70  0000 C CNN
F 1 "MCP6G0_" H 9500 3200 70  0000 C CNN
F 2 "MSOP_8" H 9100 3450 60  0001 C CNN
F 3 "" H 9100 3450 60  0000 C CNN
F 4 "microchip,MCP6G01T-E/OT" H 9100 3450 60  0001 C CNN "mfg,mfg#"
F 5 "digi,MCP6G01T-E/OT" H 9100 3450 60  0001 C CNN "vend1,vend1#"
	1    9100 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P11
U 1 1 52C6E150
P 10350 4350
F 0 "P11" H 10430 4350 40  0000 L CNN
F 1 "CONN_1" H 10350 4405 30  0001 C CNN
F 2 "SIL-1" H 10350 4350 60  0001 C CNN
F 3 "" H 10350 4350 60  0000 C CNN
	1    10350 4350
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 P10
U 1 1 52C6E156
P 10350 3450
F 0 "P10" H 10430 3450 40  0000 L CNN
F 1 "CONN_1" H 10350 3505 30  0001 C CNN
F 2 "SIL-1" H 10350 3450 60  0001 C CNN
F 3 "" H 10350 3450 60  0000 C CNN
	1    10350 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4350 9000 3750
Wire Wire Line
	9200 3750 9200 4100
Wire Wire Line
	6150 4350 10200 4350
$Comp
L GND #PWR9
U 1 1 52C6E165
P 9300 4400
F 0 "#PWR9" H 9300 4400 30  0001 C CNN
F 1 "GND" H 9300 4330 30  0001 C CNN
F 2 "" H 9300 4400 60  0000 C CNN
F 3 "" H 9300 4400 60  0000 C CNN
	1    9300 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 4350 9300 4400
Wire Wire Line
	6150 3150 6150 3850
Connection ~ 6650 3450
Wire Wire Line
	7150 3650 7200 3650
Connection ~ 9000 4350
$Comp
L R R31
U 1 1 52C6E174
P 9750 3450
F 0 "R31" V 9830 3450 50  0000 C CNN
F 1 "150R" V 9750 3450 50  0000 C CNN
F 2 "SM0805" V -4420 4225 60  0001 C CNN
F 3 "" H 9750 3450 60  0001 C CNN
F 4 "bourns,CR0805-FX-1500ELF" V -4420 4225 60  0001 C CNN "mfg,mfg#"
F 5 "digi,CR0805-FX-1500ELFCT-ND" V -4420 4225 60  0001 C CNN "vend1,vend1#"
	1    9750 3450
	0    1    -1   0   
$EndComp
Connection ~ 6650 4350
Wire Wire Line
	6650 4100 6650 4350
Connection ~ 6150 3450
Wire Wire Line
	6650 3450 6650 3700
Wire Wire Line
	6950 3900 7000 3900
Connection ~ 9000 2800
Connection ~ 9000 3150
$Comp
L GND #PWR11
U 1 1 52C6E181
P 9400 3200
F 0 "#PWR11" H 9400 3200 30  0001 C CNN
F 1 "GND" H 9400 3130 30  0001 C CNN
F 2 "" H 9400 3200 60  0000 C CNN
F 3 "" H 9400 3200 60  0000 C CNN
	1    9400 3200
	-1   0    0    -1  
$EndComp
Text Label 9000 3150 1    60   ~ 0
MCU_3.3V
Text Label 7600 3650 0    60   ~ 0
MCU_3.3V
Text Label 9300 3850 0    60   ~ 0
V+
Text Label 10000 3450 0    60   ~ 0
Vmcu_3
Wire Wire Line
	10000 3450 10200 3450
Text Label 10200 4350 2    60   ~ 0
GND
$Comp
L DIODE D10
U 1 1 52C6E190
P 6950 3700
F 0 "D10" H 6950 3800 40  0000 C CNN
F 1 "DIODE" H 6950 3600 40  0001 C CNN
F 2 "SOD-123" H 6950 3700 60  0001 C CNN
F 3 "SOD-123" H 6950 3700 60  0001 C CNN
F 4 "ON-SEMI,BAT54T1G" H 6950 3700 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,SS0520-7-F" H 6950 3700 60  0001 C CNN "vend1,vend1#"
F 6 "digi,BAT54T1GOSCT-ND" H 6950 3700 60  0001 C CNN "vend2,vend2"
	1    6950 3700
	0    1    1    0   
$EndComp
Connection ~ 6950 3900
Wire Wire Line
	6950 3500 6950 3450
Connection ~ 6950 3450
Text Label 7300 3450 0    60   ~ 0
signal_3
Wire Notes Line
	6550 3300 6550 4400
Wire Notes Line
	8850 4400 6550 4400
Wire Notes Line
	7750 2350 7750 4400
Wire Notes Line
	7750 3300 6550 3300
Connection ~ 9300 4350
Wire Wire Line
	9000 2800 9000 3150
$Comp
L CONN_3 K2
U 1 1 52C6E1A2
P 5650 3450
F 0 "K2" V 5600 3450 50  0000 C CNN
F 1 "CONN_3" V 5700 3450 40  0000 C CNN
F 2 "bornier3" H 5650 3450 60  0001 C CNN
F 3 "" H 5650 3450 60  0000 C CNN
F 4 "Weidmuller,1760500000" V 5650 3450 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,347008p1" V 5650 3450 60  0001 C CNN "vend1,vend1#"
	1    5650 3450
	-1   0    0    1   
$EndComp
Text Label 6000 3300 1    60   ~ 0
input_500Vmax_3
Text Label 6950 3000 2    60   ~ 0
input_250Vmax_3
Text Label 6150 3350 3    60   ~ 0
input_5Vmax_3
$Comp
L C C16
U 1 1 52C6E1AD
P 9200 3150
F 0 "C16" H 9010 3250 50  0000 L CNN
F 1 "1uF" H 8950 3050 50  0000 L CNN
F 2 "SM0805" V -5470 1925 60  0001 C CNN
F 3 "" H 9200 3150 60  0001 C CNN
F 4 "YAGEO,CC0805KKX7R8BB105" V -5470 1925 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,CC0805KKX7R8BB105" V -5470 1925 60  0001 C CNN "vend1,vend1#"
	1    9200 3150
	0    -1   1    0   
$EndComp
$Comp
L R R24
U 1 1 52C6E1B5
P 6900 3150
F 0 "R24" V 6980 3150 50  0000 C CNN
F 1 "243k" V 6900 3150 50  0000 C CNN
F 2 "SM0805" V -7270 3925 60  0001 C CNN
F 3 "" H 6900 3150 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7270 3925 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7270 3925 60  0001 C CNN "vend1,vend1#"
	1    6900 3150
	0    -1   -1   0   
$EndComp
$Comp
L R R20
U 1 1 52C6E1BD
P 6400 3150
F 0 "R20" V 6480 3150 50  0000 C CNN
F 1 "243k" V 6400 3150 50  0000 C CNN
F 2 "SM0805" V -7770 3925 60  0001 C CNN
F 3 "" H 6400 3150 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7770 3925 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7770 3925 60  0001 C CNN "vend1,vend1#"
	1    6400 3150
	0    -1   1    0   
$EndComp
$Comp
L R R23
U 1 1 52C6E1C5
P 6900 2800
F 0 "R23" V 6980 2800 50  0000 C CNN
F 1 "243k" V 6900 2800 50  0000 C CNN
F 2 "SM0805" V -7270 3575 60  0001 C CNN
F 3 "" H 6900 2800 60  0001 C CNN
F 4 "vishay,CRCW0805240KFKEA" V -7270 3575 60  0001 C CNN "mfg,mfg#"
F 5 "digi,541-240KCCT-ND" V -7270 3575 60  0001 C CNN "vend1,vend1#"
	1    6900 2800
	0    1    -1   0   
$EndComp
$Comp
L R R29
U 1 1 52C6E1CD
P 8450 3450
F 0 "R29" V 8530 3450 50  0000 C CNN
F 1 "4.7k" V 8450 3450 50  0000 C CNN
F 2 "SM0603" V -5720 4225 60  0001 C CNN
F 3 "" H 8450 3450 60  0001 C CNN
F 4 "Yageo,RC0603JR-074K7L" V -5720 4225 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0010030p1" V -5720 4225 60  0001 C CNN "vend1,vend1#"
	1    8450 3450
	0    1    -1   0   
$EndComp
$Comp
L R R27
U 1 1 52C6E1D5
P 7950 3450
F 0 "R27" V 8030 3450 50  0000 C CNN
F 1 "4.7k" V 7950 3450 50  0000 C CNN
F 2 "SM0603" V -6220 4225 60  0001 C CNN
F 3 "" H 7950 3450 60  0001 C CNN
F 4 "Yageo,RC0603JR-074K7L" V -6220 4225 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,0010030p1" V -6220 4225 60  0001 C CNN "vend1,vend1#"
	1    7950 3450
	0    1    -1   0   
$EndComp
Wire Wire Line
	9400 2800 9400 3200
Connection ~ 9400 3150
$Comp
L C C13
U 1 1 52C6E1E0
P 8700 3650
F 0 "C13" H 8510 3750 50  0000 L CNN
F 1 "4.7nF" H 8450 3550 50  0000 L CNN
F 2 "SM0603" V -5970 2425 60  0001 C CNN
F 3 "" H 8700 3650 60  0001 C CNN
F 4 "Yageo,CC0603KRX7R9BB472" V -5970 2425 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,0100850p1" V -5970 2425 60  0001 C CNN "vend1,vend1#"
	1    8700 3650
	1    0    0    1   
$EndComp
$Comp
L C C11
U 1 1 52C6E1E8
P 8400 2500
F 0 "C11" H 8210 2600 50  0000 L CNN
F 1 "4.7nF" H 8150 2400 50  0000 L CNN
F 2 "SM0603" V -6270 1275 60  0001 C CNN
F 3 "" H 8400 2500 60  0001 C CNN
F 4 "Yageo,CC0603KRX7R9BB472" V -6270 1275 60  0001 C CNN "mfg,mfg#"
F 5 "Seeedstudio OPL,0100850p1" V -6270 1275 60  0001 C CNN "vend1,vend1#"
	1    8400 2500
	0    1    -1   0   
$EndComp
Wire Wire Line
	8600 2500 9500 2500
Wire Wire Line
	9500 2500 9500 3450
Wire Wire Line
	8200 2500 8200 3450
Wire Wire Line
	8700 3850 8700 4350
Connection ~ 8700 4350
Wire Notes Line
	8850 2350 8850 4400
Wire Notes Line
	7750 2350 8850 2350
$Comp
L FUSE F6
U 1 1 52C6E1FB
P 6400 3450
F 0 "F6" H 6500 3500 40  0000 C CNN
F 1 ".5A" H 6300 3400 40  0000 C CNN
F 2 "SM1206" H 6400 3450 60  0001 C CNN
F 3 "~" H 6400 3450 60  0000 C CNN
F 4 "-,-" H 6400 3450 60  0001 C CNN "mfg,mfg#"
F 5 "Seeed,090030p1" H 6400 3450 60  0001 C CNN "Vend1,Vend1#"
	1    6400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3450 7700 3450
$Comp
L JUMPER3 JP2
U 1 1 52C6E205
P 9300 4100
F 0 "JP2" H 9350 4000 40  0000 L CNN
F 1 "JUMPER3" H 9300 4200 40  0001 C CNN
F 2 "SIL-3" H 9300 4100 60  0001 C CNN
F 3 "~" H 9300 4100 60  0000 C CNN
F 4 "-,-" H 9300 4100 60  0001 C CNN "mfg,mfg#"
F 5 "seeed,3460810p1" H 9300 4100 60  0001 C CNN "vend1,vend1#"
	1    9300 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 3550 6150 3550
Connection ~ 6150 3550
Wire Wire Line
	7150 2800 7150 3150
Wire Wire Line
	7150 3000 6050 3000
Wire Wire Line
	6050 3000 6050 3450
Wire Wire Line
	6050 3450 6000 3450
Connection ~ 7150 3000
Wire Wire Line
	6000 3350 6000 3350
Wire Wire Line
	6000 3350 6000 2800
Wire Wire Line
	6000 2800 6150 2800
Wire Wire Line
	7400 3950 7400 4350
Connection ~ 7150 4350
Connection ~ 7400 4350
Wire Wire Line
	3250 2700 3250 3050
Wire Notes Line
	600  5000 5450 5000
Wire Notes Line
	5450 500  5450 6250
Wire Notes Line
	5900 6250 5900 7200
Wire Notes Line
	5450 4550 10500 4550
Wire Notes Line
	5450 2200 10500 2200
Wire Notes Line
	5450 6250 5900 6250
Wire Notes Line
	5900 7200 6250 7200
Text Notes 600  5150 0    60   ~ 0
FLEX ANALOG INPUT 1
Wire Notes Line
	1650 5000 1650 500 
Text Notes 5550 4700 0    60   ~ 0
FLEX ANALOG INPUT 2
Text Notes 5550 2350 0    60   ~ 0
FLEX ANALOG INPUT 3
Text Notes 5550 600  0    60   ~ 0
5V clamp, max 5.3V when dumping ?? mA
$Comp
L CONN_3 P7
U 1 1 52C748B4
P 6950 850
F 0 "P7" V 6900 850 50  0000 C CNN
F 1 "TPS" V 7000 850 40  0000 C CNN
F 2 "Phoenix_edge_3.5mm_3pos" V 4580 400 60  0001 C CNN
F 3 "" H 6950 850 60  0001 C CNN
F 4 "Phoenix,1893698" V 4580 400 60  0001 C CNN "mfg,mfg#"
F 5 "MOUSER,651-1893698" V 4580 400 60  0001 C CNN "vend1,vend1#"
	1    6950 850 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7300 750  7650 750 
$Comp
L GND #PWR7
U 1 1 52C74AD3
P 7300 950
F 0 "#PWR7" H 7300 950 30  0001 C CNN
F 1 "GND" H 7300 880 30  0001 C CNN
F 2 "" H 7300 950 60  0000 C CNN
F 3 "" H 7300 950 60  0000 C CNN
	1    7300 950 
	1    0    0    -1  
$EndComp
Text Label 7300 850  0    60   ~ 0
MCU_3.3V
Text Notes 9450 6400 0    60   ~ 0
GAIN 50\nGAIN 1 (no jumper)\nGAIN 10
Text Notes 9450 4050 0    60   ~ 0
GAIN 50\nGAIN 1 (no jumper)\nGAIN 10
Text Notes 9350 1350 0    60   ~ 0
REMEMBER CHANGE DIODE TO WORK WITH 3.3V\nALSO CHANGE OTHER DIODES\nALSO ALSO REMOVE POT REPLACE WITH TWO RESISTORS ONCE THE VALUES ARE KNOWN. 
$EndSCHEMATC
