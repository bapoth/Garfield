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
Sheet 1 7
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
P 5550 1800
F 0 "JP7" H 5550 2850 50  0000 C CNN
F 1 "CONN_02X20" V 5550 1800 50  0000 C CNN
F 2 "" H 5550 850 50  0000 C CNN
F 3 "" H 5550 850 50  0000 C CNN
	1    5550 1800
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
P 5550 3300
F 0 "P?" H 5550 3700 50  0000 C CNN
F 1 "CONN_02X07" V 5550 3300 50  0000 C CNN
F 2 "" H 5550 2100 50  0000 C CNN
F 3 "" H 5550 2100 50  0000 C CNN
	1    5550 3300
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
VCC9
Text GLabel 2650 1900 2    60   BiDi ~ 0
GND
Text GLabel 2650 1800 2    60   BiDi ~ 0
GND
Text GLabel 2650 1700 2    60   BiDi ~ 0
VCC5
Text GLabel 2650 1600 2    60   BiDi ~ 0
VCC3P3
Text GLabel 2650 1500 2    60   BiDi ~ 0
Arduino_Reset_n
Text GLabel 2650 1400 2    60   BiDi ~ 0
VCC3P3
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
SCLK
Text GLabel 4250 1500 0    60   BiDi ~ 0
MISO
Text GLabel 4250 1600 0    60   BiDi ~ 0
MOSI
Text GLabel 4250 1700 0    60   BiDi ~ 0
TFT_CS
Text GLabel 4250 1800 0    60   BiDi ~ 0
TFT_DC
Text GLabel 4250 1900 0    60   BiDi ~ 0
TOUCH_CS
Text GLabel 4250 2750 0    60   BiDi ~ 0
Arduino_IO0
Text GLabel 4250 2650 0    60   BiDi ~ 0
Arduino_IO1
Text GLabel 4250 2550 0    60   BiDi ~ 0
Arduino_IO2
Text GLabel 4250 2450 0    60   BiDi ~ 0
Arduino_IO3
Text GLabel 4250 2350 0    60   BiDi ~ 0
SD_CS
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
Text GLabel 5300 850  0    60   BiDi ~ 0
SDA
Text GLabel 5300 950  0    60   BiDi ~ 0
SCL
Text GLabel 5300 1050 0    60   BiDi ~ 0
MOTOR_PWM_33
Text GLabel 5300 1150 0    60   BiDi ~ 0
MOTOR_DIR_33
Text GLabel 5300 1250 0    60   BiDi ~ 0
GPIO_1_D8
Text GLabel 5300 1350 0    60   BiDi ~ 0
VCC5
Text GLabel 5300 1450 0    60   BiDi ~ 0
GPIO_1_D10
Text GLabel 5300 1550 0    60   BiDi ~ 0
GPIO_1_D12
Text GLabel 5300 1650 0    60   BiDi ~ 0
GPIO_1_D14
Text GLabel 5300 1750 0    60   BiDi ~ 0
GPIO_1_D16
Text GLabel 5300 1850 0    60   BiDi ~ 0
GPIO_1_D18
Text GLabel 5300 1950 0    60   BiDi ~ 0
GPIO_1_D20
Text GLabel 5300 2050 0    60   BiDi ~ 0
GPIO_1_D22
Text GLabel 5300 2150 0    60   BiDi ~ 0
GPIO_1_D24
Text GLabel 5300 2250 0    60   BiDi ~ 0
VCC3P3
Text GLabel 5300 2350 0    60   BiDi ~ 0
GPIO_1_D26
Text GLabel 5300 2450 0    60   BiDi ~ 0
GPIO_1_D28
Text GLabel 5300 2550 0    60   BiDi ~ 0
GPIO_1_D30
Text GLabel 5300 2650 0    60   BiDi ~ 0
GPIO_1_D32
Text GLabel 5300 2750 0    60   BiDi ~ 0
GPIO_1_D34
Text GLabel 5800 850  2    60   BiDi ~ 0
LED_HL_IN
Text GLabel 5800 950  2    60   BiDi ~ 0
LED_HR_IN
Text GLabel 5800 1050 2    60   BiDi ~ 0
LED_VL_IN
Text GLabel 5800 1150 2    60   BiDi ~ 0
LED_VR_IN
Text GLabel 5800 1250 2    60   BiDi ~ 0
GPIO_1_D9
Text GLabel 5800 1350 2    60   BiDi ~ 0
GND
Text GLabel 5800 1450 2    60   BiDi ~ 0
GPIO_1_D11
Text GLabel 5800 1550 2    60   BiDi ~ 0
GPIO_1_D13
Text GLabel 5800 1650 2    60   BiDi ~ 0
GPIO_1_D15
Text GLabel 5800 1750 2    60   BiDi ~ 0
GPIO_1_D17
Text GLabel 5800 1850 2    60   BiDi ~ 0
GPIO_1_D19
Text GLabel 5800 1950 2    60   BiDi ~ 0
GPIO_1_D21
Text GLabel 5800 2050 2    60   BiDi ~ 0
GPIO_1_D23
Text GLabel 5800 2150 2    60   BiDi ~ 0
GPIO_1_D25
Text GLabel 5800 2250 2    60   BiDi ~ 0
GND
Text GLabel 5800 2350 2    60   BiDi ~ 0
GPIO_1_D27
Text GLabel 5800 2450 2    60   BiDi ~ 0
GPIO_1_D29
Text GLabel 5800 2550 2    60   BiDi ~ 0
GPIO_1_D31
Text GLabel 5800 2650 2    60   BiDi ~ 0
GPIO_1_D33
Text GLabel 5800 2750 2    60   BiDi ~ 0
GPIO_1_D35
Wire Notes Line
	8500 2400 8500 800 
