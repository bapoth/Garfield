/*
 * breezyslam.cpp
 *
 *  Created on: 22.08.2017
 *      Author: bauma
 */

#include "usebreezyslam.hpp"

#include "alf_log.hpp"
#include "Velocities.hpp"


BreezySLAM::BreezySLAM(int nmap_size_pixels, double nmap_size_meters,
					   char * nlidar_device)
: map_size_pixels(nmap_size_pixels), map_size_meters(nmap_size_meters),
  lidar_device(nlidar_device), stopRunningSlamAlg(false)
{}
// ToDo: Anlegen slam als pointer auf default-object!!Muss man später freigeben!! oder NULL

BreezySLAM::~BreezySLAM()
{}


void * BreezySLAM::runSlamAlgorithm(void * arg)
{
	BreezySLAM * pObj = (BreezySLAM *)arg;

	// Loop: Get new velocity- and lidarsensor-values
	//       and update the current map & current position
	while(!pObj->stopRunningSlamAlg)
	{
	    /* Get the velocity-values out of the vehicle */
	    // ToDo: Load velocity-values with values:
	    //    		  this->dxy_mm = dxy_mm;
	    //            this->dtheta_degrees = dtheta_degrees;
	    //            this->dt_seconds = dtSeconds;
	    Velocities velocities_values(
	    		0,0,0);


	    /* Get the lidarsensor-values */
	    unsigned int lidarsensor_values[1000];
	    pObj->laser.getScan(lidarsensor_values);

	    // Update current map & position in slam-algorithm
	    pObj->slam->update((int*)lidarsensor_values, velocities_values);
	}

	/* End the thread */
	pthread_exit(NULL);
}


int BreezySLAM::load_map_from_file(char * mapbytes, char * path2pgm)
{
	/* Open file for reading */
	FILE * fp = fopen(path2pgm, "rt");
	if(!fp)
	{
		Alf_Log::alf_log_write("Opening pgm-file failed", log_info);
		return -1;	// opening pgm-file failed
	}

	/* Read pixels of the pgm-file into the mapbytes */
    char format[500];
    int sizex,sizey,res;

    fscanf(fp, "%s", format); // Read the header-information
    fscanf(fp, "%d", &sizex);
    fscanf(fp, "%d", &sizey);
    fscanf(fp, "%d", &res);

    for(int i=0; i< this->map_size_pixels*this->map_size_pixels; i++)
    {
    	/* Read the pixel-information */
        fscanf(fp, "%d", &mapbytes[i]);
    }

    /* Close file */
    fclose(fp);

    return 0;
}

int BreezySLAM::coords2index(double x,  double y)
{
    return y * this->map_size_pixels + x;
}


int BreezySLAM::startBreezySLAM(double startpos_x, double startpos_y, double startpos_degrees,
								char * srcpath2map, bool use_srcpath2map)
{
    /* try connecting to lidarsensor */
    Alf_Log::alf_log_write("Connecting to lidar", log_info);
    bool is_connected = this->laser.connect(this->lidar_device);

    if(is_connected != 0)
    {
    	Alf_Log::alf_log_write("Connection to lidar failed", log_info);
    	return -1;	// connection with lidar failed
    }

    /* If connection was successfull */
    /* show values of lidasensor*/
    Alf_Log::alf_log_write((std::string)this->laser, log_info);


    /* Create object for calculating slam-algorithm */
    /* By Creation the startposition is given to the algorithm */
    // Pat
    /*this->slam
		= (SinglePositionSLAM*)new Deterministic_SLAM(this->laser,
													  this->map_size_pixels, this->map_size_meters,
													  startpos_x, startpos_y, startpos_degrees);*/

    this->slam
		= (SinglePositionSLAM*)new RMHC_SLAM(this->laser, this->map_size_pixels,
											this->map_size_meters, 9999);


    /* Load saved map, as pgm-File, into the slam-algorithm */
    char * mapbytes;
    if(use_srcpath2map==true)
    {
    	mapbytes = new char[this->map_size_pixels * this->map_size_pixels];

        int load_file_failed = this->load_map_from_file(mapbytes, srcpath2map);
        if(load_file_failed != 0)
        {
        	Alf_Log::alf_log_write("Loading of pgm-File failed", log_info);
        	delete [] mapbytes;
        	return -2;	// loading of pgm-File failed
        }
    }


    // Pat
    this->slam->setmap((unsigned char *)mapbytes);


    /* Start thread for running slam-algorithm */
    this->stopRunningSlamAlg = false;
    Alf_Log::alf_log_write("Start thread for running breezyslam", log_info);
    int rc = pthread_create(&(this->threadSlamAlg), NULL, runSlamAlgorithm, this);
    if (rc)
    {
    	Alf_Log::alf_log_write("Running thread for breezyslam failed", log_info);
    	return -3;	// running thread for breezyslam failed
    }


    /* Clean up */
    if(use_srcpath2map==true) delete [] mapbytes;

    return 0;
}

void BreezySLAM::getCurrentMap(unsigned char ** map)
{
	/* Create a byte array to receive the computed maps */
	*map = new unsigned char[this->map_size_pixels * this->map_size_pixels];

	/* Get current map from slam-algorithm */
	slam->getmap(*map);
}

void BreezySLAM::getCurrentPos(double &x_mm, double &y_mm, double &theta_degrees)
{
	/* Get current position from slam-algorithm */
	Position currentPos = slam->getpos();

	x_mm 			= currentPos.x_mm;
	y_mm 			= currentPos.y_mm;
	theta_degrees 	= currentPos.theta_degrees;
}

int BreezySLAM::saveCurrentMap(char * destpath2map)
{
	/* Open/Create file for writing */
    FILE * output = fopen(destpath2map, "wt");
	if(!output)
	{
		Alf_Log::alf_log_write("Opening pgm-file failed", log_info);
		return -1;	// opening pgm-file failed
	}

	/* Get the current map */
	unsigned char * currentMap;
	this->getCurrentMap(&currentMap);

	/* Write/Save current map into opened pgm-File */
    fprintf(output, "P2\n%d %d 255\n", this->map_size_pixels, this->map_size_pixels);

    for (int y=0; y<this->map_size_pixels; y++)
    {
        for (int x=0; x<this->map_size_pixels; x++)
        {
            fprintf(output, "%d ", currentMap[coords2index(x, y)]);
        }
        fprintf(output, "\n");
    }

    /* Clean up */
    delete [] currentMap;
    fclose(output);

    return 0;
}

void BreezySLAM::endBreezySLAM()
{
	/* Running thread should stop his loop and ends itself*/
	this->stopRunningSlamAlg = true;

	/* wait until running slam-algorithm-thread is finished */
	Alf_Log::alf_log_write("Wait until thread is finished", log_info);
	pthread_join(threadSlamAlg, NULL);

	/* Free slam object */
	// ToDo: Only delete, if slam != NULL
	delete ((Deterministic_SLAM *)slam);

	// ToDo: Disconnect lidarsensor
}



