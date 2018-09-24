#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>



int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string line;
	std::map<int, std::vector<int>> programGroups;

	while(std::getline(myfile, line)){
		int leftSide = atoi(line.c_str());
		int rightSideBegin = line.find("<-> ") + 4;
		char* num = strtok(&line[0] + rightSideBegin, ", ");
		while(num){
			programGroups[leftSide].push_back(atoi(num));
			num = strtok(NULL, ", ");
		}
	}
	
	std::set<int> myGroup;
	std::set<int> unvisitedPrograms;
	unvisitedPrograms.insert(0);

	while(!unvisitedPrograms.empty()){
		int newProgram = *(unvisitedPrograms.begin());
		unvisitedPrograms.erase(unvisitedPrograms.begin());

		myGroup.insert(newProgram);
		for(int i = 0; i < programGroups[newProgram].size(); i++){
			int relatedProgram = programGroups[newProgram][i];
			if(myGroup.find(relatedProgram) == myGroup.end()){
				unvisitedPrograms.insert(relatedProgram);
			}
		}
	}
	
	printf("programs in group with program ID 0: %d\n", myGroup.size());

	getchar();
    return 0;
}


 