EESchema Schematic File Version 2
LIBS:KICAD_Older_Version
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
LIBS:lm2596
LIBS:mos_p_numbered-pins
LIBS:mos_n_numbered-pins
LIBS:PWR_buck_12V_switcher-cache
EELAYER 25 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "PWR buck 12V switcher regulator"
Date "28 nov 2015"
Rev ".04"
Comp "https://sourceforge.net/p/rusefi/"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_2 P1
U 1 1 5611B0CA
P 3150 6500
F 0 "P1" V 3100 6500 40  0000 C CNN
F 1 "CONN_2" V 3200 6500 40  0000 C CNN
F 2 "AK300-2" H 3150 6500 60  0001 C CNN
F 3 "" H 3150 6500 60  0001 C CNN
F 4 "-,-" V 3150 6500 60  0001 C CNN "MFG,MFG#"
F 5 "sky-macau.com,9554316569" V 3150 6500 60  0001 C CNN "VEND1,VEND1#"
	1    3150 6500
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P3
U 1 1 5611B0CC
P 10350 6550
F 0 "P3" V 10300 6550 40  0000 C CNN
F 1 "CONN_2" V 10400 6550 40  0000 C CNN
F 2 "AK300-2" H 10350 6550 60  0001 C CNN
F 3 "" H 10350 6550 60  0001 C CNN
F 4 "-,-" V 10350 6550 60  0001 C CNN "MFG,MFG#"
F 5 "sky-macau.com,9554316569" V 10350 6550 60  0001 C CNN "VEND1,VEND1#"
	1    10350 6550
	1    0    0    -1  
$EndComp
Connection ~ -4675 3450
$Comp
L CONN_1 P2
U 1 1 5611B0DD
P 7750 6700
F 0 "P2" H 7830 6700 40  0000 L CNN
F 1 "CONN_1" H 7750 6755 30  0001 C CNN
F 2 "SIL-1" V 1130 2600 60  0001 C CNN
F 3 "" H 7750 6700 60  0001 C CNN
F 4 "DO NOT POPULATE,DNP" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "DO NOT POPULATE,DNP" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    7750 6700
	-1   0    0    1   
$EndComp
$Comp
L CP1 C1
U 1 1 5611B0DE
P 6800 6600
F 0 "C1" V 6650 6350 50  0000 L CNN
F 1 "330uF 35V" V 7000 6350 50  0000 L CNN
F 2 "SMDSVP10" H 6800 6600 60  0001 C CNN
F 3 "" H 6800 6600 60  0001 C CNN
F 4 "unitedchem,EMVY350ADA331MJA0G" H 6800 6600 60  0001 C CNN "MFG,MFG#"
F 5 "DIGI,565-2479-1-ND" H 6800 6600 60  0001 C CNN "VEND1,VEND1#"
	1    6800 6600
	-1   0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5611B0DF
P 8650 6600
F 0 "R2" V 8730 6600 50  0000 C CNN
F 1 "1k" V 8650 6600 50  0000 C CNN
F 2 "SM0805" V 1130 2600 60  0001 C CNN
F 3 "" H 8650 6600 60  0001 C CNN
F 4 "Panasonic,ERA-6AEB102V" V 1130 2600 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,P1.0KDACT-ND" V 1130 2600 60  0001 C CNN "vend1,vend1#"
	1    8650 6600
	0    1    1    0   
$EndComp
$Comp
L LED D5
U 1 1 5611B0E0
P 8600 6750
F 0 "D5" H 8600 6600 50  0000 C CNN
F 1 "LED-grn" H 8600 6925 50  0001 C CNN
F 2 "LED-0805" H 8600 6750 60  0001 C CNN
F 3 "" H 8600 6750 60  0001 C CNN
F 4 "lite-on,LTST-C171GKT" H 8600 6750 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,160-1423-1-ND" H 8600 6750 60  0001 C CNN "VEND1,VEND1#"
	1    8600 6750
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L1
U 1 1 5611B0E1
P 8600 6450
F 0 "L1" V 8550 6450 40  0000 C CNN
F 1 "38uH" V 8700 6450 40  0000 C CNN
F 2 "SM100uH" H 8600 6450 60  0001 C CNN
F 3 "" H 8600 6450 60  0001 C CNN
F 4 "ref_PULSE_ref,ref_PE-54040-S_ref-use-sky-macau-number" V 8600 6450 60  0001 C CNN "MFG,MFG#"
F 5 "sky-macau.com,3817361683" V 8600 6450 60  0001 C CNN "VEND1,VEND1#"
	1    8600 6450
	0    -1   -1   0   
