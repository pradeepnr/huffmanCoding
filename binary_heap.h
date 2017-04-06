/*
 * binary_heap.h
 *
 *  Created on: 25-Mar-2017
 *      Author: pradeepnr
 */

#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include "pqueue.h"
#include <vector>

// Min Heap

class BinaryHeap : public pqueue {
public:
	void push(SNODE);
	void pop();
	bool empty();
	SNODE top();
	long size();
	void print();
private:
	std::vector<SNODE> mVecSNode;
	// Parent
	long p(long i) { return (i-1)/2; }
	// left child
	long lc(long i) { return (i*2)+1; }
	// right child
	long rc(long i) { return (i*2)+2; }
	void swap(long i, long j) {
		SNODE temp = mVecSNode[i];
		mVecSNode[i] = mVecSNode[j];
		mVecSNode[j] = temp;
	}
};


#endif /* BINARY_HEAP_H_ */
