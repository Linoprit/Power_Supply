EESchema Schematic File Version 2
LIBS:Netzteil_Progammable-rescue
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
LIBS:Netzteil_Parts
LIBS:Netzteil_Progammable-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title "Power Supply - Main Supply"
Date "2017-03-06"
Rev "1.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L +5V #PWR25
U 1 1 5027F6B7
P 6900 5400
F 0 "#PWR25" H 6900 5490 20  0001 C CNN
F 1 "+5V" H 6950 5500 30  0000 C CNN
F 2 "" H 6900 5400 60  0001 C CNN
F 3 "" H 6900 5400 60  0001 C CNN
	1    6900 5400
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-Netzteil_Progammable C5
U 1 1 5027F682
P 6450 5800
F 0 "C5" H 6500 5900 50  0000 L CNN
F 1 "100nF" H 6500 5700 50  0000 L CNN
F 2 "" H 6450 5800 60  0001 C CNN
F 3 "" H 6450 5800 60  0001 C CNN
	1    6450 5800
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-Netzteil_Progammable C4
U 1 1 5027F67A
P 5400 5800
F 0 "C4" H 5450 5900 50  0000 L CNN
F 1 "100nF" H 5450 5700 50  0000 L CNN
F 2 "" H 5400 5800 60  0001 C CNN
F 3 "" H 5400 5800 60  0001 C CNN
	1    5400 5800
	1    0    0    -1  
$EndComp
$Comp
L 7805 U2
U 1 1 5027F64E
P 5950 5650
F 0 "U2" H 6100 5454 60  0000 C CNN
F 1 "7805" H 5950 5850 60  0000 C CNN
F 2 "" H 5950 5650 60  0001 C CNN
F 3 "" H 5950 5650 60  0001 C CNN
	1    5950 5650
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-Netzteil_Progammable R9
U 1 1 5027F4F1
P 5650 2200
F 0 "R9" V 5730 2200 50  0000 C CNN
F 1 "0.1/5W" V 5650 2200 50  0000 C CNN
F 2 "" H 5650 2200 60  0001 C CNN
F 3 "" H 5650 2200 60  0001 C CNN
	1    5650 2200
	0    1    1    0   
$EndComp
$Comp
L DIODE D3
U 1 1 5027F436
P 3550 1650
F 0 "D3" H 3550 1750 40  0000 C CNN
F 1 "1N4148" H 3550 1550 40  0000 C CNN
F 2 "" H 3550 1650 60  0001 C CNN
F 3 "" H 3550 1650 60  0001 C CNN
	1    3550 1650
	1    0    0    1   
$EndComp
$Comp
L NPN Q1
U 1 1 5027F1F1
P 3200 2000
F 0 "Q1" H 3200 1850 50  0000 R CNN
F 1 "BC548" H 3200 2150 50  0000 R CNN
F 2 "" H 3200 2000 60  0001 C CNN
F 3 "" H 3200 2000 60  0001 C CNN
	1    3200 2000
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-Netzteil_Progammable R10
U 1 1 502022E2
P 2550 2000
F 0 "R10" V 2630 2000 50  0000 C CNN
F 1 "1k" V 2550 2000 50  0000 C CNN
F 2 "" H 2550 2000 60  0001 C CNN
F 3 "" H 2550 2000 60  0001 C CNN
	1    2550 2000
	0    -1   1    0   
$EndComp
$Comp
L GND-RESCUE-Netzteil_Progammable #PWR21
U 1 1 50201F62
P 5200 2450
F 0 "#PWR21" H 5200 2450 30  0001 C CNN
F 1 "GND" H 5200 2380 30  0001 C CNN
F 2 "" H 5200 2450 60  0001 C CNN
F 3 "" H 5200 2450 60  0001 C CNN
	1    5200 2450
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR18
U 1 1 50201F43
P 3750 1400
F 0 "#PWR18" H 3750 1350 20  0001 C CNN
F 1 "+24V" H 3900 1500 30  0000 C CNN
F 2 "" H 3750 1400 60  0001 C CNN
F 3 "" H 3750 1400 60  0001 C CNN
	1    3750 1400
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P7
U 1 1 50201731
P 7900 2100
F 0 "P7" V 7850 2100 40  0000 C CNN
F 1 "+24_PWR" V 7950 2100 40  0000 C CNN
F 2 "" H 7900 2100 60  0001 C CNN
F 3 "" H 7900 2100 60  0001 C CNN
	1    7900 2100
	1    0    0    -1  