$EndComp
$Comp
L LM2596 U1
U 1 1 5611B0E2
P 7450 6550
F 0 "U1" H 7600 6850 60  0000 C CNN
F 1 "LM2596" H 7200 6400 60  0000 C CNN
F 2 "DPAK5" H 7450 6550 60  0001 C CNN
F 3 "~" H 7450 6550 60  0000 C CNN
F 4 "linear,2596-5.0" H 7450 6550 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,LM2596S-5.0/NOPB-ND" H 7450 6550 60  0001 C CNN "vend1,vend1#"
F 6 "sky-macau.com,6841999795" H 7450 6550 60  0001 C CNN "vend2,vend2#"
	1    7450 6550
	1    0    0    -1  
$EndComp
$Comp
L INDUCTOR L2
U 1 1 5611B0E3
P 9350 6450
F 0 "L2" V 9300 6400 40  0000 C CNN
F 1 "38uH" V 9450 6450 40  0000 C CNN
F 2 "SM100uH" H 9350 6450 60  0001 C CNN
F 3 "" H 9350 6450 60  0001 C CNN
F 4 "ref_PULSE_ref,ref_PE-54040-S_ref-use-sky-macau-number" V 9350 6450 60  0001 C CNN "MFG,MFG#"
F 5 "sky-macau.com,3817361683" V 9350 6450 60  0001 C CNN "VEND1,VEND1#"
	1    9350 6450
	0    -1   -1   0   
$EndComp
$Comp
L SCHDPAK D4
U 1 1 5611B0E4
P 8300 6650
F 0 "D4" H 8300 6750 40  0000 C CNN
F 1 "SCHDPAK" H 8300 6550 40  0001 C CNN
F 2 "DPAK2" H 8300 6650 60  0001 C CNN
F 3 "~" H 8300 6650 60  0000 C CNN
F 4 "VISHAY,VS-50WQ04FNPBF" H 8300 6650 60  0001 C CNN "MFG,MFG#"
F 5 "DIGI,VS-50WQ04FNPBF-ND" H 8300 6650 60  0001 C CNN "VEND1,VEND1#"
F 6 "DO NOT POPULATE" H 8300 6650 60  0001 C CNN "Field6"
	1    8300 6650
	0    -1   -1   0   
$EndComp
Text Label 6800 6400 0    60   ~ 0
VBAT
Text Label 8200 6300 0    60   ~ 0
FB
Text Label 8200 6450 0    60   ~ 0
OUT
$Comp
L GND #PWR01
U 1 1 5611B0E5
P 7450 6900
F 0 "#PWR01" H 7450 6900 30  0001 C CNN
F 1 "GND" H 7450 6830 30  0001 C CNN
F 2 "" H 7450 6900 60  0000 C CNN
F 3 "" H 7450 6900 60  0000 C CNN
	1    7450 6900
	1    0    0    -1  
$EndComp
$Comp
L MOS_Pro Q1
U 1 1 5611B0E6
P 5350 6500
F 0 "Q1" H 5350 6650 60  0000 R CNN
F 1 "20V" V 5550 6550 60  0000 R CNN
F 2 "SOT23" H 5350 6500 60  0001 C CNN
F 3 "~" H 5350 6500 60  0000 C CNN
F 4 "Vishay,SQ2301ES-T1-GE3" H 5350 6500 60  0001 C CNN "mfg,mfg"
F 5 "Newark,64T4128" H 5350 6500 60  0001 C CNN "vend1,vend1"
F 6 "Mouser,78-SQ2301ES-T1_GE3" H 5350 6500 60  0001 C CNN "vend2,vend2#"
	1    5350 6500
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 5611B0E7
P 5900 6700
F 0 "R1" V 5980 6700 50  0000 C CNN
F 1 "39k" V 5900 6700 50  0000 C CNN
F 2 "SM0805" V 1530 2600 60  0001 C CNN
F 3 "" H 5900 6700 60  0001 C CNN
F 4 "ECG,ERA6AEB393V" V 1530 2600 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,P39KDACT-ND" V 1530 2600 60  0001 C CNN "vend1,vend1#"
	1    5900 6700
	0    -1   -1   0   
