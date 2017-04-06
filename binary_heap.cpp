/*
 * binary_heap.cpp
 *
 *  Created on: 25-Mar-2017
 *      Author: pradeepnr
 */

#include "binary_heap.h"
#include <iostream>

bool BinaryHeap::empty() {
	return mVecSNode.empty();
}

void BinaryHeap::print() {
	for(auto e:mVecSNode)
		std::cout<<e.get()->freq<<" ";
	std::cout<<std::endl;
}

void BinaryHeap::pop() {
	if(empty())
		return;
	/*
	 * swap 1st and last position
	 * delete last element
	 * run while loop Top to Down
	 * till pos < size && val[pos] is more than its children
	 */
	swap(0, mVecSNode.size()-1);
	mVecSNode.pop_back();
	long pos = 0;
	while(lc(pos) < mVecSNode.size()) {
		long lesserPos = lc(pos);
		if(rc(pos) <mVecSNode.size() && mVecSNode[lc(pos)].get()->freq > mVecSNode[rc(pos)].get()->freq) {
			lesserPos = rc(pos);
		}

		if(mVecSNode[pos].get()->freq < mVecSNode[lesserPos].get()->freq) {
			break;
		}
		else {
			swap(pos, lesserPos);
			pos = lesserPos;
		}
//		cout<<"new pos="<<pos<<endl;
	}
}

void BinaryHeap::push(SNODE snode) {
	/*
	 * append at end of array
	 * loop till either root is reached or find larger parent
	 * run loop Bottom to Top
	 */
	mVecSNode.push_back(snode);
	int pos=mVecSNode.size()-1;
	while(pos > 0 && mVecSNode[p(pos)].get()->freq > mVecSNode[pos].get()->freq) {
		swap(p(pos),pos);
		pos=p(pos);
	}
}

long BinaryHeap::size() {
	return mVecSNode.size();
}

SNODE BinaryHeap::top() {
	if(!empty())
		return mVecSNode[0];
	return SNODE();
}








