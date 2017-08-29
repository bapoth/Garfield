/*
 * breezyslam.hpp
 *
 *  Created on: 22.08.2017
 *      Author: bauma
 */

#ifndef BREEZYSLAM_HPP_
#define BREEZYSLAM_HPP_

#define DEFAULT_MAP_SIZE_PIXELS		800
#define DEFAULT_MAP_SIZE_METERS 	32
#define DEFAULT_LIDAR_DEVICE		(char *)"/dev/ttyACM0"
#define DEFAULT_SRC_PATH2MAP		(char *)"/home/ubuntu/bin/srcmap.pgm"
#define DEFAULT_DEST_PATH2MAP		(char *)"/home/ubuntu/bin/destmap.pgm"


#include "Laser.hpp"
#include "algorithms.hpp"


class BreezySLAM{
public:

    /**
    * length and width of the intern map in the slam-algorithm (map is a square).
    * length and width are expressed as number of pixels.
    */
	const int map_size_pixels;

    /**
    * length and width of the area to be mapped, in meters (area is a square).
    */
	const double map_size_meters;

    /**
    * path to the connected lidar-device.
    */
	const char * lidar_device;

    /**
    * Creates a BreezySLAM object.
    * @param nmap_size_pixels 	the size of the desired map (map is square)
    * @param nmap_size_meters 	the size of the area to be mapped, in meters
    * @param nlidar_device		the path to the connected lidar-device
    * @return a new BreezySLAM object
    */
	BreezySLAM(int nmap_size_pixels 	= DEFAULT_MAP_SIZE_PIXELS,
			   double nmap_size_meters	= DEFAULT_MAP_SIZE_METERS,
			   char * nlidar_device		= DEFAULT_LIDAR_DEVICE);

    /**
    * Deallocates this BreezySLAM object.
    */
	~BreezySLAM(void);

    /**
    * Start the slam-algorithm.
    * At first a saved intern map is loaded from a .pgm-File. The slam-algorithm
    * operates based on the loaded map.
    * When a loaded map is used, the slam-algorithm has to know the startposition.
    * @param startpos_x 		the x coordinate of the startposition in millimeters
    * @param startpos_y 		the y coordinate of the startposition in millimeters
    * @param startpos_degrees	the theta degress coordinate of the startposition in degrees
    * @param srcpath2map		the path to the source .pgm-File
    * @param use_srcpath2map	enables, if a map should be loaded from a .pgm-File
    * @return  0: successfull
    * 		  -1: connection with lidar failed
    * 		  -2: loading of pgm-File failed
    * 		  -3: running thread for breezyslam failed
    * 		  -4: startBreezySLAM() was invoked a second time without calling endBreezySLAM()
    */
	int startBreezySLAM(double startpos_x, double startpos_y, double startpos_degrees,
						char * srcpath2map=DEFAULT_SRC_PATH2MAP, bool use_srcpath2map=true);

    /**
    * Get the current map, which is intern in the slam-algorithm.
    * @param map 	address of pointer, which will point to the current map
    * 				memory for the map is allocated by the function itself
    * @note: dont forget to deallocate the memory for the map, if you dont need it anymore.
    * @return  0: successfull
    * 		  -1: getCurrentMap() was invoked without calling startBreezySLAM() before
    */
	int getCurrentMap(unsigned char ** map);

    /**
    * Get the current position, which is intern in the slam-algorithm.
    * @param x_mm			value, which will be set to the current X coordinate in millimeters
    * @param y_mm			value, which will be set to the current X coordinate in millimeters
    * @param theta_degrees	value, which will be set to the current rotation angle in degrees
    * @return  0: successfull
    * 		  -1: getCurrentPos() was invoked without calling startBreezySLAM() before
    */
	int getCurrentPos(double &x_mm, double &y_mm, double &theta_degrees);

    /**
    * Get the current position, which is intern in the slam-algorithm, as pixel.
    * @param x_mm			value, which will be set to the current X coordinate in pixel
    * @param y_mm			value, which will be set to the current X coordinate in pixel
    * @param theta_degrees	value, which will be set to the current rotation angle in degrees
    * @return  0: successfull
    * 		  -1: position could not be read from slam-algorithm
    */
	int getCurrentPosAsPixel(int &x_pix, int &y_pix, double &theta_degrees);

    /**
    * Save the current map, which is intern in the slam-algorithm, as an pgm-File.
    * @param destpath2map 	the path for the be generated .pgm-File
    * @return  0: successfull
    * 		  -1: opening of pgm-File failed
    * 		  -2: getting map failed
    */
	int saveCurrentMap(char * destpath2map=DEFAULT_DEST_PATH2MAP);

    /**
    * End the slam-algorithm.
    * Used resources for algorithm are deallocated.
    * @return  0: successfull
    * 		  -1: endBreezySLAM() was invoked without calling startBreezySLAM() before
    */
	int endBreezySLAM();


private:
    /**
    * pointer to object for using the lidarsensor
    */
	URG04LX * laser;

    /**
    * object for using the slam-algorithm
    */
	SinglePositionSLAM * slam;

    /**
    * thread, which is running the slam-algorithm
    */
    pthread_t threadSlamAlg;

    /**
    * value, which indicates to stop the running thread for the slam-algorithm
    */
	bool stopRunningSlamAlg;


    /**
    * method, which is executed by the running thread for executing the slam-algorithm.
    * the method does:
    * - Get the velocity & lidarsensor-values
    * - Update current map & position in slam-algorithm
    * @param arg	pointer to the related BreezySLAM-object
    */
	static void * runSlamAlgorithm(void * arg);


	/************************** Help methods ****************************/

    /**
    * Load a map from a pgm-File. The loaded map is used as base for the slam-algorithm.
    * @param mapbytes		array with allocated memory, which will be filled
    *  						with the content of the .pgm-File
    * @param path2pgm		the path of the .pgm-File to be loaded
    * @return  0: successfull
    * 		  -1: opening pgm-file failed
    * @note: dont forget to allocate the memory for mapbytes before calling this function.
    * 		 The size of the allocated memory must be: map_size_pixels * map_size_pixels
    */
	int load_map_from_file(char * mapbytes, char * path2pgm);

    /**
    * Convert x and y coordinates into index for map (as byte-array)
    * @param x		the x coordinate
    * @param y		the y coordinate
    * @return  corresponding index
    */
	int coords2index(double x,  double y);
};



#endif /* BREEZYSLAM_HPP_ */
