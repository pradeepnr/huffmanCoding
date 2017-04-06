//============================================================================
// Name        : HuffmanEncoder.cpp
// Author      : pnr
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


//g++ -std=gnu++11 huffmanEncoder/src/Encoder.cpp -o encoder
#include "Encoder.h"
//#include "binary_heap.h"
//#include "stdpq.h"
//#include "pairing_heap.h"
#include "four_way_heap.h"
using namespace std;

int main(int args, char* argv[]) {
	if(args != 2) {
		cout<<"Invalid input arguments\n";
		return 0;
	}
	char base[] = "./";
	string ipfile(base);
	ipfile.append(argv[1]);
	if(!fileExists(ipfile)) {
		return 0;
	}
	clock_t start_time;
	start_time = clock();
	VL input;
	getInput(input, ipfile);
	huffmanEncoder hencode;
	hencode.encode(input);
	cout << "Time taken to encode (microsecond): " << (clock() - start_time)/10 << endl;
	return 0;
}

void huffmanEncoder::encode(VL& input) {
	VFREQ vfreq;
	getInputFreq(input, vfreq);

	SNODE root = createHuffmanTree(vfreq);
	string code;
	createHuffmanCode(root, code);
	createCodeTableFile("code_table.txt");
	createEncodedBinaryFile(input, "encoded.bin");
}

void huffmanEncoder::createCodeTableFile(std::string fileName) {
	std::string opfile("./");
	opfile.append(fileName);
	ofstream opFileStream(opfile);
	if(opFileStream.is_open()) {
		for(auto h : mHuffmanCodeTableOutputFormat) {
				opFileStream<<h.val<<" "<<h.code<<endl;
		}
	}
	else {
		cout<<"Error: Unable to open file\n";
	}
}

void huffmanEncoder::createEncodedBinaryFile(VL& input, std::string fileName) {
	std::string opfile("./");
	opfile.append(fileName);
	ofstream opFileStream(opfile, ios::binary);
	if(opFileStream.is_open()) {
		BYTE b=0;
		int i=7;
		for(auto v : input) {
			string code = mHuffmanCodeTable[v];
			for(auto ch:code) {
				if(ch=='1') {
					b |= 1<<i;
				}

				i--;
				if(i<0) {
					opFileStream<<b;
					b=0;
					i=7;
				}
			}
		}
		//cout<<endl;
	}
	else {
		cout<<"Error: Unable to open file\n";
	}
}

void huffmanEncoder::createHuffmanCode(SNODE root, string& code) {
	if(root && root.get()->val != -1) {
		//cout<<root.get()->val<<"->"<<code<<endl;
		mHuffmanCodeTable[root.get()->val] = code;
		mHuffmanCodeTableOutputFormat.push_back(huffmanCode(root.get()->val, code));
		code.pop_back();
		return;
	}
	code.push_back('0');
	createHuffmanCode(root.get()->left, code);

	code.push_back('1');
	createHuffmanCode(root.get()->right, code);
	if(!code.empty())
		code.pop_back();
}

SNODE huffmanEncoder::createHuffmanTree(VFREQ& vfreq) {
	/*
	 * 1) insert all the nodes into PQ
	 * 2) run loop till size is equal to 1
	 * 3) take two smallest, merge them and insert back
	 * 4) merge -> create new node with left and right node being the two nodes respectively
	 * 5) finally return the last remaining node, which will be the root
	 */
	//TODO use unique pointer instead of bare pointer
//	stdpq* pq = new stdpq();
//	BinaryHeap* pq = new BinaryHeap();
//	PairingHeap* pq = new PairingHeap();
	FourWayHeap* pq = new FourWayHeap();
	for(auto f:vfreq) {
		SNODE snode = make_shared<Node>(f.first,f.second);
//		pn(snode);
//		cout<<endl;
		pq->push(snode);
//		pq->print();
	}
//	while(!pq->empty()) {
//		pn(pq->top());
//		cout<<" arry-->";
//		pq->print();
//		pq->pop();
//		cout<<"\n";
//	}
	//cout<<endl;
#if 1
	while(pq->size()>1) {
		SNODE f = pq->top(); pq->pop();
		SNODE s = pq->top(); pq->pop();
//		cout<<"remove->";
//		pn(f);
//		cout<<" and ";
//		pn(s);

		SNODE snode = make_shared<Node>(f.get()->freq + s.get()->freq, -1);
//		cout<<" Add->";
//		pn(snode);
//		cout<<endl;
		snode.get()->left = f;
		snode.get()->right = s;
		pq->push(snode);
	}
	SNODE root = pq->top();
	pq->pop();
	delete pq;
	return root;
#else
	return SNODE();
#endif
}

void huffmanEncoder::pn(SNODE sn) {
	cout<<"("<<sn.get()->val<<", "<<sn.get()->freq<<")";
}


// Takes complete input and creates vector
// of unique values in input and its frequencies
void huffmanEncoder::getInputFreq(VL& input, VFREQ& freq) {
	VL inputFreq(INPUT_RANGE, 0);
	// count input Frequence
	for(auto v : input) {
		inputFreq[v]++;
	}
	for(long i=0; i<INPUT_RANGE; ++i) {
		if(inputFreq[i]>0) {
			freq.push_back(make_pair(inputFreq[i], i));
		}
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

void getInput(VL& input, const std::string& fileName) {
	std::fstream fs(fileName, std::ios::in);
	std::string strVal;
	while(std::getline(fs, strVal)) {
		long longVal = atol(strVal.c_str());
		input.push_back(longVal);
	}
}
