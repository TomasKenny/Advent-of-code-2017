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


std::string GetKnotHash(const std::string & data){
	std::vector<int> buffer(LIST_LENGTH);
	for(int i = 0; i < buffer.size(); i++){
		buffer[i] = i;
	}
	
	std::string input(data);
	std::string suffix = "\x11\x1F\x49\x2F\x17";
	input += suffix;
	int skipSize = 0, pos = 0;
	
	for(int rep = 0; rep < 64; rep++){
		for(int j = 0; j < input.size(); j++){
			char length = input[j];
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

	std::string result;
	char strBuf[5];
	for(int i = 0; i < 16; i++){
		sprintf(strBuf, "%02x", buffer[i]);
		result += strBuf;
	}
	return result;
}

int GetBits(char c){
	static const int BITS[16] = {
		0,1,1,2,
		1,2,2,3,
		1,2,2,3,
		2,3,3,4
	};
	if(c >= '0' && c <= '9')
		return BITS[c - '0'];
	c = tolower(c);
	if(c >= 'a' && c <= 'f')
		return BITS[c - 'a' + 10];
}

int main(){
	const std::string key = "hxtvlmkl";
	//const std::string key = "flqrgnkx";
	
	char buf[5];
	int squaresUsed = 0;
	for(int i = 0; i < 128; i++){
		std::string input(key);
		sprintf(buf, "-%d", i);
		input += buf;
		std::string hash = GetKnotHash(input);
		for(int j = 0; j < hash.size(); j++){
			squaresUsed += GetBits(hash[j]);
		}
	}

	printf("squares used: %d", squaresUsed);
	getchar();

    return 0;
}

