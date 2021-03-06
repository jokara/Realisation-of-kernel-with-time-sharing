/*
 * IVTEntry.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "Event.h"
typedef void interrupt (*pInterrupt) (...);
typedef unsigned char IVTNo;
class KernelEv;


class IVTEntry{
public:
	~IVTEntry();
	IVTEntry (IVTNo numberOfIvtEntry, pInterrupt new_Routine);
	void oldRoutine();
	void signal();
	static IVTEntry * getIVTEntry (IVTNo);
	void setEntryEvent(KernelEv *myEvent);
	static IVTEntry *interruptTable[];
public:
	IVTNo IVEntry;
	KernelEv *IVTEvent;
	pInterrupt old_Routine;
};

#endif /* IVTENTRY_H_ */
