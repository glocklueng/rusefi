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
LIBS:art-electro-conn
LIBS:logo_flipped
LIBS:mmc_usb_1-cache
EELAYER 24 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "27 Dec2013"
Rev ""
Comp ""
Comment1 ""
Comment2 "Art_Electro"
Comment3 "Art_Electro"
Comment4 "Art_Electro"
$EndDescr
Text Label 4800 1375 0    60   ~ 0
FTVCC
$Comp
L CP1 C4
U 1 1 52A59B20
P 4200 1575
F 0 "C4" H 4250 1675 50  0000 L CNN
F 1 "4.7uF" H 4250 1475 50  0000 L CNN
F 2 "" H 4200 1575 60  0001 C CNN
F 3 "" H 4200 1575 60  0001 C CNN
	1    4200 1575
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 52A59B21
P 6275 3225
F 0 "#PWR19" H 6275 3225 30  0001 C CNN
F 1 "GND" H 6275 3155 30  0001 C CNN
F 2 "" H 6275 3225 60  0001 C CNN
F 3 "" H 6275 3225 60  0001 C CNN
	1    6275 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 52A59B2B
P 2625 3275
F 0 "#PWR5" H 2625 3275 30  0001 C CNN
F 1 "GND" H 2625 3205 30  0001 C CNN
F 2 "" H 2625 3275 60  0001 C CNN
F 3 "" H 2625 3275 60  0001 C CNN
	1    2625 3275
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 52A59B2C
P 2625 3075
F 0 "D1" H 2625 3175 50  0000 C CNN
F 1 "GREEN" H 2625 2975 50  0000 C CNN
F 2 "" H 2625 3075 60  0001 C CNN
F 3 "" H 2625 3075 60  0001 C CNN
	1    2625 3075
	0    -1   1    0   
$EndComp
$Comp
L R R2
U 1 1 52A59B2D
P 2625 2575
F 0 "R2" V 2705 2575 50  0000 C CNN
F 1 "1k" V 2625 2575 50  0000 C CNN
F 2 "" H 2625 2575 60  0001 C CNN
F 3 "" H 2625 2575 60  0001 C CNN
	1    2625 2575
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 52A59B2E
P 4200 1775
F 0 "#PWR11" H 4200 1775 30  0001 C CNN
F 1 "GND" H 4200 1705 30  0001 C CNN
F 2 "" H 4200 1775 60  0001 C CNN
F 3 "" H 4200 1775 60  0001 C CNN
	1    4200 1775
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 52A59B31
P 4525 1575
F 0 "C5" H 4575 1675 50  0000 L CNN
F 1 ".1uF" H 4575 1475 50  0000 L CNN
F 2 "" H 4525 1575 60  0001 C CNN
F 3 "" H 4525 1575 60  0001 C CNN
	1    4525 1575
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR12
U 1 1 52A59B32
P 4525 1775
F 0 "#PWR12" H 4525 1775 30  0001 C CNN
F 1 "GND" H 4525 1705 30  0001 C CNN
F 2 "" H 4525 1775 60  0001 C CNN
F 3 "" H 4525 1775 60  0001 C CNN
	1    4525 1775
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 52A59B33
P 6125 3225
F 0 "#PWR18" H 6125 3225 30  0001 C CNN
F 1 "GND" H 6125 3155 30  0001 C CNN
F 2 "" H 6125 3225 60  0001 C CNN
F 3 "" H 6125 3225 60  0001 C CNN
	1    6125 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 52A59B34
P 5975 3225
F 0 "#PWR17" H 5975 3225 30  0001 C CNN
F 1 "GND" H 5975 3155 30  0001 C CNN
F 2 "" H 5975 3225 60  0001 C CNN
F 3 "" H 5975 3225 60  0001 C CNN
	1    5975 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 52A59B35
P 5825 3225
F 0 "#PWR16" H 5825 3225 30  0001 C CNN
F 1 "GND" H 5825 3155 30  0001 C CNN
F 2 "" H 5825 3225 60  0001 C CNN
F 3 "" H 5825 3225 60  0001 C CNN
	1    5825 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR15