$EndComp
$Comp
L RELAY_1RT K1
U 1 1 50201453
P 2850 1350
F 0 "K1" H 2850 1800 70  0000 C CNN
F 1 "250V/6A/24V" H 2550 1700 70  0000 C CNN
F 2 "" H 2850 1350 60  0001 C CNN
F 3 "" H 2850 1350 60  0001 C CNN
	1    2850 1350
	-1   0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 589D1F88
P 7150 1500
F 0 "#FLG2" H 7150 1595 50  0001 C CNN
F 1 "PWR_FLAG" H 7150 1680 50  0000 C CNN
F 2 "" H 7150 1500 50  0000 C CNN
F 3 "" H 7150 1500 50  0000 C CNN
	1    7150 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 589D4417
P 5950 6100
F 0 "#PWR26" H 5950 5850 50  0001 C CNN
F 1 "GND" H 5950 5950 50  0000 C CNN
F 2 "" H 5950 6100 50  0000 C CNN
F 3 "" H 5950 6100 50  0000 C CNN
	1    5950 6100
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG3
U 1 1 589E4EEB
P 6900 6100
F 0 "#FLG3" H 6900 6195 50  0001 C CNN
F 1 "PWR_FLAG" H 6900 6280 50  0000 C CNN
F 2 "" H 6900 6100 50  0000 C CNN
F 3 "" H 6900 6100 50  0000 C CNN
	1    6900 6100
	-1   0    0    1   
$EndComp
Text GLabel 2100 2000 0    60   Input ~ 0
HI/LO
Text GLabel 7600 2450 2    60   Input ~ 0
I_Sense
$Comp
L DIODE D6
U 1 1 58FF4F3C
P 6600 1900
F 0 "D6" H 6600 2000 40  0000 C CNN
F 1 "1N4002" H 6600 1800 40  0000 C CNN
F 2 "" H 6600 1900 60  0000 C CNN
F 3 "" H 6600 1900 60  0000 C CNN
	1    6600 1900
	0    -1   -1   0   
$EndComp
$Comp
L R R29
U 1 1 58FF4FDD
P 6850 1900
F 0 "R29" V 6930 1900 50  0000 C CNN
F 1 "10k" V 6850 1900 50  0000 C CNN
F 2 "" V 6780 1900 50  0001 C CNN
F 3 "" H 6850 1900 50  0001 C CNN
	1    6850 1900
	1    0    0    -1  
$EndComp
$Comp
L CP C21
U 1 1 58FF5267
P 7150 1900
F 0 "C21" H 7175 2000 50  0000 L CNN
F 1 "22µF/40V" V 7400 1700 50  0000 L CNN
F 2 "" H 7188 1750 50  0001 C CNN
F 3 "" H 7150 1900 50  0001 C CNN
	1    7150 1900
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-Netzteil_Progammable C3
U 1 1 5A627414
P 6950 3750
F 0 "C3" H 7000 3850 50  0000 L CNN
F 1 "100nF" H 7000 3650 50  0000 L CNN
F 2 "" H 6950 3750 60  0001 C CNN
F 3 "" H 6950 3750 60  0001 C CNN
	1    6950 3750
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-Netzteil_Progammable C2
U 1 1 5A62741A
P 5700 3700
F 0 "C2" H 5750 3800 50  0000 L CNN
F 1 "100nF" H 5750 3600 50  0000 L CNN
F 2 "" H 5700 3700 60  0001 C CNN
F 3 "" H 5700 3700 60  0001 C CNN
	1    5700 3700
	1    0    0    -1  
$EndComp
$Comp
L 7805 U5
U 1 1 5A627420
P 6200 3550
F 0 "U5" H 6350 3354 60  0000 C CNN
F 1 "7824" H 6200 3750 60  0000 C CNN
F 2 "" H 6200 3550 60  0001 C CNN
F 3 "" H 6200 3550 60  0001 C CNN
	1    6200 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR24
