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
Sheet 1 4
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
S 9800 1000 850  450 
U 52A53383
F0 "inj_6ch" 50
F1 "inj_6ch.sch" 50
$EndSheet
$Sheet
S 9800 1900 500  400 
U 52A5358C
F0 "adc_amp_divider" 50
F1 "adc_amp_divider.sch" 50
$EndSheet
$Sheet
S 9800 2900 1000 400 
U 52C39F6D
F0 "mmc_usb_1" 50
F1 "mmc_usb_1.sch" 50
$EndSheet
$Comp
L CONN_4X2 P1
U 1 1 52DB4402
P 3550 2500
F 0 "P1" H 3550 2750 50  0000 C CNN
F 1 "CONN_4X2" V 3550 2500 40  0000 C CNN
F 2 "" H 3550 2500 60  0000 C CNN
F 3 "" H 3550 2500 60  0000 C CNN
	1    3550 2500
	1    0    0    -1  
$EndComp
$Comp
L CONN_10X2 P2
U 1 1 52DB4411
P 3800 4050
F 0 "P2" H 3800 4600 60  0000 C CNN
F 1 "CONN_10X2" V 3800 3950 50  0000 C CNN
F 2 "" H 3800 4050 60  0000 C CNN
F 3 "" H 3800 4050 60  0000 C CNN
	1    3800 4050
	1    0    0    -1  
$EndComp
NoConn ~ 3150 2550
NoConn ~ 3150 2450
NoConn ~ 3150 2350
NoConn ~ 3950 2350
NoConn ~ 3950 2450
NoConn ~ 3950 2550
Text Label 3950 2650 0    60   ~ 0
GND
$Comp
L GND #PWR01
U 1 1 52DB443D
P 4100 2800
F 0 "#PWR01" H 4100 2800 30  0001 C CNN
F 1 "GND" H 4100 2730 30  0001 C CNN
F 2 "" H 4100 2800 60  0000 C CNN
F 3 "" H 4100 2800 60  0000 C CNN
	1    4100 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 2650 4100 2650
Wire Wire Line
	4100 2650 4100 2800
Text Label 3150 2650 2    60   ~ 0
GND
NoConn ~ 3400 3600
NoConn ~ 3400 3700
NoConn ~ 3400 3800
NoConn ~ 3400 3900
NoConn ~ 3400 4000
NoConn ~ 3400 4100
NoConn ~ 3400 4200
NoConn ~ 3400 4300
NoConn ~ 3400 4400
NoConn ~ 3400 4500
NoConn ~ 4200 4500
NoConn ~ 4200 4400
NoConn ~ 4200 4300
NoConn ~ 4200 4200
NoConn ~ 4200 4100
NoConn ~ 4200 4000
NoConn ~ 4200 3900
NoConn ~ 4200 3800
NoConn ~ 4200 3700
NoConn ~ 4200 3600
$EndSCHEMATC
