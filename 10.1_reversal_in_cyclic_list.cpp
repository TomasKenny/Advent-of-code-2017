#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <ctype.h>
#include "windows.h"

const int LIST_LENGTH = 256;
std::vector<int> lengths = {129,154,49,198,200,133,97,254,41,6,2,1,255,0,191,108}; 

int main(){
	std::vector<int> buffer(LIST_LENGTH);
	for(int i = 0; i < buffer.size(); i++){
		buffer[i] = i;
	}

	int skipSize = 0, pos = 0;
		
	for(auto length: lengths){
		int steps = length / 2;
		for(int i = 0; i < steps; i++){
			int pos1 = (pos + i) % LIST_LENGTH;
			int pos2 = (pos + length - 1 - i) % LIST_LENGTH;
			std::swap(buffer[pos1], buffer[pos2]);
		}
		pos += length + skipSize++;
		pos %= LIST_LENGTH;

	}
	
	printf("first two items product: %d", buffer[0] * buffer[1]);
	getchar();

    return 0;
}
