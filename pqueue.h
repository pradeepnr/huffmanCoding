/*
 * pqueue.h
 *
 *  Created on: 09-Mar-2017
 *      Author: pradeepnr
 */

#ifndef PQUEUE_H_
#define PQUEUE_H_

#include "node.h"

// interface
class pqueue {
public:
	virtual ~pqueue() {}
	virtual void push(SNODE) {}
	virtual void pop() {}
	virtual SNODE top() {return SNODE();}
	virtual bool empty() {return true;}
	virtual long size() = 0;
};


// End of implementation with standard class

#endif /* PQUEUE_H_ */
