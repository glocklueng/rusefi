EESchema Schematic File Version 2
LIBS:KICAD_Older_Version
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
LIBS:rn-41
LIBS:skqucaa010_joystick
LIBS:itead_hc-0X_bluetooth
LIBS:joystick_SKRHAAE010
LIBS:STM32F407IGT6
LIBS:slc_oem
LIBS:mos_n_numbered-pins
LIBS:frankenso-cache
EELAYER 25 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 15 15
Title "Frankenso"
Date "3 dec 2015"
Rev ".05"
Comp "rusEFI.com"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TEST JPO2
U 1 1 539C7A79
P 1000 9200
F 0 "JPO2" V 1000 9200 40  0000 C CNN
F 1 "TEST-gnd" H 1000 9130 40  0001 C CNN
F 2 "SIL-2" H 1000 9200 60  0001 C CNN
F 3 "" H 1000 9200 60  0000 C CNN
F 4 "dnp,dnp" V 1000 9200 60  0001 C CNN "Field4"
F 5 "dnp,dnp" V 1000 9200 60  0001 C CNN "Field5"
	1    1000 9200
	-1   0    0    1   
$EndComp
Text Notes 575  9050 0    60   ~ 0
These two jumpers \nare here to accomodate \nstm32f4discovery
$Comp
L TEST JPO3
U 1 1 539C7A95
P 1000 9350
F 0 "JPO3" V 1000 9350 40  0000 C CNN
F 1 "TEST-gnd" H 1000 9280 40  0001 C CNN
F 2 "SIL-2" H 1000 9350 60  0001 C CNN
F 3 "" H 1000 9350 60  0000 C CNN
F 4 "dnp,dnp" V 1000 9350 60  0001 C CNN "Field4"
F 5 "dnp,dnp" V 1000 9350 60  0001 C CNN "Field5"
	1    1000 9350
	-1   0    0    1   
$EndComp
Text Label 1200 9350 0    60   ~ 0
GND
Text Label 1200 9200 0    60   ~ 0
GND
Text Label 800  9200 2    60   ~ 0
GND
Text Label 800  9350 2    60   ~ 0
GND
$Comp
L TEST TEST2
U 1 1 539DA1B1
P 1100 10400
F 0 "TEST2" V 1100 10400 40  0000 C CNN
F 1 "TEST-C-C" H 1100 10330 40  0001 C CNN
F 2 "SIL-2" H 1100 10400 60  0001 C CNN
F 3 "" H 1100 10400 60  0000 C CNN
F 4 "dnp,dnp" V 1100 10400 60  0001 C CNN "MFG,MFG#"
F 5 "dnp,dnp" V 1100 10400 60  0001 C CNN "VEND1,VEND1#"
	1    1100 10400
	-1   0    0    1   
$EndComp
Text Notes 550  10225 0    60   ~ 0
That's alternative signal \nOUTPUT - these traces \nshould be routable to PC6 \nand PA5 via jumpers. \nAleternative to W212 and \nW212 routung of op-amps \nch 11 and ch 12
$Comp
L CONN_12X2 P7
U 1 1 5445D37F
P 1250 3100
F 0 "P7" H 1250 3750 60  0000 C CNN
F 1 "pin_array_12x2" V 1250 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 1250 3100 60  0001 C CNN
F 3 "" H 1250 3100 60  0000 C CNN
F 4 "dnp,dnp" H 1250 3100 60  0001 C CNN "MFG,MFG#"
F 5 "dnp,dnp" H 1250 3100 60  0001 C CNN "VEND1,VEND1#"
	1    1250 3100
	1    0    0    -1  
$EndComp
NoConn ~ 1650 2550
NoConn ~ 1650 2650
NoConn ~ 1650 2750
NoConn ~ 1650 2850
NoConn ~ 1650 2950
NoConn ~ 1650 3050
NoConn ~ 1650 3150
NoConn ~ 1650 3250
NoConn ~ 1650 3350
NoConn ~ 1650 3450
NoConn ~ 1650 3550
NoConn ~ 1650 3650
NoConn ~ 850  3650
NoConn ~ 850  3550
NoConn ~ 850  3450
NoConn ~ 850  3350
NoConn ~ 850  3250
NoConn ~ 850  3150
NoConn ~ 850  3050
NoConn ~ 850  2950
NoConn ~ 850  2750
$Comp
L CONN_12X2 P8
U 1 1 5445E017
P 2450 3100
F 0 "P8" H 2450 3750 60  0000 C CNN
F 1 "pin_array_12x2" V 2450 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 2450 3100 60  0001 C CNN
F 3 "" H 2450 3100 60  0000 C CNN
F 4 "dnp,dnp" H 2450 3100 60  0001 C CNN "MFG,MFG#"
F 5 "dnp,dnp" H 2450 3100 60  0001 C CNN "VEND1,VEND1#"
	1    2450 3100
	1    0    0    -1  
