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
  lidar_device(nlidar_device), laser(NULL), slam(NULL), threadSlamAlg(),
  stopRunningSlamAlg(false)
{}

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
	    pObj->laser->getScan(lidarsensor_values);

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
		Alf_Log::alf_log_write("load_map_from_file(): " \
								"Opening pgm-file failed", log_info);
		return -1;	// opening pgm-file failed
	}

	/* Read pixels of the pgm-file into the mapbytes */
    char format[500];
    int sizex,sizey,res;

    fscanf(fp, "%s", format); // Read the header-information
    fscanf(fp, "%d", &sizex);
    fscanf(fp, "%d", &sizey);
    fscanf(fp, "%d", &res);


    for (int y=0; y<this->map_size_pixels; y++)
    {
        for (int x=0; x<this->map_size_pixels; x++)
        {
        	/* Read the pixel-information */
            fscanf(fp, "%d", &mapbytes[coords2index(x, this->map_size_pixels-y)]);
        }
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
	/* Check if: */
	/* startBreezySLAM() was invoked a second time
	   without calling endBreezySLAM() to end the previous execution */
	if((slam != NULL)||(laser != NULL)){
		Alf_Log::alf_log_write("startBreezySLAM(): "\
								"startBreezySLAM() was invoked a second time " \
								"without calling endBreezySLAM()", log_info);
		return -4;
	}

	/* Create object for connecting to lidarsensor */
	this->laser = new URG04LX;

    /* try connecting to lidarsensor */
    Alf_Log::alf_log_write("Connecting to lidar", log_info);
    bool is_connected = this->laser->connect(this->lidar_device);

    if(is_connected != 0)
    {
    	Alf_Log::alf_log_write("startBreezySLAM():" \
    							"Connection to lidar failed", log_info);
    	return -1;	// connection with lidar failed
    }

    /* If connection was successfull */
    /* show values of lidasensor*/
    Alf_Log::alf_log_write((std::string) *(this->laser), log_info);


    /* Create object for calculating slam-algorithm */
    /* By Creation the startposition is given to the algorithm */
    if(slam != NULL)  delete ((Deterministic_SLAM *)slam);
    this->slam
		= (SinglePositionSLAM*)new Deterministic_SLAM(*(this->laser),
													  this->map_size_pixels, this->map_size_meters,
													  startpos_x, startpos_y, startpos_degrees);

    /* Load saved map, as pgm-File, into the slam-algorithm */
    char * mapbytes;
    if(use_srcpath2map==true)
    {
    	mapbytes = new char[this->map_size_pixels * this->map_size_pixels];

        int load_file_failed = this->load_map_from_file(mapbytes, srcpath2map);
        if(load_file_failed != 0)
        {
        	Alf_Log::alf_log_write("startBreezySLAM():" \
        							"Loading of pgm-File failed", log_info);
        	delete [] mapbytes;
        	return -2;	// loading of pgm-File failed
        }
    }

    this->slam->setmap((unsigned char *)mapbytes);


    /* Start thread for running slam-algorithm */
    this->stopRunningSlamAlg = false;
    Alf_Log::alf_log_write("Start thread for running breezyslam", log_info);
    int rc = pthread_create(&(this->threadSlamAlg), NULL, runSlamAlgorithm, this);
    if (rc)
    {
    	Alf_Log::alf_log_write("startBreezySLAM():" \
    							"Running thread for breezyslam failed", log_info);
    	return -3;	// running thread for breezyslam failed
    }


    /* Clean up */
    if(use_srcpath2map==true) delete [] mapbytes;

    return 0;
}

int BreezySLAM::getCurrentMap(unsigned char ** map)
{
	/* Check if slam-algorithm was started */
	if((slam == NULL)||(laser == NULL))
	{
		Alf_Log::alf_log_write("getCurrentMap():" \
								"getCurrentMap() was invoked" \
								"without calling startBreezySLAM() before", log_info);
		return -1;
	}

	/* Create a byte array to receive the computed maps */
	*map = new unsigned char[this->map_size_pixels * this->map_size_pixels];

	/* Get current map from slam-algorithm */
	if(this->slam!=NULL)
		slam->getmap(*map);

	return 0;
}

