#include "alt_types.h"
#include "io.h"
#include "system.h"

#include "Drive.hpp"
#include "PWM_Generator.h"
#include "Rotary_Encoder.h"

const static alt_u8 Drive::mot_dir_pin = 0;
const static alt_u8 Drive::speed_prescaler = 4;

void Drive::SetDriveSpeed(alt_u8 direction, alt_u8 speed) {

	if(direction == 1) { //backwards
		alt_u8 i = IORD_8DIRECT(GARFIELD_GPIO_BASE,0);
		i |= 1 << MOT_DIR_PIN;
		IOWR(GARFIELD_GPIO_BASE, 0, i);
	}
	else { //default is forward
		alt_u8 i = IORD_8DIRECT(GARFIELD_GPIO_BASE,0);
		i &= ~(1 << MOT_DIR_PIN);
		IOWR(GARFIELD_GPIO_BASE, 0, i);
	}
	PWMGen_Set_DutyCycle(DRIVE_PWM_BASE, speed/SPEED_PRESCALER);
}