$EndComp
NoConn ~ 2850 2550
NoConn ~ 2850 2650
NoConn ~ 2850 2750
NoConn ~ 2850 2850
NoConn ~ 2850 2950
NoConn ~ 2850 3050
NoConn ~ 2850 3150
NoConn ~ 2850 3250
NoConn ~ 2850 3350
NoConn ~ 2850 3450
NoConn ~ 2850 3550
NoConn ~ 2850 3650
NoConn ~ 2050 3650
NoConn ~ 2050 3550
NoConn ~ 2050 3450
NoConn ~ 2050 3350
NoConn ~ 2050 3250
NoConn ~ 2050 3150
NoConn ~ 2050 3050
NoConn ~ 2050 2950
NoConn ~ 2050 2850
NoConn ~ 2050 2650
NoConn ~ 2050 2750
NoConn ~ 2050 2550
$Comp
L CONN_12X2 P14
U 1 1 5445E2AE
P 3500 3100
F 0 "P14" H 3500 3750 60  0000 C CNN
F 1 "pin_array_12x2" V 3500 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 3500 3100 60  0001 C CNN
F 3 "" H 3500 3100 60  0000 C CNN
F 4 "dnp,dnp" H 3500 3100 60  0001 C CNN "MFG,MFG#"
F 5 "dnp,dnp" H 3500 3100 60  0001 C CNN "VEND1,VEND1#"
	1    3500 3100
	1    0    0    -1  
$EndComp
NoConn ~ 3900 2550
NoConn ~ 3900 2650
NoConn ~ 3900 2750
NoConn ~ 3900 2850
NoConn ~ 3900 2950
NoConn ~ 3900 3050
NoConn ~ 3900 3150
NoConn ~ 3900 3250
NoConn ~ 3900 3350
NoConn ~ 3900 3450
NoConn ~ 3900 3550
NoConn ~ 3900 3650
NoConn ~ 3100 3650
NoConn ~ 3100 3550
NoConn ~ 3100 3450
NoConn ~ 3100 3350
NoConn ~ 3100 3250
NoConn ~ 3100 3150
NoConn ~ 3100 3050
NoConn ~ 3100 2950
NoConn ~ 3100 2750
$Comp
L CONN_8X2 P24
U 1 1 544627FC
P 1250 4300
F 0 "P24" H 1250 4750 60  0000 C CNN
F 1 "pin_array_8x2" V 1250 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 1250 4300 60  0001 C CNN
F 3 "" H 1250 4300 60  0000 C CNN
F 4 "dnp,dnp" H 1250 4300 60  0001 C CNN "Field4"
F 5 "dnp,dnp" H 1250 4300 60  0001 C CNN "Field5"
	1    1250 4300
	1    0    0    -1  
$EndComp
NoConn ~ 1650 4650
NoConn ~ 1650 4550
NoConn ~ 1650 4450
NoConn ~ 1650 4350
NoConn ~ 1650 4250
NoConn ~ 1650 4150
NoConn ~ 1650 4050
NoConn ~ 1650 3950
NoConn ~ 850  4150
NoConn ~ 850  4350
NoConn ~ 850  4450
NoConn ~ 850  4550
NoConn ~ 850  4650
$Comp
L CONN_8X2 P25
U 1 1 54462809
P 2450 4300
F 0 "P25" H 2450 4750 60  0000 C CNN
F 1 "pin_array_8x2" V 2450 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 2450 4300 60  0001 C CNN
F 3 "" H 2450 4300 60  0000 C CNN
F 4 "dnp,dnp" H 2450 4300 60  0001 C CNN "Field4"
F 5 "dnp,dnp" H 2450 4300 60  0001 C CNN "Field5"
	1    2450 4300
	1    0    0    -1  
