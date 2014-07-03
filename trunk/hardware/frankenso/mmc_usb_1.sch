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
LIBS:art-electro-conn
LIBS:art-electro-conn_2
LIBS:art-electro-ic
LIBS:art-electro-max
LIBS:art-electro-power
LIBS:LMV324IDR
LIBS:logo
LIBS:logo_flipped
LIBS:MAX9926-9927
LIBS:max9939
LIBS:max31855
LIBS:stm32
LIBS:tc4427
LIBS:lm2596
LIBS:mos_p_numbered-pins
LIBS:project_specific_libs
LIBS:hip9011
LIBS:frankenso-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 10
Title "Frankenso"
Date "3 jul 2014"
Rev ".01"
Comp "rusEFI.com"
Comment1 ""
Comment2 "Art_Electro"
Comment3 "Art_Electro"
Comment4 "Art_Electro"
$EndDescr
Text Label 4800 1375 0    60   ~ 0
FTVCC
$Comp
L CP1 C354
U 1 1 52A59B20
P 4200 1575
F 0 "C354" H 4250 1675 50  0000 L CNN
F 1 "4.7uF" H 4250 1475 50  0000 L CNN
F 2 "SM0805" H 4200 1575 60  0001 C CNN
F 3 "" H 4200 1575 60  0001 C CNN
	1    4200 1575
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR078
U 1 1 52A59B21
P 6275 3225
F 0 "#PWR078" H 6275 3225 30  0001 C CNN
F 1 "GND" H 6275 3155 30  0001 C CNN
F 2 "" H 6275 3225 60  0001 C CNN
F 3 "" H 6275 3225 60  0001 C CNN
	1    6275 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR079
U 1 1 52A59B2B
P 2625 3275
F 0 "#PWR079" H 2625 3275 30  0001 C CNN
F 1 "GND" H 2625 3205 30  0001 C CNN
F 2 "" H 2625 3275 60  0001 C CNN
F 3 "" H 2625 3275 60  0001 C CNN
	1    2625 3275
	1    0    0    -1  
$EndComp
$Comp
L R R352
U 1 1 52A59B2D
P 2625 2575
F 0 "R352" V 2705 2575 50  0000 C CNN
F 1 "1k" V 2625 2575 50  0000 C CNN
F 2 "SM0805" H 2625 2575 60  0001 C CNN
F 3 "" H 2625 2575 60  0001 C CNN
	1    2625 2575
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR080
U 1 1 52A59B2E
P 4200 1775
F 0 "#PWR080" H 4200 1775 30  0001 C CNN
F 1 "GND" H 4200 1705 30  0001 C CNN
F 2 "" H 4200 1775 60  0001 C CNN
F 3 "" H 4200 1775 60  0001 C CNN
	1    4200 1775
	1    0    0    -1  
$EndComp
$Comp
L C C355
U 1 1 52A59B31
P 4525 1575
F 0 "C355" H 4575 1675 50  0000 L CNN
F 1 ".1uF" H 4575 1475 50  0000 L CNN
F 2 "SM0805" H 4525 1575 60  0001 C CNN
F 3 "" H 4525 1575 60  0001 C CNN
	1    4525 1575
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR081
U 1 1 52A59B32
P 4525 1775
F 0 "#PWR081" H 4525 1775 30  0001 C CNN
F 1 "GND" H 4525 1705 30  0001 C CNN
F 2 "" H 4525 1775 60  0001 C CNN
F 3 "" H 4525 1775 60  0001 C CNN
	1    4525 1775
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR082
U 1 1 52A59B33
P 6125 3225
F 0 "#PWR082" H 6125 3225 30  0001 C CNN
F 1 "GND" H 6125 3155 30  0001 C CNN
F 2 "" H 6125 3225 60  0001 C CNN
F 3 "" H 6125 3225 60  0001 C CNN
	1    6125 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR083
U 1 1 52A59B34
P 5975 3225
F 0 "#PWR083" H 5975 3225 30  0001 C CNN
F 1 "GND" H 5975 3155 30  0001 C CNN
F 2 "" H 5975 3225 60  0001 C CNN
F 3 "" H 5975 3225 60  0001 C CNN
	1    5975 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR084
U 1 1 52A59B35
P 5825 3225
F 0 "#PWR084" H 5825 3225 30  0001 C CNN
F 1 "GND" H 5825 3155 30  0001 C CNN
F 2 "" H 5825 3225 60  0001 C CNN
F 3 "" H 5825 3225 60  0001 C CNN
	1    5825 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR085
