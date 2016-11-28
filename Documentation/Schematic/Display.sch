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
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 7
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
L CONN_01X08 P14
U 1 1 5827A7DB
P 2600 1550
F 0 "P14" H 2600 2000 50  0000 C CNN
F 1 "CONN_01X08" V 2700 1550 50  0000 C CNN
F 2 "" H 2600 1550 50  0000 C CNN
F 3 "" H 2600 1550 50  0000 C CNN
	1    2600 1550
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X06 P15
U 1 1 5827A80C
P 2600 2350
F 0 "P15" H 2600 2700 50  0000 C CNN
F 1 "CONN_01X06" V 2700 2350 50  0000 C CNN
F 2 "" H 2600 2350 50  0000 C CNN
F 3 "" H 2600 2350 50  0000 C CNN
	1    2600 2350
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P16
U 1 1 5827A835
P 4100 1350
F 0 "P16" H 4100 1900 50  0000 C CNN
F 1 "CONN_01X10" V 4200 1350 50  0000 C CNN
F 2 "" H 4100 1350 50  0000 C CNN
F 3 "" H 4100 1350 50  0000 C CNN
	1    4100 1350
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X08 P17
U 1 1 5827A8EE
P 4100 2350
F 0 "P17" H 4100 2800 50  0000 C CNN
F 1 "CONN_01X08" V 4200 2350 50  0000 C CNN
F 2 "" H 4100 2350 50  0000 C CNN
F 3 "" H 4100 2350 50  0000 C CNN
	1    4100 2350
	-1   0    0    1   
$EndComp
Text HLabel 4300 1300 2    60   Input ~ 0
D13_SCLK
Text HLabel 4300 1400 2    60   Input ~ 0
D12_MISO
Text HLabel 4300 1500 2    60   Input ~ 0
D11_MOSI
Text HLabel 4300 1800 2    60   Input ~ 0
D8_TOUCH_CS
Text HLabel 4300 2400 2    60   Input ~ 0
D4_SD_CS
Text HLabel 4300 1600 2    60   Input ~ 0
D10_TFT_CS
Text HLabel 4300 1700 2    60   Input ~ 0
D9_TFT_DC
$EndSCHEMATC
