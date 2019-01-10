#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>

typedef enum Direction {
	UP,
	DOWN,
	RIGHT,
	LEFT
}Direction;

typedef enum VirusDirection {
	GO_LEFT,
	GO_RIGHT
}VirusDirection;

Direction GetNextDirection(Direction currentDirection, VirusDirection virusDirection, int & posX, int & posY) {
	switch (currentDirection) {
	case UP:
		if (virusDirection == GO_LEFT) {
			posX--;
			return LEFT;
		}
		else {
			posX++;
			return RIGHT;
		}
	case DOWN:
		if (virusDirection == GO_LEFT) {
			posX++;
			return RIGHT;
		}
		else {
			posX--;
			return LEFT;
		}
	case RIGHT:
		if (virusDirection == GO_LEFT) {
			posY--;
			return UP;
		}
		else {
			posY++;
			return DOWN;
		}
	case LEFT:
		if (virusDirection == GO_LEFT) {
			posY++;
			return DOWN;
		}
		else {
			posY--;
			return UP;
		}
	}
}

typedef enum NodeState{
	Clean = 0, 
	Weakened, 
	Infected, 
	Flagged 
}NodeState;

int infectionCounter = 0;

struct Node{
	Node(): m_state(Clean) {}
	
	void SwitchState(){
		m_state = (NodeState)(((int)m_state + 1) % 4);
		if(m_state == Infected){
			infectionCounter++;
		}
	} 

	NodeState m_state;
};


int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;

	typedef std::pair<int, int> Coord;
	std::map<Coord, Node> grid;

	std::vector<std::string> instructions;

	int i = 0;
	while (std::getline(myfile, line)) {
		for (int j = 0; j < line.size(); j++) {
			grid[{i, j}].m_state = (line[j] == '#') ? Infected : Clean;
		}
		i++;
	}

	int posX = i / 2;
	int posY = posX;
	Direction lastDirection = UP;

	const int activityCount = 10000000;
	for (int i = 0; i < activityCount; i++) {
		Node & node = grid[{posY, posX}];
		NodeState state = node.m_state;
		node.SwitchState();

		switch(state){
		case Clean:
			lastDirection = GetNextDirection(lastDirection, GO_LEFT, posX, posY);
			break;

		case Weakened:
			switch(lastDirection){
				case UP: posY--; break;
				case DOWN: posY++; break;
				case LEFT: posX--; break;
				case RIGHT: posX++; break;
			}
			break;

		case Infected:
			lastDirection = GetNextDirection(lastDirection, GO_RIGHT, posX, posY);
			break;

		case Flagged:
			switch (lastDirection) {
				case UP: 
					lastDirection = DOWN; 
					posY++; 
					break;

				case DOWN: 
					lastDirection = UP;
					posY--;
					break;

				case LEFT: 
					lastDirection = RIGHT;
					posX++;
					break;

				case RIGHT: 
					lastDirection = LEFT;
					posX--;
					break;
			}
			break;
		}
	}

	printf("infected nodes count: %d\n", infectionCounter);
	getchar();

	return 0;
}