$EndComp
$Comp
L ZENERsmall D1
U 1 1 5611B0E8
P 5650 6500
F 0 "D1" H 5650 6600 40  0000 C CNN
F 1 "7.5V" H 5650 6400 30  0000 C CNN
F 2 "SM1206" H 5650 6500 60  0001 C CNN
F 3 "~" H 5650 6500 60  0000 C CNN
F 4 "diodesinc,BZT52C7V5-7-F" H 5650 6500 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,BZT52C7V5-FDICT-ND" H 5650 6500 60  0001 C CNN "vend1,vend1#"
F 6 "sky-macau.com,5633100308" H 5650 6500 60  0001 C CNN "vend2,vend2#"
	1    5650 6500
	0    -1   -1   0   
$EndComp
$Comp
L FUSE F1
U 1 1 5611B0E9
P 3850 6400
F 0 "F1" H 3950 6450 40  0000 C CNN
F 1 "5A" H 3750 6350 40  0000 C CNN
F 2 "SIL-2" H 3850 6400 60  0001 C CNN
F 3 "~" H 3850 6400 60  0000 C CNN
F 4 "0R,jumperwire" H 3850 6400 60  0001 C CNN "mfg,mfg#"
F 5 "0R,jumperwire" H 3850 6400 60  0001 C CNN "vend1,vend1#"
	1    3850 6400
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D6
U 1 1 5611B0EA
P 8100 6650
F 0 "D6" H 8100 6750 40  0000 C CNN
F 1 "DIODESCH" H 8100 6550 40  0001 C CNN
F 2 "D4" H 8100 6650 60  0001 C CNN
F 3 "~" H 8100 6650 60  0000 C CNN
F 4 "do no populate,DNP" H 8100 6650 60  0001 C CNN "mfg,mfg#"
F 5 "sky-macau.com,1438219496" H 8100 6650 60  0001 C CNN "VEND1,VEND1#"
	1    8100 6650
	0    -1   -1   0   
$EndComp
Text Notes 7700 7150 0    60   ~ 0
ALT DIODE FOR CHINA ASSEMBLER\nLIMITS OUTPUT TO 2.3A
Text Label 4100 6400 0    60   ~ 0
Vf
$Comp
L CP1 C2
U 1 1 5611B0EB
P 9050 6650
F 0 "C2" V 8900 6550 50  0000 L CNN
F 1 "220uF 16V" H 8600 6500 50  0000 L CNN
F 2 "SM2512" H 9050 6650 60  0001 C CNN
F 3 "" H 9050 6650 60  0001 C CNN
F 4 "kemet,T491D227K016AT" H 9050 6650 60  0001 C CNN "MFG,MFG#"
F 5 "DIGI,399-10429-1-ND" H 9050 6650 60  0001 C CNN "VEND1,VEND1#"
F 6 "sky-macau.com,8702041755" H 9050 6650 60  0001 C CNN "vend2,vend2#"
	1    9050 6650
	-1   0    0    -1  
$EndComp
Text HLabel 9650 6450 1    60   Input ~ 0
5V-REG
$Comp
L CP1 C3
U 1 1 5611B0EC
P 9650 6650
F 0 "C3" V 9500 6550 50  0000 L CNN
F 1 "220uF 16V" H 9200 6500 50  0000 L CNN
F 2 "SM2512" H 9650 6650 60  0001 C CNN
F 3 "" H 9650 6650 60  0001 C CNN
F 4 "kemet,T491D227K016AT" H 9650 6650 60  0001 C CNN "MFG,MFG#"
F 5 "DIGI,399-10429-1-ND" H 9650 6650 60  0001 C CNN "VEND1,VEND1#"
F 6 "sky-macau.com,8702041755" H 9650 6650 60  0001 C CNN "vend2,vend2#"
	1    9650 6650
	-1   0    0    -1  
