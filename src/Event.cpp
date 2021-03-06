/*
 * Event.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */


#include "Event.h"
#include "KernelEv.h"
#include "PCB.h"

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myImpl = new KernelEv(ivtNo);
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}


void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myImpl->wait();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}
