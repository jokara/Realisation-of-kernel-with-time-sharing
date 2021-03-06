/*
 * Lista.cpp
 *
 *  Created on: May 8, 2018
 *      Author: OS1
 */

#include "Lista.h"
#include <iostream.h>
#include "SCHEDULE.H"

Lista::~Lista() {
	Elem *old=first;
	while(old!=0){
		first=first->next;
		first->previous=0;
		old->next=0;
		old->previous=0;
		delete(old);
		old=first;
	}
	first=last=0;
}

Lista::Lista() {
	first=last=0;
}


Lista* Lista::AddOnBeggining(PCB *p){
	Elem *novi=new Elem(p);
	if (first==0){
		first=last=novi;
		first->previous=0;
		last->next=0;
	}
	else {
		novi->next=first;
		first->previous=novi;
		first=novi;
		first->previous=0;
	}

	return this;
}

Lista* Lista::AddOnEnd(PCB* p) {
	Elem *novi=new Elem(p);
		if (first==0){
			first=last=novi;
			first->previous=0;
		}
		else {
			last->next=novi;
			novi->previous=last;
			last=novi;
		}
		last->next=0;
		return this;
	}

PCB* Lista::TakeFromBeggining() {
	Elem *old=0;

	if (first==last){
		if(first!=0){
			old=first;
			first=0;
			last=0;
			return old->pcb;
		}
	}
	else{
		old=first;
		first=first->next;
		first->previous=0;
		old->next=0;
	}
	if (first==0) first=last=0;
	return old->pcb;
}

PCB* Lista::TakeFromEnd() {
	Elem *old=0;
	PCB* pointToPCB=0;

	if (first!=last) {
		old=last;
		pointToPCB=old->pcb;
		last=last->previous;
		old->previous=0;
		last->next=0;
	}
	else{
		if(first!=0){
			old=first;
			pointToPCB=old->pcb;
			first=last=0;
		}
	}
	//delete old;
	return pointToPCB;
}

PCB* Lista::DeleteByID(int id) {
	PCB* PointToPCB=0;
	Elem *old=first;
	while(old!=0 && old->pcb->id!=id) {
		old=old->next;
	}
	if (old!=0) {
		if (first==last){
			first=last=0;
			PointToPCB=old->pcb;
			old->next=0;
			old->previous=0;
			old->pcb=0;
			delete old;
		}
		else{
			if (old==first){
				first=first->next;
				if(first!=0) first->previous=0;
				PointToPCB=old->pcb;
				old->next=0;
				old->previous=0;
				old->pcb=0;
				delete old;
			}
			else {
				if (old==last){
					last=last->previous;
					if (last!=0){
						last->next=0;
					}
					PointToPCB=old->pcb;
					old->next=0;
					old->previous=0;
					old->pcb=0;
					delete old;
				}
				else {
					if (old->next!=0) {
						old->next->previous=old->previous;
					}
					if (old->previous!=0){
						old->previous->next=old->next;
					}
					PointToPCB=old->pcb;
					old->next=0;
					old->previous=0;
					old->pcb=0;
					delete old;
				}
			}
		}

	}
	return PointToPCB;
}

void Lista::update(){
	if((first!=0)&&(first->pcb->sleeptime>0)){
		first->pcb->sleeptime=first->pcb->sleeptime-1;
	}
	Elem *tek=first;
	while(first!=0 && first->pcb->sleeptime==0) {
		Elem* old=first;
		PCB* p=old->pcb;
		first=first->next;
		old->next=0;
		first->previous=0;
		p->stanje=PCB::ready;
		Scheduler::put(p);
		delete old;
	}
}


void Lista::add(PCB* p){
		Elem *tek=first;
		if(p->sleeptime<=0) return;
		Elem *novi=new Elem(p);
		if (first==0){
			first=last=novi;
			last->next=0;
			first->previous=0;
		}
		else {
			while ((tek!=0)&&(novi->pcb->sleeptime>=tek->pcb->sleeptime)) {
				novi->pcb->sleeptime=novi->pcb->sleeptime-tek->pcb->sleeptime;
				tek=tek->next;
			}
			if (tek==first) {
				novi->next=first;
				first->previous=novi;
				first=novi;
				first->previous=0;
				tek=first->next;
				tek->pcb->sleeptime-=first->pcb->sleeptime;
			}
			else {
				if (tek==0) {
					last->next=novi;
					novi->previous=last;
					last=novi;
					last->next=0;
				}
				else {
					novi->previous=tek->previous;
					novi->next=tek;
					tek->previous->next=novi;
					tek->previous=novi;
					novi->next->pcb->sleeptime-=novi->pcb->sleeptime;
				}
			}
		}
		return;
}



