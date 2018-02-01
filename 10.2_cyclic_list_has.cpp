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
std::string lengths = "129,154,49,198,200,133,97,254,41,6,2,1,255,0,191,108"; 


int main(){
	std::vector<int> buffer(LIST_LENGTH);
	for(int i = 0; i < buffer.size(); i++){
		buffer[i] = i;
	}

	std::string suffix = {17, 31, 73, 47, 23};
	lengths += suffix;
	int skipSize = 0, pos = 0;
	
	for(int rep = 0; rep < 64; rep++){
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
	}

	for(int block = 0; block < 16; block++){
		int val = 0;
		for(int i = 0; i < 16; i++){
			val ^= buffer[block * 16 + i];
		}
		buffer[block] = val;
	}

	for(int i = 0; i < 16; i++){
		printf("%x", buffer[i]);
	}
	getchar();

    return 0;
}



