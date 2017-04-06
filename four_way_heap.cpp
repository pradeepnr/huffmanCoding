/*
 * four_way_heap.cpp
 *
 *  Created on: 27-Mar-2017
 *      Author: pradeepnr
 */

#include "four_way_heap.h"
#include <iostream>

bool FourWayHeap::empty() {
	if(mVecSNode.size()>offset)
		return false;
	return true;
}

void FourWayHeap::print() {
	for(long i=3;i<mVecSNode.size();i++) {
		std::cout<<mVecSNode[i].get()->freq<<" ";
	}
	//std::cout<<std::endl;
}

void FourWayHeap::pop() {
	if(empty())
		return;
	/*
	 * swap 1st and last position
	 * delete last element
	 * run while loop Top to Down
	 * till pos < size && val[pos] is more than its children
	 */
	swap(offset, mVecSNode.size()-1);
	mVecSNode.pop_back();
	long pos = offset;
	while(nc(pos,1) < mVecSNode.size()) {
		long lesserPos = leastValueChild(pos);
		//std::cout<<" min pos->"<<lesserPos<<" ";

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

void FourWayHeap::push(SNODE snode) {
	/*
	 * append at end of array
	 * loop till either root is reached or find larger parent
	 * run loop Bottom to Top
	 */
	mVecSNode.push_back(snode);
	int pos=mVecSNode.size()-1;
	while(pos > offset && mVecSNode[p(pos)].get()->freq > mVecSNode[pos].get()->freq) {
		swap(p(pos),pos);
		pos=p(pos);
	}
}

long FourWayHeap::leastValueChild(long pos) {
	long fcp = nc(pos, 1);//first child position
	if(fcp>=mVecSNode.size()) {
		std::cout<<"Error no children\n";
		return -1;
	}
	int len=mVecSNode.size() -1 -fcp;
	if(len > 3) {
		len=3;
	}
	long minChildPos=fcp;
	for(int i=1;i<=len;++i) {
		if(mVecSNode[fcp+i].get()->freq < mVecSNode[minChildPos].get()->freq) {
			minChildPos = fcp + i;
		}
	}
	return minChildPos;
}

long FourWayHeap::size() {
	return mVecSNode.size()-offset;
}

SNODE FourWayHeap::top() {
	if(!empty())
		return mVecSNode[offset];
	return SNODE();
}