$EndComp
NoConn ~ 2850 4650
NoConn ~ 2850 4550
NoConn ~ 2850 4450
NoConn ~ 2850 4350
NoConn ~ 2850 4250
NoConn ~ 2850 4150
NoConn ~ 2850 4050
NoConn ~ 2850 3950
NoConn ~ 2050 3950
NoConn ~ 2050 4050
NoConn ~ 2050 4150
NoConn ~ 2050 4250
NoConn ~ 2050 4350
NoConn ~ 2050 4450
NoConn ~ 2050 4550
NoConn ~ 2050 4650
$Comp
L CONN_8X2 P26
U 1 1 544634A5
P 3500 4300
F 0 "P26" H 3500 4750 60  0000 C CNN
F 1 "pin_array_8x2" V 3500 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 3500 4300 60  0001 C CNN
F 3 "" H 3500 4300 60  0000 C CNN
F 4 "dnp,dnp" H 3500 4300 60  0001 C CNN "Field4"
F 5 "dnp,dnp" H 3500 4300 60  0001 C CNN "Field5"
	1    3500 4300
	1    0    0    -1  
$EndComp
NoConn ~ 3900 4650
NoConn ~ 3900 4550
NoConn ~ 3900 4450
NoConn ~ 3900 4350
NoConn ~ 3900 4250
NoConn ~ 3900 4150
NoConn ~ 3900 4050
NoConn ~ 3900 3950
NoConn ~ 3100 4150
NoConn ~ 3100 4350
NoConn ~ 3100 4450
NoConn ~ 3100 4550
NoConn ~ 3100 4650
Text Notes 4950 6750 0    60   ~ 0
PROTO AREA
Wire Notes Line
	3500 8700 500  8700
$Comp
L TEST JPO6
U 1 1 5446F00B
P 2300 9200
F 0 "JPO6" V 2300 9200 40  0000 C CNN
F 1 "TEST-gnd" H 2300 9130 40  0001 C CNN
F 2 "SIL-2" H 2300 9200 60  0001 C CNN
F 3 "" H 2300 9200 60  0000 C CNN
F 4 "dnp,dnp" V 2300 9200 60  0001 C CNN "Field4"
F 5 "dnp,dnp" V 2300 9200 60  0001 C CNN "Field5"
	1    2300 9200
	-1   0    0    1   
$EndComp
$Comp
L TEST JPO7
U 1 1 5446F013
P 2300 9350
F 0 "JPO7" V 2300 9350 40  0000 C CNN
F 1 "TEST-gnd" H 2300 9280 40  0001 C CNN
F 2 "SIL-2" H 2300 9350 60  0001 C CNN
F 3 "" H 2300 9350 60  0000 C CNN
F 4 "dnp,dnp" V 2300 9350 60  0001 C CNN "Field4"
F 5 "dnp,dnp" V 2300 9350 60  0001 C CNN "Field5"
	1    2300 9350
	-1   0    0    1   
$EndComp
$Comp
L TEST JPO8
U 1 1 5446F01B
P 3100 9200
F 0 "JPO8" V 3100 9200 40  0000 C CNN
F 1 "TEST-gnd" H 3100 9130 40  0001 C CNN
F 2 "SIL-2" H 3100 9200 60  0001 C CNN
F 3 "" H 3100 9200 60  0000 C CNN
F 4 "dnp,dnp" V 3100 9200 60  0001 C CNN "Field4"
F 5 "dnp,dnp" V 3100 9200 60  0001 C CNN "Field5"
	1    3100 9200
	-1   0    0    1   
$EndComp
Text Label 2500 9350 0    60   ~ 0
GND
$Comp
L TEST JPO9
U 1 1 5446F519
P 3100 9350
F 0 "JPO9" V 3100 9350 40  0000 C CNN
F 1 "TEST-gnd" H 3100 9280 40  0001 C CNN
F 2 "SIL-2" H 3100 9350 60  0001 C CNN
F 3 "" H 3100 9350 60  0000 C CNN
F 4 "dnp,dnp" V 3100 9350 60  0001 C CNN "Field4"
F 5 "dnp,dnp" V 3100 9350 60  0001 C CNN "Field5"
	1    3100 9350
	-1   0    0    1   
$EndComp
Text Label 3300 9200 0    60   ~ 0
5V
Wire Wire Line
	2100 9200 2500 9200
Text Notes 2325 9000 0    60   ~ 0
These four jumpers \nare test points
Wire Notes Line
	3500 9500 500  9500
