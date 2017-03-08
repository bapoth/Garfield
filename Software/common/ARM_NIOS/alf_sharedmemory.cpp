/*
 * alf_sharedmemory.cpp
 *
 *  Created on: 02.03.2017
 *      Author: florian
 */

#include "alf_sharedmemory.hpp"
#include "alf_message_types.hpp"
#include <cstdint>
#include <cstring>

#ifdef __linux__	// there are two implementations: one for the nios and one for the linux arm system
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <unistd.h>
#else

#endif

#define RW_REGISTER(reg) *(volatile uint32_t*)(reg)
#define RAW_NEXT_REG 0x04

using namespace std;

bool Alf_SharedMemoryComm::Init(uint32_t sh_mem_wr_addr, uint32_t wr_mut_addr, uint32_t wr_mb_addr, uint32_t sh_mem_rd_addr,
									 uint32_t rd_mut_addr, uint32_t rd_mb_addr, uint16_t cp_id, uint32_t addr_offset){
	bool write_mapped = false, read_mapped = false;

#ifdef __linux__	// using the shared memory within linux
	int fd;

	Alf_Log::alf_log_write("Initializing Hardware Communication...", log_info);
	cpu_id = cp_id;

	shared_memory_wr_addr = sh_mem_wr_addr + addr_offset;
	wr_mutex_addr = wr_mut_addr + addr_offset;
	wr_mailbox_addr = wr_mb_addr + addr_offset;

	shared_memory_rd_addr = sh_mem_rd_addr + addr_offset;
	rd_mutex_addr = rd_mut_addr + addr_offset;
	rd_mailbox_addr = wr_mb_addr + addr_offset;
	wr_memory_addr_offset = addr_offset;

	if((fd = open("/dev/mem", (O_RDWR))) == -1){
		Alf_Log::alf_log_write("Cannot open /dev/mem. Do you have permissions to do this?", log_error);
	}else{
		// this mapping only work with correct address alignment. Linux can only use mmap with multiple of 0x1000
		shared_memory_wr = mmap(NULL, shared_memory_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, shared_memory_wr_addr);
		wr_mutex = mmap(NULL, mutex_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, wr_mutex_addr);
		wr_mailbox = mmap(NULL, mailbox_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, wr_mailbox_addr);
		rd_mailbox = mmap(NULL, mailbox_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, rd_mailbox_addr);
		rd_mutex = mmap(NULL, mutex_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, rd_mutex_addr);
		shared_memory_rd = mmap(NULL, shared_memory_size, PROT_READ, MAP_SHARED, fd, shared_memory_rd_addr);

		if(shared_memory_wr == MAP_FAILED){
			Alf_Log::alf_log_write("Write Memory failed!", log_error);
		}
		else if(wr_mutex == MAP_FAILED){
			Alf_Log::alf_log_write("Write Mutex failed!", log_error);
		}
		else if(wr_mailbox == MAP_FAILED){
			Alf_Log::alf_log_write("Write Mailbox failed!", log_error);
		}
		else{	// all addresses for write could be initialized
			wr_memory_pos = 0;
			ResetWriteMutex();
			write_mapped = true;
		}

		if(shared_memory_rd == MAP_FAILED){
			Alf_Log::alf_log_write("Read Memory failed!", log_error);
		}
		else if(rd_mutex == MAP_FAILED){
			Alf_Log::alf_log_write("Read Mutex failed!", log_error);
		}
		else if(rd_mailbox == MAP_FAILED){
			Alf_Log::alf_log_write("Read Mailbox failed!", log_error);
		}
		else{	// all addresses for read could be initialized
			read_mapped = true;
		}
	}
	close(fd);

#else

#endif

	all_write_addr_mapped = write_mapped;
	all_read_addr_mapped = read_mapped;
	return (all_write_addr_mapped and all_read_addr_mapped);
}

bool Alf_SharedMemoryComm::TryLock(void *addr){
	bool success = false;
	uint32_t register_write = ((uint32_t(cpu_id) << 16) | 0x1);	//trying to write the cpu id and a 1 to the register
	RW_REGISTER(addr) = register_write;
	if(RW_REGISTER(addr) == register_write){	//checking if what we write is the same like what we now read
		success = true;	//if its the same, it works to get the lock, otherwise we have no lock on the shared memory
	}
	return success;
}

void Alf_SharedMemoryComm::WaitForLock(void *addr){
	while(not TryLock(addr));
}

void Alf_SharedMemoryComm::ReleaseLock(void *addr){
	RW_REGISTER(addr) = ((uint32_t(cpu_id) << 16) | 0x00);	//writing a 0 with the right cpu id means that we release the lock
}

bool Alf_SharedMemoryComm::WriteAndCommitMailbox(void *addr, uint32_t top_address){
	RW_REGISTER(addr + RAW_NEXT_REG) = top_address; //offset for pointer register, write the address to the mailbox' pointer register
	RW_REGISTER(addr) = 0x01; // now commit the message by writing any value to the command register, an interrupt will be triggered
	return true;
}

template <typename t>
alf_error Alf_SharedMemoryComm::HardwareWrite(const t &obj, uint32_t message_id, uint32_t size){
	alf_error ret_var = ALF_NO_ERROR;
	uint32_t message_start = wr_memory_pos;
	uint32_t new_pos = ((size/RAW_NEXT_REG)*RAW_NEXT_REG) + ((size%RAW_NEXT_REG) > 0 ? RAW_NEXT_REG : 0);
	if(all_write_addr_mapped){
		if(TryLock(wr_mutex)){
			//first writing the message ID to the shared memory
			if(wr_memory_pos + new_pos > shared_memory_size)
				wr_memory_pos = 0;	//starting writing from 0 if the storage is full
			RW_REGISTER(shared_memory_wr + wr_memory_pos) = message_id;
			wr_memory_pos += RAW_NEXT_REG;
			/// then copying the whole object to the memory
			std::memcpy(shared_memory_wr + wr_memory_pos, (void*)&obj, size);
			wr_memory_pos += new_pos;
			ReleaseLock(wr_mutex);
			WriteAndCommitMailbox(wr_mailbox, shared_memory_wr_addr - wr_memory_addr_offset + message_start);
		}else{
			ret_var = ALF_LOCK_MEMORY_FAILED;
		}
	}else{
		ret_var = ALF_NO_WELL_FPGABridge_MAPPING;
	}

	return ret_var;
}

alf_error Alf_SharedMemoryComm::Write(const Alf_Drive_Command &drive){
	return HardwareWrite(drive, ALF_DRIVE_COMMAND_ID, sizeof(drive));
}

void Alf_SharedMemoryComm::ResetWriteMutex(){
	RW_REGISTER(wr_mutex + 0x04) = 0x1;		// first write a 1 to the reset register which set this register to 0
	RW_REGISTER(wr_mutex) = (uint32_t(cpu_id) << 16 ) | 0x0;	// then give the mutex free by writing the cpu id(thats also the default value) and 0 to the register
}

void Alf_SharedMemoryComm::Read(){

}

