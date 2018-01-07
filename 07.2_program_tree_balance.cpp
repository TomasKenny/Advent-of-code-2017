#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

//			node		parent
std::map<std::string, std::string> nodes;
std::map<std::string, int> weights;

struct Tree{
	Tree(std::string name, int weight):
		m_name(name),
		m_weight(weight)
	{}

	int GetTreeWeight(bool includeRoot = true){
		int weight = 0;
		for(int i = 0; i < m_children.size(); i++){
			weight += m_children[i].GetTreeWeight();
		}
		return weight + (includeRoot ? m_weight : 0); 
	}

	std::string m_name;
	int m_weight;
	std::vector<Tree> m_children;
};

void AddNodes(Tree & rootPtr){
	std::map<std::string, std::string>::iterator it;

	std::vector<std::string> children;
	for(it = nodes.begin(); it != nodes.end(); it++){
		if(it->second.compare(rootPtr.m_name) == 0){
			std::string childName = it->first;
			Tree child(childName, weights[it->first]);
			rootPtr.m_children.push_back(child);
			AddNodes(rootPtr.m_children.back());
		}
	}
}

bool IsTreeBalanced(Tree & tree, int & unbalancedChildIndex, int & correctSubtreeWeight){
	//		weight, occurences
	std::map<int,int> weightMap;
	for(int i = 0; i < tree.m_children.size(); i++){
		weightMap[tree.m_children[i].GetTreeWeight()]++;
	}
	if(weightMap.size() == 1){
		return true;
	}

	int oddOneOutWeight;
	std::map<int,int>::iterator it;
	for(it = weightMap.begin(); it != weightMap.end(); it++){
		if(it->second == 1){
			oddOneOutWeight = it->first;
			break;
		}
		else{
			correctSubtreeWeight = it->first;
		}
	}
	for(int i = 0; i < tree.m_children.size(); i++){
		if(tree.m_children[i].GetTreeWeight() == oddOneOutWeight){
			unbalancedChildIndex = i;
			break;
		}
	}
	return false;
}

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string line;
	
	

	while(std::getline(myfile, line)){
		std::string root;
		root.resize(20);
		int weight;
		if(sscanf(line.c_str(), "%s (%d)", &root[0], &weight) != 2){
			throw std::exception("bad input");
		}
		root.resize(strlen(root.c_str()));
		weights[root] = weight;

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

	Tree myTree(rootName, weights[rootName]);
	AddNodes(myTree);

	int unBalancedChild, correctSubtreeWeight;
	Tree* treePtr = &myTree;
	while(!IsTreeBalanced(*treePtr, unBalancedChild, correctSubtreeWeight)){
		treePtr = &treePtr->m_children[unBalancedChild];
	}

	int correctWeight = correctSubtreeWeight - treePtr->GetTreeWeight(false);

	printf("Correct weight of node %s is %d\n", treePtr->m_name.c_str(), correctWeight);
	getchar();

    return 0;
}

 