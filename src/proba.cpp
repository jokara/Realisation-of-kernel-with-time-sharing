/*
 * proba.cpp
 *
 *  Created on: May 4, 2018
 *      Author: OS1
 */

#include <iostream.h>
#include "Thread.h"
#include "IVTEntry.h"
#include "KernelEv.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include <STDIO.H>
#include "idleh.h"
#include <stdlib.h>
#include "Timer.h"
#include <STDARG.H>
#include <MATH.H>
#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif


int userMain(int argc, char* argv[]);

int syncPrintf(const char *format, ...){
	int res;
	va_list args;
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
		return res;
}



void _FARFUNC operator delete(void* ptr){
	#ifndef BCC_BLOCK_IGNORE
		lockInterrupt
	#endif
		free(ptr);
	#ifndef BCC_BLOCK_IGNORE
		unlockInterrupt
	#endif
	}


void _FAR * _FARFUNC operator new( unsigned size ){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	void _FAR * mem = malloc(size);
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
	return mem;
}



int main(int argc,char* argv[]) {
	PCB::mainThread= new Thread();
	PCB::mainThread->getMyPCB()->stanje=PCB::ready;
	PCB::runningThread= PCB::mainThread->getMyPCB();
	PCB::runningThread->stanje=PCB::ready;
	ThreadIdle *idle=new ThreadIdle();
	PCB::idle=idle->getMyPCB();
	idle->start();
	Timer::start();
	int ret = userMain(argc, argv);
	Timer::end();
	delete idle;
	delete PCB::runningThread;
	//return ret;

}



