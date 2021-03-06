/*
 * KernEv.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_


class PCB;
typedef unsigned char IVTNo;


class KernelEv{

public:
	~KernelEv();
	KernelEv (IVTNo IVT);
	void wait();
	void signal();
	int getVal();
	void setVal(int i);
	IVTNo getIVTNumber();
	PCB* getPCBEvent();

private:
	PCB *PCB_event;
	int val;
	IVTNo IVT;
};


#endif /* KERNELEV_H_ */
