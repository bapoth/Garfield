/*!
 * @file Display.hpp
 */
#ifndef STEERING
#define STEERING

//maximum possible steering angle
#define MAX_STEERING_ANGLE 120

//Value at wich servo takes neutral position
#define NEUTRAL_POS_VALUE 48

/*!
 *class Steering for controlling the steering servo. No object is needed because of static functions
 */
class Steering {
public:
    /*!
     * Delete the default constructor
     */
    Steering() = delete;
	/*!
	* Init Function for initializing the Steering with the maximum steering angle
	* @param max_angle: This is the maximum steering angle in one direction (e.g. 50 deg). If the Set(alt_8 angle) is called with a bigger angle, it is set to max_angle_delta
	*/
	static void Init(alt_u8 max_angle);
	/*!
	* Set Function for setinga given angle to the servo
	* @param angle: This is the angle to set the servo (between -max_angle_delta and max_angle_delta)
	*/
	static void Set(alt_8 angle);
private:
	static alt_u8 max_angle_delta; /*!<Stores the maximum anghle of the servo to prevent it from to wide angles */
};

#endif
