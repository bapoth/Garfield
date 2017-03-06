#include "tasks_nios.hpp"

#include "alt_types.h"

#include "mpu6050.hpp"
#include "ultrasonic.hpp"
#include "Steering.hpp"
#include "Rotary_Encoder.h"

#include "FreeRTOS.h"
#include "task.h"

//set FreeRTOS tick to 5ms

static const float pulses_to_meter 1.0;

static const alt_u8 max_steering_angle = 60;

static alt_u8 dummy_communication_steering_variable = 42;


/*
 * Task communication over static variables
 * */
static mpu6050::AccelerometerData global_acc_data = {0, 0, 0};
static mpu6050::GyroscopeData global_gyro_data = {0, 0, 0};
static mpu6050::temp global_temp_data = 0;

static alt_u16 global_us_front_left_data = 0;
static alt_u16 global_us_front_right_data = 0;
static alt_u16 global_us_rear_left_data = 0;
static alt_u16 global_us_rear_right_data = 0;

static alt_u32 global_rotary_data = 0;


void readMPU( void* p)
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;

	/* mpu */
	mpu6050 mpu(MPU6050_Addresses::DEVICE_0);
	mpu.InitMPU6050(AccelerometerSettings::RANGE_2G, GyroscopeSettings::RANGE_250_DEG);


	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	while(1)
	{
		// Wait for the next cycle ( every 50ms )
		vTaskDelayUntil( &xLastWakeTime, xFrequency );
		mpu.ReadAccelerometer(global_acc_data);
		mpu.ReadGyroscope(global_gyro_data);
		mpu.ReadTemperature(global_temp_data);

	}
}

void readUltraSonic ( void* p )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 13;

	 // Initialise the xLastWakeTime variable with the current time.
	 xLastWakeTime = xTaskGetTickCount();

	 UltraSonicDevice us_front_left(UltraSonicAddress::DEVICE_00);
	 UltraSonicDevice us_front_right(UltraSonicAddress::DEVICE_01);
	 UltraSonicDevice us_rear_left(UltraSonicAddress::DEVICE_03);
	 UltraSonicDevice us_rear_right(UltraSonicAddress::DEVICE_02);


	 while(1)
	 {
		 us_front_left.writeCMDRegister(UltraSonicCommands::START_MEAS_CM, true);
		 // Wait for the next cycle ( every 65ms )
		 vTaskDelayUntil( &xLastWakeTime, xFrequency );

		 us_front_left.readRegister(UltraSonicRegisterRead::ECHO_0x01, global_us_front_left_data);
		 us_rear_right.readRegister(UltraSonicRegisterRead::ECHO_0x01, global_us_front_right_data);
		 us_rear_left.readRegister(UltraSonicRegisterRead::ECHO_0x01, global_us_rear_left_data);
		 us_rear_right.readRegister(UltraSonicRegisterRead::ECHO_0x01, global_us_rear_right_data);
	 }
}

void readRotary ( void* p )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 10;

	 // Initialise the xLastWakeTime variable with the current time.
	 xLastWakeTime = xTaskGetTickCount();

	 while(1)
	 {
         TickType_t old_value = xLastWakeTime;
		 // Wait for the next cycle ( every 50ms )
		 vTaskDelayUntil( &xLastWakeTime, xFrequency );

		 //global_rotary_data = ROT_ENC_GetRotations(ROTARY_ENCODER_0_BASE);
         
         //Calculation of current speed
         alt_u32 curr_value = ROT_ENC_GetRotations(ROTARY_ENCODER_0_BASE);
         ROT_ENC_ClearCounter();
         alt_u8 speed = (curr_value * pulses_to_meter) / ((xLastWakeTime-old_value)*(1/configTICK_RATE_HZ));
	 }
}

void setMotor_and_Steering ( void* p )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 4;


	Steering::Init(max_steering_angle);

	 // Initialise the xLastWakeTime variable with the current time.
	 xLastWakeTime = xTaskGetTickCount();

	 while(1)
	 {
		 // Wait for the next cycle ( every 20ms )
		 vTaskDelayUntil( &xLastWakeTime, xFrequency );

		 Steering::Set(dummy_communication_steering_variable);
		 //set motor speed
	 }
}
