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
Sheet 1 1
Title "Schematic of ALF Project - Top file"
Date "2016-10-24"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X08 JP3
U 1 1 58171139
P 2450 1650
F 0 "JP3" H 2450 2100 50  0000 C CNN
F 1 "CONN_01X08" V 2550 1650 50  0000 C CNN
F 2 "" H 2450 1650 50  0000 C CNN
F 3 "" H 2450 1650 50  0000 C CNN
	1    2450 1650
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X06 JP5
U 1 1 58171216
P 2450 2450
F 0 "JP5" H 2450 2800 50  0000 C CNN
F 1 "CONN_01X06" V 2550 2450 50  0000 C CNN
F 2 "" H 2450 2450 50  0000 C CNN
F 3 "" H 2450 2450 50  0000 C CNN
	1    2450 2450
	-1   0    0    -1  
$EndComp
$Comp
L CONN_01X10 JP4
U 1 1 5817132D
P 4450 1450
F 0 "JP4" H 4450 2000 50  0000 C CNN
F 1 "CONN_01X10" V 4550 1450 50  0000 C CNN
F 2 "" H 4450 1450 50  0000 C CNN
F 3 "" H 4450 1450 50  0000 C CNN
	1    4450 1450
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 JP6
U 1 1 58171519
P 4450 2400
F 0 "JP6" H 4450 2850 50  0000 C CNN
F 1 "CONN_01X08" V 4550 2400 50  0000 C CNN
F 2 "" H 4450 2400 50  0000 C CNN
F 3 "" H 4450 2400 50  0000 C CNN
	1    4450 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X20 JP1
U 1 1 58171620
P 1400 1800
F 0 "JP1" H 1400 2850 50  0000 C CNN
F 1 "CONN_02X20" V 1400 1800 50  0000 C CNN
F 2 "" H 1400 850 50  0000 C CNN
F 3 "" H 1400 850 50  0000 C CNN
	1    1400 1800
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X20 JP7
U 1 1 581716E3
P 5500 1900
F 0 "JP7" H 5500 2950 50  0000 C CNN
F 1 "CONN_02X20" V 5500 1900 50  0000 C CNN
F 2 "" H 5500 950 50  0000 C CNN
F 3 "" H 5500 950 50  0000 C CNN
	1    5500 1900
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X05 P?
U 1 1 58171862
P 1400 3550
F 0 "P?" H 1400 3850 50  0000 C CNN
F 1 "CONN_02X05" H 1400 3250 50  0000 C CNN
F 2 "" H 1400 2350 50  0000 C CNN
F 3 "" H 1400 2350 50  0000 C CNN
	1    1400 3550
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X07 P?
U 1 1 581718D6
P 5500 3450
F 0 "P?" H 5500 3850 50  0000 C CNN
F 1 "CONN_02X07" V 5500 3450 50  0000 C CNN
F 2 "" H 5500 2250 50  0000 C CNN
F 3 "" H 5500 2250 50  0000 C CNN
	1    5500 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 JP2
U 1 1 58171955
P 3450 3000
F 0 "JP2" H 3450 3200 50  0000 C CNN
F 1 "CONN_02X03" H 3450 2800 50  0000 C CNN
F 2 "" H 3450 1800 50  0000 C CNN
F 3 "" H 3450 1800 50  0000 C CNN
	1    3450 3000
	0    1    1    0   
