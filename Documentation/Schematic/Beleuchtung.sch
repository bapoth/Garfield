EESchema Schematic File Version 2
LIBS:ALF-rescue
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
Sheet 3 7
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
L LED-RESCUE-ALF D1
U 1 1 582079CB
P 2550 3050
AR Path="/582079CB" Ref="D1"  Part="1" 
AR Path="/58207938/582079CB" Ref="D1"  Part="1" 
F 0 "D1" H 2550 3150 50  0000 C CNN
F 1 "LED" H 2550 2950 50  0000 C CNN
F 2 "" H 2550 3050 50  0000 C CNN
F 3 "" H 2550 3050 50  0000 C CNN
	1    2550 3050
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-ALF R4
U 1 1 582079F7
P 2550 2700
AR Path="/582079F7" Ref="R4"  Part="1" 
AR Path="/58207938/582079F7" Ref="R4"  Part="1" 
F 0 "R4" V 2630 2700 50  0000 C CNN
F 1 "R" V 2550 2700 50  0000 C CNN
F 2 "" V 2480 2700 50  0000 C CNN
F 3 "" H 2550 2700 50  0000 C CNN
	1    2550 2700
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-ALF D2
U 1 1 58207A7E
P 3150 3050
AR Path="/58207A7E" Ref="D2"  Part="1" 
AR Path="/58207938/58207A7E" Ref="D2"  Part="1" 
F 0 "D2" H 3150 3150 50  0000 C CNN
F 1 "LED" H 3150 2950 50  0000 C CNN
F 2 "" H 3150 3050 50  0000 C CNN
F 3 "" H 3150 3050 50  0000 C CNN
	1    3150 3050
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-ALF R5
U 1 1 58207A84
P 3150 2700
AR Path="/58207A84" Ref="R5"  Part="1" 
AR Path="/58207938/58207A84" Ref="R5"  Part="1" 
F 0 "R5" V 3230 2700 50  0000 C CNN
F 1 "R" V 3150 2700 50  0000 C CNN
F 2 "" V 3080 2700 50  0000 C CNN
F 3 "" H 3150 2700 50  0000 C CNN
	1    3150 2700
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-ALF D3
U 1 1 58207AFC
P 3750 3050
AR Path="/58207AFC" Ref="D3"  Part="1" 
AR Path="/58207938/58207AFC" Ref="D3"  Part="1" 
F 0 "D3" H 3750 3150 50  0000 C CNN
F 1 "LED" H 3750 2950 50  0000 C CNN
F 2 "" H 3750 3050 50  0000 C CNN
F 3 "" H 3750 3050 50  0000 C CNN
	1    3750 3050
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-ALF R6
U 1 1 58207B02
P 3750 2700
AR Path="/58207B02" Ref="R6"  Part="1" 
AR Path="/58207938/58207B02" Ref="R6"  Part="1" 
F 0 "R6" V 3830 2700 50  0000 C CNN
F 1 "R" V 3750 2700 50  0000 C CNN
F 2 "" V 3680 2700 50  0000 C CNN
F 3 "" H 3750 2700 50  0000 C CNN
	1    3750 2700
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-ALF D4
U 1 1 58207B74
P 4300 3050
AR Path="/58207B74" Ref="D4"  Part="1" 
AR Path="/58207938/58207B74" Ref="D4"  Part="1" 
F 0 "D4" H 4300 3150 50  0000 C CNN
F 1 "LED" H 4300 2950 50  0000 C CNN
F 2 "" H 4300 3050 50  0000 C CNN
F 3 "" H 4300 3050 50  0000 C CNN
	1    4300 3050
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-ALF R7
U 1 1 58207B7A
P 4300 2700
AR Path="/58207B7A" Ref="R7"  Part="1" 
AR Path="/58207938/58207B7A" Ref="R7"  Part="1" 
F 0 "R7" V 4380 2700 50  0000 C CNN
F 1 "R" V 4300 2700 50  0000 C CNN
F 2 "" V 4230 2700 50  0000 C CNN
F 3 "" H 4300 2700 50  0000 C CNN
	1    4300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3250 4300 3250
Connection ~ 3150 3250
Connection ~ 3750 3250
Wire Wire Line
	3450 3250 3450 3350
Connection ~ 3450 3250
Text HLabel 3450 3350 3    60   Input ~ 0
LED
Wire Wire Line
	2550 2450 4300 2450
Connection ~ 3150 2450
Connection ~ 3750 2450
Wire Wire Line
	3450 2450 3450 2350
Connection ~ 3450 2450
Text HLabel 3450 2350 1    60   Input ~ 0
5V
Text Notes 3350 2100 2    60   ~ 0
Low active circuit
$EndSCHEMATC
