#ifndef Robot_Alf_hpp
#define Robot_Alf_hpp

#include "WheeledRobot.hpp"
#include "Velocities.hpp"

#include "alf_data.hpp"
#include "alf_data_info.hpp"

class Robot_Alf //: WheeledRobot
{

public:

	Robot_Alf();

    Velocities computeVelocities(Alf_Drive_Info * odometry/*,double timestamp/*, Velocities & velocities*/);

protected:

    void extractOdometry(
            double timestamp,
            float Gyrox_odometrie,
    		float acc_x_odometrie,
    		float acc_y_odometrie,
            double & timestampSeconds,
            float & degx,
            float & pos_x,
    		float & pos_y);

    void descriptorString(char * str);

private:

    double ticksToDegrees(double ticks);

    static const int TICKS_PER_CYCLE = 2000;

    double timestamp_seconds_prev;
    //float degrex_prev, posx_prev, posy_prev;
};


#endif
