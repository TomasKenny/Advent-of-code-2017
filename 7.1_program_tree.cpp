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
	
	//			node		parent
	std::map<std::string, std::string> nodes;

	while(std::getline(myfile, line)){
		std::string root;
		root.resize(20);
		int weight;
		if(sscanf(line.c_str(), "%s (%d)", &root[0], &weight) != 2){
			throw std::exception("bad input");
		}
		root.resize(strlen(root.c_str()));
		int pos = line.find("-> ");
		if(pos != std::string::npos){
			line.erase(0, pos + 3);
			
			char* bufferPtr = &line[0];
			bufferPtr = strtok(bufferPtr, " ,");
			while(bufferPtr){
				nodes[std::string(bufferPtr)] = root;
				bufferPtr = strtok(NULL, " ,");
			}
		}
	}

	//find root
	std::string rootName, key;
	std::map<std::string, std::string>::iterator it;
	key = nodes.begin()->second;
	while(true){
		it = nodes.find(key);
		if(it == nodes.end()){
			rootName = key;
			break;
		}
		key = it->second;
	}

	printf("tree root: %s\n", rootName.c_str());
	getchar();

    return 0;
}

 