U 1 1 5A62742C
P 6200 4600
F 0 "#PWR24" H 6200 4350 50  0001 C CNN
F 1 "GND" H 6200 4450 50  0000 C CNN
F 2 "" H 6200 4600 50  0000 C CNN
F 3 "" H 6200 4600 50  0000 C CNN
	1    6200 4600
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 J1
U 1 1 5A6297BB
P 1100 3450
F 0 "J1" H 1100 3650 50  0000 C CNN
F 1 "from Trafo" V 1200 3450 50  0000 C CNN
F 2 "" H 1100 3450 50  0001 C CNN
F 3 "" H 1100 3450 50  0001 C CNN
	1    1100 3450
	-1   0    0    -1  
$EndComp
Text Notes 900  3150 0    60   ~ 0
Trafo\n1 = 24V AC\n2 = 12V AC\n3 = 24V AC
$Comp
L D_Bridge_-A+A D1
U 1 1 5A62E70D
P 4650 1650
F 0 "D1" H 4700 1925 50  0000 L CNN
F 1 "10A" H 4700 1850 50  0000 L CNN
F 2 "" H 4650 1650 50  0001 C CNN
F 3 "" H 4650 1650 50  0001 C CNN
	1    4650 1650
	1    0    0    -1  
$EndComp
$Comp
L D_Bridge_-A+A D8
U 1 1 5A62F059
P 4350 5600
F 0 "D8" H 4400 5875 50  0000 L CNN
F 1 "500mA" H 4400 5800 50  0000 L CNN
F 2 "" H 4350 5600 50  0001 C CNN
F 3 "" H 4350 5600 50  0001 C CNN
	1    4350 5600
	1    0    0    -1  
$EndComp
$Comp
L D_Bridge_-A+A D4
U 1 1 5A62F7A9
P 4600 3500
F 0 "D4" H 4650 3775 50  0000 L CNN
F 1 "1500mA" H 4650 3700 50  0000 L CNN
F 2 "" H 4600 3500 50  0001 C CNN
F 3 "" H 4600 3500 50  0001 C CNN
	1    4600 3500
	1    0    0    -1  
$EndComp
$Comp
L +VSW #PWR19
U 1 1 5A63694C
P 7550 1500
F 0 "#PWR19" H 7550 1350 50  0001 C CNN
F 1 "+VSW" H 7550 1640 50  0000 C CNN
F 2 "" H 7550 1500 50  0001 C CNN
F 3 "" H 7550 1500 50  0001 C CNN
	1    7550 1500
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-Netzteil_Progammable #PWR20
U 1 1 5A637EA5
P 3300 2400
F 0 "#PWR20" H 3300 2400 30  0001 C CNN
F 1 "GND" H 3300 2330 30  0001 C CNN
F 2 "" H 3300 2400 60  0001 C CNN
F 3 "" H 3300 2400 60  0001 C CNN
	1    3300 2400
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 5A638D9C
P 5200 1900
F 0 "C1" H 5225 2000 50  0000 L CNN
F 1 "4700µF/40V" V 5400 1650 50  0000 L CNN
F 2 "" H 5238 1750 50  0001 C CNN
F 3 "" H 5200 1900 50  0001 C CNN
	1    5200 1900
	1    0    0    -1  
$EndComp
Text GLabel 1500 3650 2    60   Output ~ 0
24VAC_Lo
Text GLabel 4550 2450 0    60   Input ~ 0
24AC_Lo
Text GLabel 1500 3450 2    60   Output ~ 0
12VAC
Text GLabel 1500 3250 2    60   Output ~ 0
24VAC_Hi
Text GLabel 2250 1300 0    60   Input ~ 0
24VAC_Hi
Text GLabel 2150 1100 0    60   Input ~ 0
12VAC
Text GLabel 4050 3100 0    60   Input ~ 0
24VAC_Hi
Text GLabel 4050 4000 0    60   Input ~ 0
24VAC_Lo
Text GLabel 4050 6150 0    60   Input ~ 0
24VAC_Lo
Text GLabel 3900 5200 0    60   Input ~ 0
12VAC
$Comp
L CP C24
U 1 1 5A63C3F1
P 5200 4000
F 0 "C24" H 5225 4100 50  0000 L CNN
F 1 "1000µF/40V" V 5350 3800 50  0000 L CNN
F 2 "" H 5238 3850 50  0001 C CNN
F 3 "" H 5200 4000 50  0001 C CNN
	1    5200 4000
	1    0    0    -1  