$EndComp
$Comp
L CONN_1 P4
U 1 1 5611B0EE
P 5650 6250
F 0 "P4" H 5730 6250 40  0000 L CNN
F 1 "CONN_1" H 5650 6305 30  0001 C CNN
F 2 "SIL-1" H 5650 6250 60  0001 C CNN
F 3 "" H 5650 6250 60  0000 C CNN
F 4 "dnp,dnp" H 5650 6250 60  0001 C CNN "Field4"
F 5 "dnp,dnp" H 5650 6250 60  0001 C CNN "Field5"
	1    5650 6250
	0    -1   -1   0   
$EndComp
$Comp
L MOS_Nro Q2
U 1 1 5611B0EF
P 4800 6500
F 0 "Q2" H 4800 6350 60  0000 R CNN
F 1 "200V" V 5000 6600 60  0000 R CNN
F 2 "m-pad-2.1-TO-263AB" H 4800 6500 60  0001 C CNN
F 3 "~" H 4800 6500 60  0000 C CNN
F 4 "IXYS,IXTA6N50D2" H 4800 6500 60  0001 C CNN "mfg,mfg#"
F 5 "digikey,IXTA6N50D2-ND" H 4800 6500 60  0001 C CNN "vend1,vend1#"
	1    4800 6500
	0    -1   -1   0   
$EndComp
$Comp
L ZENERsmall D2
U 1 1 5611B0F0
P 4600 6750
F 0 "D2" H 4600 6850 40  0000 C CNN
F 1 "14V" H 4600 6650 30  0000 C CNN
F 2 "D3" H 4600 6750 60  0001 C CNN
F 3 "~" H 4600 6750 60  0000 C CNN
F 4 "FAIRCHILD,1N5244B" H 4600 6750 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,1N5244B-ND" H 4600 6750 60  0001 C CNN "vend1,vend1#"
F 6 " " H 4600 6750 60  0001 C CNN "vend2,vend2#"
	1    4600 6750
	0    -1   -1   0   
$EndComp
$Comp
L R R3
U 1 1 5611B0F1
P 4350 6600
F 0 "R3" V 4430 6600 50  0000 C CNN
F 1 "100k" V 4350 6600 50  0000 C CNN
F 2 "SM0805" V -20 2500 60  0001 C CNN
F 3 "" H 4350 6600 60  0001 C CNN
F 4 "ECG,ERA6AEB104V" V -20 2500 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,P100KDACT-ND" V -20 2500 60  0001 C CNN "vend1,vend1#"
	1    4350 6600
	0    -1   -1   0   
$EndComp
Connection ~ 9050 6850
Connection ~ 7450 6850
Wire Wire Line
	6800 6850 6800 6800
Connection ~ 6800 6850
Wire Wire Line
	8800 6850 8800 6750
Connection ~ 8800 6850
Wire Wire Line
	8400 6750 8400 6600
Wire Wire Line
	8900 6300 8900 6600
Wire Wire Line
	8900 6450 9050 6450
Connection ~ 9050 6450
Connection ~ 6800 6400
Wire Wire Line
	7000 6850 7000 6550
Connection ~ 7000 6850
Wire Wire Line
	8900 6300 7900 6300
Wire Wire Line
	7900 6300 7900 6400
Connection ~ 8900 6450
Wire Wire Line
	10000 6850 10000 6650
Connection ~ 9650 6850
Wire Wire Line
	10000 6450 9650 6450
Wire Wire Line
	7900 6450 7900 6700
Wire Wire Line
	7900 6450 8300 6450
Connection ~ 7900 6550
Connection ~ 8300 6450
Connection ~ 8250 6850
Connection ~ 8350 6850
Connection ~ 9650 6450
Wire Wire Line
	7450 6850 7450 6900
Connection ~ 6350 6400
Wire Wire Line
	6350 6850 6350 6600
Connection ~ 6350 6850
Wire Wire Line
	3500 6850 3500 6600
Wire Wire Line
	6150 6850 6150 6700
Connection ~ 6150 6850
Wire Wire Line
	5650 6700 5350 6700
Wire Wire Line
	3500 6400 3600 6400
Connection ~ 5650 6400
Connection ~ 8100 6450
Connection ~ 8100 6850
Wire Notes Line
	8100 6900 8100 7050
Wire Wire Line
	3500 6850 10000 6850
