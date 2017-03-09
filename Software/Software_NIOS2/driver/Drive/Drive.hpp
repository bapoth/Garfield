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
     * Delete the default constructor
     */
    Drive() = delete;
    
	/*!
	*Method SetDriveSpeed for setting the speed and direction to the motor. The speed value gets rescaled by the maximum percent speed given by SetMaxSpeed(alt_u8 max_percent_speed)
	*@param[in] direction: 1: backwards, 0: forward
	*@param[in] speed: value from 0 - 255 for setting speed. SPEED_PRESCALER is divided by speed for setting max speed
	*/
	static void SetDriveSpeed(alt_u8 direction, alt_u8 speed);

	/*!
	*Method SetMaxSpeed for setting the max percentage speed. The speed value which is given by SetDriveSpeed gets rescaled to the maximum percentage speed value
	*@param[in] max_percent_speed is the maximum percentage speed value.
	*/
	static void SetMaxSpeed(alt_u8 max_percent_speed);
    
private:
    const static alt_u8 mot_dir_pin;
    static alt_u8 max_speed_percent;
};

#endif