$EndComp
$Comp
L CP C23
U 1 1 5A63C4BC
P 7450 3950
F 0 "C23" H 7475 4050 50  0000 L CNN
F 1 "47µF/40V" V 7600 3750 50  0000 L CNN
F 2 "" H 7488 3800 50  0001 C CNN
F 3 "" H 7450 3950 50  0001 C CNN
	1    7450 3950
	1    0    0    -1  
$EndComp
$Comp
L CP C25
U 1 1 5A63DEB6
P 4900 5800
F 0 "C25" H 4925 5900 50  0000 L CNN
F 1 "1000µF/40V" V 5050 5600 50  0000 L CNN
F 2 "" H 4938 5650 50  0001 C CNN
F 3 "" H 4900 5800 50  0001 C CNN
	1    4900 5800
	1    0    0    -1  
$EndComp
$Comp
L CP C26
U 1 1 5A63DF6D
P 6900 5800
F 0 "C26" H 6925 5900 50  0000 L CNN
F 1 "47µF/40V" V 7050 5600 50  0000 L CNN
F 2 "" H 6938 5650 50  0001 C CNN
F 3 "" H 6900 5800 50  0001 C CNN
	1    6900 5800
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-Netzteil_Progammable R30
U 1 1 5A64133C
P 6700 3750
F 0 "R30" V 6780 3750 50  0000 C CNN
F 1 "390" V 6700 3750 50  0000 C CNN
F 2 "" H 6700 3750 60  0001 C CNN
F 3 "" H 6700 3750 60  0001 C CNN
	1    6700 3750
	-1   0    0    -1  
$EndComp
Text Notes 6500 4150 0    60   ~ 0
390-560 Ohm
$Comp
L POT 1k1
U 1 1 5A6415E3
P 6200 4250
F 0 "1k1" V 6025 4250 50  0000 C CNN
F 1 "POT" V 6100 4250 50  0000 C CNN
F 2 "" H 6200 4250 50  0001 C CNN
F 3 "" H 6200 4250 50  0001 C CNN
	1    6200 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 5600 4900 5600
Wire Wire Line
	4900 5600 5400 5600
Wire Wire Line
	5400 5600 5550 5600
Connection ~ 4900 5600
Connection ~ 5950 6000
Wire Wire Line
	5950 5900 5950 6000
Wire Wire Line
	5950 6000 5950 6100
Connection ~ 5400 5600
Wire Wire Line
	4300 2200 5200 2200
Wire Wire Line
	5200 2200 5400 2200
Connection ~ 5200 2200
Wire Wire Line
	5200 2050 5200 2200
Wire Wire Line
	5200 2200 5200 2450
Wire Wire Line
	3000 2000 2800 2000
Wire Wire Line
	3300 1500 3300 1650
Wire Wire Line
	3300 1650 3300 1800
Wire Wire Line
	3300 2400 3300 2200
Wire Wire Line
	2300 2000 2100 2000
Wire Wire Line
	5900 2200 6600 2200
Wire Wire Line
	6600 2200 6600 2200
Wire Wire Line
	6600 2200 6850 2200
Wire Wire Line
	6850 2200 7150 2200
Wire Wire Line
	7150 2200 7550 2200
Wire Wire Line
	7600 2450 6600 2450
Wire Wire Line
	6600 2450 6600 2200
Wire Wire Line
	4050 6000 4900 6000
Wire Wire Line
	4900 6000 5400 6000
Wire Wire Line
	5400 6000 5950 6000
Wire Wire Line
	5950 6000 6450 6000
Wire Wire Line
	6450 6000 6900 6000
Connection ~ 6900 6000
Wire Wire Line
	6350 5600 6450 5600
Wire Wire Line
	6450 5600 6900 5600
Connection ~ 5400 6000
Wire Wire Line
	5400 5200 5400 5600
Wire Wire Line
	7150 1500 7150 1650
Wire Wire Line
	7150 1650 7150 1750
Wire Wire Line
	6900 5950 6900 6000
Wire Wire Line
	6900 6000 6900 6100
Wire Wire Line
	7550 1500 7550 1650
