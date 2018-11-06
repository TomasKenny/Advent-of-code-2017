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

void Spin(std::string & str, int x){
	//ab cde
	str = str.substr(str.size() - x) + str.substr(0, str.size() - x);
}

void Exchange(std::string & str, int a, int b){
	std::swap(str[a], str[b]);
}

void Partner(std::string & str, char a, char b){
	std::string::iterator it = std::find(str.begin(), str.end(), a);
	std::string::iterator it2 = std::find(str.begin(), str.end(), b);
	std::swap(*it, *it2);
}

int main(){
	
	char c = 'a';
	const int stringLen = 16;

	std::string s;
	for(int i = 0; i < stringLen; i++){
		s += c++;
	}

	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string danceMoves, danceMoves2;
	
	std::map<std::string, std::string> nodes;
	std::getline(myfile, danceMoves2);
	//danceMoves = "s1,x3/4,pe/b";
	std::vector<std::string> permutations;
	std::vector<std::string>::iterator it;

	for(volatile int i = 0; i < 1000000000; i++){
		danceMoves = danceMoves2;
		char* move = strtok(&danceMoves[0], ",");
		do{
			switch(move[0]){
				case 's':
					Spin(s, atoi(move + 1));
					break;
				case 'x':
					Exchange(s, atoi(move + 1), atoi(strstr(move, "/") + 1));
					break;
				case 'p':
					Partner(s, move[1], move[3]);
			}
		}while(move = strtok(NULL, ","));

		//----------------------------------------------------
		it = std::find(permutations.begin(), permutations.end(), s);
		if(it != permutations.end()){
			int startOfPeriod = it - permutations.begin();
			int period = i - startOfPeriod;
			int indexOfBillionth = (1000000000 - 1 - startOfPeriod) % period + startOfPeriod;
			s = permutations[indexOfBillionth];
			break;
		}
		permutations.push_back(s);
	}

	printf("modified string: %s", s.c_str());
	getchar();

    return 0;
}
