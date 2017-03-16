#include "Comm_Gateway.hpp"

///Port on which socket is created
#define COMPORT 6666

///Send/Receive Frequence in Hz
#define COMFREQ 50

///Mailbox defines
#define HPS_OFFSET 0xff200000
#define SHARED_MEMORY_MASTER_HPS_0_BASE 		0x60000
#define SHARED_MEMORY_MUTEX_MASTER_HPS_0_BASE 	0x50000
#define SHARED_MEMORY_MUTEX_MASTER_NIOS_0_BASE	0x80000
#define SHARED_MEMORY_MASTER_NIOS_0_BASE		0x90000
#define MAILBOX_ARM2NIOS_0_BASE					0x20000
#define MAILBOX_NIOS2ARM_0_BASE					0x70000

///Alf Communication Server object
Alf_Communication<Server> ServerComm;

/// variable to let sleep the main thread
std::condition_variable Run_Main_Task_cond;

/// mutex to for the main thread
std::mutex Run_Main_Task_mut;

///Alf Log
Alf_Log log;

///Shared Memory Mailbox object
Alf_SharedMemoryComm shared_mem;

///Run or close threads
bool run_threads = true;


void Stop_Program(int sig) {

	Run_Main_Task_cond.notify_all();
}

void writeData(void) {

	while(run_threads) {
		ServerComm.Write(global_drive_info);

		std::this_thread::sleep_for(std::chrono::milliseconds(1/COMFREQ*1000));
	}
}

void readData(void) {
	std::string rec;

	while(run_threads) {
		Alf_Urg_Measurements_Buffer readBuffer(10);
		alf_mess_types msgType;

		ServerComm.Read(readBuffer, msgType);

		rec = "Speed: " + std::to_string(global_drive_command.speed);
		rec += ", Direction: " + std::to_string(global_drive_command.direction);
		rec += ", Angle: " + std::to_string(global_drive_command.angle);
		rec += ", Light: " + std::to_string(global_drive_command.light);

		log.alf_log_write(rec, log_info);

		shared_mem.Write(global_drive_command);

		std::this_thread::sleep_for(std::chrono::milliseconds(1/COMFREQ*1000));
	}
}

int main()
{
	std::unique_lock<std::mutex> lck(Run_Main_Task_mut);
	signal(SIGINT, Stop_Program);

	log.alf_log_init("Melmac.log", log_debug, true);

	global_drive_info.speed = 42;
	global_drive_info.acceleration = 43;
	global_drive_info.lateral_acceleration = 44;
	global_drive_info.z_acceleration = 45;
	global_drive_info.Gyroscope_X = 1;
	global_drive_info.Gyroscope_Y = 1;
	global_drive_info.Gyroscope_Z = 1;
	global_drive_info.temperature = 13;

	if(shared_mem.Init(SHARED_MEMORY_MASTER_HPS_0_BASE, SHARED_MEMORY_MUTEX_MASTER_HPS_0_BASE, MAILBOX_ARM2NIOS_0_BASE, SHARED_MEMORY_MASTER_NIOS_0_BASE, SHARED_MEMORY_MUTEX_MASTER_NIOS_0_BASE, MAILBOX_NIOS2ARM_0_BASE, 01, HPS_OFFSET)) {

		Alf_Log::alf_log_write("Initialized Mailbox", log_info);

		if(ServerComm.Init(COMPORT)) {

			Alf_Log::alf_log_write("Created socket", log_info);
			std::thread sendThread(writeData);
			std::thread recThread(readData);

			//Run_Main_Task_cond.wait(lck); //waiting until this main thread should continue

			Run_Main_Task_cond.wait(lck);

			run_threads = false;

			sendThread.join();
			recThread.join();

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
