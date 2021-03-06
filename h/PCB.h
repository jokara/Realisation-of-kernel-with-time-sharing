/*
 * PCB.h
 *
 *  Created on: May 4, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"

class Lista;

#define lockInterrupt asm{pushf;cli;}
#define unlockInterrupt asm popf;


class KernS;

class PCB {
public:
	enum Stanje{
			blocked,ready,finished,created,pauzed,sleeped
		};
	Time sleeptime;
	unsigned *stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	Time timeslice;
	Stanje stanje;
	Thread* thread;
	StackSize stackSize;
	static int ID;
	int id;
	Lista* waitList; //lista PCB-ova koji cekaju na zavrsetak ovog PCB
	static PCB* runningThread;
	static Thread* mainThread;
	PCB* myParent;
	static Lista* pcbList; //lista svih PCB-ova
	static PCB* idle;
	KernS *kernelsem; //semafor na kom se blokira
	friend interrupt void timer();
	friend class Timer;

	~PCB();
	PCB(StackSize stackSizee,Time timeslicee,Thread *thread);
	void start();
	void waitToComplete();
	void closeThread();
	void ThreadInit();
	static void interrupt dispatch1();
	static void wrapper();
	static void ThreadPauze();

};



#endif /* PCB_H_ */
