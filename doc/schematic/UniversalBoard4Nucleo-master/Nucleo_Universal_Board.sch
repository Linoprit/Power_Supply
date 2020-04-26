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
LIBS:noritsuna
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Nucleo F303 Board (STM32 RET6)"
Date "2016-05-26"
Rev "1.0"
Comp "SIProp.org: Noritsuna Imamura noritsuna@siprop.org"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_02X19 CN7
U 1 1 5745A3EA
P 3500 3550
F 0 "CN7" H 3500 4550 50  0000 C CNN
F 1 "CONN_02X19" V 3500 3550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x19" H 3500 2550 50  0001 C CNN
F 3 "" H 3500 2550 50  0000 C CNN
	1    3500 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X19 CN10
U 1 1 5745A41F
P 8000 3550
F 0 "CN10" H 8000 4550 50  0000 C CNN
F 1 "CONN_02X19" V 8000 3550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x19" H 8000 2550 50  0001 C CNN
F 3 "" H 8000 2550 50  0000 C CNN
	1    8000 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 CN6
U 1 1 5745A4A1
P 5550 3400
F 0 "CN6" H 5550 3850 50  0000 C CNN
F 1 "CONN_01X08" V 5650 3400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 5550 3400 50  0001 C CNN
F 3 "" H 5550 3400 50  0000 C CNN
	1    5550 3400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 CN8
U 1 1 5745A54E
P 5550 4200
F 0 "CN8" H 5550 4550 50  0000 C CNN
F 1 "CONN_01X06" V 5650 4200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06" H 5550 4200 50  0001 C CNN
F 3 "" H 5550 4200 50  0000 C CNN
	1    5550 4200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 CN5
U 1 1 5745A5D3
P 6750 3100
F 0 "CN5" H 6750 3650 50  0000 C CNN
F 1 "CONN_01X10" V 6850 3100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 6750 3100 50  0001 C CNN
F 3 "" H 6750 3100 50  0000 C CNN
	1    6750 3100
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X08 CN9
U 1 1 5745A666
P 6750 4100
F 0 "CN9" H 6750 4550 50  0000 C CNN
F 1 "CONN_01X08" V 6850 4100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 6750 4100 50  0001 C CNN
F 3 "" H 6750 4100 50  0000 C CNN
	1    6750 4100
	-1   0    0    1   
$EndComp
Text Label 3000 2650 0    60   ~ 0
PC10
Text Label 3000 2750 0    60   ~ 0
PC12
Text Label 3000 2850 0    60   ~ 0
VDD
Text Label 3000 2950 0    60   ~ 0
BOOT0
Text Label 3000 3250 0    60   ~ 0
PA13
Text Label 3000 3350 0    60   ~ 0
PA14
Text Label 3000 3450 0    60   ~ 0
PA15
Text Label 3000 3550 0    60   ~ 0
GND
Text Label 3000 3650 0    60   ~ 0
PB7
Text Label 3000 3750 0    60   ~ 0
PC13
Text Label 3000 3850 0    60   ~ 0
PC14
Text Label 3000 3950 0    60   ~ 0
PC15
Text Label 3000 4050 0    60   ~ 0
PF0
Text Label 3000 4150 0    60   ~ 0
PF1
Text Label 3000 4250 0    60   ~ 0
VBAT
Text Label 3000 4350 0    60   ~ 0
PC2
Text Label 3000 4450 0    60   ~ 0
PC3
Text Label 3750 2650 0    60   ~ 0
PC11
Text Label 3750 2750 0    60   ~ 0
PD2
Text Label 3750 2850 0    60   ~ 0
E5V
Text Label 3750 2950 0    60   ~ 0
GND
Text Label 3750 3150 0    60   ~ 0
IOREF
Text Label 3750 3250 0    60   ~ 0
RES
Text Label 3750 3350 0    60   ~ 0
+3V3
Text Label 3750 3450 0    60   ~ 0
+5
Text Label 3750 3550 0    60   ~ 0
GND
Text Label 3750 3650 0    60   ~ 0
GND
Text Label 3750 3750 0    60   ~ 0
VIN
Text Label 3750 3850 0    60   ~ 0
NC
Text Label 3750 3950 0    60   ~ 0
PA0
Text Label 3750 4050 0    60   ~ 0
PA1
Text Label 3750 4150 0    60   ~ 0
PA4
Text Label 3750 4250 0    60   ~ 0
PB0
Text Label 3750 4350 0    60   ~ 0
PC1
Text Label 3750 4450 0    60   ~ 0
PC0
Text Label 5150 3150 0    60   ~ 0
IOREF
Text Label 5150 3250 0    60   ~ 0
RES
Text Label 5150 3350 0    60   ~ 0
+3V3
Text Label 5150 3450 0    60   ~ 0
+5V
Text Label 5150 3550 0    60   ~ 0
GND
Text Label 5150 3650 0    60   ~ 0
GND
Text Label 5150 3750 0    60   ~ 0
VIN
Text Label 5150 3950 0    60   ~ 0
PA0
Text Label 5150 4050 0    60   ~ 0
PA1
Text Label 5150 4150 0    60   ~ 0
PA4
Text Label 5150 4250 0    60   ~ 0
PB0
Text Label 5150 4350 0    60   ~ 0
PC1
Text Label 5150 4450 0    60   ~ 0
PC0
Entry Wire Line
	2900 2550 3000 2650
