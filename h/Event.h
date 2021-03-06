/*
 * Event.h
 *
 *  Created on: May 22, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "KernelEv.h"
#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KernelEv;


#define PREPAREENTRY(numEntry, callOld) \
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) { \
	if (callOld == 1) \
		newEntry##numEntry.old_Routine(); \
	newEntry##numEntry.signal(); \
	dispatch(); \
}


class Event {
public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();
protected:
 friend class KernelEv;
 void signal(); // can call KernelEv
private:
 KernelEv* myImpl;

};





#endif /* EVENT_H_ */
