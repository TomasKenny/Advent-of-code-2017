#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>

typedef enum Direction{
	UP,
	DOWN,
	RIGHT,
	LEFT
}Direction;

typedef enum VirusDirection{
	GO_LEFT,
	GO_RIGHT
}VirusDirection;

Direction GetNextDirection(Direction currentDirection, VirusDirection virusDirection, int & posX, int & posY){
	switch(currentDirection){
	case UP:
		if(virusDirection == GO_LEFT){
			posX--;
			return LEFT;
		}
		else{
			posX++;
			return RIGHT;
		} 
	case DOWN:
		if(virusDirection == GO_LEFT){
			posX++;
			return RIGHT;
		}
		else{
			posX--;
			return LEFT;
		} 
	case RIGHT:
		if(virusDirection == GO_LEFT){
			posY--;
			return UP;
		}
		else{
			posY++;
			return DOWN;
		}
	case LEFT:
		if(virusDirection == GO_LEFT){
			posY++;
			return DOWN;
		}
		else{
			posY--;
			return UP;
		}
	}
}

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;

	typedef std::pair<int, int> Node;
	std::map<Node, char> grid;

	std::vector<std::string> instructions;

	int i = 0;
	while (std::getline(myfile, line)) {
		for(int j = 0; j < line.size(); j++){
			grid[{i, j}] = (line[j] == '#');
		}
		i++;
	}

	int posX = i / 2;
	int posY = posX;
	Direction lastDirection = UP;

	const int activityCount = 10000;
	int infectionCounter = 0;
	for(int i = 0; i < activityCount; i++){
		bool infected = grid[{posY, posX}];
		grid[{posY, posX}] = !grid[{posY, posX}];
		if(infected){
			lastDirection = GetNextDirection(lastDirection, GO_RIGHT, posX, posY);
		}
		else{
			infectionCounter++;
			lastDirection = GetNextDirection(lastDirection, GO_LEFT, posX, posY);
		}
	}

	printf("infected nodes count: %d\n", infectionCounter);
	getchar();

	return 0;
}
