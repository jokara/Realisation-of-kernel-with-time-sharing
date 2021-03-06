/*
 * Sem.cpp
 *
 *  Created on: May 21, 2018
 *      Author: OS1
 */

#include "Sem.h"
#include "PCB.h"
#include "Kernsem.h"

Semaphore::~Semaphore(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	//razmotri dal treba if ili odmah da se brise
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}


void Semaphore::signal(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

int Semaphore::wait(int toBlock){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	int retValue = myImpl->wait(toBlock);
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
	return retValue;
}


Semaphore::Semaphore(int init) {
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myImpl=new KernS(init);
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

int Semaphore::val()const{
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	int ret = myImpl->val;
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
	return ret;
}