U 1 1 52A59B36
P 5675 3225
F 0 "#PWR15" H 5675 3225 30  0001 C CNN
F 1 "GND" H 5675 3155 30  0001 C CNN
F 2 "" H 5675 3225 60  0001 C CNN
F 3 "" H 5675 3225 60  0001 C CNN
	1    5675 3225
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 52A59B37
P 5025 2925
F 0 "#PWR14" H 5025 2925 30  0001 C CNN
F 1 "GND" H 5025 2855 30  0001 C CNN
F 2 "" H 5025 2925 60  0001 C CNN
F 3 "" H 5025 2925 60  0001 C CNN
	1    5025 2925
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 52A59B38
P 5025 2725
F 0 "C6" H 5075 2825 50  0000 L CNN
F 1 ".1uF" H 5075 2625 50  0000 L CNN
F 2 "" H 5025 2725 60  0001 C CNN
F 3 "" H 5025 2725 60  0001 C CNN
	1    5025 2725
	-1   0    0    1   
$EndComp
$Comp
L C C1
U 1 1 52A59B39
P 2100 2875
F 0 "C1" H 2150 2725 50  0000 L CNN
F 1 "4700pF" H 2050 2600 50  0000 L CNN
F 2 "" H 2100 2875 60  0001 C CNN
F 3 "" H 2100 2875 60  0001 C CNN
	1    2100 2875
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 52A59B3A
P 2300 2925
F 0 "R1" V 2400 2900 50  0000 C CNN
F 1 "1M" V 2300 2925 50  0000 C CNN
F 2 "" H 2300 2925 60  0001 C CNN
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
L FT232RL U1
U 1 1 52A59B51
P 5975 2025
F 0 "U1" H 5975 2925 60  0000 C CNN
F 1 "FT232RL" H 6375 1025 60  0000 L CNN
F 2 "" H 5975 2025 60  0001 C CNN
F 3 "" H 5975 2025 60  0001 C CNN
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
L R R3
U 1 1 52A5A342
P 3675 1375
F 0 "R3" V 3755 1375 50  0000 C CNN
F 1 "1k" V 3675 1375 50  0000 C CNN
F 2 "" H 3675 1375 60  0001 C CNN
F 3 "" H 3675 1375 60  0001 C CNN
	1    3675 1375
	0    -1   1    0   
$EndComp
$Comp
L LED D2
U 1 1 52A5A380
P 3225 1375
F 0 "D2" H 3225 1475 50  0000 C CNN
F 1 "RED" H 3225 1275 50  0000 C CNN
F 2 "" H 3225 1375 60  0001 C CNN
F 3 "" H 3225 1375 60  0001 C CNN
	1    3225 1375
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 52A5A386
P 3025 1375
F 0 "#PWR6" H 3025 1375 30  0001 C CNN
F 1 "GND" H 3025 1305 30  0001 C CNN
F 2 "" H 3025 1375 60  0001 C CNN
F 3 "" H 3025 1375 60  0001 C CNN
	1    3025 1375
	0    1    1    0   
$EndComp
$Comp
L GND #PWR2
U 1 1 52A5A5A0
P 2300 2275
F 0 "#PWR2" H 2300 2275 30  0001 C CNN
F 1 "GND" H 2300 2205 30  0001 C CNN
F 2 "" H 2300 2275 60  0001 C CNN
F 3 "" H 2300 2275 60  0001 C CNN
	1    2300 2275
	0    -1   -1   0   
$EndComp
NoConn ~ 5025 2025
$Comp
L GND #PWR1
U 1 1 52A5A60C
P 2100 3275
F 0 "#PWR1" H 2100 3275 30  0001 C CNN
F 1 "GND" H 2100 3205 30  0001 C CNN
F 2 "" H 2100 3275 60  0001 C CNN
F 3 "" H 2100 3275 60  0001 C CNN
	1    2100 3275
	1    0    0    -1  
$EndComp
NoConn ~ 2300 2175
$Comp
L C C2
U 1 1 52A5A67B
P 2950 2275
F 0 "C2" H 3000 2375 50  0000 L CNN
F 1 "47pF" H 3000 2175 50  0000 L CNN
F 2 "" H 2950 2275 60  0001 C CNN
F 3 "" H 2950 2275 60  0001 C CNN
	1    2950 2275
	-1   0    0    1   