Entry Wire Line
	2900 2650 3000 2750
Entry Wire Line
	2900 2750 3000 2850
Entry Wire Line
	2900 2850 3000 2950
Entry Wire Line
	2900 3150 3000 3250
Entry Wire Line
	2900 3250 3000 3350
Entry Wire Line
	2900 3350 3000 3450
Entry Wire Line
	2900 3450 3000 3550
Entry Wire Line
	2900 3550 3000 3650
Entry Wire Line
	2900 3650 3000 3750
Entry Wire Line
	2900 3750 3000 3850
Entry Wire Line
	2900 3850 3000 3950
Entry Wire Line
	2900 3950 3000 4050
Entry Wire Line
	2900 4050 3000 4150
Entry Wire Line
	2900 4150 3000 4250
Entry Wire Line
	2900 4250 3000 4350
Entry Wire Line
	2900 4350 3000 4450
Entry Wire Line
	4000 2650 4100 2750
Entry Wire Line
	4000 2750 4100 2850
Entry Wire Line
	4000 2850 4100 2950
Entry Wire Line
	4000 2950 4100 3050
Entry Wire Line
	4000 3150 4100 3250
Entry Wire Line
	4000 3250 4100 3350
Entry Wire Line
	4000 3350 4100 3450
Entry Wire Line
	4000 3450 4100 3550
Entry Wire Line
	4000 3550 4100 3650
Entry Wire Line
	4000 3650 4100 3750
Entry Wire Line
	4000 3750 4100 3850
Entry Wire Line
	4000 3950 4100 4050
Entry Wire Line
	4000 4050 4100 4150
Entry Wire Line
	4000 4150 4100 4250
Entry Wire Line
	4000 4250 4100 4350
Entry Wire Line
	4000 4350 4100 4450
Entry Wire Line
	4000 4450 4100 4550
Entry Wire Line
	5050 3050 5150 3150
Entry Wire Line
	5050 3150 5150 3250
Entry Wire Line
	5050 3250 5150 3350
Entry Wire Line
	5050 3350 5150 3450
Entry Wire Line
	5050 3450 5150 3550
Entry Wire Line
	5050 3550 5150 3650
Entry Wire Line
	5050 3650 5150 3750
Entry Wire Line
	5050 3850 5150 3950
Entry Wire Line
	5050 3950 5150 4050
Entry Wire Line
	5050 4050 5150 4150
Entry Wire Line
	5050 4150 5150 4250
Entry Wire Line
	5050 4250 5150 4350
Entry Wire Line
	5050 4350 5150 4450
Entry Bus Bus
	4100 4850 4200 4950
