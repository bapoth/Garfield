/*!
 * @file
 * */
#include "Comm_Gateway.hpp"
#include "hps_fpga_addresses.h"
#include <stdint.h>
#include <poll.h>
#include <fcntl.h>

#include "Robot_Alf.hpp"

///Port on which socket is created
#define COMPORT 6667

///Send/Receive Frequence in Hz
#define COMFREQ 50

///delay of info-transportation to HQ/GUI
#define COMPOSMAP 30
#define COMSAVEMAP 30

///BreezySLAM: File for saving the current map
#define SAVEPGMFILE "/home/ubuntu/bin/savingSlamMap.pgm"
///BreezySLAM: File, which is loaded into slam-algorithm
#define SOURCEPGMFILE "/home/ubuntu/bin/srcSlamMap.pgm"

///Alf Communication Server object
Alf_Communication<Server> ServerComm;

/// variable to let sleep the main thread
std::condition_variable Run_Main_Task_cond;
std::condition_variable Run_ServerWrite_Task;

/// mutex to for the main thread
std::mutex Run_Main_Task_mut;

///Alf Log
Alf_Log mylog;

///Shared Memory Mailbox object
Alf_SharedMemoryComm shared_mem;

///Run or close threads
bool run_threads = true;
bool notify_ServerWrite_Task = false;

int fd;


void Stop_Program(int sig) {

	Run_Main_Task_cond.notify_all();
}

/**
 * @brief This function is for interrupt handling in user mode. It should run in its own thread
 */
void HardwareReadHandler(void){
	Alf_Log::alf_log_write("Started HardwareReadHandler thread", log_info);
	Alf_Drive_Info drive_info_local_copy;
	uint32_t irq_info;
	int ret;
	ssize_t nb;
    struct pollfd fds = {
        .fd = fd,
        .events = POLLIN,
    };
	while(run_threads){

	    irq_info = 1; /* unmask */

	    nb = write(fd, &irq_info, sizeof(irq_info));
	    if (nb < sizeof(irq_info)){
	    	Alf_Log::alf_log_write("Cannot write to fd", log_error);
	    	run_threads = false;
	    	break;
	    }

		ret = poll(&fds, 1, -1);	//waiting until interrupt was coming

        if (ret >= 1) {
            nb = read(fd, &irq_info, sizeof(irq_info));
            if (nb == sizeof(irq_info)) {
            	shared_mem.ReadInterruptHandler();

            	notify_ServerWrite_Task = true;
            	Run_ServerWrite_Task.notify_one();
            }
        } else {
            Alf_Log::alf_log_write("Error while handling interrupt in user mode!", log_error);
            run_threads = false;
        }
	}
	uint32_t end = ALF_END_ID;
	shared_mem.Write(end);
	Alf_Log::alf_log_write("Ended HardwareReadHandler thread", log_info);
}

void saveCurrentMap(BreezySLAM slamAlg) {
	Alf_Log::alf_log_write("Started saveCurrentMap thread", log_info);

	/* Loop: save map into an pgm-File*/
	std::mutex mux;
	std::unique_lock<std::mutex> lock(mux);
	while(run_threads) {

		/* Save the current map */
		slamAlg.saveCurrentMap((char*)SAVEPGMFILE);

		/* Wait => avoid overloading of vehicle */
		std::this_thread::sleep_for(std::chrono::milliseconds(1/COMSAVEMAP*1000));
	}
	Alf_Log::alf_log_write("Ended saveCurrentMap thread", log_info);
}