$EndComp
$Comp
L C C3
U 1 1 52A5A68B
P 3300 2325
F 0 "C3" H 3350 2425 50  0000 L CNN
F 1 "47pF" H 3350 2225 50  0000 L CNN
F 2 "" H 3300 2325 60  0001 C CNN
F 3 "" H 3300 2325 60  0001 C CNN
	1    3300 2325
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR7
U 1 1 52A5A701
P 3100 2600
F 0 "#PWR7" H 3100 2600 30  0001 C CNN
F 1 "GND" H 3100 2530 30  0001 C CNN
F 2 "" H 3100 2600 60  0001 C CNN
F 3 "" H 3100 2600 60  0001 C CNN
	1    3100 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 52A5A913
P 3825 3875
F 0 "#PWR10" H 3825 3875 30  0001 C CNN
F 1 "GND" H 3825 3805 30  0001 C CNN
F 2 "" H 3825 3875 60  0001 C CNN
F 3 "" H 3825 3875 60  0001 C CNN
	1    3825 3875
	0    -1   -1   0   
$EndComp
Text Label 7025 1425 0    60   ~ 0
USART_RX
Text Label 7025 1325 0    60   ~ 0
USART_TX
Text Label 3900 5200 0    60   ~ 0
SPI_MISO
Text Label 2850 4275 2    60   ~ 0
SPI_SCK
$Comp
L GND #PWR9
U 1 1 52A5AE4C
P 3775 3300
F 0 "#PWR9" H 3775 3300 30  0001 C CNN
F 1 "GND" H 3775 3230 30  0001 C CNN
F 2 "" H 3775 3300 60  0001 C CNN
F 3 "" H 3775 3300 60  0001 C CNN
	1    3775 3300
	0    -1   -1   0   
$EndComp
Text Label 3775 3200 0    60   ~ 0
5V
$Comp
L PWR_FLAG #FLG1
U 1 1 52A5AFCB
P 3300 2525
F 0 "#FLG1" H 3300 2620 30  0001 C CNN
F 1 "PWR_FLAG" H 3300 2705 30  0000 C CNN
F 2 "" H 3300 2525 60  0000 C CNN
F 3 "" H 3300 2525 60  0000 C CNN
	1    3300 2525
	0    1    1    0   
$EndComp
Text Label 3775 3100 0    60   ~ 0
3,3V
$Comp
L PWR_FLAG #FLG3
U 1 1 52A5B0CD
P 4075 3100
F 0 "#FLG3" H 4075 3195 30  0001 C CNN
F 1 "PWR_FLAG" H 4075 3280 30  0000 C CNN
F 2 "" H 4075 3100 60  0000 C CNN
F 3 "" H 4075 3100 60  0000 C CNN
	1    4075 3100
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 52A5C800
P 4000 1375
F 0 "#FLG2" H 4000 1470 30  0001 C CNN
F 1 "PWR_FLAG" H 4000 1555 30  0000 C CNN
F 2 "" H 4000 1375 60  0000 C CNN
F 3 "" H 4000 1375 60  0000 C CNN
	1    4000 1375
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 52A5C8B9
P 4325 3275
F 0 "R4" V 4405 3275 50  0000 C CNN
F 1 "1k" V 4325 3275 50  0000 C CNN
F 2 "" H 4325 3275 60  0001 C CNN
F 3 "" H 4325 3275 60  0001 C CNN
	1    4325 3275
	0    -1   1    0   
$EndComp
$Comp
L LED D3
U 1 1 52A5C8BF
P 4775 3275
F 0 "D3" H 4775 3375 50  0000 C CNN
F 1 "RED" H 4775 3175 50  0000 C CNN
F 2 "" H 4775 3275 60  0001 C CNN
F 3 "" H 4775 3275 60  0001 C CNN
	1    4775 3275
	1    0    0    1   
$EndComp
$Comp
L GND #PWR13
U 1 1 52A5C8C5
P 4975 3275
F 0 "#PWR13" H 4975 3275 30  0001 C CNN
F 1 "GND" H 4975 3205 30  0001 C CNN
F 2 "" H 4975 3275 60  0001 C CNN
F 3 "" H 4975 3275 60  0001 C CNN
	1    4975 3275
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 K1
U 1 1 52A5D5AA
P 3425 3200
F 0 "K1" V 3375 3200 50  0000 C CNN
F 1 "CONN_3" V 3475 3200 40  0000 C CNN
F 2 "" H 3425 3200 60  0000 C CNN
F 3 "" H 3425 3200 60  0000 C CNN
	1    3425 3200
	-1   0    0    1   