Text Label 8250 2650 0    60   ~ 0
PC8
Text Label 8250 2750 0    60   ~ 0
PC6
Text Label 8250 2850 0    60   ~ 0
PC5
Text Label 8250 2950 0    60   ~ 0
U5V
Text Label 8250 3150 0    60   ~ 0
PA12
Text Label 8250 3250 0    60   ~ 0
PA11
Text Label 8250 3350 0    60   ~ 0
PB12
Text Label 8250 3450 0    60   ~ 0
PB11
Text Label 8250 3550 0    60   ~ 0
GND
Text Label 8250 3650 0    60   ~ 0
PB2
Text Label 8250 3750 0    60   ~ 0
PB1
Text Label 8250 3850 0    60   ~ 0
PB15
Text Label 8250 3950 0    60   ~ 0
PB14
Text Label 8250 4050 0    60   ~ 0
PB13
Text Label 8250 4150 0    60   ~ 0
AGND
Text Label 8250 4250 0    60   ~ 0
PC4
Text Label 7500 2650 0    60   ~ 0
PC9
Text Label 7500 2750 0    60   ~ 0
PB8
Text Label 7500 2850 0    60   ~ 0
PB9
Text Label 7500 2950 0    60   ~ 0
AVDD
Text Label 7500 3050 0    60   ~ 0
GND
Text Label 7500 3150 0    60   ~ 0
PA5
Text Label 7500 3250 0    60   ~ 0
PA6
Text Label 7500 3350 0    60   ~ 0
PA7
Text Label 7500 3450 0    60   ~ 0
PB6
Text Label 7500 3550 0    60   ~ 0
PC7
Text Label 7500 3650 0    60   ~ 0
PA9
Text Label 7500 3750 0    60   ~ 0
PA8
Text Label 7500 3850 0    60   ~ 0
PB10
Text Label 7500 3950 0    60   ~ 0
PB4
Text Label 7500 4050 0    60   ~ 0
PB5
Text Label 7500 4150 0    60   ~ 0
PB3
Text Label 7500 4250 0    60   ~ 0
PA10
Text Label 7500 4350 0    60   ~ 0
PA2
Text Label 7500 4450 0    60   ~ 0
PA3
Text Label 6950 2650 0    60   ~ 0
PB8
Text Label 6950 2750 0    60   ~ 0
PB9
Text Label 6950 2850 0    60   ~ 0
AVDD
Text Label 6950 2950 0    60   ~ 0
GND
Text Label 6950 3050 0    60   ~ 0
PA5
Text Label 6950 3150 0    60   ~ 0
PA6
Text Label 6950 3250 0    60   ~ 0
PA7
Text Label 6950 3350 0    60   ~ 0
PB6
Text Label 6950 3450 0    60   ~ 0
PC7
Text Label 6950 3550 0    60   ~ 0
PA9
Text Label 6950 3750 0    60   ~ 0
PA8
Text Label 6950 3850 0    60   ~ 0
PB10
Text Label 6950 3950 0    60   ~ 0
PB4
Text Label 6950 4050 0    60   ~ 0
PB5
Text Label 6950 4150 0    60   ~ 0
PB3
Text Label 6950 4250 0    60   ~ 0
PA10
Text Label 6950 4350 0    60   ~ 0
PA2
Text Label 6950 4450 0    60   ~ 0
PA3
Entry Wire Line
	7200 2650 7300 2750
Entry Wire Line
	7200 2750 7300 2850
Entry Wire Line
	7200 2850 7300 2950
Entry Wire Line
	7200 2950 7300 3050
Entry Wire Line
	7200 3050 7300 3150
Entry Wire Line
	7200 3150 7300 3250
Entry Wire Line
	7200 3250 7300 3350
Entry Wire Line
	7200 3350 7300 3450
Entry Wire Line
	7200 3450 7300 3550
Entry Wire Line
	7200 3550 7300 3650
Entry Wire Line
	7200 3750 7300 3850
Entry Wire Line
	7200 3850 7300 3950
Entry Wire Line
	7200 3950 7300 4050
Entry Wire Line
	7200 4050 7300 4150
Entry Wire Line
	7200 4150 7300 4250
Entry Wire Line
	7200 4250 7300 4350
Entry Wire Line
	7200 4350 7300 4450
Entry Wire Line
	7200 4450 7300 4550
Entry Wire Line
	7400 2550 7500 2650