void writeData(void) {
	Alf_Log::alf_log_write("Started writeData thread", log_info);

	double forward_dist =0;//new forward distance traveled in millimeters
	double theta_degrees=0;//new angular rotation in degrees
	double secounds=0;//secounds since last update
	double timestamp= time(NULL);//wie soll timestamp aussehen?
	Robot_Alf robot= Robot_Alf();
	float geschwindigkeit;
	Velocities v;
	Alf_Drive_Info drive_info_local_copy;
	std::mutex mux;
	std::unique_lock<std::mutex> lock(mux);


	while(run_threads) {

		//if(DEBUG) printf("write Data thread\n");
		while(not notify_ServerWrite_Task){
			Run_ServerWrite_Task.wait(lock);
		}
		if(shared_mem.Read(drive_info_local_copy) == ALF_NO_ERROR){
			//ServerComm.Write(drive_info_local_copy);
			//printf("before: gx= %.2f | gy= %.2f | accx= %.2f | accy= %.2f | time= %.1f \n",
			//		drive_info_local_copy.Gyroscope_X, drive_info_local_copy.Gyroscope_Y, drive_info_local_copy.acceleration, drive_info_local_copy.lateral_acceleration, drive_info_local_copy.timestamp);

			v= robot.computeVelocities(&drive_info_local_copy);
			geschwindigkeit= v.dxy_mm/(1000*v.dt_seconds);
			//printf("geschwindigkeit: %.2f m/s \n", geschwindigkeit);
			printf("v.sec: %.1f | v.dist: %.1f | v[m/s]= %.4f \n",v.dt_seconds, v.dxy_mm, geschwindigkeit);
			//printf("after: gx= %.2f | gy= %.2f | accx= %.2f | accy= %.2f | time= %.1f \n",
			//		drive_info_local_copy.Gyroscope_X, drive_info_local_copy.Gyroscope_Y, drive_info_local_copy.acceleration, drive_info_local_copy.lateral_acceleration, drive_info_local_copy.timestamp);
			/*printf("mit d= %.2f  || t= %d  | gx= %.2f | acc= %.2f |time= %d",
					v.dxy_mm,  v.dt_seconds, drive_info_local_copy.Gyroscope_X, drive_info_local_copy.acceleration, drive_info_local_copy.timestamp);
*/
			if (DEBUG) printf("servercomm write something\n");
			if (DEBUG) Alf_Log::alf_log_write("write Data thread doing something", log_info);
		}
		notify_ServerWrite_Task = false;
	}
	Alf_Log::alf_log_write("Ended writeData thread", log_info);
}

void writePositionAndMap(BreezySLAM slamAlg) {
	Alf_Log::alf_log_write("Started writePosition thread", log_info);

	int currentXPos;
	int currentYPos;
	double currentThetaPos;
	Alf_Position currentPosition;
	unsigned char * currentMap;
	int currentMapSize;
	std::vector<unsigned char> currentMapVector;
	Alf_PositionAndMap posAndMap;


	/* Loop: Update&Send current position and map to HQ/GUI */
	std::mutex mux;
	std::unique_lock<std::mutex> lock(mux);
	while(run_threads) {

			/* Get current position values from slam-algorithm */
			slamAlg.getCurrentPosAsPixel(currentXPos, currentYPos, currentThetaPos);
			currentPosition.x_position 		= currentXPos;
			currentPosition.y_position 		= currentYPos;
			currentPosition.theta_position 	= currentThetaPos;


			/* Get the current map from slam-algorithm */
			slamAlg.getCurrentMap(&currentMap);
			currentMapSize = slamAlg.map_size_pixels * slamAlg.map_size_pixels;
			currentMapVector.assign(currentMap, currentMap + currentMapSize);

			/* Set info into one datastructur */
			posAndMap.pixPosition = currentPosition;
			posAndMap.map		  = currentMapVector;

			/* Send to HQ/GUI */
			ServerComm.Write(posAndMap);
			if (DEBUG) printf("PositionAndMap thread write something\n");
			if (DEBUG) Alf_Log::alf_log_write("write PositionAndMap thread doing something", log_info);

			/* Clean up */
			if(currentMap != NULL)
			{
				delete [] currentMap;
				currentMap = NULL;
			}

			/* Wait => avoid overloading of vehicle */
			std::this_thread::sleep_for(std::chrono::milliseconds(1/COMPOSMAP*1000));
	}
	Alf_Log::alf_log_write("Ended writePositionAndMap thread", log_info);
}