$EndComp
$Comp
L MINI-USB-5P-3400030P1 J1
U 1 1 52A7387D
P 2100 2125
F 0 "J1" H 1825 2475 60  0000 C CNN
F 1 "MINI-USB-5P-3400030P1" H 2100 2575 60  0001 C CNN
F 2 "" H 2100 2125 60  0000 C CNN
F 3 "" H 2100 2125 60  0000 C CNN
	1    2100 2125
	1    0    0    -1  
$EndComp
$Comp
L MICRO-SDCARD-CONNECTOR-3300060P1 P2
U 1 1 52A75274
P 3325 5000
F 0 "P2" H 3175 5500 60  0000 C CNN
F 1 "MICRO-SDCARD-CONNECTOR-3300060P1" H 3325 4500 60  0001 C CNN
F 2 "" H 3325 5000 60  0000 C CNN
F 3 "" H 3325 5000 60  0000 C CNN
	1    3325 5000
	-1   0    0    -1  
$EndComp
NoConn ~ 3725 4600
NoConn ~ 3725 5300
NoConn ~ 3725 5400
$Comp
L GND #PWR8
U 1 1 52A752F4
P 3725 5100
F 0 "#PWR8" H 3725 5100 30  0001 C CNN
F 1 "GND" H 3725 5030 30  0001 C CNN
F 2 "" H 3725 5100 60  0001 C CNN
F 3 "" H 3725 5100 60  0001 C CNN
	1    3725 5100
	0    -1   -1   0   
$EndComp
$Comp
L CONN_5X2 P1
U 1 1 52B45CE3
P 3425 4075
F 0 "P1" H 3425 4375 60  0000 C CNN
F 1 "CONN_5X2" V 3425 4075 50  0000 C CNN
F 2 "" H 3425 4075 60  0000 C CNN
F 3 "" H 3425 4075 60  0000 C CNN
	1    3425 4075
	1    0    0    -1  
$EndComp
Text Label 3900 4800 0    60   ~ 0
SPI_MOSI
Text Notes 3300 3700 0    60   ~ 0
Ext SPI
Text Notes 8300 3475 0    60   ~ 0
For left conn
Text Notes 5325 3475 0    60   ~ 0
For right conn
$Comp
L CONN_10X2 P3
U 1 1 52B479E1
P 5625 4125
F 0 "P3" H 5625 4675 60  0000 C CNN
F 1 "CONN_10X2" V 5625 4025 50  0000 C CNN
F 2 "" H 5625 4125 60  0000 C CNN
F 3 "" H 5625 4125 60  0000 C CNN
	1    5625 4125
	1    0    0    -1  
$EndComp
$Comp
L CONN_10X2 P4
U 1 1 52B479EE
P 8550 4125
F 0 "P4" H 8550 4675 60  0000 C CNN
F 1 "CONN_10X2" V 8550 4025 50  0000 C CNN
F 2 "" H 8550 4125 60  0000 C CNN
F 3 "" H 8550 4125 60  0000 C CNN
	1    8550 4125
	1    0    0    -1  
$EndComp
Text Label 8000 3675 2    60   ~ 0
CS1
Text Label 8000 3775 2    60   ~ 0
CS3
Text Label 9100 3675 0    60   ~ 0
CS2
NoConn ~ 8950 3775
NoConn ~ 8950 4275
NoConn ~ 8950 4375
NoConn ~ 8950 4475
NoConn ~ 8150 3875
Text Label 9100 3975 0    60   ~ 0
SPI_MISO
Text Label 9100 4075 0    60   ~ 0
USART_TX
Text Label 8000 3975 2    60   ~ 0
SPI_SCK
Text Label 8000 4075 2    60   ~ 0
SPI_MOSI
Text Label 8000 4175 2    60   ~ 0
USART_RX
Text Label 8000 4275 2    60   ~ 0
CS_SD_MODULE
NoConn ~ 8150 4375
NoConn ~ 8150 4475
Text Label 3900 5000 0    60   ~ 0
SPI_SCK
Text Label 3950 3975 0    60   ~ 0
CS1
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
	2300 1975 4775 1975
