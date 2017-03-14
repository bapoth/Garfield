#ifndef TASKS_NIOS_HPP_
#define TASKS_NIOS_HPP_

#include "alt_types.h"
#include "alf_sharedmemory.hpp"

/*
 * define here the prototypes for all tasks
 * */

void readUltraSonic( void* p);
void readMPU ( void* p );
void readRotary( void* p );
void setMotor_and_Steering( void* p);

/*
 * @brief the interrupt routine for the mailbox communication
 * */
void Mailbox_isr(void* ptr, alt_u32 a);

/*
 * @brief global sharedMem variable
 * */
extern Alf_SharedMemoryComm sharedMem;


#endif /* TASKS_NIOS_HPP_ */
