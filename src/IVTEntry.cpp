/*
 * IVTEntry.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_CPP_
#define IVTENTRY_CPP_

#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif
#include "KernelEv.h"
#include "helper.h"
#include <IOSTREAM.H>
#include "IVTEntry.h"
#include "PCB.h"

IVTEntry * IVTEntry::interruptTable[256] = {0};

IVTEntry::IVTEntry(IVTNo numberOfIvtEntry, pInterrupt new_Routine){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	IVTEvent = 0;
	IVEntry = numberOfIvtEntry;
	interruptTable [IVEntry] = this;
#ifndef BCC_BLOCK_IGNORE
	old_Routine = getvect(numberOfIvtEntry);
	setvect(numberOfIvtEntry, new_Routine);
	unlockInterrupt
#endif
}


void IVTEntry::signal(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	if (IVTEvent!=0){
		IVTEvent->signal();
	}
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

void IVTEntry::oldRoutine(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	if (old_Routine!=0){
		old_Routine();
	}
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

void IVTEntry::setEntryEvent (KernelEv *myEvent){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	IVTEvent = myEvent;
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

IVTEntry * IVTEntry::getIVTEntry(IVTNo Entry){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	IVTEntry *IVeentry = interruptTable[Entry];
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	return IVeentry;
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
	setvect(IVEntry, old_Routine);
#endif
	interruptTable[IVEntry] = 0;
	IVTEvent = 0;
	oldRoutine();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
	#endif

}

#endif /* IVTENTRY_CPP_ */