Wire Wire Line
	4775 1975 4775 1725
Wire Wire Line
	4775 1725 5025 1725
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
Connection ~ 2950 2075
Wire Wire Line
	3300 2125 3300 1975
Connection ~ 3300 1975
Wire Wire Line
	2950 2475 2950 2525
Wire Wire Line
	2950 2525 3300 2525
Wire Wire Line
	3100 2600 3100 2525
Connection ~ 3100 2525
Wire Wire Line
	5025 1625 4700 1625
Wire Wire Line
	4700 1625 4700 2075
Wire Wire Line
	4700 2075 2300 2075
Wire Wire Line
	7025 1425 6875 1425
Wire Wire Line
	6875 1325 7025 1325
Wire Wire Line
	4075 3100 3775 3100
Wire Wire Line
	3775 3200 4000 3200
Wire Wire Line
	4000 3200 4000 1375
Connection ~ 4000 1375
Wire Wire Line
	3900 5000 3725 5000
Wire Wire Line
	3725 5200 3900 5200
Wire Wire Line
	3900 4900 3725 4900
Wire Wire Line
	3025 3875 2850 3875
Wire Wire Line
	3025 3975 2850 3975
Wire Wire Line
	2850 4175 3025 4175
Wire Wire Line
	3025 4275 2850 4275
Wire Wire Line
	3825 4175 3950 4175
Wire Wire Line
	3900 4800 3725 4800
Wire Wire Line
	3900 4700 3725 4700
Wire Wire Line
	8150 3675 8000 3675
Wire Wire Line
	8150 3775 8000 3775
Wire Wire Line
	8150 3975 8000 3975
Wire Wire Line
	8150 4075 8000 4075
Wire Wire Line
	8150 4175 8000 4175
Wire Wire Line
	8150 4275 8000 4275
Wire Wire Line
	8950 3675 9100 3675
Wire Wire Line
	8950 3975 9100 3975
Wire Wire Line
	8950 4075 9100 4075
Wire Wire Line
	8950 4175 9100 4175
Wire Wire Line
	3825 3975 3950 3975
Wire Wire Line
	3825 4075 3950 4075
Wire Wire Line
	3825 4275 3950 4275
Wire Wire Line
	3025 4075 2850 4075
Text Label 3900 4900 0    60   ~ 0
3,3V
Text Label 2850 3875 2    60   ~ 0
3,3V
Text Label 2850 4075 2    60   ~ 0
CS2
Wire Wire Line
	4075 3100 4075 3275
Text Label 3950 4075 0    60   ~ 0
CS3
Text Label 2850 3975 2    60   ~ 0
5V
Text Label 3950 4175 0    60   ~ 0
SPI_MOSI
Text Label 3950 4275 0    60   ~ 0
CS4
Text Label 2850 4175 2    60   ~ 0
SPI_MISO
$Comp
L GND #PWR21
U 1 1 52B9BB90
P 8950 4575
F 0 "#PWR21" H 8950 4575 30  0001 C CNN
F 1 "GND" H 8950 4505 30  0001 C CNN
F 2 "" H 8950 4575 60  0001 C CNN
F 3 "" H 8950 4575 60  0001 C CNN
	1    8950 4575
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR20
U 1 1 52B9BB96
P 8150 4575
F 0 "#PWR20" H 8150 4575 30  0001 C CNN
F 1 "GND" H 8150 4505 30  0001 C CNN
F 2 "" H 8150 4575 60  0001 C CNN
F 3 "" H 8150 4575 60  0001 C CNN
	1    8150 4575
	0    1    1    0   
$EndComp
Text Label 5050 3875 2    60   ~ 0
CS1
Text Label 5050 3975 2    60   ~ 0
CS3
Text Label 6175 3675 0    60   ~ 0
CS2
Text Label 6200 4075 0    60   ~ 0
CS_SD_MODULE
Wire Wire Line
	6025 4075 6200 4075
Wire Wire Line
	5225 3875 5050 3875
