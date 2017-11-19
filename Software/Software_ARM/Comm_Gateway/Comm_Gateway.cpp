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

///SavingMapLocalOnVehicle Frequence in Hz
#define SAVEMAPLOCALFREQ 6


///BreezySLAM: File for saving the current map
#define SAVEPGMFILE "/home/ubuntu/bin/savingSlamMap.pgm"
///BreezySLAM: File, which is loaded into slam-algorithm
#define SOURCEPGMFILE "/home/ubuntu/bin/srcSlamMap.pgm"

///Communication ARM -> HQ:
///  Number of writeData-cycles until the position of the vehicle should be updated on HQ
#define UPDATEPOSITIONCOUNTER 100

///Alf Communication Server object
Alf_Communication<Server> ServerComm;

/// variable to let sleep the main thread
std::condition_variable Run_Main_Task_cond;
std::condition_variable Run_ServerWrite_Task;
/// variable to let sleep the saveCurrentMap thread
std::condition_variable Run_HQ_Relase_Map_Task;

/// mutex to for the main thread
std::mutex Run_Main_Task_mut;


Alf_Log mylog;

///Shared Memory Mailbox object
Alf_SharedMemoryComm shared_mem;

///Run or close threads
bool run_threads = true;
bool notify_ServerWrite_Task = false;
bool notify_HQ_Relase_Map_Task = false;

/// determines that the HQ should invoke a copying of the map-pgm-file
bool allowHQAccessMAP = false;

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

	std::mutex mux;
	std::unique_lock<std::mutex> lock(mux);

	/* Loop: save map into an pgm-File*/
	while(run_threads) {

		/* Save the current map */
		slamAlg.saveCurrentMap((char*)SAVEPGMFILE);

		if (DEBUG) printf("map is saved on vehicle\n");

		// ARM should send a request to HQ to invoke copying
		allowHQAccessMAP = true;

		// thread sleep until notified by reply of HQ
		while(not notify_HQ_Relase_Map_Task){
			Run_HQ_Relase_Map_Task.wait(lock);
		}
		if (DEBUG) printf("Continue saving-map-thread after receiving Reply from HQ\n");
		notify_HQ_Relase_Map_Task = false;

		/* Wait => avoid overloading of vehicle */
		std::this_thread::sleep_for(std::chrono::milliseconds(1/SAVEMAPLOCALFREQ*1000));
	}
	Alf_Log::alf_log_write("Ended saveCurrentMap thread", log_info);
}

void writeData(BreezySLAM slamAlg) {

	Alf_Log::alf_log_write("Started writeData thread", log_info);

	Velocities v;
	Alf_Drive_Info drive_info_local_copy;
	std::mutex mux;
	std::unique_lock<std::mutex> lock(mux);

	int currentXPos;
	int currentYPos;
	double currentThetaPos;
	int calculatePositionCounter=50;

	while(run_threads) {

		while(not notify_ServerWrite_Task){
			Run_ServerWrite_Task.wait(lock);
		}
		if(shared_mem.Read(drive_info_local_copy) == ALF_NO_ERROR){

			// decide if HQ should invoke a copying of map-pgm-file
			if(allowHQAccessMAP)
			{
				if (DEBUG) printf("Send Request from ARM to HQ\n");
				drive_info_local_copy.invokeCopyMapFile = true;
				allowHQAccessMAP = false;

			} else {
				drive_info_local_copy.invokeCopyMapFile = false;
			}

			// Decide, if the current position of the vehicle should also be send to HQ
			if(calculatePositionCounter == UPDATEPOSITIONCOUNTER) {

				// Get the current position of the vehicle
				slamAlg.getCurrentPosAsPixel(currentXPos, currentYPos, currentThetaPos);
				drive_info_local_copy.x_position = currentXPos;
				drive_info_local_copy.y_position = currentYPos;
				drive_info_local_copy.theta_position = currentThetaPos;
				calculatePositionCounter =0;
			}
			else
			{
				// Don´t update the position of the vehicle
				drive_info_local_copy.x_position = currentXPos;
				drive_info_local_copy.y_position = currentYPos;
				drive_info_local_copy.theta_position = currentThetaPos;
			}
			calculatePositionCounter++;

			// Send info to HQ
			ServerComm.Write(drive_info_local_copy);

			if (DEBUG) printf("servercomm write something\n");
			if (DEBUG) Alf_Log::alf_log_write("write Data thread doing something", log_info);
		}
		notify_ServerWrite_Task = false;
	}
	Alf_Log::alf_log_write("Ended writeData thread", log_info);
}


void readData(void) {
	std::string rec;
	Alf_Log::alf_log_write("Started readData thread", log_info);

	while(run_threads) {
		Alf_Urg_Measurements_Buffer readBuffer(10);
		alf_mess_types msgType;

		// Read the userinput from the string, which is sended by HQ
		ServerComm.Read(readBuffer, msgType);
		rec = "Speed: " + std::to_string(global_drive_command.speed);
		rec += ", Direction: " + std::to_string(global_drive_command.direction);
		rec += ", Angle: " + std::to_string(global_drive_command.angle);
		rec += ", Light: " + std::to_string(global_drive_command.light);

		if(DEBUG) printf("read Data: %s",rec.c_str());

		// Forward the userinput to the FPGA
		shared_mem.Write(global_drive_command);

		// Check, if HQ has finished copying the map-pgm-file.
		// If Yes, resource can be released
		if(global_drive_command.finishedCopyMapFile)
		{
			if(DEBUG) printf("Reply from HQ is received\n");
			notify_HQ_Relase_Map_Task = true;
			Run_HQ_Relase_Map_Task.notify_one();
			global_drive_command.finishedCopyMapFile = false;
		}

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

    /* Start the slam-algorithm "BreezySLAM" */
	BreezySLAM slamAlg;
	int slamStartSuccessful = slamAlg.startBreezySLAM(16000,16000,0,(char*)SOURCEPGMFILE);
	if (slamStartSuccessful != 0)
	{
        Alf_Log::alf_log_write("BreezySLAM could not be started successful -> Abort!", log_error);
        exit(EXIT_FAILURE);
	}

	if(shared_mem.Init(SHARED_MEMORY_MASTER_HPS_0_BASE, SHARED_MEMORY_MUTEX_MASTER_HPS_0_BASE, MAILBOX_ARM2NIOS_0_BASE, SHARED_MEMORY_MASTER_NIOS_0_BASE, SHARED_MEMORY_MUTEX_MASTER_NIOS_0_BASE, MAILBOX_NIOS2ARM_0_BASE, 01, HPS_OFFSET)) {

		shared_mem.EnableMailboxInterrupt();
		Alf_Log::alf_log_write("Initialized Mailbox", log_info);

		if(ServerComm.Init(COMPORT)) {

			Alf_Log::alf_log_write("Created socket", log_info);
			shared_mem.WriteInterfaceStatus = true;

			// Init all necessary threads
			std::thread hardwareReadThread(HardwareReadHandler);
			std::thread sendThread(writeData,slamAlg);
			std::thread recThread(readData);
			std::thread savingMapThread(saveCurrentMap, slamAlg);

			// Wait until Programm is stopped by user
			Run_Main_Task_cond.wait(lck);

			// Invoke the finishing of the created threads
			run_threads = false;

			// Wait until all threads are finished
			sendThread.join();
			recThread.join();
			hardwareReadThread.join();
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