int BreezySLAM::getCurrentPos(double &x_mm, double &y_mm, double &theta_degrees)
{
	/* Check if slam-algorithm was started */
	if((slam == NULL)||(laser == NULL))
	{
		Alf_Log::alf_log_write("getCurrentPos():" \
								"getCurrentPos() was invoked" \
								"without calling startBreezySLAM() before", log_info);
		return -1;
	}

	/* Get current position from slam-algorithm */
	Position currentPos;
	if(this->slam!=NULL)
		currentPos = slam->getpos();

	x_mm 			= currentPos.x_mm;
	y_mm 			= currentPos.y_mm;
	theta_degrees 	= currentPos.theta_degrees;

	return 0;
}

int BreezySLAM::getCurrentPosAsPixel(int &x_pix, int &y_pix, double &theta_degrees)
{
	/* Get current positon as millimeter */
	double x_mm, y_mm;
	int ret = this->getCurrentPos(x_mm, y_mm, theta_degrees);

	/* Check if position could be read */
	if(ret != 0)
	{
		Alf_Log::alf_log_write("getCurrentPosAsPixel():" \
								"Position could not be read from slam-algorithm", log_info);
		return -1;
	}

	/* Convert from millimeter to pixel */
	x_pix = (int)(x_mm / (this->map_size_meters * 1000. / this->map_size_pixels));
	y_pix = (int)(y_mm / (this->map_size_meters * 1000. / this->map_size_pixels));

	return 0;
}


int BreezySLAM::saveCurrentMap(char * destpath2map)
{
	/* Open/Create file for writing */
    FILE * output = fopen(destpath2map, "wt");
	if(!output)
	{
		Alf_Log::alf_log_write("saveCurrentMap():" \
								"Opening pgm-file failed", log_info);
		return -1;	// opening pgm-file failed
	}

	/* Get the current map */
	unsigned char * currentMap;
	int getMapSucceded = this->getCurrentMap(&currentMap);
	if(getMapSucceded!=0)
	{
		Alf_Log::alf_log_write("saveCurrentMap():" \
								"Getting map failed", log_info);

	    fclose(output);

		return -2;	// Getting map failed
	}

	/* Write/Save current map into opened pgm-File */
    fprintf(output, "P2\n%d %d 255\n", this->map_size_pixels, this->map_size_pixels);

    for (int y=0; y<this->map_size_pixels; y++)
    {
        for (int x=0; x<this->map_size_pixels; x++)
        {
            fprintf(output, "%d ", currentMap[coords2index(x, this->map_size_pixels-y)]);
            //Note: With "this->map_size_pixels-y" -> avoid mirror at x-axis
        }
        fprintf(output, "\n");
    }

    /* Clean up */
    delete [] currentMap;
    fclose(output);

	Alf_Log::alf_log_write("Map was saved successfully", log_info);

    return 0;
}

int BreezySLAM::endBreezySLAM()
{
	/* Check if slam-algorithm was started */
	if((slam == NULL)||(laser == NULL))
	{
		Alf_Log::alf_log_write("endBreezySLAM():" \
								"endBreezySLAM() was invoked" \
								"without calling startBreezySLAM() before", log_info);
		return -1;
	}

	/* Running thread should stop his loop and ends itself*/
	this->stopRunningSlamAlg = true;

	/* wait until running slam-algorithm-thread is finished */
	Alf_Log::alf_log_write("Wait until slam-algorithm-thread is finished", log_info);
	pthread_join(threadSlamAlg, NULL);

	/* Free slam object */
	Alf_Log::alf_log_write("Free: slam object", log_info);
	if(slam != NULL)  delete ((Deterministic_SLAM *)slam);
	slam = NULL;

	/* Disconnect lidarsensor */
	Alf_Log::alf_log_write("Free: laser object", log_info);
	if(laser != NULL) delete laser;
	laser = NULL;

	Alf_Log::alf_log_write("BreezySLAM ended", log_info);

	return 0;
}