Wire Wire Line
	4100 6400 4600 6400
Wire Wire Line
	5000 6400 5150 6400
Wire Wire Line
	4100 6600 4100 6400
Connection ~ 4600 6850
Wire Wire Line
	4600 6600 4600 6650
Wire Wire Line
	4700 6700 4800 6700
Wire Wire Line
	4700 6600 4700 6700
$Comp
L ZENERsmall D3
U 1 1 5611B0F3
P 6350 6500
F 0 "D3" H 6350 6600 40  0000 C CNN
F 1 "24V" H 6350 6400 30  0000 C CNN
F 2 "D3" H 6350 6500 60  0001 C CNN
F 3 "~" H 6350 6500 60  0000 C CNN
F 4 "MicroComercial,1N5359B-TP" H 6350 6500 60  0001 C CNN "mfg,mfg#"
F 5 "DIGI,1N5359BTPMSCT-ND" H 6350 6500 60  0001 C CNN "vend1,vend1#"
F 6 "sky-macau.com,0533550982" H 6350 6500 60  0001 C CNN "vend2,vend2#"
	1    6350 6500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6350 6400 6350 6400
Wire Wire Line
	5650 6600 5650 6700
Text Label 5000 6400 0    60   ~ 0
Vs2
Text Label 4700 6600 2    60   ~ 0
Vs1
Wire Wire Line
	4700 6600 4600 6600
Connection ~ 4600 6600
Text Notes 2825 5900 0    60   ~ 0
Brief overview\n-- F1 is a fuse, you should have an up stream fuse at the source, but in the event you over draw this board, this fuse will blow before traces burn off.\n-- Q2, R3, D2 preform an active transient protection. It will suppress voltages up to 200V, down to 19V.\n-- Q1, R1, D1 preform a reverse polarity protection. If the input signal is the wrong polarity, the gate will not conduct which will prevent current from flowing. \n-- L3 is an RF choke\n-- D3 is a second transient suppressor, it would catch faster transients allowing a brief amount of time for Q2 to preform it's duty. \n-- C1 is a bulk cap, it simply stores energy locally such that the regulator can draw large currents in short periods of time. \n-- U1, D6 L1, C2 are a buck style switching regulator, that will pull the 5V line up to 5V.\n-- R2, D5 is a power indicator, which simply shows you have power\n-- L2, C3  is a low pass filter which prevents RF ripple from getting onto the 5V node. 
Text Label 3600 6400 2    60   ~ 0
Vin
Text Label 3500 6600 0    60   ~ 0
GND
$Comp
L INDUCTOR L3
U 1 1 56A0BD42
P 6000 6400
F 0 "L3" V 5950 6400 40  0000 C CNN
F 1 "38uH" V 6100 6400 40  0000 C CNN
F 2 "SM100uH" H 6000 6400 60  0001 C CNN
F 3 "" H 6000 6400 60  0001 C CNN
F 4 "ref_PULSE_ref,ref_PE-54040-S_ref-use-sky-macau-number" V 6000 6400 60  0001 C CNN "MFG,MFG#"
F 5 "sky-macau.com,3817361683" V 6000 6400 60  0001 C CNN "VEND1,VEND1#"
	1    6000 6400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5700 6400 5550 6400
Wire Wire Line
	6300 6400 7000 6400
$Comp
L PWR_FLAG #FLG02
U 1 1 56A0D7DE
P 9650 6850
F 0 "#FLG02" H 9650 6945 30  0001 C CNN
F 1 "PWR_FLAG" H 9650 7030 30  0000 C CNN
F 2 "" H 9650 6850 60  0000 C CNN
F 3 "" H 9650 6850 60  0000 C CNN
	1    9650 6850
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 P5
U 1 1 56A0E175
P 6350 6250
F 0 "P5" H 6430 6250 40  0000 L CNN
F 1 "CONN_1" H 6350 6305 30  0001 C CNN
F 2 "SIL-1" H 6350 6250 60  0001 C CNN
F 3 "" H 6350 6250 60  0000 C CNN
F 4 "dnp,dnp" H 6350 6250 60  0001 C CNN "Field4"
F 5 "dnp,dnp" H 6350 6250 60  0001 C CNN "Field5"
	1    6350 6250
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