Text Label 850  1250 2    60   ~ 0
5V
Text Label 850  1050 2    60   ~ 0
GND
Text Label 850  2050 2    60   ~ 0
5V
Text Label 850  2250 2    60   ~ 0
GND
Text Label 850  1150 2    60   ~ 0
3.3V
Text Label 850  2150 2    60   ~ 0
3.3V
NoConn ~ 850  2850
NoConn ~ 850  2650
NoConn ~ 850  2550
NoConn ~ 850  4250
NoConn ~ 850  4050
NoConn ~ 850  3950
Text HLabel 2100 9200 0    60   Input ~ 0
12V-SWITCH
Text HLabel 2900 9200 0    60   Input ~ 0
5V
Text Label 3300 9350 0    60   ~ 0
3.3V
Text HLabel 2900 9350 0    60   Input ~ 0
3.3V
Text HLabel 2100 9350 0    60   Input ~ 0
GND
Text HLabel 900  10400 0    60   Input ~ 0
CRANK
Text HLabel 1300 10400 2    60   Input ~ 0
CAM
$Comp
L CONN_12X2 P28
U 1 1 553A3905
P 4450 3100
F 0 "P28" H 4450 3750 60  0000 C CNN
F 1 "CONN_12X2" V 4450 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 4450 3100 60  0001 C CNN
F 3 "" H 4450 3100 60  0000 C CNN
	1    4450 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P29
U 1 1 553A3914
P 1250 6000
F 0 "P29" H 1250 6300 60  0000 C CNN
F 1 "CONN_5X2" V 1250 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 1250 6000 60  0001 C CNN
F 3 "" H 1250 6000 60  0000 C CNN
	1    1250 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_6X2 P27
U 1 1 553A3923
P 1250 5250
F 0 "P27" H 1250 5600 60  0000 C CNN
F 1 "CONN_6X2" V 1250 5250 60  0000 C CNN
F 2 "pin_array_6x2" H 1250 5250 60  0001 C CNN
F 3 "" H 1250 5250 60  0000 C CNN
	1    1250 5250
	1    0    0    -1  
$EndComp
$Comp
L CONN_13X2 P50
U 1 1 553A3932
P 1250 1650
F 0 "P50" H 1250 2350 60  0000 C CNN
F 1 "CONN_13X2" V 1250 1650 50  0000 C CNN
F 2 "pin_array_13x2" H 1250 1650 60  0001 C CNN
F 3 "" H 1250 1650 60  0000 C CNN
	1    1250 1650
	1    0    0    -1  
$EndComp
$Comp
L CONN_4X2 P31
U 1 1 553A3941
P 1250 6700
F 0 "P31" H 1250 6950 50  0000 C CNN
F 1 "CONN_4X2" V 1250 6700 40  0000 C CNN
F 2 "Pin_Header_Straight_2x04" H 1250 6700 60  0001 C CNN
F 3 "" H 1250 6700 60  0000 C CNN
	1    1250 6700
	1    0    0    -1  
$EndComp
$Comp
L CONN_8X2 P33
U 1 1 553A3950
P 4450 4300
F 0 "P33" H 4450 4750 60  0000 C CNN
F 1 "CONN_8X2" V 4450 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 4450 4300 60  0001 C CNN
F 3 "" H 4450 4300 60  0000 C CNN
	1    4450 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_2X2 P49
U 1 1 553A395F
P 1250 7350
F 0 "P49" H 1250 7500 50  0000 C CNN
F 1 "CONN_2X2" H 1260 7220 40  0000 C CNN
F 2 "PIN_ARRAY_2X2" H 1250 7350 60  0001 C CNN
F 3 "" H 1250 7350 60  0000 C CNN
	1    1250 7350
	1    0    0    -1  
$EndComp
$Comp
L CONN_12X2 P35
U 1 1 553A8F5F
P 5400 3100
F 0 "P35" H 5400 3750 60  0000 C CNN
F 1 "CONN_12X2" V 5400 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 5400 3100 60  0001 C CNN
F 3 "" H 5400 3100 60  0000 C CNN
	1    5400 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_12X2 P36
U 1 1 553A8F65
P 6300 3100
F 0 "P36" H 6300 3750 60  0000 C CNN
F 1 "CONN_12X2" V 6300 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 6300 3100 60  0001 C CNN
F 3 "" H 6300 3100 60  0000 C CNN
	1    6300 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_12X2 P42
U 1 1 553A8F6B
P 7250 3100
F 0 "P42" H 7250 3750 60  0000 C CNN
F 1 "CONN_12X2" V 7250 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 7250 3100 60  0001 C CNN
F 3 "" H 7250 3100 60  0000 C CNN
	1    7250 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_12X2 P43
