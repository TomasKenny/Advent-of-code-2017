#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;
	
	// rcv a
	// jgz a -1
			
	std::vector<std::string> instructions;
	
	while(std::getline(myfile, line)){
		instructions.push_back(line);
		
	}

	char operation[10], op1[10], op2[10];
	int64_t instrPtr = 0;
	std::map<std::string, int64_t> registers;
	int64_t lastPlayedSound = 0;

	while((instrPtr >= 0) && (instrPtr < instructions.size())){
		std::string instruction = instructions[instrPtr];
		sscanf(instruction.c_str(), "%s %s %s", operation, op1, op2);
		
		if(strcmp(operation, "snd") == 0){
			if(isalpha(op1[0])){
				lastPlayedSound = registers[op1];
			}
			else{
				lastPlayedSound = atoi(op1);
			}
			instrPtr++;
		}
		else if(strcmp(operation, "set") == 0){
			if(isalpha(op2[0])){
				registers[op1] = registers[op2];
			}
			else{
				registers[op1] = atoi(op2);
			}
			instrPtr++;
		}
		else if(strcmp(operation, "add") == 0){
			if(isalpha(op2[0])){
				registers[op1] += registers[op2];
			}
			else{
				registers[op1] += atoi(op2);
			}
			instrPtr++;
		}
		else if(strcmp(operation, "mul") == 0){
			if(isalpha(op2[0])){
				registers[op1] *= registers[op2];
			}
			else{
				registers[op1] *= atoi(op2);
			}
			instrPtr++;
		}
		else if(strcmp(operation, "mod") == 0){
			if(isalpha(op2[0])){
				registers[op1] %= registers[op2];
			}
			else{
				registers[op1] %= atoi(op2);
			}
			instrPtr++;
		}
		else if(strcmp(operation, "jgz") == 0){
			int64_t jump;
			int64_t cond;
			if(isalpha(op2[0])){
				jump = registers[op2];
			}
			else{
				jump = atoi(op2);
			}

			if(isalpha(op1[0])){
				cond = registers[op1];
			}
			else{
				cond = atoi(op1);
			}
			if(cond > 0){
				instrPtr += jump;
			}
			else{
				instrPtr++;
			}
		}
		else if(strcmp(operation, "rcv") == 0){
			int64_t cond;
			if(isalpha(op1[0])){
				cond = registers[op1];
			}
			else{
				cond = atoi(op1);
			}
			if(cond){
				break;
			}
			else{
				instrPtr++;
			}
		}
	}
	
	printf("max value in registers at the end: %d\n", lastPlayedSound);
	getchar();

    return 0;
}



