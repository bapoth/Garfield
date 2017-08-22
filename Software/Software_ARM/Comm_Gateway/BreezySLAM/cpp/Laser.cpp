/**
* 
* BreezySLAM: Simple, efficient SLAM in C++
*
* Laser.cpp - C++ code for Laser model class
*
* Original File from:
* Copyright (C) 2014 Simon D. Levy

File was changed for Garfield-Project.


* This code is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as 
* published by the Free Software Foundation, either version 3 of the 
* License, or (at your option) any later version.
* 
* This code is distributed in the hope that it will be useful,     
* but WITHOUT ANY WARRANTY without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License 
* along with this code.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <math.h>

#include <iostream>
#include <vector>
using namespace std; 

#include "Laser.hpp"
#include "../c/coreslam.h"


Laser::Laser(void)
{
   // this = new laser_t;

    this->scan_size = 0;
    this->scan_rate_hz = 0;
    this->detection_angle_degrees = 0;
    this->distance_no_detection_mm = 0;
    this->detection_margin = 0;
    this->offset_mm = 0;
}
/*URG04LX::URG04LX(const bool debug)

{
        this->hokuyo = hokuyo_create("URG04LX::URG04LX", debug);
}*/

URG04LX::~URG04LX()
{
        hokuyo_destroy(this->hokuyo, "URG04LX::~URG04LX");

}

int URG04LX::connect(const std::string device, int baud_rate)
{
        return hokuyo_connect(this->hokuyo, "URG04LX::connect", (char *)device.c_str(), baud_rate);
}

int URG04LX::getScan(unsigned int * range)
{
        return hokuyo_get_scan(this->hokuyo, "URG04LX::getScan", range);
}