$EndComp
Text GLabel 3450 3250 3    60   Input ~ 0
Arduino_IO11
Text GLabel 3350 3250 3    60   BiDi ~ 0
GND
Text GLabel 3550 3250 3    60   BiDi ~ 0
VCC5
Text GLabel 3350 2750 1    60   BiDi ~ 0
Arduino_Reset_n
Text GLabel 3450 2750 1    60   BiDi ~ 0
Arduino_IO13
Text GLabel 3550 2750 1    60   BiDi ~ 0
Arduino_IO12
Text GLabel 2650 2000 2    60   BiDi ~ 0
Arduino_IO0
Text GLabel 2650 1900 2    60   BiDi ~ 0
Arduino_IO1
Text GLabel 2650 1800 2    60   BiDi ~ 0
Arduino_IO2
Text GLabel 2650 1700 2    60   BiDi ~ 0
Arduino_IO3
Text GLabel 2650 1600 2    60   BiDi ~ 0
Arduino_IO4
Text GLabel 2650 1500 2    60   BiDi ~ 0
Arduino_IO5
Text GLabel 2650 1400 2    60   BiDi ~ 0
Arduino_IO6
Text GLabel 2650 1300 2    60   BiDi ~ 0
Arduino_IO7
Text GLabel 2650 2200 2    60   Input ~ 0
ADC_IN0
Text GLabel 2650 2300 2    60   Input ~ 0
ADC_IN1
Text GLabel 2650 2400 2    60   Input ~ 0
ADC_IN2
Text GLabel 2650 2500 2    60   Input ~ 0
ADC_IN3
Text GLabel 2650 2600 2    60   Input ~ 0
ADC_IN4
Text GLabel 2650 2700 2    60   Input ~ 0
ADC_IN5
Text GLabel 4250 1000 0    60   BiDi ~ 0
Arduino_IO15
Text GLabel 4250 1100 0    60   BiDi ~ 0
Arduino_IO14
Text GLabel 4250 1200 0    60   BiDi ~ 0
Arduino_VREF
Text GLabel 4250 1300 0    60   BiDi ~ 0
GND
Text GLabel 4250 1400 0    60   BiDi ~ 0
Arduino_IO13
Text GLabel 4250 1500 0    60   BiDi ~ 0
Arduino_IO12
Text GLabel 4250 1600 0    60   BiDi ~ 0
Arduino_IO11
Text GLabel 4250 1700 0    60   BiDi ~ 0
Arduino_IO10
Text GLabel 4250 1800 0    60   BiDi ~ 0
Arduino_IO9
Text GLabel 4250 1900 0    60   BiDi ~ 0
Arduino_IO8
Text GLabel 4250 2750 0    60   BiDi ~ 0
Arduino_IO0
Text GLabel 4250 2650 0    60   BiDi ~ 0
Arduino_IO1
Text GLabel 4250 2550 0    60   BiDi ~ 0
Arduino_IO2
Text GLabel 4250 2450 0    60   BiDi ~ 0
Arduino_IO3
Text GLabel 4250 2350 0    60   BiDi ~ 0
Arduino_IO4
Text GLabel 4250 2250 0    60   BiDi ~ 0
Arduino_IO5
Text GLabel 4250 2150 0    60   BiDi ~ 0
Arduino_IO6
Text GLabel 4250 2050 0    60   BiDi ~ 0
Arduino_IO7
Text GLabel 1650 850  2    60   BiDi ~ 0
GPIO_0_D1
Text GLabel 1650 950  2    60   BiDi ~ 0
GPIO_0_D3
Text GLabel 1650 1050 2    60   BiDi ~ 0
GPIO_0_D5
Text GLabel 1650 1150 2    60   BiDi ~ 0
GPIO_0_D7
Text GLabel 1650 1250 2    60   BiDi ~ 0
GPIO_0_D9
Text GLabel 1650 1350 2    60   BiDi ~ 0
GND
Text GLabel 1650 1450 2    60   BiDi ~ 0
GPIO_0_D11
Text GLabel 1650 1550 2    60   BiDi ~ 0
GPIO_0_D13
Text GLabel 1650 1650 2    60   BiDi ~ 0
GPIO_0_D15
Text GLabel 1650 1750 2    60   BiDi ~ 0
GPIO_0_D17
Text GLabel 1650 1850 2    60   BiDi ~ 0
GPIO_0_D19
Text GLabel 1650 1950 2    60   BiDi ~ 0
GPIO_0_D21
Text GLabel 1650 2050 2    60   BiDi ~ 0
GPIO_0_D23
Text GLabel 1650 2150 2    60   BiDi ~ 0
GPIO_0_D25
Text GLabel 1650 2250 2    60   BiDi ~ 0
GND
Text GLabel 1650 2350 2    60   BiDi ~ 0
GPIO_0_D27
Text GLabel 1650 2450 2    60   BiDi ~ 0
GPIO_0_D29
Text GLabel 1650 2550 2    60   BiDi ~ 0
GPIO_0_D31
Text GLabel 1650 2650 2    60   BiDi ~ 0
GPIO_0_D33
Text GLabel 1650 2750 2    60   BiDi ~ 0
GPIO_0_D35
Text GLabel 1150 850  0    60   BiDi ~ 0
GPIO_0_D0
Text GLabel 1150 950  0    60   BiDi ~ 0
GPIO_0_D2
Text GLabel 1150 1050 0    60   BiDi ~ 0
GPIO_0_D4
Text GLabel 1150 1150 0    60   BiDi ~ 0
GPIO_0_D6
Text GLabel 1150 1250 0    60   BiDi ~ 0
GPIO_0_D8
Text GLabel 1150 1350 0    60   BiDi ~ 0
VCC5
Text GLabel 1150 1450 0    60   BiDi ~ 0
GPIO_0_D10
Text GLabel 1150 1550 0    60   BiDi ~ 0
GPIO_0_D12
Text GLabel 1150 1650 0    60   BiDi ~ 0
GPIO_0_D14
Text GLabel 1150 1750 0    60   BiDi ~ 0
GPIO_0_D16
Text GLabel 1150 1850 0    60   BiDi ~ 0
GPIO_0_D18
Text GLabel 1150 1950 0    60   BiDi ~ 0
GPIO_0_D20
Text GLabel 1150 2050 0    60   BiDi ~ 0
GPIO_0_D22
Text GLabel 1150 2150 0    60   BiDi ~ 0
GPIO_0_D24
Text GLabel 1150 2250 0    60   BiDi ~ 0
VCC3P3
Text GLabel 1150 2350 0    60   BiDi ~ 0
GPIO_0_D26
Text GLabel 1150 2450 0    60   BiDi ~ 0
GPIO_0_D28
Text GLabel 1150 2550 0    60   BiDi ~ 0
GPIO_0_D30
Text GLabel 1150 2650 0    60   BiDi ~ 0
GPIO_0_D32
Text GLabel 1150 2750 0    60   BiDi ~ 0
GPIO_0_D34
Text GLabel 5250 950  0    60   BiDi ~ 0
GPIO_1_D0
Text GLabel 5250 1050 0    60   BiDi ~ 0
GPIO_1_D2
Text GLabel 5250 1150 0    60   BiDi ~ 0
GPIO_1_D4
Text GLabel 5250 1250 0    60   BiDi ~ 0
GPIO_1_D6
Text GLabel 5250 1350 0    60   BiDi ~ 0
GPIO_1_D8
Text GLabel 5250 1450 0    60   BiDi ~ 0
VCC5
Text GLabel 5250 1550 0    60   BiDi ~ 0
GPIO_1_D10
Text GLabel 5250 1650 0    60   BiDi ~ 0
GPIO_1_D12
Text GLabel 5250 1750 0    60   BiDi ~ 0
GPIO_1_D14
Text GLabel 5250 1850 0    60   BiDi ~ 0
GPIO_1_D16
Text GLabel 5250 1950 0    60   BiDi ~ 0
GPIO_1_D18
Text GLabel 5250 2050 0    60   BiDi ~ 0
GPIO_1_D20
Text GLabel 5250 2150 0    60   BiDi ~ 0
GPIO_1_D22
Text GLabel 5250 2250 0    60   BiDi ~ 0
GPIO_1_D24
Text GLabel 5250 2350 0    60   BiDi ~ 0
VCC3P3
Text GLabel 5250 2450 0    60   BiDi ~ 0
GPIO_1_D26
Text GLabel 5250 2550 0    60   BiDi ~ 0
GPIO_1_D28
Text GLabel 5250 2650 0    60   BiDi ~ 0
GPIO_1_D30
Text GLabel 5250 2750 0    60   BiDi ~ 0
GPIO_1_D32
Text GLabel 5250 2850 0    60   BiDi ~ 0
GPIO_1_D34
Text GLabel 5750 950  2    60   BiDi ~ 0
GPIO_1_D1
Text GLabel 5750 1050 2    60   BiDi ~ 0
GPIO_1_D3
Text GLabel 5750 1150 2    60   BiDi ~ 0
GPIO_1_D5
Text GLabel 5750 1250 2    60   BiDi ~ 0
GPIO_1_D7
Text GLabel 5750 1350 2    60   BiDi ~ 0
GPIO_1_D9
Text GLabel 5750 1450 2    60   BiDi ~ 0
GND
Text GLabel 5750 1550 2    60   BiDi ~ 0
GPIO_1_D11
Text GLabel 5750 1650 2    60   BiDi ~ 0
GPIO_1_D13
Text GLabel 5750 1750 2    60   BiDi ~ 0
GPIO_1_D15
Text GLabel 5750 1850 2    60   BiDi ~ 0
GPIO_1_D17
Text GLabel 5750 1950 2    60   BiDi ~ 0
GPIO_1_D19
Text GLabel 5750 2050 2    60   BiDi ~ 0
GPIO_1_D21
Text GLabel 5750 2150 2    60   BiDi ~ 0
GPIO_1_D23
Text GLabel 5750 2250 2    60   BiDi ~ 0
GPIO_1_D25
Text GLabel 5750 2350 2    60   BiDi ~ 0
GND
Text GLabel 5750 2450 2    60   BiDi ~ 0
GPIO_1_D27
Text GLabel 5750 2550 2    60   BiDi ~ 0
GPIO_1_D29
Text GLabel 5750 2650 2    60   BiDi ~ 0
GPIO_1_D31
Text GLabel 5750 2750 2    60   BiDi ~ 0
GPIO_1_D33
Text GLabel 5750 2850 2    60   BiDi ~ 0
GPIO_1_D35
Wire Notes Line
	8500 2400 8500 800 