Entry Wire Line
	7400 2650 7500 2750
Entry Wire Line
	7400 2750 7500 2850
Entry Wire Line
	7400 2850 7500 2950
Entry Wire Line
	7400 2950 7500 3050
Entry Wire Line
	7400 3050 7500 3150
Entry Wire Line
	7400 3150 7500 3250
Entry Wire Line
	7400 3250 7500 3350
Entry Wire Line
	7400 3350 7500 3450
Entry Wire Line
	7400 3450 7500 3550
Entry Wire Line
	7400 3550 7500 3650
Entry Wire Line
	7400 3650 7500 3750
Entry Wire Line
	7400 3750 7500 3850
Entry Wire Line
	7400 3850 7500 3950
Entry Wire Line
	7400 3950 7500 4050
Entry Wire Line
	7400 4050 7500 4150
Entry Wire Line
	7400 4150 7500 4250
Entry Wire Line
	7400 4250 7500 4350
Entry Wire Line
	7400 4350 7500 4450
Entry Wire Line
	8600 2650 8700 2750
Entry Wire Line
	8600 2750 8700 2850
Entry Wire Line
	8600 2850 8700 2950
Entry Wire Line
	8600 2950 8700 3050
Entry Wire Line
	8600 3150 8700 3250
Entry Wire Line
	8600 3250 8700 3350
Entry Wire Line
	8600 3350 8700 3450
Entry Wire Line
	8600 3450 8700 3550
Entry Wire Line
	8600 3550 8700 3650
Entry Wire Line
	8600 3650 8700 3750
Entry Wire Line
	8600 3750 8700 3850
Entry Wire Line
	8600 3850 8700 3950
Entry Wire Line
	8600 3950 8700 4050
Entry Wire Line
	8600 4050 8700 4150
Entry Wire Line
	8600 4150 8700 4250
Entry Wire Line
	8600 4250 8700 4350
Entry Bus Bus
	7300 4850 7400 4950
Entry Bus Bus
	7400 4850 7500 4950
Wire Bus Line
	7400 2550 7400 4850
Wire Bus Line
	7300 2750 7300 4850
Wire Bus Line
	8700 4950 8700 2750
Wire Wire Line
	8250 4250 8600 4250
Wire Wire Line
	8250 4150 8600 4150
Wire Wire Line
	8250 4050 8600 4050
Wire Wire Line
	8250 3950 8600 3950
Wire Wire Line
	8250 3850 8600 3850
Wire Wire Line
	8250 3750 8600 3750
Wire Wire Line
	8250 3650 8600 3650
Wire Wire Line
	8250 3550 8600 3550
Wire Wire Line
	8250 3450 8600 3450
Wire Wire Line
	8250 3350 8600 3350
Wire Wire Line
	8250 3250 8600 3250
Wire Wire Line
	8250 3150 8600 3150
Wire Wire Line
	8250 2950 8600 2950
Wire Wire Line
	8250 2850 8600 2850
Wire Wire Line
	8250 2750 8600 2750
Wire Wire Line
	8250 2650 8600 2650
Wire Wire Line
	7750 4450 7500 4450
Wire Wire Line
	7750 4350 7500 4350
Wire Wire Line
	7750 4250 7500 4250
Wire Wire Line
	7750 4150 7500 4150
Wire Wire Line
	7750 4050 7500 4050
Wire Wire Line
	7750 3950 7500 3950
Wire Wire Line
	7750 3850 7500 3850
Wire Wire Line
	7750 3750 7500 3750
Wire Wire Line
	7750 3650 7500 3650
Wire Wire Line
	7750 3550 7500 3550
Wire Wire Line
	7750 3450 7500 3450
Wire Wire Line
	7750 3350 7500 3350
Wire Wire Line
	7750 3250 7500 3250
Wire Wire Line
	7750 3150 7500 3150
Wire Wire Line
	7750 3050 7500 3050
Wire Wire Line
	7750 2950 7500 2950
Wire Wire Line
	7750 2850 7500 2850
Wire Wire Line
	7750 2750 7500 2750
Wire Wire Line
	6950 4450 7200 4450
Wire Wire Line
	6950 4350 7200 4350
