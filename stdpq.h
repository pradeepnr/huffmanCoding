/*
 * stdpq.h
 *
 *  Created on: 26-Mar-2017
 *      Author: pradeepnr
 */

#ifndef STDPQ_H_
#define STDPQ_H_

#include "pqueue.h"
#include <queue>

struct COMPARENODES {
	bool operator () (SNODE const & sn1, SNODE const & sn2) {
		return sn1.get()->freq > sn2.get()->freq;
	}
};

// Implementation with standard class
class stdpq : public pqueue {
public:
	void push(SNODE);
	void pop();
	bool empty();
	SNODE top();
	long size();
private:
	std::priority_queue<SNODE, std::vector<SNODE>, COMPARENODES> mPQ;
};



#endif /* STDPQ_H_ */