Text Notes 9350 900  2    60   ~ 0
Ultraschall SRF08
Wire Notes Line
	8500 3850 8500 2450
Text Notes 9050 2550 2    60   ~ 0
Beleuchtung
Wire Notes Line
	8500 3900 8500 5100
Text Notes 8500 4000 0    60   ~ 0
Levelshifter
Wire Notes Line
	10800 2400 10800 800 
Wire Notes Line
	10800 2400 8500 2400
Wire Notes Line
	10800 800  8500 800 
Wire Notes Line
	10800 2450 10800 3850
Wire Notes Line
	8500 2450 10800 2450
Wire Notes Line
	10800 3850 8500 3850
Wire Notes Line
	10800 3900 10800 5100
Wire Notes Line
	10800 3900 8500 3900
Wire Notes Line
	10800 5100 8500 5100
Wire Notes Line
	8500 5150 10800 5150
Wire Notes Line
	10800 5150 10800 6450
Wire Notes Line
	10800 6450 8500 6450
Wire Notes Line
	8500 6450 8500 5150
Text Notes 8500 5250 0    60   ~ 0
Motortreiber
Wire Notes Line
	8450 5150 8450 6450
Wire Notes Line
	5750 6450 8450 6450
Wire Notes Line
	5750 5150 8450 5150
