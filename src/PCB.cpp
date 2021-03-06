/*
 * PCB.cpp
 *
 *  Created on: May 4, 2018
 *      Author: OS1
 */

#include "PCB.h"
#include "Thread.h"
#include "Lista.h"
#include "SCHEDULE.H"
#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif
#include "Timer.h"
#include <iostream.h>
#include "helper.h"
#include "Kernsem.h"


int PCB::ID=0;
PCB* PCB::idle=0;
PCB* PCB::runningThread=0;
Thread* PCB::mainThread=0;
Lista* PCB::pcbList=new Lista();

PCB::~PCB(){
	pcbList->DeleteByID(this->id);
	delete this->waitList;
	this->waitList=0;
	delete [] stack;
}



PCB::PCB(StackSize stackSizee,Time timeslicee,Thread* thread){
	if (stackSizee>65536){
		stackSizee=65536;
	}
	stackSize=stackSizee;
	timeslice=timeslicee;
	ss=sp=bp=0;
	stack=0;
	sleeptime=0;
	stanje=created;
	id=++ID;
	this->thread=thread;
	waitList=new Lista();
	pcbList->AddOnEnd(this);
	myParent=runningThread;
	kernelsem=0;
}

void PCB::start(){
	if(stanje!=created) return;
	stanje=ready;
	ThreadInit();
	if(this!= idle)
		Scheduler::put(this);
}


void PCB::waitToComplete(){

	if ((this->stanje==created)||(PCB::idle == this) || (PCB::runningThread==this)||(this->stanje==finished)) return;
	PCB::runningThread->stanje=blocked;
	waitList->AddOnEnd(PCB::runningThread);
	dispatch();

}


void PCB::closeThread(){
#ifndef BCC_BLOCK_IGNORE
	lockInterrupt;
#endif
	Lista::Elem *tek;
	tek=waitList->first;
	Lista::Elem *old;
	while (tek!=0){
		old=tek;
		tek->pcb->stanje=ready;
		Scheduler::put(tek->pcb);
		tek->pcb=0;
		tek=tek->next;
		old->next=0;
		delete old;
	}
	delete waitList;
	waitList=0;
	this->stanje=finished;

#ifndef BCC_BLOCK_IGNORE
	unlockInterrupt;
#endif
dispatch();
}


void PCB::wrapper() {
	//thread->run();
	PCB::runningThread->thread->run();
	PCB::runningThread->closeThread();
}

unsigned int bp2nd,ss2nd,sp2nd;

void interrupt PCB::dispatch1() {

#ifndef BCC_BLOCK_IGNORE
	asm{
		mov ss2nd,ss
		mov sp2nd,sp
		mov bp2nd,bp
	}
#endif

	PCB::runningThread->ss=ss2nd;
	PCB::runningThread->bp=bp2nd;
	PCB::runningThread->sp=sp2nd;


	if((PCB::runningThread->stanje==ready)&&(PCB::runningThread!=idle)){
		Scheduler::put(runningThread);
	}
	PCB::runningThread=Scheduler::get();


	if (runningThread==0) {
		runningThread=idle;
	}
	ss2nd=PCB::runningThread->ss;
	sp2nd=PCB::runningThread->sp;
	bp2nd=PCB::runningThread->bp;

	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov ss,ss2nd
			mov sp,sp2nd
			mov bp,bp2nd
		}
	#endif

	Timer::restart();
}



void PCB::ThreadInit(){
	stackSize /= sizeof(unsigned);
	stack=new unsigned[stackSize];
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-1]=0x200;
	stack[stackSize-2]=FP_SEG(&wrapper);
	stack[stackSize-3]=FP_OFF(&wrapper);
#endif


#ifndef BCC_BLOCK_IGNORE

	ss = FP_SEG(stack + stackSize-12);
	sp = FP_OFF(stack + stackSize-12);

#endif

	bp=sp;
}


void PCB::ThreadPauze(){
	//cout<<"Usao sam u pauzu\n";
	PCB::runningThread->stanje=pauzed;
	dispatch();
}





