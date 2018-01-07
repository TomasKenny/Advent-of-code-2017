#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
//#include <ctype>

std::string g_message;
int steps = 0;

enum Direction{
	UP = 1,
	DOWN = ~UP,
	LEFT = 2,
	RIGHT = ~LEFT
};

struct Network{
	char GetItemAt(int x, int y){
		if(y < 0 || y >= m_grid.size()){
			return ' ';
		}
		if(x < 0 || x >= m_grid[y].size()){
			return ' ';
		}
		return m_grid[y][x];
	}

	bool GetNextPos(int & x, int & y, Direction & direction){
		steps++;
		std::vector<Direction> moves;
		moves.push_back(UP);
		moves.push_back(DOWN);
		moves.push_back(LEFT);
		moves.push_back(RIGHT);

		//prevent going backwards
		moves.erase(std::find(moves.begin(), moves.end(), (Direction)~direction));

		//prioritize last direction
		moves.erase(std::find(moves.begin(), moves.end(), direction));
		moves.insert(moves.begin(), direction);

		char item;
		int nextPosX, nextPosY;
		for(int i = 0; i < moves.size(); i++){
			switch(moves[i]){
				case UP:
					nextPosX = x;
					nextPosY = y - 1;
					break;
				case DOWN:
					nextPosX = x;
					nextPosY = y + 1;
					break;
				case LEFT:
					nextPosX = x - 1;
					nextPosY = y;
					break;
				case RIGHT:
					nextPosX = x + 1;
					nextPosY = y;
					break;
			}

			item = GetItemAt(nextPosX, nextPosY);
			if(isspace(item)){
				continue;
			}
			if(isalnum(item)){
				g_message += item;
			}
			x = nextPosX;
			y = nextPosY;
			direction = moves[i];
			return true;

		}
		return false;
	}


	std::vector<std::string> m_grid;
};



int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string line;
	Network network;
	while(std::getline(myfile, line)){
		network.m_grid.push_back(line);
	}
	
	int x, y = 0;
	x = network.m_grid[0].find("|");
	Direction direction = DOWN;

	while(network.GetNextPos(x, y, direction));

	
	printf("message on path: %s, steps: %d\n", g_message.c_str(), steps);
	getchar();

    return 0;
}
 