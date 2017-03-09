#include <string>
#include <unistd.h>
#include <stdint.h>

#include <thread>
#include <chrono>

//ALF INCLUDES
#include "alf_log.hpp"
#include "alf_data.hpp"
#include "alf_erno.h"
#include "alf_communication.hpp"
#include "alf_message_types.hpp"

//Port on which socket is created
#define COMPORT 6667

//Send/Receive Frequence in Hz
#define COMFREQ 50

Alf_Communication<Server> ServerComm;

Alf_Log log;

void writeData(void) {
	Alf_Drive_Info *info;

	while(1) {
		ServerComm.Write(*info);

		std::this_thread::sleep_for(std::chrono::milliseconds(1/COMFREQ*1000));
	}
}

void readData(void) {
	std::string rec;

	while(1) {
		Alf_Urg_Measurements_Buffer readBuffer(10);
		alf_mess_types msgType;

		ServerComm.Read(readBuffer, msgType);

		rec = "Speed: " + std::to_string(global_drive_command.speed);
		rec += ", Direction: " + std::to_string(global_drive_command.direction);
		rec += ", Angle: " + std::to_string(global_drive_command.angle);
		rec += ", Light: " + std::to_string(global_drive_command.light);

		log.alf_log_write(rec, log_info);

		std::this_thread::sleep_for(std::chrono::milliseconds(1/COMFREQ*1000));
	}
}

int main()
{
	log.alf_log_init("Melmac.log", log_debug, true);

	global_drive_info.speed = 42;
	global_drive_info.acceleration = 43;
	global_drive_info.lateral_acceleration = 44;
	global_drive_info.z_acceleration = 45;
	global_drive_info.Gyroscope_X = 1;
	global_drive_info.Gyroscope_Y = 1;
	global_drive_info.Gyroscope_Z = 1;
	global_drive_info.temperature = 13;

	if(ServerComm.Init(COMPORT)) {
		std::thread sendThread(writeData);
		std::thread recThread(readData);

		sendThread.join();
		recThread.join();

		ServerComm.EndCommunication();
	}
	else {
		Alf_Log::alf_log_write("Could not create socket", log_error);
	}


	Alf_Log::alf_log_write("Ending the application", log_info);
	Alf_Log::alf_log_end();

  	return 0;
}