Text Notes 6300 5250 0    60   ~ 0
MPU 6050
Wire Notes Line
	8450 3900 8450 5100
Wire Notes Line
	8450 5100 6300 5100
Wire Notes Line
	6300 3900 8450 3900
Text Notes 6300 4000 0    60   ~ 0
Drehzahlsensor
Wire Notes Line
	6300 5100 6300 3900
Wire Notes Line
	5700 6450 5700 5150
Wire Notes Line
	3700 6450 5700 6450
Wire Notes Line
	3700 6450 3700 5150
Wire Notes Line
	3700 5150 5700 5150
Text Notes 3700 5250 0    60   ~ 0
Display
Wire Notes Line
	2250 6450 2250 5150
Text Notes 2250 5250 0    60   ~ 0
Buttons
$Comp
L LED D?
U 1 1 58176890
P 10400 3200
F 0 "D?" H 10400 3300 50  0000 C CNN
F 1 "LED" H 10400 3100 50  0000 C CNN
F 2 "" H 10400 3200 50  0000 C CNN
F 3 "" H 10400 3200 50  0000 C CNN
	1    10400 3200
	0    -1   -1   0   
$EndComp
$Comp
L LED D?
U 1 1 581768EF
P 9900 3200
F 0 "D?" H 9900 3300 50  0000 C CNN
F 1 "LED" H 9900 3100 50  0000 C CNN
F 2 "" H 9900 3200 50  0000 C CNN
F 3 "" H 9900 3200 50  0000 C CNN
	1    9900 3200
	0    -1   -1   0   
