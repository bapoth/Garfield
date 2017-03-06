/*!
 * @file Drive.hpp
 */
#ifndef DRIVE
#define DRIVE

/*!
 *class Drive for setting the speed an direction and getting the speed from the rotary encoder
 */
class Drive {
public:

	/*!
	*Method SetDriveSpeed for setting the speed and direction to the motor
	*@param[in] direction: 1: backwards, 0: forward
	*@param[in] speed: value from 0 - 255 for setting speed. SPEED_PRESCALER is divided by speed for setting max speed
	*/
	static void SetDriveSpeed(alt_u8 direction, alt_u8 speed);
    
private:
    const static alt_u8 mot_dir_pin;
    const static speed_prescaler;
};

#endif
