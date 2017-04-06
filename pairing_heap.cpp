/*
 * pairing_heap.cpp
 *
 *  Created on: 26-Mar-2017
 *      Author: pradeepnr
 */
#include "pairing_heap.h"
#include <iostream>

using namespace std;
void PairingHeap::push(SNODE _snode) {
	mSize++;
	PNODE* pnode = new PNODE(_snode);
	mRoot = add(mRoot, pnode);
}

void PairingHeap::pop() {
	if(empty())
		return;
	mSize--;
	meld();
}
bool PairingHeap::empty() {
	if(mSize==0)
		return true;
	return false;
}

SNODE PairingHeap::top() {
	if(mSize > 0)
		return mRoot->snode;
	else
		return SNODE();
}

long PairingHeap::size() {
	return mSize;
}

void PairingHeap::print() {
}

void PairingHeap::pn(SNODE sn) {
	std::cout<<"("<<sn.get()->val<<", "<<sn.get()->freq<<")";
}

void PairingHeap::meld() {
	PNODE* first = mRoot->child;
	delete mRoot;
	mRoot = NULL;

	if(!first)
		return;
	first->left = NULL;
	VP oneWay;
	PNODE* pnode = first;
	long pos=0;
	while(pnode) {
		oneWay.push_back(pnode);
		pnode=pnode->right;
		oneWay[pos]->left = NULL;
		oneWay[pos]->right = NULL;
		pos++;
	}
	VP twoWay;
	pos=0;
	while(pos < oneWay.size()-1) {
		PNODE* meldNodes = add(oneWay[pos], oneWay[pos+1]);
		twoWay.push_back(meldNodes);
		pos=pos+2;
	}
	if(pos<oneWay.size()) {
		twoWay.push_back(oneWay[pos]);
	}
	mRoot = twoWay[0];

	for(int i=1; i< twoWay.size(); i++) {
		mRoot = add(mRoot, twoWay[i]);
	}
}

PNODE* PairingHeap::add(PNODE* pnode1, PNODE* pnode2) {
	//pnode1 may be NULL, but pnode2 will never be NULL
	if(!pnode1) {
		pnode2->left = pnode2;
		return pnode2;
	}
	// pnode1 is root
	if(pnode1->snode.get()->freq <= pnode2->snode.get()->freq) {
		pnode2->left = pnode1;
		pnode2->right = pnode1->child;
		if(pnode1->child)
			pnode1->child->left = pnode2;
		pnode1->child = pnode2;
		return pnode1;
	}
	else { // pnode2 is root
		pnode1->left = pnode2;
		pnode1->right = pnode2->child;
		if(pnode2->child) {
			pnode2->child->left = pnode1;
		}
		pnode2->child = pnode1;
		return pnode2;
	}

}
