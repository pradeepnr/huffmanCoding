/*
 * stdpq.cpp
 *
 *  Created on: 26-Mar-2017
 *      Author: pradeepnr
 */

#include "stdpq.h"

void stdpq::push(SNODE elem) {
	mPQ.push(elem);
}

void stdpq::pop() {
	mPQ.pop();
}

SNODE stdpq::top() {
	return mPQ.top();
}

bool stdpq::empty() {
	return mPQ.empty();
}

long stdpq::size() {
	return mPQ.size();
}



