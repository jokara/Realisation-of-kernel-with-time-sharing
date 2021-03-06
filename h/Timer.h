/*
 * Timer.h
 *
 *  Created on: May 14, 2018
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "PCB.h";
typedef void interrupt (*toInterrupt)(...);


class Timer {
public:
	static void start();
	static void end();
	static void restart();
	Time getCurr() {return currentCnt;}
	static void setCurrentCnt();
	static void interrupt timer(...);
private:
	static Time currentCnt;
	static toInterrupt oldTimer;
};


#endif /* TIMER_H_ */
