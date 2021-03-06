/*
 * Kernsem.h
 *
 *  Created on: May 21, 2018
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "Lista.h"
#include "helper.h"

class KernS{
public:
	~KernS();
	KernS(int initVal);
	int wait(int toBlock);
	void signal();

	int val;
	Lista* kernelSemList;
};



#endif /* KERNSEM_H_ */