U 1 1 52A59B36
P 5675 3225
F 0 "#PWR085" H 5675 3225 30  0001 C CNN
F 1 "GND" H 5675 3155 30  0001 C CNN
F 2 "" H 5675 3225 60  0001 C CNN
F 3 "" H 5675 3225 60  0001 C CNN
	1    5675 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR086
U 1 1 52A59B37
P 5025 2925
F 0 "#PWR086" H 5025 2925 30  0001 C CNN
F 1 "GND" H 5025 2855 30  0001 C CNN
F 2 "" H 5025 2925 60  0001 C CNN
F 3 "" H 5025 2925 60  0001 C CNN
	1    5025 2925
	1    0    0    -1  
$EndComp
$Comp
L C C356
U 1 1 52A59B38
P 5025 2725
F 0 "C356" H 5075 2825 50  0000 L CNN
F 1 ".1uF" H 5075 2625 50  0000 L CNN
F 2 "SM0805" H 5025 2725 60  0001 C CNN
F 3 "" H 5025 2725 60  0001 C CNN
	1    5025 2725
	-1   0    0    1   
$EndComp
$Comp
L C C351
U 1 1 52A59B39
P 2100 2875
F 0 "C351" H 2150 2725 50  0000 L CNN
F 1 "4700pF" H 2050 2600 50  0000 L CNN
F 2 "SM0805" H 2100 2875 60  0001 C CNN
F 3 "" H 2100 2875 60  0001 C CNN
	1    2100 2875
	-1   0    0    1   
$EndComp
$Comp
L R R351
U 1 1 52A59B3A
P 2300 2925
F 0 "R351" V 2400 2900 50  0000 C CNN
F 1 "1M" V 2300 2925 50  0000 C CNN
F 2 "SM0805" H 2300 2925 60  0001 C CNN
F 3 "" H 2300 2925 60  0001 C CNN
	1    2300 2925
	1    0    0    -1  
$EndComp
NoConn ~ 6875 2025
NoConn ~ 6875 1725
NoConn ~ 6875 1925
NoConn ~ 6875 1825
NoConn ~ 5025 2325
NoConn ~ 5025 2225
$Comp
L FT232RL U351
U 1 1 52A59B51
P 5975 2025
F 0 "U351" H 5975 2925 60  0000 C CNN
F 1 "FT232RL" H 6375 1025 60  0000 L CNN
F 2 "ssop-28" H 5975 2025 60  0001 C CNN
F 3 "" H 5975 2025 60  0001 C CNN
F 4 "digi,768-1007-2-ND" H 5975 2025 60  0001 C CNN "vend1,vend1#"
F 5 "seeed,1720010P1" H 5975 2025 60  0001 C CNN "vend2,vend2#"
	1    5975 2025
	1    0    0    -1  
$EndComp
NoConn ~ 6875 2125
NoConn ~ 6875 2225
NoConn ~ 6875 1525
NoConn ~ 6875 1625
NoConn ~ 6875 2325
NoConn ~ 6875 2425
NoConn ~ 6875 2525
$Comp
L GND #PWR087
U 1 1 52A5A5A0
P 2300 2275
F 0 "#PWR087" H 2300 2275 30  0001 C CNN
F 1 "GND" H 2300 2205 30  0001 C CNN
F 2 "" H 2300 2275 60  0001 C CNN
F 3 "" H 2300 2275 60  0001 C CNN
	1    2300 2275
	0    -1   -1   0   
$EndComp
NoConn ~ 5025 2025
$Comp
L GND #PWR088
U 1 1 52A5A60C
P 2100 3275
F 0 "#PWR088" H 2100 3275 30  0001 C CNN
F 1 "GND" H 2100 3205 30  0001 C CNN
F 2 "" H 2100 3275 60  0001 C CNN
F 3 "" H 2100 3275 60  0001 C CNN
	1    2100 3275
	1    0    0    -1  
$EndComp
NoConn ~ 2300 2175
$Comp
L C C352
U 1 1 52A5A67B
P 2950 2275
F 0 "C352" H 3000 2375 50  0000 L CNN
F 1 "47pF" H 3000 2175 50  0000 L CNN
F 2 "SM0805" H 2950 2275 60  0001 C CNN
F 3 "" H 2950 2275 60  0001 C CNN
	1    2950 2275
	-1   0    0    1   
