/*
 * node.h
 *
 *  Created on: 25-Mar-2017
 *      Author: pradeepnr
 */

#ifndef NODE_H_
#define NODE_H_

#include <memory>

struct Node;

// using smart pointers i.e shared pointer
typedef std::shared_ptr<Node> SNODE;

typedef struct Node {
	long freq; // upto 100,000,000
	long val; // INPUT_RANGE, it will be -1 for internal nodes
	// if both left and right child are empty its leaf node
	SNODE left;
	SNODE right;
	Node(long _freq, long _val) : freq(_freq), val(_val), left(NULL), right(NULL) { }
} Node;



#endif /* NODE_H_ */
