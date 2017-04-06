//============================================================================
// Name        : Decoder.cpp
// Author      : pnr
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// g++ -std=gnu++11 huffmanDecoder/src/Decoder.cpp
#include "Decoder.h"
using namespace std;

VHCODE vhCode;

int main(int args, char* argv[]) {
	clock_t start_time;
	start_time = clock();
	if(args != 3) {
		cout<<"Invalid input arguments\n";
		return 0;
	}
	char base[] = "./";
	string encodedFile(base);
	string codeTableFile(base);
	encodedFile.append(argv[1]);
	codeTableFile.append(argv[2]);
	if(!fileExists(encodedFile) || !fileExists(codeTableFile)) {
		return 0;
	}

	/*
	 * two input files, encoded binary and code table, are given
	 * 1) code table text to huffman tree
	 * 1.1) fill a vector with pair of value and its code
	 * 1.2) iterator through each value and code
	 * 1.2.1) take the code and scan through it one by one 0 ->left side and 1->right side
	 * 1.2.2) keep adding one node dynamically till the scan completes.
	 * 1.2.3) Then add code into the last node which will form the leaf
	 * 2) decode the encoded binary using huffman tree
	 */
	huffmanDecoder decoder;
	SNODE root = make_shared<Node>();
	decoder.readCodeTextIntoArray(codeTableFile);
	for(auto entry : vhCode) {
		if(entry.second.size() > 0 )
			decoder.createHuffmanTreeRecurrsively(entry.first, entry.second, root, 0);
	}
	cout << "Time taken to create tree (microsecond): " << (clock() - start_time)/10 << endl;
	decoder.readBinaryFileToArray(encodedFile);
	cout << "Time taken to read encoded file (microsecond): " << (clock() - start_time)/10 << endl;
	decoder.decodeToFile("decoded.txt", root);
	cout << "Time taken to decode (microsecond): " << (clock() - start_time)/10 << endl;
	return 0;
}

void huffmanDecoder::decodeToFile(std::string outputFileName, SNODE root) {
	stringstream ss(stringstream::out);
	SNODE node = root;

	for(auto byte : mInputCode) {
		BYTE i = MSB;
		while(i!=0) {
			if(byte & i) {
				node = node.get()->right;
			} else {
				node = node.get()->left;
			}
			if(node.get()->val != -1) {
				ss<<node.get()->val<<endl;
				node = root;
			}
			i=i>>1;
		}
	}
	std::ofstream mOFile(outputFileName);
	if(mOFile.is_open()) {
		mOFile<<ss.str();
		mOFile.close();
	}
}

void huffmanDecoder::readBinaryFileToArray(string fileName) {
	std::istream* mIFile = new std::ifstream(fileName, std::ifstream::binary);
	if(!mIFile) {
		cout<<"Error creating ifstream\n";
		return;
	}
	BYTE byte;
	while(!mIFile->eof() && mIFile->read((char*) &byte, 1)) {
		mInputCode.push_back(byte);
	}
	delete mIFile;
}

// This function considers the code is at least of one char
void huffmanDecoder::createHuffmanTreeRecurrsively(long val, string& code, SNODE root, int pos) {
	if(code[pos]=='\0') {
		root.get()->val=val;
		return;
	}
	if(code[pos]=='0') {
		//go left
		if(!root.get()->left) {
			root.get()->left = make_shared<Node>();
		}
		createHuffmanTreeRecurrsively(val, code, root.get()->left, pos + 1);
	}
	else {
		//go right
		if(!root.get()->right) {
			root.get()->right = make_shared<Node>();
		}
		createHuffmanTreeRecurrsively(val, code, root.get()->right, pos + 1);
	}
}

void huffmanDecoder::readCodeTextIntoArray(const std::string& fileName) {
	std::fstream fs(fileName, std::ios::in);
		std::string strVal;
		while(std::getline(fs, strVal)) {
			stringstream ss(strVal);
			string token;
			char delim = ' ';
			std::getline(ss, token, delim);
			long val = std::stol(token);
			string code;
			std::getline(ss, code, delim);
			vhCode.push_back(make_pair(val, code));
		}
}

bool fileExists (const std::string& fileName) {
	if (FILE *file = fopen(fileName.c_str(), "r")) {
		fclose(file);
		return true;
	} else {
		cout<<"Error: Invalid input file ";
		return false;
	}
}
