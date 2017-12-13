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
	int checksum = 0;
	
	while(std::getline(myfile, line)){
		std::istringstream lineStream(line);
		std::vector<int> numbers;
		int num;
		for(int i = 0; lineStream >> num; i++){
			numbers.push_back(num);	
		}
		for(int i = 0; i < numbers.size(); i++){
			for(int j = 0; j < numbers.size(); j++){
				if(i == j){
					continue;
				}
				if(numbers[i] % numbers[j] == 0){
					checksum += numbers[i] / numbers[j];
				}
			}
		}
	}

	printf("checksum is: %d\n", checksum);
	getchar();

    return 0;
}

