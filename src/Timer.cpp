/*
 * Timer.cpp
 *
 *  Created on: May 14, 2018
 *      Author: OS1
 */

#include "Timer.h"
#include "PCB.h"
#include <iostream.h>
#include "SCHEDULE.H"
#include "Lista.h"
#ifndef BCC_BLOCK_IGNORE
#include <dos.h>
#endif


Time Timer::currentCnt=0;
toInterrupt Timer::oldTimer=0;


void tick();

void Timer::restart() {
	Timer::currentCnt=0;
}


void Timer::start(){
#ifndef BCC_BLOCK_IGNORE
	oldTimer=getvect(8);
	setvect(8,&timer);
#endif
	restart();
}

void Timer::end(){
#ifndef BCC_BLOCK_IGNORE
	setvect(8,oldTimer);
#endif
}

void Timer::setCurrentCnt() {currentCnt=0;}


void interrupt Timer::timer(...){
	(*oldTimer)();
	tick();
	Thread::sleepers->update();
	if (PCB::runningThread->timeslice!=0){
		currentCnt=currentCnt+1;
		if (currentCnt>=PCB::runningThread->timeslice){
			dispatch();
		}
	}
}



/*
 * unsigned int bp2ndd,ss2ndd,sp2ndd;
 *
 * #ifndef BCC_BLOCK_IGNORE
	asm{
		mov ss2ndd,ss
		mov sp2ndd,sp
		mov bp2ndd,bp
	}
#endif

	PCB::runningThread->ss=ss2ndd;
	PCB::runningThread->bp=bp2ndd;
	PCB::runningThread->sp=sp2ndd;


	if((PCB::runningThread->stanje==PCB::ready)&&(PCB::runningThread!=PCB::idle)){
		Scheduler::put(PCB::runningThread);
	}
	PCB::runningThread=Scheduler::get();


	if (PCB::runningThread==0) {
		PCB::runningThread=PCB::idle;
	}
	ss2ndd=PCB::runningThread->ss;
	sp2ndd=PCB::runningThread->sp;
	bp2ndd=PCB::runningThread->bp;

	#ifndef BCC_BLOCK_IGNORE
		asm{
			mov ss,ss2ndd
			mov sp,sp2ndd
			mov bp,bp2ndd
		}
	#endif

	Timer::restart();
		}
	}


	*/








