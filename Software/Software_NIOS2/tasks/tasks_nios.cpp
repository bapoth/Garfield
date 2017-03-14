#include "tasks_nios.hpp"

#include "alt_types.h"

#include "mpu6050.hpp"
#include "ultrasonic.hpp"
#include "Steering.hpp"
#include "Drive.hpp"
#include "alf_data_info.hpp"
#include "Rotary_Encoder.h"

#include "FreeRTOS.h"
#include "task.h"


Alf_SharedMemoryComm sharedMem{};


static const float pulses_to_meter = 1.0;
static const alt_u8 max_steering_angle = 60;
static const alt_u8 emergency_stop_distance = 12;
static const alt_u8 close_range_distance = 25;
static const alt_u8 close_range_speed = 20;

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


void readMPU( void* p)
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 55;

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

		global_drive_info.acceleration = global_acc_data.acc_x;
		global_drive_info.lateral_acceleration = global_acc_data.acc_y;
		global_drive_info.z_acceleration = global_acc_data.acc_z;
		global_drive_info.Gyroscope_X = global_gyro_data.gyro_x;
		global_drive_info.Gyroscope_Y = global_gyro_data.gyro_y;
		global_drive_info.Gyroscope_Z = global_gyro_data.gyro_z;
		global_drive_info.temperature = global_temp_data;
	}
}

void readUltraSonic ( void* p )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 70;

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

		 // check front
		 if(global_us_front_left_data < emergency_stop_distance || global_us_front_right_data < emergency_stop_distance)
		 { // emergency stop front
			 Drive::setBlock_Front(true);
		 }
		 else if (global_us_front_left_data < close_range_distance || global_us_front_right_data < close_range_distance)
		 { // close range, careful
			 Drive::SetMaxSpeed(close_range_speed);
		 }
		 else
		 { // nothing in sight -> full throttle
			 Drive::SetMaxSpeed(Drive::GetMax_Speed_Percent());
			 Drive::setBlock_Front(false);
		 }

		 // check rear
		 if(global_us_rear_left_data < emergency_stop_distance || global_us_rear_right_data < emergency_stop_distance)
		 { // emergency stop back
			 Drive::SetBlock_Rear(true);
		 }
		 else if (global_us_rear_left_data < close_range_distance || global_us_rear_right_data < emergency_stop_distance)
		 { // close range, careful
			 Drive::SetMaxSpeed(close_range_speed);
		 }
		 else
		 { // nothing in sight -> full throttle
			 Drive::SetMaxSpeed(Drive::GetMax_Speed_Percent());
			 Drive::SetBlock_Rear(false);
		 }

	 }
}

void readRotary ( void* p )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 55;

	 // Initialise the xLastWakeTime variable with the current time.
	 xLastWakeTime = xTaskGetTickCount();

	 while(1)
	 {
         TickType_t old_value = xLastWakeTime;
		 // Wait for the next cycle ( every 50ms )
		 vTaskDelayUntil( &xLastWakeTime, xFrequency );
         
         //Calculation of current speed
         alt_u32 curr_value = ROT_ENC_GetRotations(ROTARY_ENCODER_0_BASE);
         ROT_ENC_ClearCounter();
         alt_u8 speed = (curr_value * pulses_to_meter) / ((xLastWakeTime-old_value)*(1.0/configTICK_RATE_HZ));
         global_drive_info.speed = speed;
	 }
}

void setMotor_and_Steering ( void* p )
{
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 25;


	Steering::Init(max_steering_angle);

	// Initialise the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	Alf_Drive_Command drive{};

	alt_u8 real_speed = 0;
	alt_u8 real_direction = 0;

	while(1)
	{
		// Wait for the next cycle ( every 20ms )
		vTaskDelayUntil( &xLastWakeTime, xFrequency );

		vTaskSuspendAll();
		sharedMem.Read(drive);
		xTaskResumeAll();

		real_speed = drive.speed;
		real_direction = drive.direction;

		Steering::Set(drive.angle);

		if(Drive::GetBlock_Front() == true && real_direction == 0)
		{ //drive forward -> stop motor
			real_speed = 0;
			real_direction = 0;
		}
		if(Drive::GetBlock_Rear() == true && real_direction == 1)
		{ //drive backward -> stop motor
			real_speed = 0;
			real_direction = 1;
		}
		Drive::SetDriveSpeed(real_direction, real_speed);
	}
}

void Mailbox_isr(void* ptr, alt_u32 a)
{
	alt_u32 h = alt_irq_disable_all();
	sharedMem.ReadInterruptHandler();
	IORD(MAILBOX_ARM2NIOS_0_BASE, 0);
	alt_irq_enable_all(h);
}