U 1 1 553A8F71
P 8200 3100
F 0 "P43" H 8200 3750 60  0000 C CNN
F 1 "CONN_12X2" V 8200 3100 50  0000 C CNN
F 2 "pin_array_12x2" H 8200 3100 60  0001 C CNN
F 3 "" H 8200 3100 60  0000 C CNN
	1    8200 3100
	1    0    0    -1  
$EndComp
$Comp
L CONN_8X2 P39
U 1 1 553A8F77
P 5400 4300
F 0 "P39" H 5400 4750 60  0000 C CNN
F 1 "CONN_8X2" V 5400 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 5400 4300 60  0001 C CNN
F 3 "" H 5400 4300 60  0000 C CNN
	1    5400 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_8X2 P40
U 1 1 553A8F7D
P 6300 4300
F 0 "P40" H 6300 4750 60  0000 C CNN
F 1 "CONN_8X2" V 6300 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 6300 4300 60  0001 C CNN
F 3 "" H 6300 4300 60  0000 C CNN
	1    6300 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_8X2 P44
U 1 1 553A8F83
P 7250 4300
F 0 "P44" H 7250 4750 60  0000 C CNN
F 1 "CONN_8X2" V 7250 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 7250 4300 60  0001 C CNN
F 3 "" H 7250 4300 60  0000 C CNN
	1    7250 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_8X2 P46
U 1 1 553A8F89
P 8200 4300
F 0 "P46" H 8200 4750 60  0000 C CNN
F 1 "CONN_8X2" V 8200 4300 50  0000 C CNN
F 2 "pin_array_8x2" H 8200 4300 60  0001 C CNN
F 3 "" H 8200 4300 60  0000 C CNN
	1    8200 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P34
U 1 1 553A8F8F
P 2450 6000
F 0 "P34" H 2450 6300 60  0000 C CNN
F 1 "CONN_5X2" V 2450 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 2450 6000 60  0001 C CNN
F 3 "" H 2450 6000 60  0000 C CNN
	1    2450 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P37
U 1 1 553A8F95
P 3500 6000
F 0 "P37" H 3500 6300 60  0000 C CNN
F 1 "CONN_5X2" V 3500 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 3500 6000 60  0001 C CNN
F 3 "" H 3500 6000 60  0000 C CNN
	1    3500 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P38
U 1 1 553A8F9B
P 4450 6000
F 0 "P38" H 4450 6300 60  0000 C CNN
F 1 "CONN_5X2" V 4450 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 4450 6000 60  0001 C CNN
F 3 "" H 4450 6000 60  0000 C CNN
	1    4450 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P41
U 1 1 553A8FA1
P 5400 6000
F 0 "P41" H 5400 6300 60  0000 C CNN
F 1 "CONN_5X2" V 5400 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 5400 6000 60  0001 C CNN
F 3 "" H 5400 6000 60  0000 C CNN
	1    5400 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P45
U 1 1 553A8FA7
P 6300 6000
F 0 "P45" H 6300 6300 60  0000 C CNN
F 1 "CONN_5X2" V 6300 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 6300 6000 60  0001 C CNN
F 3 "" H 6300 6000 60  0000 C CNN
	1    6300 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_5X2 P47
U 1 1 553A8FAD
P 7450 6000
F 0 "P47" H 7450 6300 60  0000 C CNN
F 1 "CONN_5X2" V 7450 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 7450 6000 60  0001 C CNN
F 3 "" H 7450 6000 60  0000 C CNN
	1    7450 6000
	1    0    0    -1  
$EndComp
$Comp
L CONN_4X2 P32
U 1 1 553A8FB3
P 2450 6700
F 0 "P32" H 2450 6950 50  0000 C CNN
F 1 "CONN_4X2" V 2450 6700 40  0000 C CNN
F 2 "Pin_Header_Straight_2x04" H 2450 6700 60  0001 C CNN
F 3 "" H 2450 6700 60  0000 C CNN
	1    2450 6700
	1    0    0    -1  
$EndComp
$Comp
L CONN_4X2 P48
U 1 1 553A8FB9
P 3500 6700
F 0 "P48" H 3500 6950 50  0000 C CNN
F 1 "CONN_4X2" V 3500 6700 40  0000 C CNN
F 2 "Pin_Header_Straight_2x04" H 3500 6700 60  0001 C CNN
F 3 "" H 3500 6700 60  0000 C CNN
	1    3500 6700
	1    0    0    -1  