Text Notes 9350 900  2    60   ~ 0
Ultraschall SRF08
Text Notes 9050 2550 2    60   ~ 0
Beleuchtung
Text Notes 650  5250 0    60   ~ 0
Levelshifter
Wire Notes Line
	10800 2400 10800 800 
Wire Notes Line
	10800 2400 8500 2400
Wire Notes Line
	10800 800  8500 800 
Wire Notes Line
	8500 2450 10800 2450
Wire Notes Line
	10800 3750 8500 3750
Wire Notes Line
	7300 5150 10800 5150
Wire Notes Line
	10800 5150 10800 6450
Wire Notes Line
	10800 6450 7300 6450
Wire Notes Line
	7300 6450 7300 5150
Text Notes 7300 5250 0    60   ~ 0
Motortreiber
Wire Notes Line
	7250 5150 7250 6450
Text Notes 5950 5250 0    60   ~ 0
MPU 6050
Text Notes 4150 6600 0    60   ~ 0
Drehzahlsensor
Wire Notes Line
	5850 6450 5850 5150
Wire Notes Line
	4050 6450 4050 5150
Text Notes 4050 5250 0    60   ~ 0
Display
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
Wire Notes Line
	5900 6450 5900 5150
Text GLabel 1150 3350 0    60   Input ~ 0
VCC5
Text GLabel 1150 3450 0    60   Input ~ 0
ADC_IN1
Text GLabel 1150 3550 0    60   Input ~ 0
ADC_IN3
Text GLabel 1150 3650 0    60   Input ~ 0
ADC_IN5
Text GLabel 1150 3750 0    60   Input ~ 0
ADC_IN7
Text GLabel 1650 3350 2    60   Input ~ 0
ADC_IN0
Text GLabel 1650 3450 2    60   Input ~ 0
ADC_IN2
Text GLabel 1650 3550 2    60   Input ~ 0
ADC_IN4
Text GLabel 1650 3650 2    60   Input ~ 0
ADC_IN6
Text GLabel 1650 3750 2    60   Input ~ 0
GND
Wire Notes Line
	10800 5100 10800 3800
Wire Notes Line
	7300 5100 10800 5100
Wire Notes Line
	7300 5100 7300 3800
Wire Notes Line
	7300 3800 10800 3800
Text Notes 8150 3900 2    60   ~ 0
Spannungswandler
$Comp
L BARREL_JACK CON?
U 1 1 58205FBE
P 2450 4750
F 0 "CON?" H 2450 5000 50  0000 C CNN
F 1 "BARREL_JACK" H 2450 4550 50  0000 C CNN
F 2 "" H 2450 4750 50  0000 C CNN
F 3 "" H 2450 4750 50  0000 C CNN
	1    2450 4750
	1    0    0    -1  