$EndComp
$Comp
L LED D?
U 1 1 58176930
P 9400 3200
F 0 "D?" H 9400 3300 50  0000 C CNN
F 1 "LED" H 9400 3100 50  0000 C CNN
F 2 "" H 9400 3200 50  0000 C CNN
F 3 "" H 9400 3200 50  0000 C CNN
	1    9400 3200
	0    -1   -1   0   
$EndComp
$Comp
L LED D?
U 1 1 58176972
P 8950 3200
F 0 "D?" H 8950 3300 50  0000 C CNN
F 1 "LED" H 8950 3100 50  0000 C CNN
F 2 "" H 8950 3200 50  0000 C CNN
F 3 "" H 8950 3200 50  0000 C CNN
	1    8950 3200
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 58176A88
P 10400 2850
F 0 "R?" V 10480 2850 50  0000 C CNN
F 1 "R" V 10400 2850 50  0000 C CNN
F 2 "" V 10330 2850 50  0000 C CNN
F 3 "" H 10400 2850 50  0000 C CNN
	1    10400 2850
	-1   0    0    1   
$EndComp
$Comp
L R R?
U 1 1 58176B0D
P 9900 2850
F 0 "R?" V 9980 2850 50  0000 C CNN
F 1 "R" V 9900 2850 50  0000 C CNN
F 2 "" V 9830 2850 50  0000 C CNN
F 3 "" H 9900 2850 50  0000 C CNN
	1    9900 2850
	-1   0    0    1   
$EndComp
$Comp
L R R?
U 1 1 58176B6B
P 9400 2850
F 0 "R?" V 9480 2850 50  0000 C CNN
F 1 "R" V 9400 2850 50  0000 C CNN
F 2 "" V 9330 2850 50  0000 C CNN
F 3 "" H 9400 2850 50  0000 C CNN
	1    9400 2850
	-1   0    0    1   
$EndComp
$Comp
L R R?
U 1 1 58176BD3
P 8950 2850
F 0 "R?" V 9030 2850 50  0000 C CNN
F 1 "R" V 8950 2850 50  0000 C CNN
F 2 "" V 8880 2850 50  0000 C CNN
F 3 "" H 8950 2850 50  0000 C CNN
	1    8950 2850
	-1   0    0    1   
$EndComp
Text GLabel 10400 3400 3    60   Input ~ 0
GND
Text GLabel 9900 3400 3    60   Input ~ 0
GND
Text GLabel 9400 3400 3    60   Input ~ 0
GND
Text GLabel 8950 3400 3    60   Input ~ 0
GND
Text GLabel 7750 1000 1    60   Input ~ 0
GND
$Comp
L GND #PWR?
U 1 1 5818C15E
P 7750 1100
F 0 "#PWR?" H 7750 850 50  0001 C CNN
F 1 "GND" H 7750 950 50  0000 C CNN
F 2 "" H 7750 1100 50  0000 C CNN
F 3 "" H 7750 1100 50  0000 C CNN
	1    7750 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1000 7750 1100
$Comp
L CONN_01X05 P?
U 1 1 5818C3FE
P 9200 1900
F 0 "P?" H 9200 2200 50  0000 C CNN
F 1 "CONN_01X05" V 9300 1900 50  0000 C CNN
F 2 "" H 9200 1900 50  0000 C CNN
F 3 "" H 9200 1900 50  0000 C CNN
	1    9200 1900
	1    0    0    -1  
