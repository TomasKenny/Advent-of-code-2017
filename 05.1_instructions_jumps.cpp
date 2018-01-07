#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;
	int jumps = 0;
	std::vector<int> instructions;
	while(std::getline(myfile, line)){
		instructions.push_back(atoi(line.c_str()));
	}

	int ptr = 0;
	while(ptr >= 0 && ptr < instructions.size()){
		int newPtr = ptr + instructions[ptr];
		instructions[ptr]++;
		ptr = newPtr;
		jumps++;
	}

	printf("jumps count is: %d\n", jumps);
	getchar();

    return 0;
}

