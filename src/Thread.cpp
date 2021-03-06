/*
 * Thread.cpp
 *
 *  Created on: May 9, 2018
 *      Author: OS1
 */

#include <iostream.h>
#include "PCB.h"
#include "Thread.h"
#include "SCHEDULE.H"
#include "helper.h"
#include "Lista.h"



Lista* Thread::sleepers=new Lista();

void dispatch() {
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	PCB::dispatch1();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

Thread::~Thread(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	waitToComplete();
	delete myPCB;
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

Thread::Thread(StackSize ss,Time ts){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif

	myPCB=new PCB(ss,ts,this);
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

void Thread::waitToComplete(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myPCB->waitToComplete();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}


void Thread::start(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	myPCB->start();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}

void Thread::pause(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt
#endif
	PCB::ThreadPauze();
#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt
#endif
}


void Thread::sleep(Time timeToSleep){
	if (timeToSleep>0){
		PCB::runningThread->sleeptime=timeToSleep;
		PCB::runningThread->stanje=PCB::sleeped;
		sleepers->add(PCB::runningThread);
		dispatch();
	}
	return;
}


PCB* Thread::getMyPCB() {
	return myPCB;
}

Thread* Thread::getThreadById(int id) {
	Thread* t=0;
	PCB* novi=PCB::pcbList->DeleteByID(id);
	if (novi!=0) t=novi->thread;
	return t;
}
