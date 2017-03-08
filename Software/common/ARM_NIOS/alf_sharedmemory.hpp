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
	/// the real address of the write shared memory section
	uint32_t shared_memory_wr_addr;
	/// the virtual address of the shared memory within the context (in linux this is virtuel, within NIOS without MMU not)
	void *shared_memory_wr;
	/// the real address of the write mutex peripheral
	uint32_t wr_mutex_addr;
	/// the virtual|real address of the write mutex peripheral
	void *wr_mutex;
	/// rhe real address of the write mailbox peripheral
	uint32_t wr_mailbox_addr;
	/// the virtual|real address of the write mailbox periph
	void *wr_mailbox;

	/// the real address of the read shared memory section
	uint32_t shared_memory_rd_addr;
	/// the virtual|real address of the shared memory section
	void *shared_memory_rd;
	/// the real address of the mutex for the read memory section
	uint32_t rd_mutex_addr;
	/// the virtual|real address of the mutex for the read memory section
	void *rd_mutex;
	/// the real address of the mailbox for reading of the shared memory
	uint32_t rd_mailbox_addr;
	/// the virtual|real address of the mailbox
	void *rd_mailbox;

	/// The CPU-ID which is unique in system context. This is very important for giving access to the shared memory via locking it through the mutex
	uint16_t cpu_id;
	/// flag that all addresses for read of the shared memory could be mapped
	bool all_read_addr_mapped;
	/// flag that all addresses for write of the shared memory could be mapped
	bool all_write_addr_mapped;

	/// used for calculating the position wihtin the shared memory section. The shared memory is used like a queue, #wr_memory_pos goes up until it reachs the end, then starting from beginning
	uint16_t wr_memory_pos;
	uint32_t wr_memory_addr_offset;
	/// the size of the shared memory, taken from the system overview
	const uint32_t shared_memory_size = 2048;
	/// the size (span, how much register are there) of the mailbox, taken from the system overview
	const uint32_t mailbox_size = 16;
	/// the size of the mutex, taken from the sys overview
	const uint32_t mutex_size = 8;

	bool TryLock(void *addr);
	void ReleaseLock(void *addr);
	bool WriteAndCommitMailbox(void *addr, uint32_t top_address);
	void ReadMailbox(void *addr);
	void WaitForLock(void *addr);
	void ResetWriteMutex();

	template <typename t>
	alf_error HardwareWrite(const t &obj, uint32_t message_id, uint32_t size);

public:
	bool Init(uint32_t sh_mem_wr_addr, uint32_t wr_mutex_addr, uint32_t wr_mb_addr, uint32_t sh_mem_rd_addr,
			 uint32_t rd_mutex_addr, uint32_t rd_mb_addr, uint16_t cp_id, uint32_t addr_offset);

	alf_error Write(const Alf_Drive_Info &drive);

	alf_error Write(const Alf_Drive_Command &drive);

	void Read();
};



#endif /* ARM_NIOS_ALF_SHAREDMEMORY_HPP_ */
