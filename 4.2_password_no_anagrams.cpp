#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;
	int validPasswords = 0;

	while(std::getline(myfile, line)){
		std::istringstream lineStream(line);
		std::set<std::string> bunchOfWords;
		std::string word;
		bool valid = true;
		while(lineStream >> word){
			std::sort(word.begin(), word.end());
			if(bunchOfWords.find(word) == bunchOfWords.end()){
				bunchOfWords.insert(word);
			}
			else{
				valid = false;
				break;
			}
		}
		if(valid){
			validPasswords++;
		}
	}

	printf("valid passwords count is: %d\n", validPasswords);
	getchar();

    return 0;
}

