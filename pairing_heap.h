/*
 * pairing_heap.h
 *
 *  Created on: 26-Mar-2017
 *      Author: pradeepnr
 */

#ifndef PAIRING_HEAP_H_
#define PAIRING_HEAP_H_

#include "pqueue.h"
#include <vector>

typedef struct PNODE {
	SNODE snode;
	PNODE* left;
	PNODE* right;
	PNODE* child;
	PNODE(SNODE _snode) : snode(_snode), left(NULL), right(NULL), child(NULL) {}
} PNODE;

typedef std::vector<PNODE*> VP;

class PairingHeap : public pqueue {
public:
	PairingHeap() : mSize(0), mRoot(NULL) { }
	void push(SNODE);
	void pop();
	bool empty();
	SNODE top();
	long size();
	void print();
private:
	void meld();
	void pn(SNODE sn);
	long mSize;
	PNODE* mRoot;
	PNODE* add(PNODE* spnode1, PNODE* spnode2);
};



#endif /* PAIRING_HEAP_H_ */
