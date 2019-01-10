#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <regex>
#include <assert.h>

std::map<std::string, __int64> registers;

__int64 GetEffectiveValue(std::string val){
	if(val[0] >= 'a' && val[0] <= 'h'){
		return registers[val];
	}
	return atoi(val.c_str());
}

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;
	std::vector<std::string> program;
	
	
	while (std::getline(myfile, line)) {
		program.push_back(line);
	}

	int mulCounter = 0;
	int ip = 0;
	while(ip >= 0 && ip < program.size()){
		std::string instructionStr = program[ip];
		
		std::string instruction = strtok(&instructionStr[0], " ");
		std::string operand1 = strtok(nullptr, " ");
		std::string operand2 = strtok(nullptr, " ");

		if(instruction == "set"){
			registers[operand1] = GetEffectiveValue(operand2);
		}
		else if (instruction == "sub") {
			registers[operand1] -= GetEffectiveValue(operand2);
		}
		else if (instruction == "mul") {
			mulCounter++;
			registers[operand1] *= GetEffectiveValue(operand2);
		}
		else if (instruction == "jnz") {
			if(GetEffectiveValue(operand1) != 0){
				ip += GetEffectiveValue(operand2);
				continue;
			}
		}
		else{
			assert(false && "bad instruction");
		}
		ip++;
	}
	

	printf("mul counter: %d\n", mulCounter);

	return 0;
}
