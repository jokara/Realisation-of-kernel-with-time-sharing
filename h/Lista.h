/*
 * Lista.h
 *
 *  Created on: May 8, 2018
 *      Author: OS1
 */

#ifndef LISTA_H_
#define LISTA_H_
#include "Thread.h"
#include "PCB.h"


class Lista {
public:
	struct Elem {
		PCB* pcb;
		Elem *next;
		Elem *previous;
		Elem(PCB* p=0,Elem *n=0, Elem* pre=0) {
			pcb=p;
			next=n;
			previous=pre;
		}

	};

	Elem *first,*last;

	~Lista();
	Lista();
	Lista* AddOnBeggining(PCB* p);
	Lista* AddOnEnd(PCB* p);
	PCB* TakeFromBeggining();
	PCB* TakeFromEnd();
	PCB* DeleteByID(int id);
	void add(PCB * pcb);
	void update();


};



#endif /* LISTA_H_ */