Wire Wire Line
	5225 3975 5050 3975
Wire Wire Line
	5225 4075 5050 4075
$Comp
L CONN_1 P5
U 1 1 52BAA4A8
P 9100 3875
F 0 "P5" H 9180 3875 40  0000 L CNN
F 1 "CONN_1" H 9100 3930 30  0001 C CNN
F 2 "" H 9100 3875 60  0000 C CNN
F 3 "" H 9100 3875 60  0000 C CNN
	1    9100 3875
	1    0    0    -1  
$EndComp
Text Label 3900 4700 0    60   ~ 0
CS_SD_MODULE
Text Label 9100 4175 0    60   ~ 0
CS4
Text Label 5050 4075 2    60   ~ 0
CS4
Text Label 5050 4375 2    60   ~ 0
USART_TX
Wire Wire Line
	5225 4375 5050 4375
Text Label 6200 4375 0    60   ~ 0
USART_RX
Wire Wire Line
	6025 4375 6200 4375
Wire Wire Line
	6025 3675 6175 3675
Text Label 6200 3775 0    60   ~ 0
SPI_MOSI
Wire Wire Line
	6025 3775 6200 3775
Text Label 6200 3875 0    60   ~ 0
SPI_SCK
Wire Wire Line
	6025 3875 6200 3875
$Comp
L CONN_1 P6
U 1 1 52BAF879
P 5075 3675
F 0 "P6" H 5155 3675 40  0000 L CNN
F 1 "CONN_1" H 5075 3730 30  0001 C CNN
F 2 "" H 5075 3675 60  0000 C CNN
F 3 "" H 5075 3675 60  0000 C CNN
	1    5075 3675
	-1   0    0    1   
$EndComp
Text Label 5050 3775 2    60   ~ 0
SPI_MISO
Wire Wire Line
	5225 3775 5050 3775
NoConn ~ 6025 3975
NoConn ~ 6025 4175
NoConn ~ 6025 4275
NoConn ~ 6025 4475
NoConn ~ 6025 4575
NoConn ~ 5225 4175
NoConn ~ 5225 4275
NoConn ~ 5225 4475
NoConn ~ 5225 4575
$Comp
L LOGO G1
U 1 1 52BD6BB8
P 5050 5100
F 0 "G1" H 5050 4997 60  0001 C CNN
F 1 "LOGO" H 5050 5203 60  0001 C CNN
F 2 "" H 5050 5100 60  0000 C CNN
F 3 "" H 5050 5100 60  0000 C CNN
	1    5050 5100
	1    0    0    -1  
$EndComp
$Comp
L CP1 C8
U 1 1 52BEFB29
P 2300 6000
F 0 "C8" H 2350 6100 50  0000 L CNN
F 1 "4.7uF" H 2350 5900 50  0000 L CNN
F 2 "" H 2300 6000 60  0001 C CNN
F 3 "" H 2300 6000 60  0001 C CNN
	1    2300 6000
	-1   0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 52BEFB4C
P 2300 5450
F 0 "C7" H 2350 5550 50  0000 L CNN
F 1 ".1uF" H 2350 5350 50  0000 L CNN
F 2 "" H 2300 5450 60  0001 C CNN
F 3 "" H 2300 5450 60  0001 C CNN
	1    2300 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 5650 2300 5800
Wire Wire Line
	2000 5750 2300 5750
Connection ~ 2300 5750
$Comp
L GND #PWR4
U 1 1 52BEFC07
P 2300 6200
F 0 "#PWR4" H 2300 6200 30  0001 C CNN
F 1 "GND" H 2300 6130 30  0001 C CNN
F 2 "" H 2300 6200 60  0001 C CNN
F 3 "" H 2300 6200 60  0001 C CNN
	1    2300 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 52BEFC0D
P 2300 5250
F 0 "#PWR3" H 2300 5250 30  0001 C CNN
F 1 "GND" H 2300 5180 30  0001 C CNN
F 2 "" H 2300 5250 60  0001 C CNN
F 3 "" H 2300 5250 60  0001 C CNN
	1    2300 5250
	-1   0    0    1   
$EndComp
Text Label 2000 5750 2    60   ~ 0
3,3V
$EndSCHEMATC
