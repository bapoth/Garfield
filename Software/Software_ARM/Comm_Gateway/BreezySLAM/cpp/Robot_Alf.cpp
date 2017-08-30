#ifndef Robot_Alf_cpp
#define Robot_Alf_cpp

#include "Robot_Alf.hpp"
#include "Velocities.hpp"
#include <math.h>

    void Robot_Alf::extractOdometry(
        double timestamp,//timestamp in millisecounds
        float Gyrox_odometrie,
		float acc_x_odometrie,
		float acc_y_odometrie,
        double & timestampSeconds,
        float & degx,
        float & pos_x,
		float & pos_y)
    {
        // Convert microseconds to seconds, ticks to angles
        timestampSeconds = 0.005*timestamp;//umrechnung tick von freertos auf sekunden(vgl. configTICK_RATE_HZ in FreeRTOSconfig.h)
        double timediff;
        if(timestamp_seconds_prev == 0)//falls Timestamp noch nicht gesetzt wurde, wird er hier gesetzt
        {
            timestamp_seconds_prev = timestampSeconds;
            printf("die zeit wurde initialisiert\n");
        }
        //printf("extractOdometry timesakt= %.4f | timelast: %.4f | accx_od: %.1f \n", timestampSeconds,timestamp_seconds_prev, acc_x_odometrie);
        /*leftWheelDegrees = ticksToDegrees(leftWheelOdometry);
        rightWheelDegrees = ticksToDegrees(rightWheelOdometry);*/


        timediff=(timestampSeconds - timestamp_seconds_prev);
        printf("timediff= %.1f",timediff);
        pos_x= 0.5f* 9.81*acc_x_odometrie/*g-> a[m/s^2]*/ * (timestampSeconds - timestamp_seconds_prev)*(timestampSeconds - timestamp_seconds_prev)/*t2*/ * 1000/*m->mm*/; // x=1/2* a * t^2; m-> mm
        pos_y= 0.5f* 9.81*acc_y_odometrie * (timestampSeconds - timestamp_seconds_prev)*(timestampSeconds - timestamp_seconds_prev) * 1000;
        degx= Gyrox_odometrie * (timestampSeconds - timestamp_seconds_prev);//degree= (degree per secound) * t
        printf("accx: %.6f | posx: %.6f | dt= %.1f \n",acc_x_odometrie, pos_x, (timestampSeconds - timestamp_seconds_prev));

        timestamp_seconds_prev = timestampSeconds;
    }

    void Robot_Alf::descriptorString(char * str)
    {
        sprintf(str, "ticks_per_cycle=%d", this->TICKS_PER_CYCLE);
    }

    double Robot_Alf::ticksToDegrees(double ticks)
    {
        return ticks * (180. / this->TICKS_PER_CYCLE);
    }

	Robot_Alf::Robot_Alf()/* : WheeledRobot(
         77,     // wheelRadiusMillimeters
        165)     // halfAxleLengthMillimeters*/
    {
		timestamp_seconds_prev=0;
    }

    Velocities Robot_Alf::computeVelocities(Alf_Drive_Info * odometry/*, double timestamp/*, Velocities & velocities*/)
    {
       /* return WheeledRobot::computeVelocities(
            odometry[0],
            odometry[1],
            odometry[2]);*/

	    Velocities ret_velocities;

	    double timestamp_seconds_curr;
	    float degx,posx,posy;

    	//1: mit extractOdometrie die odometriedaten in richtige absolutwerte bringen (z.b g-> m/s bzw. in distanz)
	    this->extractOdometry(odometry->timestamp, odometry->Gyroscope_X, odometry->acceleration, odometry->lateral_acceleration,
	        timestamp_seconds_curr, degx, posx, posy);

    	//2: die absolutwerte in relative werte umändern(vorherigen wert abziehen/addieren)
	    ret_velocities.dt_seconds=timestamp_seconds_curr/1000;//-timestamp_seconds_prev;
	    ret_velocities.dtheta_degrees=degx;
	    ret_velocities.dxy_mm=sqrt(posx*posy);


       timestamp_seconds_prev = timestamp_seconds_curr;
	   return  ret_velocities;


	    /*
	    if (this->timestamp_seconds_prev > 0)
	    {
	        double left_diff_degrees = left_wheel_degrees_curr - this->left_wheel_degrees_prev;
	        double right_diff_degrees = right_wheel_degrees_curr - this->right_wheel_degrees_prev;

	        velocities.dxy_mm =  this->wheel_radius_mm * (radians(left_diff_degrees) + radians(right_diff_degrees));

	        velocities.dtheta_degrees = this->wheel_radius_mm / this->half_axle_length_mm *
	        (right_diff_degrees - left_diff_degrees);

	        velocities.dt_seconds = timestamp_seconds_curr - timestamp_seconds_prev;
	    }

	    // Store current odometry for next time
	    this->timestamp_seconds_prev = timestamp_seconds_curr;
	    this->left_wheel_degrees_prev = left_wheel_degrees_curr;
	    this->right_wheel_degrees_prev = right_wheel_degrees_curr;

	    return velocities;*/



    }

#endif
