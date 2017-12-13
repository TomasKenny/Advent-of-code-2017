#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::stringstream stringStream;
	stringStream << myfile.rdbuf();
	std::string content = stringStream.str();
	content.erase(content.find_last_not_of(" \n\r\t") + 1);
	myfile.close();

	int sum = 0;
	int halfway = content.size() >> 1;
	for(int i = 0; i < content.size(); i++){
		if(content[i] == content[(i + halfway) % content.size()]){
			sum += content[i] - '0';
		}
	}
	
	printf("sum is: %d\n", sum);
	getchar();

    return 0;
}