$EndComp
NoConn ~ 850  1350
NoConn ~ 850  1450
NoConn ~ 850  1550
NoConn ~ 850  1650
NoConn ~ 850  1750
NoConn ~ 850  1850
NoConn ~ 850  1950
NoConn ~ 850  7300
NoConn ~ 850  7400
NoConn ~ 3900 6550
NoConn ~ 4050 3650
NoConn ~ 4050 3550
NoConn ~ 4050 3450
NoConn ~ 4050 3350
NoConn ~ 4050 3250
NoConn ~ 4050 3150
NoConn ~ 4050 3050
NoConn ~ 4050 2950
NoConn ~ 4050 2850
NoConn ~ 4050 2750
NoConn ~ 4050 2650
NoConn ~ 4050 2550
NoConn ~ 4850 2550
NoConn ~ 1650 2250
NoConn ~ 1650 2150
NoConn ~ 1650 2050
NoConn ~ 1650 1950
NoConn ~ 1650 1850
NoConn ~ 1650 1750
NoConn ~ 1650 1650
NoConn ~ 1650 1550
NoConn ~ 1650 1450
NoConn ~ 1650 1350
NoConn ~ 1650 1250
NoConn ~ 1650 1150
NoConn ~ 1650 1050
NoConn ~ 4850 3650
NoConn ~ 4850 3550
NoConn ~ 4850 3450
NoConn ~ 4850 3350
NoConn ~ 4850 3250
NoConn ~ 4850 3150
NoConn ~ 4850 3050
NoConn ~ 4850 2850
NoConn ~ 4850 2950
NoConn ~ 4850 2750
NoConn ~ 4850 2650
NoConn ~ 5000 2550
NoConn ~ 5000 2650
NoConn ~ 5000 2750
NoConn ~ 5000 2850
NoConn ~ 5000 2950
NoConn ~ 5000 3050
NoConn ~ 5000 3150
NoConn ~ 5000 3250
NoConn ~ 5000 3350
NoConn ~ 5000 3450
NoConn ~ 5000 3550
NoConn ~ 5000 3650
NoConn ~ 5800 3650
NoConn ~ 5800 3550
NoConn ~ 5800 3450
NoConn ~ 5800 3350
NoConn ~ 5800 3250
NoConn ~ 5800 3150
NoConn ~ 5800 3050
NoConn ~ 5800 2950
NoConn ~ 5800 2850
NoConn ~ 5800 2750
NoConn ~ 5800 2650
NoConn ~ 5800 2550
NoConn ~ 5900 2550
NoConn ~ 5900 2650
NoConn ~ 5900 2750
NoConn ~ 5900 2850
NoConn ~ 5900 2950
NoConn ~ 5900 3050
NoConn ~ 5900 3150
NoConn ~ 5900 3250
NoConn ~ 5900 3350
NoConn ~ 5900 3450
NoConn ~ 5900 3550
NoConn ~ 5900 3650
NoConn ~ 5900 4650
NoConn ~ 5900 4550
NoConn ~ 5900 4450
NoConn ~ 5900 4350
NoConn ~ 5900 4250
NoConn ~ 5900 4150
NoConn ~ 5900 4050
NoConn ~ 5900 3950
NoConn ~ 5800 3950
NoConn ~ 5800 4050
NoConn ~ 5800 4150
NoConn ~ 5800 4250
NoConn ~ 5800 4350
NoConn ~ 5800 4450
NoConn ~ 5800 4550
NoConn ~ 5800 4650
NoConn ~ 5000 4650
NoConn ~ 5000 4550
NoConn ~ 5000 4450
NoConn ~ 5000 4350
NoConn ~ 5000 4250
NoConn ~ 5000 4150
NoConn ~ 5000 4050
NoConn ~ 5000 3950
NoConn ~ 4850 3950
NoConn ~ 4850 4050
NoConn ~ 4850 4150
NoConn ~ 4850 4250
NoConn ~ 4850 4350
NoConn ~ 4850 4450
NoConn ~ 4850 4550
NoConn ~ 4850 4650
NoConn ~ 4050 4650
NoConn ~ 4050 4550
NoConn ~ 4050 4450
NoConn ~ 4050 4350
NoConn ~ 4050 4250
NoConn ~ 4050 4150
NoConn ~ 4050 4050
NoConn ~ 4050 3950
NoConn ~ 850  5000
NoConn ~ 850  5100
NoConn ~ 850  5200
NoConn ~ 850  5300
NoConn ~ 850  5400
NoConn ~ 850  5500
NoConn ~ 1650 5500
NoConn ~ 1650 5400
NoConn ~ 1650 5300
NoConn ~ 1650 5200
NoConn ~ 1650 5100
NoConn ~ 1650 5000
NoConn ~ 1650 7400
NoConn ~ 1650 7300
NoConn ~ 850  6850
NoConn ~ 850  6750
NoConn ~ 850  6650
NoConn ~ 850  6550
NoConn ~ 1650 6550
NoConn ~ 1650 6650
NoConn ~ 1650 6750
NoConn ~ 1650 6850
NoConn ~ 2050 6850
NoConn ~ 2050 6750
NoConn ~ 2050 6650
NoConn ~ 2050 6550
NoConn ~ 2850 6550
NoConn ~ 2850 6650
NoConn ~ 2850 6750
NoConn ~ 2850 6850
NoConn ~ 3100 6850
NoConn ~ 3100 6750
NoConn ~ 3100 6650
NoConn ~ 3100 6550
NoConn ~ 3100 6200
NoConn ~ 3100 6100
NoConn ~ 3100 6000
NoConn ~ 3100 5900
NoConn ~ 3100 5800
NoConn ~ 2850 5800
NoConn ~ 2850 5900
NoConn ~ 2850 6000
NoConn ~ 2850 6100
NoConn ~ 2850 6200
NoConn ~ 2050 6200
NoConn ~ 2050 6100
NoConn ~ 2050 6000
NoConn ~ 2050 5900
NoConn ~ 2050 5800
NoConn ~ 1650 5800
NoConn ~ 1650 5900
NoConn ~ 1650 6000
NoConn ~ 1650 6100
NoConn ~ 1650 6200
NoConn ~ 850  6200
NoConn ~ 850  6100
NoConn ~ 850  6000
NoConn ~ 850  5900
NoConn ~ 850  5800
NoConn ~ 7850 5800
NoConn ~ 7850 5900
NoConn ~ 7850 6000
NoConn ~ 7850 6100
NoConn ~ 7050 6100
NoConn ~ 7050 6000
NoConn ~ 7050 5900
NoConn ~ 7050 5800
NoConn ~ 6700 5800
NoConn ~ 6700 5900
NoConn ~ 6700 6000
NoConn ~ 6700 6100
NoConn ~ 6700 6200
NoConn ~ 5900 6200
NoConn ~ 5900 6100
NoConn ~ 5900 6000
NoConn ~ 5900 5900
NoConn ~ 5900 5800
NoConn ~ 5800 5800
NoConn ~ 5800 5900
NoConn ~ 5800 6000
NoConn ~ 5800 6100
NoConn ~ 5800 6200
NoConn ~ 5000 6200
NoConn ~ 5000 6100
NoConn ~ 5000 6000
NoConn ~ 5000 5900
NoConn ~ 5000 5800
NoConn ~ 4850 5800
NoConn ~ 4850 5900
NoConn ~ 4850 6000
NoConn ~ 4850 6100
NoConn ~ 4850 6200
NoConn ~ 4050 6200
NoConn ~ 4050 6100
NoConn ~ 4050 6000
NoConn ~ 4050 5900
NoConn ~ 4050 5800
NoConn ~ 3900 5800
NoConn ~ 3900 5900
NoConn ~ 3900 6000
NoConn ~ 3900 6100
NoConn ~ 3900 6200
NoConn ~ 3900 6650
NoConn ~ 3900 6750
NoConn ~ 3900 6850
NoConn ~ 8600 4650
NoConn ~ 8600 4550
NoConn ~ 8600 4450
NoConn ~ 8600 4350
NoConn ~ 8600 4250
NoConn ~ 8600 4150
NoConn ~ 8600 4050
NoConn ~ 8600 3950
NoConn ~ 7800 3950
NoConn ~ 7800 4050
NoConn ~ 7800 4150
NoConn ~ 7800 4250
NoConn ~ 7800 4350
NoConn ~ 7800 4450
NoConn ~ 7800 4550
NoConn ~ 7800 4650
NoConn ~ 7650 4650
NoConn ~ 7650 4550
NoConn ~ 7650 4450
NoConn ~ 7650 4350
NoConn ~ 7650 4250
NoConn ~ 7650 4150
NoConn ~ 7650 4050
NoConn ~ 7650 3950
NoConn ~ 6850 3950
NoConn ~ 6850 4050
NoConn ~ 6850 4150
NoConn ~ 6850 4250
NoConn ~ 6850 4350
NoConn ~ 6850 4450
NoConn ~ 6850 4550
NoConn ~ 6850 4650
NoConn ~ 6700 4650
NoConn ~ 6700 4550
NoConn ~ 6700 4450
NoConn ~ 6700 4350
NoConn ~ 6700 4250
NoConn ~ 6700 4150
NoConn ~ 6700 4050
NoConn ~ 6700 3950
NoConn ~ 6700 3650
NoConn ~ 6700 3550
NoConn ~ 6700 3450
NoConn ~ 6700 3350
NoConn ~ 6700 3250
NoConn ~ 6700 3150
NoConn ~ 6700 3050
NoConn ~ 6700 2950
NoConn ~ 6700 2850
NoConn ~ 6700 2750
NoConn ~ 6700 2650
NoConn ~ 6700 2550
NoConn ~ 6850 2550
NoConn ~ 6850 2650
NoConn ~ 6850 2750
NoConn ~ 6850 2850
NoConn ~ 6850 2950
NoConn ~ 6850 3050
NoConn ~ 6850 3150
NoConn ~ 6850 3250
NoConn ~ 6850 3350
NoConn ~ 6850 3450
NoConn ~ 6850 3550
NoConn ~ 6850 3650
NoConn ~ 7650 3650
NoConn ~ 7650 3550
NoConn ~ 7650 3450
NoConn ~ 7650 3350
NoConn ~ 7650 3250
NoConn ~ 7650 3150
NoConn ~ 7650 3050
NoConn ~ 7650 2950
NoConn ~ 7650 2850
NoConn ~ 7650 2750
NoConn ~ 7650 2650
NoConn ~ 7650 2550
NoConn ~ 7800 2550
NoConn ~ 7800 2650
NoConn ~ 7800 2750
NoConn ~ 7800 2850
NoConn ~ 7800 2950
NoConn ~ 7800 3050
NoConn ~ 7800 3150
NoConn ~ 7800 3250
NoConn ~ 7800 3350
NoConn ~ 7800 3450
NoConn ~ 7800 3550
NoConn ~ 7800 3650
NoConn ~ 8600 3650
NoConn ~ 8600 3550
NoConn ~ 8600 3450
NoConn ~ 8600 3350
NoConn ~ 8600 3250
NoConn ~ 8600 3150
NoConn ~ 8600 3050
NoConn ~ 8600 2950
NoConn ~ 8600 2850
NoConn ~ 8600 2750
NoConn ~ 8600 2650
NoConn ~ 8600 2550
NoConn ~ 3100 3950
NoConn ~ 3100 4050
NoConn ~ 3100 4250
NoConn ~ 3100 2850
NoConn ~ 3100 2650
NoConn ~ 3100 2550
Wire Notes Line
	3500 8700 3500 10500