$EndComp
$Sheet
S 8950 1100 1300 1100
U 582051C8
F0 "Ultraschall" 60
F1 "Ultraschall.sch" 60
F2 "VCC" I L 8950 1550 60 
F3 "GND" I L 8950 1700 60 
F4 "SDA" B R 10250 1550 60 
F5 "SCL" I R 10250 1700 60 
$EndSheet
$Sheet
S 9300 2600 1150 1000
U 58207938
F0 "Beleuchtung" 60
F1 "Beleuchtung.sch" 60
F2 "GND" I R 10450 3150 60 
F3 "LED_VR" I L 9300 3500 60 
F4 "LED_VL" I L 9300 3300 60 
F5 "LED_HR" I L 9300 2900 60 
F6 "LED_HL" I L 9300 2700 60 
$EndSheet
$Comp
L CONN_01X02 P?
U 1 1 582235DE
P 7900 4450
F 0 "P?" H 7900 4600 50  0000 C CNN
F 1 "CONN_AKKU" V 8000 4450 50  0000 C CNN
F 2 "" H 7900 4450 50  0000 C CNN
F 3 "" H 7900 4450 50  0000 C CNN
	1    7900 4450
	-1   0    0    1   
$EndComp
$Sheet
S 8200 4200 1750 600 
U 58224F6D
F0 "Spannungswandler" 60
F1 "Spannungswandler.sch" 60
F2 "VOUT_3.3" O R 9950 4500 60 
F3 "VOUT_5" O R 9950 4700 60 
F4 "AKKU+" I L 8200 4350 60 
F5 "AKKU-" I L 8200 4600 60 
F6 "GND" O R 9950 4300 60 
$EndSheet
Text GLabel 10150 4500 2    60   BiDi ~ 0
VCC_33
Text GLabel 10200 4700 2    60   BiDi ~ 0
VCC_5
Wire Wire Line
	8100 4300 8100 4350
Wire Wire Line
	8100 4350 8100 4400
Wire Wire Line
	8100 4350 8200 4350
Wire Wire Line
	8100 4500 8100 4600
Wire Wire Line
	8100 4600 8200 4600
Text GLabel 10200 4300 2    60   BiDi ~ 0
GND
Wire Wire Line
	10200 4300 9950 4300
Wire Wire Line
	10150 4500 9950 4500
Wire Wire Line
	10200 4700 9950 4700
Wire Notes Line
	4050 5150 5850 5150
Wire Wire Line
	2750 4750 2750 4800
Wire Wire Line
	2750 4800 2750 4850
Text GLabel 2900 4800 2    60   Input ~ 0
GND
Text GLabel 2900 4650 2    60   Input ~ 0
VCC33
Wire Wire Line
	2900 4650 2750 4650
Wire Wire Line
	2750 4800 2900 4800
Connection ~ 2750 4800
$Comp
L CONN_01X08 P?
U 1 1 5822E87F
P 7050 5800
F 0 "P?" H 7050 6250 50  0000 C CNN
F 1 "CONN_01X08" V 7150 5800 50  0000 C CNN
F 2 "" H 7050 5800 50  0000 C CNN
F 3 "" H 7050 5800 50  0000 C CNN
	1    7050 5800
	1    0    0    -1  
$EndComp
Text GLabel 6650 5450 0    60   Input ~ 0
VCC_33
Text GLabel 6650 5550 0    60   Input ~ 0
GND
Text GLabel 6650 5650 0    60   Input ~ 0
SCL
Text GLabel 6650 5750 0    60   Input ~ 0
SDA
Text GLabel 6650 5850 0    60   Input ~ 0
MPU6050_XDA
Text GLabel 6650 5950 0    60   Input ~ 0
MPU6050_XCL
Text GLabel 6650 6050 0    60   Input ~ 0
MPU6050_AD0
Text GLabel 6650 6150 0    60   Input ~ 0
MPU6050_INT
Wire Wire Line
	6850 5450 6650 5450
