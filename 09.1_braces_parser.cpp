#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

int garbageCharacters = 0;

enum Token{
	LEFT_BRACE,
	RIGHT_BRACE,
	COMMA,
	END
};

Token GetNextToken(char const* & input){
	while(true){
		if(!input || !input[0]){
			return END;
		}
		else if(input[0] == '{'){
			input = input + 1;
			return LEFT_BRACE;
		}
		else if(input[0] == '}'){
			input = input + 1;
			return RIGHT_BRACE;
		}
		else if(input[0] == ','){
			input = input + 1;
			return COMMA;
		}
		else if(input[0] == ','){
			input = input + 1;
			return COMMA;
		}
		else if(input[0] == '<'){
			input++;
			do{
				if(*input == '>'){
					input++;
					break;
				}
				else if(*input == '!'){
					input++;
					if(!*input){
						break;
					}
				}
				else{
					garbageCharacters++;
				}
			}while(*input++);
		}
	}
}

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string line;
	std::getline(myfile, line);
	line += '\0';

	char const* inputPtr = &line[0];
	int braceNesting = 0;
	int nestingSum = 0;
	Token tok;
	while((tok = GetNextToken(inputPtr)) != END){
		switch(tok){
			case LEFT_BRACE: 
				nestingSum += ++braceNesting;
				break;

			case RIGHT_BRACE:
				braceNesting--;
				break;
		}
	}

	printf("Nested braces sum: %d, garbage: %d\n", nestingSum, garbageCharacters);
	getchar();

    return 0;
}


 