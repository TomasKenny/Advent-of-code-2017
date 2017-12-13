#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;
	int checksum = 0;
	while(std::getline(myfile, line)){
		std::istringstream lineStream(line);
		int num, min, max;
		for(int i = 0; lineStream >> num; i++){
			if(i == 0){
				min = max = num;
				continue;
			}
			min = std::min(min, num);
			max = std::max(max, num);
		}
		checksum += max - min;
	}

	printf("checksum is: %d\n", checksum);
	getchar();

    return 0;
}