Wire Notes Line
	550  7700 8900 7700
Wire Notes Line
	8900 7700 8900 550 
Text Label 7850 6200 0    60   ~ 0
5V
Text Label 7050 6200 2    60   ~ 0
GND
$Comp
L CONN_5X2 P54
U 1 1 56CA8F18
P 8450 6000
F 0 "P54" H 8450 6300 60  0000 C CNN
F 1 "CONN_5X2" V 8450 6000 50  0000 C CNN
F 2 "Pin_Header_Straight_2x05" H 8450 6000 60  0001 C CNN
F 3 "" H 8450 6000 60  0000 C CNN
	1    8450 6000
	1    0    0    -1  
$EndComp
NoConn ~ 8850 5800
NoConn ~ 8850 5900
NoConn ~ 8850 6000
NoConn ~ 8850 6100
NoConn ~ 8850 6200
NoConn ~ 8050 6200
NoConn ~ 8050 6100
NoConn ~ 8050 6000
NoConn ~ 8050 5900
NoConn ~ 8050 5800
$Comp
L CONN_4X2 P53
U 1 1 56CA9222
P 4425 6700
F 0 "P53" H 4425 6950 50  0000 C CNN
F 1 "CONN_4X2" V 4425 6700 40  0000 C CNN
F 2 "Pin_Header_Straight_2x04" H 4425 6700 60  0001 C CNN
F 3 "" H 4425 6700 60  0000 C CNN
	1    4425 6700
	1    0    0    -1  
$EndComp
NoConn ~ 4825 6550
NoConn ~ 4025 6850
NoConn ~ 4025 6750
NoConn ~ 4025 6650
NoConn ~ 4025 6550
NoConn ~ 4825 6650
NoConn ~ 4825 6750
NoConn ~ 4825 6850
$EndSCHEMATC