$EndComp
Text GLabel 9000 1700 0    60   Input ~ 0
VCC
Text GLabel 9000 1800 0    60   Input ~ 0
SDA_U2
Text GLabel 9000 1900 0    60   Input ~ 0
SCL_U2
Text GLabel 9000 2100 0    60   Input ~ 0
GND
$Comp
L CONN_01X05 P?
U 1 1 5818D039
P 9200 1250
F 0 "P?" H 9200 1550 50  0000 C CNN
F 1 "CONN_01X05" V 9300 1250 50  0000 C CNN
F 2 "" H 9200 1250 50  0000 C CNN
F 3 "" H 9200 1250 50  0000 C CNN
	1    9200 1250
	1    0    0    -1  
$EndComp
Text GLabel 9000 1050 0    60   Input ~ 0
VCC
Text GLabel 9000 1150 0    60   Input ~ 0
SDA_U1
Text GLabel 9000 1250 0    60   Input ~ 0
SCL_U1
Text GLabel 9000 1450 0    60   Input ~ 0
GND
$Comp
L CONN_01X05 P?
U 1 1 5818D193
P 10400 1250
F 0 "P?" H 10400 1550 50  0000 C CNN
F 1 "CONN_01X05" V 10500 1250 50  0000 C CNN
F 2 "" H 10400 1250 50  0000 C CNN
F 3 "" H 10400 1250 50  0000 C CNN
	1    10400 1250
	1    0    0    -1  
$EndComp
Text GLabel 10200 1050 0    60   Input ~ 0
VCC
Text GLabel 10200 1150 0    60   Input ~ 0
SDA_U3
Text GLabel 10200 1250 0    60   Input ~ 0
SCL_U3
Text GLabel 10200 1450 0    60   Input ~ 0
GND
$Comp
L CONN_01X05 P?
U 1 1 5818D22D
P 10400 1900
F 0 "P?" H 10400 2200 50  0000 C CNN
F 1 "CONN_01X05" V 10500 1900 50  0000 C CNN
F 2 "" H 10400 1900 50  0000 C CNN
F 3 "" H 10400 1900 50  0000 C CNN
	1    10400 1900
	1    0    0    -1  
$EndComp
Text GLabel 10200 1700 0    60   Input ~ 0
VCC
Text GLabel 10200 1800 0    60   Input ~ 0
SDA_U4
Text GLabel 10200 1900 0    60   Input ~ 0
SCL_U4
Text GLabel 10200 2100 0    60   Input ~ 0
GND
$Comp
L CONN_01X24 P?
U 1 1 5818D72B
P 7100 6100
F 0 "P?" H 7100 7350 50  0000 C CNN
F 1 "CONN_01X24" V 7200 6100 50  0000 C CNN
F 2 "" H 7100 6100 50  0000 C CNN
F 3 "" H 7100 6100 50  0000 C CNN
	1    7100 6100
	0    1    1    0   
$EndComp
Wire Notes Line
	3650 5150 3650 6450
Wire Notes Line
	2250 5150 3650 5150
Wire Notes Line
	3650 6450 2250 6450
Wire Notes Line
	5750 5150 5750 6450
Text GLabel 8250 5900 1    60   Input ~ 0
CLKIN
Text GLabel 7750 5900 1    60   Input ~ 0
AUX_DA
Text GLabel 7650 5900 1    60   Input ~ 0
AUX_CL
Text GLabel 7550 5900 1    60   Input ~ 0
VLOGIC
Text GLabel 7450 5900 1    60   Input ~ 0
AD0
Text GLabel 7350 5900 1    60   Input ~ 0
REGOUT
Text GLabel 7250 5900 1    60   Input ~ 0
FSYNC
Text GLabel 7150 5900 1    60   Input ~ 0
INT
Text GLabel 7050 5900 1    60   Input ~ 0
VDD
Text GLabel 6550 5900 1    60   Input ~ 0
GND
Text GLabel 6450 5900 1    60   Input ~ 0
RESV
Text GLabel 6350 5900 1    60   Input ~ 0
CPOUT
Text GLabel 6250 5900 1    60   Input ~ 0
RESV
Text GLabel 6150 5900 1    60   Input ~ 0
RESV
Text GLabel 6050 5900 1    60   Input ~ 0
SCL
Text GLabel 5950 5900 1    60   Input ~ 0
SDA
$EndSCHEMATC
