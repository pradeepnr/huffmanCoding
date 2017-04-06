all:
	g++ -std=gnu++11 Decoder.cpp -o decoder
	g++ -std=gnu++11 Encoder.cpp four_way_heap.cpp -o encoder
