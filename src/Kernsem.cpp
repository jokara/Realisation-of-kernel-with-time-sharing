/*
 * Kernsem.cpp
 *
 *  Created on: May 21, 2018
 *      Author: OS1
 */

#include "Kernsem.h"
#include "Lista.h"
#include "PCB.h"
#include "SCHEDULE.H"


KernS::~KernS() {
	while(val<0){
		signal();
	}
	delete kernelSemList;
	kernelSemList=0;
}



int KernS::wait(int toBlock) {
	int ret=0;
	if(!(toBlock) && (val<=0)){
		ret=-1;
	}
	else {
		val=val-1;
		if (val<0){
			ret=1;
			PCB::runningThread->stanje=PCB::blocked;
			PCB::runningThread->kernelsem=this;
			kernelSemList->AddOnEnd(PCB::runningThread);
			dispatch();
		}
	}
return ret;
}


void KernS::signal() {
	if (val<0){
		PCB* block=kernelSemList->TakeFromBeggining();
		if(block==0) return;
		block->stanje=PCB::ready;
		block->kernelsem=0;
		Scheduler::put(block);
	}
	val=val+1;
}


KernS::KernS(int init){
	val=init;
	if (val<0){
		val=0;
	}
	kernelSemList=new Lista();
}