$EndComp
$Comp
L C C353
U 1 1 52A5A68B
P 3300 2325
F 0 "C353" H 3350 2425 50  0000 L CNN
F 1 "47pF" H 3350 2225 50  0000 L CNN
F 2 "SM0805" H 3300 2325 60  0001 C CNN
F 3 "" H 3300 2325 60  0001 C CNN
	1    3300 2325
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR089
U 1 1 52A5A701
P 3100 2600
F 0 "#PWR089" H 3100 2600 30  0001 C CNN
F 1 "GND" H 3100 2530 30  0001 C CNN
F 2 "" H 3100 2600 60  0001 C CNN
F 3 "" H 3100 2600 60  0001 C CNN
	1    3100 2600
	1    0    0    -1  
$EndComp
$Comp
L MICRO-SDCARD-CONNECTOR-3300060P1 P352
U 1 1 52A75274
P 3300 5000
F 0 "P352" H 3150 5500 60  0000 C CNN
F 1 "MICRO-SDCARD-CONNECTOR-3300060P1" H 3300 4500 60  0001 C CNN
F 2 "MICRO-SDCARD-CONNECTOR-3300060P1" H 3300 5000 60  0001 C CNN
F 3 "" H 3300 5000 60  0000 C CNN
F 4 "seeed,3300060P1" H 3300 5000 60  0001 C CNN "vend2,vend2#"
	1    3300 5000
	-1   0    0    -1  
$EndComp
NoConn ~ 3700 4600
NoConn ~ 3700 5300
NoConn ~ 3700 5400
$Comp
L GND #PWR090
U 1 1 52A752F4
P 3700 5100
F 0 "#PWR090" H 3700 5100 30  0001 C CNN
F 1 "GND" H 3700 5030 30  0001 C CNN
F 2 "" H 3700 5100 60  0001 C CNN
F 3 "" H 3700 5100 60  0001 C CNN
	1    3700 5100
	1    0    0    -1  
$EndComp
Text Notes 5425 3550 0    60   ~ 0
For right conn
Connection ~ 2100 3175
Wire Wire Line
	2100 2675 2300 2675
Connection ~ -4675 3450
Wire Wire Line
	2300 3175 2100 3175
Connection ~ 4525 1375
Wire Wire Line
	2625 2875 2625 2825
Wire Wire Line
	3925 1375 5025 1375
Connection ~ 4200 1375
Wire Wire Line
	5025 1275 4525 1275
Wire Wire Line
	4525 1275 4525 1375
Wire Wire Line
	2100 3075 2100 3275
Wire Wire Line
	2300 2675 2300 2375
Connection ~ 2300 2675
Wire Wire Line
	2300 1875 2625 1875
Wire Wire Line
	2625 1875 2625 2325
Wire Wire Line
	2950 2475 2950 2525
Wire Wire Line
	2950 2525 3300 2525
Wire Wire Line
	3100 2600 3100 2525
Connection ~ 3100 2525
Wire Wire Line
	7025 1425 6875 1425
Wire Wire Line
	6875 1325 7025 1325
Wire Wire Line
	3775 3200 4000 3200
Wire Wire Line
	4000 3200 4000 1375
Connection ~ 4000 1375
Wire Wire Line
	3875 5000 3700 5000
Wire Wire Line
	3700 5200 3875 5200
Wire Wire Line
	3875 4900 3700 4900
Wire Wire Line
	3875 4800 3700 4800
Wire Wire Line
	3875 4700 3700 4700
$Comp
L LOGO G305
U 1 1 52BD6BB8
P 5050 5100
F 0 "G305" H 5050 4997 60  0001 C CNN
F 1 "LOGO" H 5050 5203 60  0001 C CNN
F 2 "LOGO_F" H 5050 5100 60  0001 C CNN
F 3 "" H 5050 5100 60  0000 C CNN
	1    5050 5100
	1    0    0    -1  
$EndComp
$Comp
L CP1 C358
U 1 1 52BEFB29
P 6900 5725
F 0 "C358" H 6950 5825 50  0000 L CNN
F 1 "4.7uF" H 6950 5625 50  0000 L CNN
F 2 "SM0805" H 6900 5725 60  0001 C CNN
F 3 "" H 6900 5725 60  0001 C CNN
	1    6900 5725
	-1   0    0    -1  