Wire Wire Line
	6650 5550 6850 5550
Wire Wire Line
	6850 5650 6650 5650
Wire Wire Line
	6650 5750 6850 5750
Wire Wire Line
	6850 5850 6650 5850
Wire Wire Line
	6650 5950 6850 5950
Wire Wire Line
	6850 6050 6650 6050
Wire Wire Line
	6650 6150 6850 6150
$Comp
L CONN_01X04 P?
U 1 1 58230541
P 6400 7200
F 0 "P?" H 6400 7450 50  0000 C CNN
F 1 "CONN_01X04" V 6500 7200 50  0000 C CNN
F 2 "" H 6400 7200 50  0000 C CNN
F 3 "" H 6400 7200 50  0000 C CNN
	1    6400 7200
	1    0    0    -1  
$EndComp
Text GLabel 5950 7050 0    60   Input ~ 0
GND
Wire Wire Line
	5950 7050 6050 7050
Wire Wire Line
	6050 7050 6200 7050
Wire Wire Line
	6200 7250 6050 7250
Wire Wire Line
	6050 7250 6050 7050
Connection ~ 6050 7050
Text GLabel 5950 7150 0    60   Input ~ 0
VCC_33
Text GLabel 5250 7350 0    60   Output ~ 0
ROT_OUT
Wire Wire Line
	5750 7350 6200 7350
Wire Wire Line
	6200 7150 5950 7150
$Comp
L R R?
U 1 1 58231B4F
P 5600 7350
F 0 "R?" V 5680 7350 50  0000 C CNN
F 1 "120" V 5600 7350 50  0000 C CNN
F 2 "" V 5530 7350 50  0000 C CNN
F 3 "" H 5600 7350 50  0000 C CNN
	1    5600 7350
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 7350 5250 7350
$Sheet
S 8300 5400 1600 800 
U 58232BD1
F0 "Motortreiber" 60
F1 "Motortreiber.sch" 60
F2 "V+" I L 8300 5450 60 
F3 "5V(OUT)" O L 8300 6150 60 
F4 "FF2" O L 8300 5550 60 
F5 "FF1" O L 8300 5650 60 
F6 "RESET" I L 8300 5750 60 
F7 "PWM" I L 8300 5850 60 
F8 "DIR" I L 8300 5950 60 
F9 "GND" I L 8300 6050 60 
F10 "OUTA" O R 9900 5650 60 
F11 "OUTB" O R 9900 5900 60 
$EndSheet
Text GLabel 8100 4300 1    60   Input ~ 0
AKKU+
Connection ~ 8100 4350
Text GLabel 8100 5450 0    60   Input ~ 0
AKKU+
Text GLabel 8100 5850 0    60   Input ~ 0
MOTOR_PWM_5V
Text GLabel 8100 5950 0    60   Input ~ 0
MOTOR_DIR_5V
Text GLabel 8100 6050 0    60   Input ~ 0
GND
Wire Wire Line
	8300 5450 8100 5450
Wire Wire Line
	8300 5850 8100 5850
Wire Wire Line
	8300 5950 8100 5950
Wire Wire Line
	8300 6050 8100 6050
Text GLabel 10150 5650 2    60   Input ~ 0
MOTOR_A
Text GLabel 10150 5900 2    60   Input ~ 0
MOTOR_B
Wire Wire Line
	10150 5650 9900 5650
Wire Wire Line
	10150 5900 9900 5900
