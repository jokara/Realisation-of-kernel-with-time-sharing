/*
 * KernEv.cpp
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */



#ifndef KEVENT_CPP_
#define KEVENT_CPP_

#include "helper.h"
#include "PCB.h"
#include "IVTEntry.h"
#include "SCHEDULE.H"
#include "KernelEv.h"

int KernelEv::getVal() {return val;}

IVTNo KernelEv::getIVTNumber() {return IVT;}

void KernelEv::setVal(int i) {val=i;}


KernelEv::KernelEv (IVTNo i){
	PCB_event=PCB::runningThread;
	IVT=i;
	if (IVTEntry::interruptTable [getIVTNumber()]!=0){
			IVTEntry::interruptTable [getIVTNumber()]->setEntryEvent(this);
	}
	setVal(0);
}


void KernelEv::signal(){
	if(getVal()==-1){ //nit se blokirala, ceka se da se dogodi dogadjaj
		setVal(0);
		PCB_event->stanje=PCB::ready;
		Scheduler::put(PCB_event);
	}
	else{	//dogodio se event, ceka se nit koja ceka ovaj event
	 setVal(1);
	}
}

void KernelEv::wait(){
	if (PCB::runningThread->id == PCB_event->id){
		if (getVal()==1){ // dogadjaj se nije desio, nit ce morati da ceka
			setVal(0);
		}
		else{// desio se dog pre nego sto je ova nit usla u svoj wait
			setVal(-1);
			PCB_event->stanje=PCB::blocked;
			dispatch();
		}
    }
}

PCB* KernelEv::getPCBEvent(){
	return PCB_event;
}


KernelEv::~KernelEv(){
	signal();
	if (IVTEntry::interruptTable [getIVTNumber()!=0]){
			IVTEntry::interruptTable [getIVTNumber()]->setEntryEvent(0);
	}
}


#endif /* KEVENT_CPP_ */
