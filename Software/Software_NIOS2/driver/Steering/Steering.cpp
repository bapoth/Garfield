#include "alt_types.h"
#include "io.h"
#include "system.h"

#include "Steering.hpp"

alt_u8 Steering::max_angle_delta = 0;

void Steering::Init(alt_u8 max_angle) {
	if(max_angle > MAX_STEERING_ANGLE/2) {
		max_angle_delta = MAX_STEERING_ANGLE/2;
	}
	else {
		max_angle_delta = max_angle;
	}
}

void Steering::Set(alt_8 angle) {
	if(angle > max_angle_delta) {
		angle = max_angle_delta;
	}
	else if(angle < max_angle_delta * -1) {
		angle = max_angle_delta * -1;
	}
	else {
        static const float val_per_deg = 19/60;
        //PWMgen_Set_DutyCycle(NEUTRAL_POS_VALUE - (val_per_deg*angle));
	}
}
