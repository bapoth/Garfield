/*
 * alf_sharedmemory.hpp
 *
 *  Created on: 02.03.2017
 *      Author: florian
 */

#ifndef ARM_NIOS_ALF_SHAREDMEMORY_HPP_
#define ARM_NIOS_ALF_SHAREDMEMORY_HPP_

#include "alf_erno.h"
#include "alf_log.hpp"
#include "alf_data.hpp"

class Alf_SharedMemoryComm{
private:
	void *sysid;

	uint32_t shared_memory_wr_addr;
	void *shared_memory_wr;
	uint32_t wr_mutex_addr;
	void *wr_mutex;
	uint32_t wr_mailbox_addr;
	void *wr_mailbox;

	uint32_t shared_memory_rd_addr;
	void *shared_memory_rd;
	uint32_t rd_mutex_addr;
	void *rd_mutex;
	uint32_t rd_mailbox_addr;
	void *rd_mailbox;

	uint32_t cpu_id;
	bool all_address_mapped;

	bool TryLock(void *addr);
	void ReleaseLock(void *addr);
	void WriteAndCommitMailbox(void *addr);
	void ReadMailbox(void *addr);

public:
	bool Init(uint32_t sh_mem_wr_addr, uint32_t wr_mutex_addr, uint32_t wr_mb_addr, uint32_t sh_mem_rd_addr,
			 uint32_t rd_mutex_addr, uint32_t rd_mb_addr, uint32_t cp_id, uint32_t addr_offset);

	alf_error Write(Alf_Drive_Info &drive);

	alf_error Write(Alf_Drive_Command &drive);

	template <typename object>
	alf_error Write(object);
};



#endif /* ARM_NIOS_ALF_SHAREDMEMORY_HPP_ */
