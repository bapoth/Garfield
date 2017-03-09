#include "alt_types.h"
#include "io.h"
#include "system.h"

#include "Drive.hpp"
#include "PWM_Generator.h"
#include "Rotary_Encoder.h"

const alt_u8 Drive::mot_dir_pin = 0;
alt_u8 Drive::max_speed_percent = 50;

void Drive::SetDriveSpeed(alt_u8 direction, alt_u8 speed) {

	if(direction == 1) { //backwards
		alt_u8 i = IORD_8DIRECT(GARFIELD_GPIO_BASE,0);
		i |= 1 << mot_dir_pin;
		IOWR(GARFIELD_GPIO_BASE, 0, i);
	}
	else { //default is forward
		alt_u8 i = IORD_8DIRECT(GARFIELD_GPIO_BASE,0);
		i &= ~(1 << mot_dir_pin);
		IOWR(GARFIELD_GPIO_BASE, 0, i);
	}

	PWMGen_Set_DutyCycle(DRIVE_PWM_BASE, ((float)max_speed_percent/100)*speed);
}

void Drive::SetMaxSpeed(alt_u8 max_percent_speed) {
	if(max_percent_speed >= 100) {
		max_percent_speed = 100;
	}
	max_speed_percent = max_percent_speed;
}