$Sheet
S 1550 5450 1400 2150
U 5823B53D
F0 "Levelshifter" 60
F1 "Levelshifter.sch" 60
F2 "VCC1A" I L 1550 5500 60 
F3 "A11" B L 1550 5600 60 
F4 "A12" B L 1550 5700 60 
F5 "A13" B L 1550 5800 60 
F6 "A14" B L 1550 5900 60 
F7 "A15" B L 1550 6000 60 
F8 "A16" B L 1550 6100 60 
F9 "A17" B L 1550 6200 60 
F10 "A18" B L 1550 6300 60 
F11 "OE1" I L 1550 7550 60 
F12 "B11" B R 2950 5600 60 
F13 "VCC1B" I R 2950 5500 60 
F14 "B12" B R 2950 5700 60 
F15 "B13" B R 2950 5800 60 
F16 "B14" B R 2950 5900 60 
F17 "B15" B R 2950 6000 60 
F18 "B16" B R 2950 6100 60 
F19 "B17" B R 2950 6200 60 
F20 "B18" B R 2950 6300 60 
F21 "GND" I R 2950 7500 60 
F22 "VCC2A" I L 1550 6450 60 
F23 "A21" B L 1550 6550 60 
F24 "A22" B L 1550 6650 60 
F25 "A23" B L 1550 6750 60 
F26 "A24" B L 1550 6850 60 
F27 "A25" B L 1550 6950 60 
F28 "A26" B L 1550 7050 60 
F29 "A27" B L 1550 7150 60 
F30 "A28" B L 1550 7250 60 
F31 "OE2" I L 1550 7450 60 
F32 "B21" B R 2950 6550 60 
F33 "VCC2B" I R 2950 6450 60 
F34 "B22" B R 2950 6650 60 
F35 "B23" B R 2950 6750 60 
F36 "B24" B R 2950 6850 60 
F37 "B25" B R 2950 6950 60 
F38 "B26" B R 2950 7050 60 
F39 "B27" B R 2950 7150 60 
F40 "B28" B R 2950 7250 60 
$EndSheet
Wire Notes Line
	10800 2450 10800 3750
Wire Notes Line
	8500 3750 8500 2450
Wire Notes Line
	550  7750 2500 7750
Text GLabel 3250 7500 2    60   Input ~ 0
GND
Text GLabel 1350 5500 0    60   Input ~ 0
VCC_33
Wire Wire Line
	1350 5500 1550 5500
Wire Wire Line
	3250 7500 2950 7500
Text GLabel 3150 5500 2    60   Input ~ 0
VCC_5
Wire Wire Line
	3150 5500 2950 5500
Text GLabel 1300 6450 0    60   Input ~ 0
VCC_33
Wire Wire Line
	1300 6450 1550 6450
Text GLabel 3200 6450 2    60   Input ~ 0
VCC_5
Wire Wire Line
	3200 6450 2950 6450
Wire Notes Line
	550  5150 4000 5150
Wire Notes Line
	550  5150 550  7750
Wire Notes Line
	4000 5150 4000 7750
Wire Notes Line
	4000 7750 2450 7750
Wire Notes Line
	4050 7750 4050 6500
Wire Notes Line
	6900 7750 6900 6500
Wire Notes Line
	5850 6450 4050 6450
$Sheet
S 4150 5350 800  900 
U 5827A6E7
F0 "Display" 60
F1 "Display.sch" 60
F2 "D13_SCLK" I R 4950 5400 60 
F3 "D12_MISO" I R 4950 5500 60 
F4 "D11_MOSI" I R 4950 5600 60 
F5 "D8_TOUCH_CS" I R 4950 5900 60 
F6 "D4_SD_CS" I R 4950 6200 60 
F7 "D10_TFT_CS" I R 4950 5700 60 
F8 "D9_TFT_DC" I R 4950 5800 60 
$EndSheet
Text GLabel 9200 2700 0    60   Input ~ 0
LED_HL_OUT
Text GLabel 9200 2900 0    60   Input ~ 0
LED_HR_OUT
Text GLabel 9200 3300 0    60   Input ~ 0
LED_VL_OUT
Text GLabel 9200 3500 0    60   Input ~ 0
LED_VR_OUT
Wire Wire Line
	9200 2700 9300 2700
Wire Wire Line
	9200 2900 9300 2900
Wire Wire Line
	9200 3300 9300 3300
Wire Wire Line
	9200 3500 9300 3500
Text GLabel 10500 3150 2    60   Input ~ 0
GND
Wire Wire Line
	10500 3150 10450 3150
Text GLabel 3150 5700 2    60   Input ~ 0
LED_HR_OUT
Text GLabel 3150 5600 2    60   Input ~ 0
LED_HL_OUT
Text GLabel 3150 5800 2    60   Input ~ 0
LED_VL_OUT
Text GLabel 3150 5900 2    60   Input ~ 0
LED_VR_OUT
Wire Wire Line
	3150 5600 2950 5600
