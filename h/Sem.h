/*
 * Sem.h
 *
 *  Created on: May 21, 2018
 *      Author: OS1
 */

#ifndef SEM_H_
#define SEM_H_

class KernS;

class Semaphore {
public:
 Semaphore (int init=1);
 virtual ~Semaphore ();
 virtual int wait (int toBlock);
 virtual void signal();
 int val () const; // Returns the current value of the semaphore
private:
 KernS* myImpl;

};


#endif /* SEM_H_ */
