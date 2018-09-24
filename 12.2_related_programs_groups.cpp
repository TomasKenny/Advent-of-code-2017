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
	std::map<int, std::vector<int>>::iterator it;

	while(std::getline(myfile, line)){
		int leftSide = atoi(line.c_str());
		int rightSideBegin = line.find("<-> ") + 4;
		char* num = strtok(&line[0] + rightSideBegin, ", ");
		while(num){
			programGroups[leftSide].push_back(atoi(num));
			num = strtok(NULL, ", ");
		}
	}
	
	std::set<std::set<int>> groupOfGroups;

	for(it = programGroups.begin(); it != programGroups.end(); it++){

		std::set<int> myGroup;
		std::set<int> unvisitedPrograms;
		unvisitedPrograms.insert(it->first);

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
		groupOfGroups.insert(myGroup);
	}
	printf("how many groups: %d\n", groupOfGroups.size());

	getchar();
    return 0;
}


 