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
LIBS:ALF-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
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
L CONN_01X03 P?
U 1 1 5822507B
P 2000 1200
F 0 "P?" H 2000 1400 50  0000 C CNN
F 1 "CONN_01X03" V 2100 1200 50  0000 C CNN
F 2 "" H 2000 1200 50  0000 C CNN
F 3 "" H 2000 1200 50  0000 C CNN
	1    2000 1200
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X03 P?
U 1 1 582250EA
P 3050 1200
F 0 "P?" H 3050 1400 50  0000 C CNN
F 1 "CONN_01X03" V 3150 1200 50  0000 C CNN
F 2 "" H 3050 1200 50  0000 C CNN
F 3 "" H 3050 1200 50  0000 C CNN
	1    3050 1200
	0    -1   -1   0   
$EndComp
Text HLabel 2100 1400 3    60   Output ~ 0
VOUT_3.3
Text HLabel 3150 1400 3    60   Output ~ 0
VOUT_5
Text HLabel 1150 2150 0    60   Input ~ 0
AKKU+
Text HLabel 1150 2350 0    60   Input ~ 0
AKKU-
Wire Wire Line
	1150 2350 3200 2350
Wire Wire Line
	3050 2350 3050 1400
Wire Wire Line
	2000 1400 2000 2350
Connection ~ 2000 2350
Wire Wire Line
	1150 2150 2950 2150
Wire Wire Line
	2950 2150 2950 1400
Wire Wire Line
	1900 1400 1900 2150
Connection ~ 1900 2150
Text HLabel 3200 2350 2    60   Output ~ 0
GND
Connection ~ 3050 2350
$EndSCHEMATC