Wire Wire Line
	7550 1650 7550 2000
Connection ~ 7150 1650
Wire Wire Line
	6850 1650 6850 1750
Connection ~ 6850 1650
Wire Wire Line
	6600 1650 6600 1700
Connection ~ 6600 1650
Wire Wire Line
	6600 2100 6600 2200
Connection ~ 6600 2200
Wire Wire Line
	6850 2050 6850 2200
Connection ~ 6850 2200
Wire Wire Line
	7150 2200 7150 2050
Connection ~ 7150 2200
Connection ~ 6450 5600
Connection ~ 6450 6000
Connection ~ 4900 6000
Connection ~ 5200 3500
Wire Wire Line
	4900 3500 5200 3500
Wire Wire Line
	5200 3500 5700 3500
Wire Wire Line
	5700 3500 5800 3500
Connection ~ 6200 4400
Wire Wire Line
	6050 4400 6200 4400
Wire Wire Line
	6200 4400 6200 4500
Wire Wire Line
	6200 4500 6200 4600
Connection ~ 5700 3500
Wire Wire Line
	7450 3500 7450 3800
Wire Wire Line
	4250 3500 4250 4500
Wire Wire Line
	6600 3500 6700 3500
Wire Wire Line
	6700 3500 6950 3500
Wire Wire Line
	6950 3500 7450 3500
Wire Wire Line
	7450 3500 7800 3500
Wire Wire Line
	7800 3500 7900 3500
Connection ~ 7450 3500
Connection ~ 5200 4500
Wire Wire Line
	4050 6000 4050 5600
Wire Wire Line
	4250 3500 4300 3500
Connection ~ 7550 1650
Wire Wire Line
	5200 1750 5200 1650
Connection ~ 5200 1650
Wire Wire Line
	4950 1650 5200 1650
Wire Wire Line
	5200 1650 6600 1650
Wire Wire Line
	6600 1650 6850 1650
Wire Wire Line
	6850 1650 7150 1650
Wire Wire Line
	7150 1650 7550 1650
Wire Wire Line
	4350 1650 4300 1650
Wire Wire Line
	4300 1650 4300 2200
Wire Wire Line
	4650 1350 4650 1200
Wire Wire Line
	4650 1200 3300 1200
Wire Wire Line
	2150 1100 2500 1100
Wire Wire Line
	3300 1400 3750 1400
Wire Wire Line
	3750 1400 3750 1650
Wire Wire Line
	3300 1650 3350 1650
Connection ~ 3750 1400
Connection ~ 3300 1650
Wire Wire Line
	1300 3550 1300 3650
Wire Wire Line
	1300 3650 1500 3650
Wire Wire Line
	4650 1950 4650 2450
Wire Wire Line
	4650 2450 4550 2450
Wire Wire Line
	1300 3450 1500 3450
Wire Wire Line
	1300 3350 1300 3250
Wire Wire Line
	1300 3250 1500 3250
Wire Wire Line
	2250 1300 2500 1300
Wire Wire Line
	4600 3200 4600 3100
Wire Wire Line
	4600 3100 4050 3100
Wire Wire Line
	4600 3800 4600 4000
Wire Wire Line
	4600 4000 4050 4000
Wire Wire Line
	4350 5300 4350 5200
Wire Wire Line
	4350 5200 3900 5200
Wire Wire Line
	4350 5900 4350 6150
Wire Wire Line
	4350 6150 4050 6150
Wire Wire Line
	7450 4500 7450 4100
Wire Wire Line
	5200 4150 5200 4500
Wire Wire Line
	5200 3850 5200 3500
Wire Wire Line
	4900 5950 4900 6000
Wire Wire Line
	4900 5650 4900 5600
Wire Wire Line
	6700 3500 6700 3500
Connection ~ 6700 3500
Wire Wire Line
	6050 4250 6050 4400
Wire Wire Line
	6200 3800 6200 4000
Wire Wire Line
	6200 4000 6200 4100
Wire Wire Line
	5700 4000 6200 4000
Wire Wire Line
	6200 4000 6700 4000
Wire Wire Line
	6700 4000 6950 4000
Connection ~ 6200 4000
Wire Wire Line
	6950 4000 6950 3950
Connection ~ 6700 4000
Wire Wire Line
	5700 3900 5700 4000
