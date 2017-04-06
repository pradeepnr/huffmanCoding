/*
 * Decoder.h
 *
 *  Created on: 16-Mar-2017
 *      Author: pradeepnr
 */

#ifndef DECODER_H_
#define DECODER_H_
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <memory>

#define MSB 128
bool fileExists (const std::string& fileName);

struct Node;

typedef unsigned char BYTE;
typedef std::shared_ptr<Node> SNODE;
typedef std::pair<long /* value */, std::string /* code */> HCODE;
typedef std::vector<HCODE> VHCODE;
typedef std::vector<BYTE> VB;

typedef struct Node {
	long val; // INPUT_RANGE, it will be -1 for internal nodes
	// if both left and right child are empty its leaf node
	SNODE left;
	SNODE right;
	Node() : val(-1), left(NULL), right(NULL) { }
} Node;

class huffmanDecoder {
public:
	huffmanDecoder() { }
	void readCodeTextIntoArray(const std::string& fileName);
	void createHuffmanTreeRecurrsively(long val, std::string& str, SNODE root, int pos);
	void readBinaryFileToArray(std::string fileName);
	void decodeToFile(std::string outputFileName, SNODE root);
private:
	VB mInputCode;
};


#endif /* DECODER_H_ */