Wire Wire Line
	6950 4250 7200 4250
Wire Wire Line
	6950 4150 7200 4150
Wire Wire Line
	6950 4050 7200 4050
Wire Wire Line
	6950 3950 7200 3950
Wire Wire Line
	6950 3850 7200 3850
Wire Wire Line
	6950 3750 7200 3750
Wire Wire Line
	6950 3550 7200 3550
Wire Wire Line
	6950 3450 7200 3450
Wire Wire Line
	6950 3350 7200 3350
Wire Wire Line
	6950 3250 7200 3250
Wire Wire Line
	6950 3150 7200 3150
Wire Wire Line
	6950 3050 7200 3050
Wire Wire Line
	6950 2950 7200 2950
Wire Wire Line
	6950 2850 7200 2850
Wire Wire Line
	6950 2750 7200 2750
Wire Wire Line
	7750 2650 7500 2650
Wire Wire Line
	6950 2650 7200 2650
Wire Bus Line
	5050 2950 5050 4850
Wire Bus Line
	4100 2750 4100 4850
Wire Bus Line
	2900 2550 2900 4950
Wire Wire Line
	5350 4450 5150 4450
Wire Wire Line
	5350 4350 5150 4350
Wire Wire Line
	5350 4250 5150 4250
Wire Wire Line
	5350 4150 5150 4150
Wire Wire Line
	5350 4050 5150 4050
Wire Wire Line
	5350 3950 5150 3950
Wire Wire Line
	5350 3750 5150 3750
Wire Wire Line
	5350 3650 5150 3650
Wire Wire Line
	5350 3550 5150 3550
Wire Wire Line
	5350 3450 5150 3450
Wire Wire Line
	5350 3350 5150 3350
Wire Wire Line
	5350 3150 5150 3150
Wire Wire Line
	3750 4450 4000 4450
Wire Wire Line
	3750 4350 4000 4350
Wire Wire Line
	3750 4250 4000 4250
Wire Wire Line
	3750 4150 4000 4150
Wire Wire Line
	3750 4050 4000 4050
Wire Wire Line
	3750 3950 4000 3950
Wire Wire Line
	3750 3750 4000 3750
Wire Wire Line
	3750 3650 4000 3650
Wire Wire Line
	3750 3550 4000 3550
Wire Wire Line
	3750 3450 4000 3450
Wire Wire Line
	3750 3350 4000 3350
Wire Wire Line
	3750 3250 4000 3250
Wire Wire Line
	3750 3150 4000 3150
Wire Wire Line
	3750 2950 4000 2950
Wire Wire Line
	3750 2850 4000 2850
Wire Wire Line
	3750 2750 4000 2750
Wire Wire Line
	3750 2650 4000 2650
Wire Wire Line
	3250 4450 3000 4450
Wire Wire Line
	3250 4350 3000 4350
Wire Wire Line
	3250 4250 3000 4250
Wire Wire Line
	3250 4150 3000 4150
Wire Wire Line
	3250 4050 3000 4050
Wire Wire Line
	3250 3950 3000 3950
Wire Wire Line
	3250 3850 3000 3850
Wire Wire Line
	3250 3750 3000 3750
Wire Wire Line
	3250 3650 3000 3650
Wire Wire Line
	3250 3550 3000 3550
Wire Wire Line
	3250 3450 3000 3450
Wire Wire Line
	3250 3350 3000 3350
Wire Wire Line
	3250 3250 3000 3250
Wire Wire Line
	3250 2950 3000 2950
Wire Wire Line
	3250 2850 3000 2850
Wire Wire Line
	3250 2750 3000 2750
Wire Wire Line
	3250 2650 3000 2650
Wire Wire Line
	5150 3250 5350 3250
Wire Bus Line
	2900 4950 8700 4950
Entry Bus Bus
	5050 4850 5150 4950
NoConn ~ 3750 3850
NoConn ~ 5350 3050
NoConn ~ 3750 3050
NoConn ~ 3250 3050
NoConn ~ 3250 3150
NoConn ~ 8250 3050
NoConn ~ 8250 4350
NoConn ~ 8250 4450
$EndSCHEMATC
