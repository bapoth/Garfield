/**
 * @file
 * @brief
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
#include "alf_log.hpp"
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

	_cpu_id = cp_id;

	_shared_memory_wr_addr = sh_mem_wr_addr + addr_offset;
	_wr_mutex_addr = wr_mut_addr + addr_offset;
	_wr_mailbox_addr = wr_mb_addr + addr_offset;

	_shared_memory_rd_addr = sh_mem_rd_addr + addr_offset;
	_rd_mutex_addr = rd_mut_addr + addr_offset;
	_rd_mailbox_addr = rd_mb_addr + addr_offset;
	_wr_memory_addr_offset = addr_offset;

#ifdef __linux__	// using the shared memory within linux
	int fd;

	Alf_Log::alf_log_write("Initializing Hardware Communication...", log_info);

	if((fd = open("/dev/mem", (O_RDWR))) == -1){
		Alf_Log::alf_log_write("Cannot open /dev/mem. Do you have permissions to do this?", log_error);
	}else{
		// this mapping only work with correct address alignment. Linux can only use mmap with multiple of 0x1000
		_shared_memory_wr = mmap(NULL, _shared_memory_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, _shared_memory_wr_addr);
		_wr_mutex = mmap(NULL, _mutex_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, _wr_mutex_addr);
		_wr_mailbox = mmap(NULL, _mailbox_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, _wr_mailbox_addr);
		_rd_mailbox = mmap(NULL, _mailbox_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, _rd_mailbox_addr);
		_rd_mutex = mmap(NULL, _mutex_size, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, _rd_mutex_addr);
		_shared_memory_rd = mmap(NULL, _shared_memory_size, PROT_READ, MAP_SHARED, fd, _shared_memory_rd_addr);

		if(_shared_memory_wr == MAP_FAILED){
			Alf_Log::alf_log_write("Write Memory failed!", log_error);
		}
		else if(_wr_mutex == MAP_FAILED){
			Alf_Log::alf_log_write("Write Mutex failed!", log_error);
		}
		else if(_wr_mailbox == MAP_FAILED){
			Alf_Log::alf_log_write("Write Mailbox failed!", log_error);
		}
		else{	// all addresses for write could be initialized
			_wr_memory_pos = 0;
			ResetWriteMutex();
			write_mapped = true;
		}

		if(_shared_memory_rd == MAP_FAILED){
			Alf_Log::alf_log_write("Read Memory failed!", log_error);
		}
		else if(_rd_mutex == MAP_FAILED){
			Alf_Log::alf_log_write("Read Mutex failed!", log_error);
		}
		else if(_rd_mailbox == MAP_FAILED){
			Alf_Log::alf_log_write("Read Mailbox failed!", log_error);
			DisableMailboxInterrupt();
		}
		else{	// all addresses for read could be initialized
			read_mapped = true;
		}
	}
	close(fd);

#else
	_shared_memory_wr = (void*)_shared_memory_wr_addr;
	_shared_memory_rd = (void*)_shared_memory_rd_addr;
	_wr_mutex = (void*)_wr_mutex_addr;
	_rd_mutex = (void*)_rd_mutex_addr;
	_wr_mailbox = (void*)_wr_mailbox_addr;
	_rd_mailbox = (void*)_rd_mailbox_addr;
	_wr_memory_pos = 0;
	ResetWriteMutex();
	DisableMailboxInterrupt();
	write_mapped = true;
	read_mapped = true;
#endif

	_all_write_addr_mapped = write_mapped;
	_all_read_addr_mapped = read_mapped;
	return (_all_write_addr_mapped and _all_read_addr_mapped);
}

bool Alf_SharedMemoryComm::TryLock(void *addr){
	bool success = false;
	uint32_t register_write = ((uint32_t(_cpu_id) << 16) | 0x1);	//trying to write the cpu id and a 1 to the register
	RW_REGISTER(addr) = register_write;
	if(RW_REGISTER(addr) == register_write){	//checking if what we write is the same like what we now read
		success = true;	//if its the same, it works to get the lock, otherwise we have no lock on the shared memory
	}
	return success;
}

void Alf_SharedMemoryComm::DisableMailboxInterrupt(){
	RW_REGISTER(_rd_mailbox + RAW_NEXT_REG*3) = 0x0;
}

void Alf_SharedMemoryComm::EnableMailboxInterrupt(){
	RW_REGISTER(_rd_mailbox + RAW_NEXT_REG*3) = 0x03;
}

void Alf_SharedMemoryComm::WaitForLock(void *addr){
	while(not TryLock(addr));
}

void Alf_SharedMemoryComm::ReleaseLock(void *addr){
	RW_REGISTER(addr) = ((uint32_t(_cpu_id) << 16) | 0x00);	//writing a 0 with the right cpu id means that we release the lock
}

bool Alf_SharedMemoryComm::WriteAndCommitMailbox(const void *addr, const uint32_t top_address, const uint32_t &message_id){
	RW_REGISTER(addr + RAW_NEXT_REG) = top_address; //offset for pointer register, write the address to the mailbox' pointer register
	RW_REGISTER(addr) = message_id; // now commit the message by writing any value to the command register, an interrupt will be triggered
	return true;
}

template <typename t>
alf_error Alf_SharedMemoryComm::HardwareWrite(const t &obj, const uint32_t &message_id, const uint32_t &size){
	alf_error ret_var = ALF_NO_ERROR;
	uint32_t message_start = _wr_memory_pos;
	uint32_t new_pos = ((size/RAW_NEXT_REG)*RAW_NEXT_REG) + ((size%RAW_NEXT_REG) > 0 ? RAW_NEXT_REG : 0);
	if(_all_write_addr_mapped){
		if(TryLock(_wr_mutex)){
			if(_wr_memory_pos + new_pos > _shared_memory_size)
				_wr_memory_pos = 0;	//starting writing from 0 if the storage is full
			/// then copying the whole object to the memory
			std::memcpy(_shared_memory_wr + _wr_memory_pos, (void*)&obj, size);
			_wr_memory_pos += new_pos;
			ReleaseLock(_wr_mutex);
			WriteAndCommitMailbox(_wr_mailbox, _shared_memory_wr_addr - _wr_memory_addr_offset + message_start, message_id);
		}else{
			ret_var = ALF_LOCK_MEMORY_FAILED;
		}
	}else{
		ret_var = ALF_NO_WELL_FPGABridge_MAPPING;
	}

	return ret_var;
}

template <typename t>
alf_error Alf_SharedMemoryComm::HardwareRead(t &obj, const uint32_t &size, const uint32_t &addr){
	alf_error ret_var = ALF_NO_ERROR;
	if(_all_write_addr_mapped){
		if(TryLock(_rd_mutex)){
			std::memcpy((void*)&obj, (void*)addr, size);
			ReleaseLock(_rd_mutex);
		}else
			ret_var = ALF_LOCK_MEMORY_FAILED;
	}else
		ret_var = ALF_NO_WELL_FPGABridge_MAPPING;
	return ret_var;
}

alf_error Alf_SharedMemoryComm::Write(const Alf_Drive_Command &drive){
	return HardwareWrite(drive, ALF_DRIVE_COMMAND_ID, sizeof(drive));
}

alf_error Alf_SharedMemoryComm::Write(const Alf_Drive_Info &drive){
	return HardwareWrite(drive, ALF_DRIVE_INFO_ID, sizeof(drive));
}

void Alf_SharedMemoryComm::ResetWriteMutex(){
	RW_REGISTER(_wr_mutex + 0x04) = 0x1;		// first write a 1 to the reset register which set this register to 0
	RW_REGISTER(_wr_mutex) = (uint32_t(_cpu_id) << 16 ) | 0x0;	// then give the mutex free by writing the cpu id(thats also the default value) and 0 to the register
}

void Alf_SharedMemoryComm::ReadInterruptHandler(void){
	mailbox_s act_var;
	act_var.reg = RW_REGISTER(_rd_mailbox + RAW_NEXT_REG);	//first read the address register
	uint32_t message_id = RW_REGISTER(_rd_mailbox); 	// then read the message id which is communicated and implies to the sender that we read the message completely
		switch (message_id) {
			case ALF_DRIVE_INFO_ID:
				_buffer_drive_info.push(act_var);
				break;
			case ALF_DRIVE_COMMAND_ID:
				_buffer_drive_command.push(act_var);
				break;
			default:
				break;
	}
}

alf_error Alf_SharedMemoryComm::Read(Alf_Drive_Info &drive){
	if(not _buffer_drive_info.empty()){
		mailbox_s top = _buffer_drive_info.top();
		_buffer_drive_info.pop();	//"remove" the top object
		return HardwareRead(drive, sizeof(drive), top.reg + _wr_memory_addr_offset);
	}else
		return ALF_NOTHING_IN_BUFFER;
}

alf_error Alf_SharedMemoryComm::Read(Alf_Drive_Command &drive){
	if(not _buffer_drive_command.empty()){
		mailbox_s top = _buffer_drive_command.top();
		_buffer_drive_command.pop();
		return HardwareRead(drive, sizeof(drive), top.reg + _wr_memory_addr_offset);
	}else
		return ALF_NOTHING_IN_BUFFER;
}