Wire Wire Line
	3150 5700 2950 5700
Wire Wire Line
	3150 5800 2950 5800
Wire Wire Line
	3150 5900 2950 5900
Text GLabel 1350 5600 0    60   Input ~ 0
LED_HL_IN
Text GLabel 1350 5700 0    60   Input ~ 0
LED_HR_IN
Text GLabel 1350 5800 0    60   Input ~ 0
LED_VL_IN
Text GLabel 1350 5900 0    60   Input ~ 0
LED_VR_IN
Wire Wire Line
	1350 5600 1550 5600
Wire Wire Line
	1350 5700 1550 5700
Wire Wire Line
	1350 5800 1550 5800
Wire Wire Line
	1350 5900 1550 5900
Text GLabel 10400 1550 2    60   Input ~ 0
SDA_5V
Text GLabel 10400 1700 2    60   Input ~ 0
SCL_5V
Wire Wire Line
	10400 1550 10250 1550
Wire Wire Line
	10400 1700 10250 1700
Text GLabel 8850 1550 0    60   Input ~ 0
VCC_5
Text GLabel 8850 1700 0    60   Input ~ 0
GND
Wire Wire Line
	8850 1550 8950 1550
Wire Wire Line
	8850 1700 8950 1700
Text GLabel 5050 5400 2    60   Input ~ 0
SCLK
Text GLabel 5050 5500 2    60   Input ~ 0
MISO
Text GLabel 5050 5600 2    60   Input ~ 0
MOSI
Text GLabel 5050 5700 2    60   Input ~ 0
TFT_CS
Text GLabel 5050 5800 2    60   Input ~ 0
TFT_DC
Text GLabel 5050 5900 2    60   Input ~ 0
TOUCH_CS
Text GLabel 5050 6200 2    60   Input ~ 0
SD_CS
Wire Wire Line
	5050 5400 4950 5400
Wire Wire Line
	5050 5500 4950 5500
Wire Wire Line
	5050 5600 4950 5600
Wire Wire Line
	5050 5700 4950 5700
Wire Wire Line
	5050 5800 4950 5800
Wire Wire Line
	5050 5900 4950 5900
Wire Wire Line
	5050 6200 4950 6200
Text GLabel 3200 7150 2    60   Input ~ 0
SDA_5V
Text GLabel 3200 7250 2    60   Input ~ 0
SCL_5V
Wire Wire Line
	3200 7150 2950 7150
Wire Wire Line
	3200 7250 2950 7250
Text GLabel 850  7150 0    60   Input ~ 0
SDA
Text GLabel 1300 7250 0    60   Input ~ 0
SCL
Wire Wire Line
	1550 7250 1300 7250
Wire Wire Line
	850  7150 900  7150
Wire Wire Line
	900  7150 1550 7150
Wire Notes Line
	550  5100 550  4350
Wire Notes Line
	550  4350 4000 4350
Wire Notes Line
	4000 4350 4000 5100
Wire Notes Line
	4000 5100 600  5100
Text Notes 600  4450 0    60   ~ 0
Spannungsversorgung FPGA
Text GLabel 3200 6950 2    60   Input ~ 0
MOTOR_PWM_5V
Text GLabel 1350 6950 0    60   Input ~ 0
MOTOR_PWM_33
Text GLabel 3200 7050 2    60   Input ~ 0
MOTOR_DIR_5V
Text GLabel 1350 7050 0    60   Input ~ 0
MOTOR_DIR_33
Wire Wire Line
	3200 6950 2950 6950
Wire Wire Line
	3200 7050 2950 7050
Wire Wire Line
	1550 6950 1350 6950
Wire Wire Line
	1550 7050 1350 7050
Wire Notes Line
	5900 5150 7250 5150
Wire Notes Line
	7250 6450 5900 6450
Wire Notes Line
	6900 6500 4050 6500
Wire Notes Line
	6900 7750 4050 7750
Wire Notes Line
	550  5100 650  5100
Text GLabel 900  7300 3    60   Input ~ 0
VCC_33
Wire Wire Line
	900  7300 900  7150
Connection ~ 900  7150
$EndSCHEMATC
