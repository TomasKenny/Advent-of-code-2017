#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>

int main(){
	std::set<std::vector<int>> states;
	std::vector<int> banks = {5, 1, 10, 0, 1, 7, 13, 14, 3, 12, 8, 10, 7, 12, 0, 6};
	states.insert(banks);

	int jumps;
	for(jumps = 1;;jumps++){
		auto biggestBank = std::max_element(banks.begin(), banks.end());
		int index = biggestBank - banks.begin();
		int blocks = banks[index];
		banks[index] = 0;
		for(; blocks > 0; blocks--){
			banks[++index % banks.size()]++;
		}
		if(states.find(banks) != states.end()){
			break;
		}
		states.insert(banks);
	}

	
	printf("jumps count is: %d\n", jumps);
	getchar();

    return 0;
}

