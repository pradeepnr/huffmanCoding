/*
 * four_way_heap.h
 *
 *  Created on: 27-Mar-2017
 *      Author: pradeepnr
 */

#ifndef FOUR_WAY_HEAP_H_
#define FOUR_WAY_HEAP_H_

#include "pqueue.h"
#include <vector>

class FourWayHeap : public pqueue {
public:
	FourWayHeap() {
		mVecSNode.push_back(SNODE());
		mVecSNode.push_back(SNODE());
		mVecSNode.push_back(SNODE());
	}
	void push(SNODE);
	void pop();
	bool empty();
	SNODE top();
	long size();
	void print();
private:
	const int offset = 3;
	const int k = 4; // 4 way
	// Parent
	long p(long i) { return ((i-1-offset)/k)+offset; }
	// node i's  nth child (1,2,3,4)
	long nc(long i, long n) { return (((i-offset)*k)+n+offset);  }

	long leastValueChild(long pos);

	void swap(long i, long j) {
		SNODE temp = mVecSNode[i];
		mVecSNode[i] = mVecSNode[j];
		mVecSNode[j] = temp;
	}
	std::vector<SNODE> mVecSNode;
};



#endif /* FOUR_WAY_HEAP_H_ */
