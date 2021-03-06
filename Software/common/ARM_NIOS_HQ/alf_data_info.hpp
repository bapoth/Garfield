/*!
 * @file
 * */
#ifndef ALF_DATA_INFO
#define ALF_DATA_INFO
#include "stdint.h"
#include <vector>

/*!
 * @brief The Alf_Drive_Info class holds the Infos for steering the Alf
 */
class Alf_Drive_Info {
public:
    /// This is the current speed
    uint8_t speed;
    /// This is the acceleration of the car
    float acceleration;
    /// This is the lateral acceleration of the car
    float lateral_acceleration;
    /// This is the acceleration in Z direction
    float z_acceleration;
    /// This is the Gyroscope value x axis
    float Gyroscope_X;
    /// This is the Gyroscope value y axis
    float Gyroscope_Y;
    /// This is the Gyroscope value z axis
    float Gyroscope_Z;
    /// This is the temperature
    float temperature;

    //LEX::get the timestamp from the freertos system while measuring!!
    // Timestamp for data
    double timestamp;

    ///For Copying the map-pgm-file from ARM to HQ:
    /// ARM advise HQ to copy the map-pgm-file
    bool invokeCopyMapFile;

    ///This variable holds the x-coordinate of the car's current position on the map
    int x_position;
    ///This variable holds the y-coordinate of the car's current position on the map
    int y_position;
    ///This variable holds the theta-coordinate of the car's current position on the map
    double theta_position;


};

class Alf_Drive_Command {
public:
    /// This variable holds the current speed (0 - 100%)
    uint8_t speed;
    /// This is the direction to drive (0: forward, 1: backward)
    uint8_t direction;
    /// This is the currents steering angle (-90 - 90°)
    int8_t angle;
    /// This holds the state of the light
    bool light;

    ///For Copying the map-pgm-file from ARM to HQ:
    /// HQ has successfully finished the copying of the file
    bool finishedCopyMapFile;
};

class Alf_Position{
public:
    ///This variable holds the x-coordinate of the car's current position on the map
    int x_position;
    ///This variable holds the y-coordinate of the car's current position on the map
    int y_position;
    ///This variable holds the theta-coordinate of the car's current position on the map
    double theta_position;
};

class Alf_PositionAndMap{
public:
    ///This variable holds the coordinate of the car's current position on the map
    ///in pixel.
	Alf_Position pixPosition;

	///This variable holds the map.
	///The map is an vector of char. Each char represents an Pixel value.
	std::vector<unsigned char> map;
};

/// global variables
extern Alf_Drive_Info global_drive_info;
extern Alf_Drive_Command global_drive_command;
extern Alf_Position global_alf_position;

#endif