Wire Wire Line
	4250 4500 5200 4500
Wire Wire Line
	5200 4500 6200 4500
Wire Wire Line
	6200 4500 7450 4500
Connection ~ 6200 4500
Wire Wire Line
	6950 3550 6950 3500
Connection ~ 6950 3500
Text GLabel 7900 3350 2    60   Output ~ 0
+30V_FAN
Text GLabel 7900 3500 2    60   Output ~ 0
+30V_OPV
Wire Wire Line
	7900 3350 7800 3350
Wire Wire Line
	7800 3350 7800 3500
Connection ~ 7800 3500
$Comp
L CONN_01X08 P1
U 1 1 5A647847
P 9600 3700
F 0 "P1" H 9600 4150 50  0000 C CNN
F 1 "Power Board" V 9700 3700 50  0000 C CNN
F 2 "" H 9600 3700 50  0001 C CNN
F 3 "" H 9600 3700 50  0000 C CNN
	1    9600 3700
	-1   0    0    -1  
$EndComp
Text Notes 9500 3100 0    60   ~ 0
Power\n1 = HI/LO\n2 = +30V_OPV\n3 = +5\n4 = GND\n5 = I_Sense\n6 = GND\n7 = U_Sense*\n8 = +30_FAN\n* U_Sense is connected\nto U_out from Endstufe
Text GLabel 10000 3750 2    60   Input ~ 0
I_Sense
Wire Wire Line
	9800 3750 10000 3750
$Comp
L GND #PWR23
U 1 1 5A647851
P 10550 3950
F 0 "#PWR23" H 10550 3700 50  0001 C CNN
F 1 "GND" H 10550 3800 50  0000 C CNN
F 2 "" H 10550 3950 50  0000 C CNN
F 3 "" H 10550 3950 50  0000 C CNN
	1    10550 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 3850 10550 3850
Wire Wire Line
	10550 3650 10550 3850
Wire Wire Line
	10550 3850 10550 3950
Wire Wire Line
	9800 3650 10550 3650
Connection ~ 10550 3850
Text GLabel 10000 3950 2    60   Input ~ 0
U_Sense
Wire Wire Line
	10000 3950 9800 3950
$Comp
L +5V #PWR22
U 1 1 5A64785D
P 10550 3550
F 0 "#PWR22" H 10550 3640 20  0001 C CNN
F 1 "+5V" H 10550 3700 30  0000 C CNN
F 2 "" H 10550 3550 60  0001 C CNN
F 3 "" H 10550 3550 60  0001 C CNN
	1    10550 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 3550 10550 3550
Wire Wire Line
	9800 3450 9900 3450
Text GLabel 10100 3300 2    60   Output ~ 0
HI/LO
Wire Wire Line
	9800 3350 10100 3300
Wire Wire Line
	9800 4050 9900 4100
Text GLabel 9900 4100 2    60   Input ~ 0
+30V_FAN
Text GLabel 9900 3450 2    60   Input ~ 0
+30V_OPV
$Comp
L DIODE D2
U 1 1 5A64BEDC
P 6200 3100
F 0 "D2" H 6200 3200 40  0000 C CNN
F 1 "1N4148" H 6200 3000 40  0000 C CNN
F 2 "" H 6200 3100 60  0000 C CNN
F 3 "" H 6200 3100 60  0000 C CNN
	1    6200 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	6400 3100 6700 3100
Wire Wire Line
	6700 3100 6700 3500
Wire Wire Line
	6000 3100 5700 3100
Wire Wire Line
	5700 3100 5700 3500
$Comp
L DIODE D7
U 1 1 5A64C33C
P 5950 5200
F 0 "D7" H 5950 5300 40  0000 C CNN
F 1 "1N4148" H 5950 5100 40  0000 C CNN
F 2 "" H 5950 5200 60  0000 C CNN
F 3 "" H 5950 5200 60  0000 C CNN
	1    5950 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	6450 5200 6150 5200
Wire Wire Line
	5400 5200 5750 5200
Wire Wire Line
	6450 5200 6450 5600
Connection ~ 6900 5600
Wire Wire Line
	6900 5400 6900 5600
Wire Wire Line
	6900 5600 6900 5650
$EndSCHEMATC