$EndComp
$Comp
L C C357
U 1 1 52BEFB4C
P 6900 5175
F 0 "C357" H 6950 5275 50  0000 L CNN
F 1 ".1uF" H 6950 5075 50  0000 L CNN
F 2 "SM0805" H 6900 5175 60  0001 C CNN
F 3 "" H 6900 5175 60  0001 C CNN
	1    6900 5175
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5375 6900 5525
Wire Wire Line
	6600 5475 6900 5475
Connection ~ 6900 5475
$Comp
L GND #PWR091
U 1 1 52BEFC07
P 6900 5925
F 0 "#PWR091" H 6900 5925 30  0001 C CNN
F 1 "GND" H 6900 5855 30  0001 C CNN
F 2 "" H 6900 5925 60  0001 C CNN
F 3 "" H 6900 5925 60  0001 C CNN
	1    6900 5925
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR092
U 1 1 52BEFC0D
P 6900 4975
F 0 "#PWR092" H 6900 4975 30  0001 C CNN
F 1 "GND" H 6900 4905 30  0001 C CNN
F 2 "" H 6900 4975 60  0001 C CNN
F 3 "" H 6900 4975 60  0001 C CNN
	1    6900 4975
	-1   0    0    1   
$EndComp
Text Label 6600 5475 2    60   ~ 0
3.3V
$Comp
L MINI-USB-5P-3400020P1 J351
U 1 1 52C034E1
P 2100 2125
F 0 "J351" H 1825 2475 60  0000 C CNN
F 1 "MINI-USB-5P-3400020P1" H 2100 2575 60  0001 C CNN
F 2 "MINI-USB-5P-3400020P1" H 2100 2125 60  0001 C CNN
F 3 "" H 2100 2125 60  0000 C CNN
F 4 "digi,670-1190-1-ND" H 2100 2125 60  0001 C CNN "vend1,vend1#"
F 5 "seeed,3400020P1" H 2100 2125 60  0001 C CNN "vend2,vend2#"
	1    2100 2125
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR093
U 1 1 52C0C35C
P 2700 5200
F 0 "#PWR093" H 2700 5200 30  0001 C CNN
F 1 "GND" H 2700 5130 30  0001 C CNN
F 2 "" H 2700 5200 60  0001 C CNN
F 3 "" H 2700 5200 60  0001 C CNN
	1    2700 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 4850 2700 5200
Connection ~ 2700 4950
Connection ~ 2700 5050
Connection ~ 2700 5150
Text Notes 2200 6250 0    160  ~ 0
SD card slot\nUSB TTL module
Text Label 4850 1725 2    60   ~ 0
D+
Text Label 4850 1625 2    60   ~ 0
D-
Wire Wire Line
	5025 1625 4850 1625
Wire Wire Line
	5025 1725 4850 1725
Text Label 2950 2000 2    60   ~ 0
D-
Wire Wire Line
	2950 2075 2950 2000
Text Label 3300 2000 2    60   ~ 0
D+
Wire Wire Line
	3300 2125 3300 2000
Text Label 2400 1975 0    60   ~ 0
D-
Wire Wire Line
	2300 1975 2400 1975
Text Label 2400 2075 0    60   ~ 0
D+
Wire Wire Line
	2300 2075 2400 2075
$Comp
L LED_0805 D351
U 1 1 53070C5F
P 2625 3075
F 0 "D351" H 2625 3175 50  0000 C CNN
F 1 "GREEN" H 2625 2975 50  0000 C CNN
F 2 "LED-0805_A" H 2625 3075 60  0001 C CNN
F 3 "" H 2625 3075 60  0000 C CNN
	1    2625 3075
	0    1    1    0   
$EndComp
Text HLabel 4000 3200 2    60   Input ~ 0
5V
Text HLabel 3900 5100 2    60   Input ~ 0
GND
Text HLabel 3875 4700 2    60   Input ~ 0
CS_SD_MODULE
Text HLabel 3875 4800 2    60   Input ~ 0
SPI_MOSI
Text HLabel 3875 4900 2    60   Input ~ 0
3.3V
Text HLabel 3875 5000 2    60   Input ~ 0
SPI_SCK
Text HLabel 3875 5200 2    60   Input ~ 0
SPI_MISO
Wire Wire Line
	3700 5100 3900 5100
Text HLabel 7025 1325 2    60   Input ~ 0
USART_RX
Text HLabel 7025 1425 2    60   Input ~ 0
USART_TX
$EndSCHEMATC
