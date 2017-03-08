/*
 * alf_sharedmemory.cpp
 *
 *  Created on: 02.03.2017
 *      Author: florian
 */

#include "alf_sharedmemory.hpp"
#include <fcntl.h>
#include "hps_0_arm_a9_0.h"
#include <stdlib.h>
#include <sys/mman.h>

bool Alf_SharedMemoryComm::Init(uint32_t sh_mem_wr_addr, uint32_t wr_mut_addr, uint32_t wr_mb_addr, uint32_t sh_mem_rd_addr,
									 uint32_t rd_mut_addr, uint32_t rd_mb_addr, uint32_t cp_id, uint32_t addr_offset){
	bool ret_var = false;
	int fd;

	Alf_Log::alf_log_write("Initializing Hardware Communication...", log_info);
	cpu_id = cp_id;

	shared_memory_wr_addr = sh_mem_wr_addr + addr_offset;
	wr_mutex_addr = wr_mut_addr + addr_offset;
	wr_mailbox_addr = wr_mb_addr + addr_offset;

	shared_memory_rd_addr = sh_mem_rd_addr + addr_offset;
	rd_mutex_addr = rd_mut_addr + addr_offset;
	rd_mailbox_addr = wr_mb_addr + addr_offset;

	if((fd = open("/dev/mem", (O_RDWR | O_SYNC))) == -1){
		Alf_Log::alf_log_write("Cannot open /dev/mem. Do you have permissions to do this?", log_error);
	}else{
		shared_memory_wr = mmap(NULL, SHARED_MEMORY_MASTER_NIOS_0_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, shared_memory_wr_addr);
		wr_mutex = mmap(NULL, SHARED_MEMORY_MUTEX_MASTER_NIOS_0_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, wr_mutex_addr);
		wr_mailbox = mmap(NULL, MAILBOX_NIOS2ARM_0_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, wr_mailbox_addr);
		rd_mailbox = mmap(NULL, MAILBOX_NIOS2ARM_0_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, rd_mailbox_addr);
		rd_mutex = mmap(NULL, SHARED_MEMORY_MUTEX_MASTER_NIOS_0_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, rd_mutex_addr);
		shared_memory_wr = mmap(NULL, SHARED_MEMORY_MASTER_NIOS_0_SPAN, PROT_READ, MAP_SHARED, fd, shared_memory_rd_addr);
		if(shared_memory_wr == MAP_FAILED or wr_mutex == MAP_FAILED or wr_mailbox == MAP_FAILED
			or rd_mailbox == MAP_FAILED or rd_mutex == MAP_FAILED or shared_memory_wr == MAP_FAILED){
			Alf_Log::alf_log_write("One or more memory maps are not available!", log_error);
		}else{
			ret_var = true;
		}
	}

	all_address_mapped = ret_var;
	return ret_var;
}

template <typename object>
alf_error Alf_SharedMemoryComm::Write(object){
	alf_error ret_var = ALF_NO_ERROR;
	if(all_address_mapped){
		if(TryLock(wr_mutex)){
			// first write the message id to the first register
			// then write the hole object via memcpy to the address after that
		}else ret_var = ALF_LOCK_MEMORY_FAILED;
	}else{
		ret_var = ALF_NO_WELL_FPGABridge_MAPPING;
	}
	return ret_var;
}

