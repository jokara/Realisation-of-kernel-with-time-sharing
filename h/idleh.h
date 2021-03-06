/*
 * idleh.h
 *
 *  Created on: May 9, 2018
 *      Author: OS1
 */

#ifndef IDLEH_H_
#define IDLEH_H_

#include "Thread.h"
#include <iostream.h>
#include "helper.h"

class ThreadIdle:public Thread{
public:
	ThreadIdle():Thread(200,1){}
	void run(){
		while(1){

		}
	}
};


#endif /* IDLEH_H_ */
