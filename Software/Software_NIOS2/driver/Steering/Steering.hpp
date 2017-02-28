/*!
 * @file Display.hpp
 */
#ifndef STEERING
#define STEERING

#define MAX_STEERING_ANGLE 120
#define MIN_PULSE_LENGTH_US 900
#define MAX_PULSE_LENGTH_US 2100
#define ONE_PERCENT_PERIOD_TIME 80

class Steering {
public:
	static void Init(alt_u8 max_angle_delta);
	static void Set(alt_8 angle);
private:
	static alt_u8 max_angle_delta;
};

#endif
