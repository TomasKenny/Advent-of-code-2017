#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <regex>

using namespace std::tr1;

int maxValue = 0;
std::map<std::string, int> registers;
typedef std::map<std::string, int>::value_type RegisterMapValue;
typedef std::map<std::string, int>::iterator RegisterIterator;

bool mapcmp(const RegisterMapValue &a, const RegisterMapValue &b){
	return a.second < b.second;
}


enum Operation{
	INC, DEC
};

enum Comparator{
	LT,
	GT,
	LE,
	GE,
	EQ,
	NEQ
};

const char* ComparatorTokens[] = {
	"<", ">", "<=", ">=", "==", "!="
};

bool EvalCondition(const std::string & operand, Comparator comp, int value){
	switch(comp){
		case LT: return registers[operand] < value;
		case GT: return registers[operand] > value;
		case LE: return registers[operand] <= value;
		case GE: return registers[operand] >= value;
		case EQ: return registers[operand] == value;
		case NEQ: return registers[operand] != value;
	}
}

void EvalOperation(const std::string & operand, Operation op, int value){
	switch(op){
		case INC: 
			registers[operand] += value;
			break;
		case DEC: 
			registers[operand] -= value;
			break;
	}
	maxValue = std::max(maxValue, registers[operand]);
}



int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string line;
	
	//c inc -20 if c == 10
	regex instructionRegex("^(.+) (inc|dec) (.+) if (.+) (.+) (.+)$");
		
	
	while(std::getline(myfile, line)){
		cmatch match;
		if(!regex_match(line.c_str(), match, instructionRegex)){
			throw std::exception("bad input");
		}
		std::string operand = match[1].str();
		Operation op = (strcmp(match[2].str().c_str(), "inc") == 0) ? INC : DEC;
		int value = atoi(match[3].str().c_str());
		std::string conditionOperand = match[4].str();
		std::string comparatorStr = match[5].str();
		Comparator comparator;
		for(int i = 0; i < sizeof(ComparatorTokens) / sizeof(ComparatorTokens[0]); i++){
			if(strcmp(ComparatorTokens[i], comparatorStr.c_str()) == 0){
				comparator = (Comparator)i;
				break;
			}
		}
		int conditionValue = atoi(match[6].str().c_str());
		if(EvalCondition(conditionOperand, comparator, conditionValue)){
			EvalOperation(operand, op, value);
		}
	}

	RegisterIterator it = std::max_element(registers.begin(), registers.end(), mapcmp); 


	printf("max value in registers at the end: %d\n"
		"max value ever: %d\n", it->second, maxValue);
	getchar();

    return 0;
}

 