/*
 * HuffmanEncoder.h
 *
 *  Created on: 08-Mar-2017
 *      Author: pradeepnr
 */

#ifndef HUFFMANENCODER_H_
#define HUFFMANENCODER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <time.h>
#include "node.h"

#define INPUT_RANGE 1000001 // range of decimal value 0 - 1000000

struct huffmanCode;

typedef std::vector<long> VL;
typedef unsigned char BYTE;
typedef std::vector<std::string> VS;
typedef std::vector<huffmanCode> VH;
typedef std::vector<BYTE> VB;
typedef std::pair<long, long> FREQ;
typedef std::vector<FREQ> VFREQ;
//typedef std::priority_queue<SNODE, std::vector<SNODE>, COMPARENODES> PQ; // min heap

std::string mHuffmanCodeTable[INPUT_RANGE];

struct huffmanCode {
	long val;
	std::string code;
	huffmanCode(long _val, std::string _code) : val(_val), code(_code) {}
};

class huffmanEncoder {
public:
	void encode(VL& input);
	void generateCodeTableFile(std::string fileName);
	void getEncodedBinaryFIle(std::string fileName);
	SNODE createHuffmanTree(VFREQ& vfreq);
	void createHuffmanCode(SNODE, std::string& code);
	void pn(SNODE sn);
	void createCodeTableFile(std::string);
	void createEncodedBinaryFile(VL& input, std::string);

private:
	void getInputFreq(VL& input, VFREQ& freq);

	VH mHuffmanCodeTableOutputFormat;
	VB mEncodedText;
};

void getInput(VL& input, const std::string& fileName);
bool fileExists (const std::string& file);
void encode(VL& input, VL& inputFreq);


#endif /* HUFFMANENCODER_H_ */