void readData(void) {
	std::string rec;
	Alf_Log::alf_log_write("Started readData thread", log_info);

	while(run_threads) {
		Alf_Urg_Measurements_Buffer readBuffer(10);
		alf_mess_types msgType;

		ServerComm.Read(readBuffer, msgType);
		rec = "Speed: " + std::to_string(global_drive_command.speed);
		rec += ", Direction: " + std::to_string(global_drive_command.direction);
		rec += ", Angle: " + std::to_string(global_drive_command.angle);
		rec += ", Light: " + std::to_string(global_drive_command.light);

		//mylog.alf_log_write(rec, log_info);
		if(DEBUG) printf("read Data: %s",rec.c_str());

		shared_mem.Write(global_drive_command);

		std::this_thread::sleep_for(std::chrono::milliseconds(1/COMFREQ*1000));
	}
	Alf_Log::alf_log_write("Ended readData thread", log_info);
}

int main()
{
	std::unique_lock<std::mutex> lck(Run_Main_Task_mut);
	signal(SIGINT, Stop_Program);

	mylog.alf_log_init("Melmac.log", log_debug, true);

	global_drive_info.speed = 42;
	global_drive_info.acceleration = 43;
	global_drive_info.lateral_acceleration = 44;
	global_drive_info.z_acceleration = 45;
	global_drive_info.Gyroscope_X = 1;
	global_drive_info.Gyroscope_Y = 1;
	global_drive_info.Gyroscope_Z = 1;
	global_drive_info.temperature = 13;

    fd = open("/dev/uio0", O_RDWR);
    if (fd < 0) {
        Alf_Log::alf_log_write("Opening /dev/uio0 does not work -> Abort!", log_error);
        exit(EXIT_FAILURE);
    }
	if(shared_mem.Init(SHARED_MEMORY_MASTER_HPS_0_BASE, SHARED_MEMORY_MUTEX_MASTER_HPS_0_BASE, MAILBOX_ARM2NIOS_0_BASE, SHARED_MEMORY_MASTER_NIOS_0_BASE, SHARED_MEMORY_MUTEX_MASTER_NIOS_0_BASE, MAILBOX_NIOS2ARM_0_BASE, 01, HPS_OFFSET)) {

		shared_mem.EnableMailboxInterrupt();
		Alf_Log::alf_log_write("Initialized Mailbox", log_info);

		if(ServerComm.Init(COMPORT)) {

			/* Start the slam-algorithm "BreezySLAM" */
			BreezySLAM slamAlg;
			slamAlg.startBreezySLAM(16000,16000,0,(char*)SOURCEPGMFILE);

			Alf_Log::alf_log_write("Created socket", log_info);
			shared_mem.WriteInterfaceStatus = true;
			std::thread hardwareReadThread(HardwareReadHandler);
			std::thread sendThread(writeData);
			std::thread recThread(readData);
			std::thread posAndMapThread(writePositionAndMap, slamAlg);
			std::thread savingMapThread(saveCurrentMap, slamAlg);

			Run_Main_Task_cond.wait(lck);

			run_threads = false;

			sendThread.join();
			recThread.join();
			hardwareReadThread.join();
			posAndMapThread.join();
			savingMapThread.join();

			/* End the slam-algorithm "BreezySLAM" */
			slamAlg.endBreezySLAM();

			close(fd);
			ServerComm.EndCommunication();
		}
		else {
			Alf_Log::alf_log_write("Could not create socket", log_error);
		}
	}
	else {
		Alf_Log::alf_log_write("Could not initialize Mailbox", log_error);
	}


	Alf_Log::alf_log_write("Ending the application", log_info);
	Alf_Log::alf_log_end();

  	return 0;
}
