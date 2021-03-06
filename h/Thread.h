/*
 * Thread.h
 *
 *  Created on: May 4, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

class ListTimer;

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:
	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);
public:
	friend class PCB;
	friend class Lista;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice =defaultTimeSlice);
	virtual void run() {}
	static void pause();
	static Lista* sleepers;
	PCB* getMyPCB();
	static Thread* getThreadById(int);
private:
	PCB* myPCB;
};

void dispatch ();

#endif /* THREAD_H_ */
