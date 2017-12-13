#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <math.h>

const char* results[] = {
	"", "(0,0)", "(1,0)", "(1,1)", "(0,1)",
	"(-1,1)", "(-1,0)", "(-1,-1)", "(0,-1)", "(1,-1)",
	"(2,-1)", "(2,0)", "(2,1)", "(2,2)", "(1,2)",
	"(0,2)", "(-1,2)", "(-2,2)", "(-2,1)", "(-2,0)",
	"(-2,-1)", "(-2,-2)", "(-1,-2)", "(0,-2)", "(1,-2)", "(2,-2)"
};

struct SPoint{
	SPoint(int _i, int _j): 
		i(_i), 
		j(_j)
	{}

	int i;
	int j;
	bool operator<(const SPoint& other) const{
		if(this->i == other.i)
			return this->j < other.j;
		return i < other.i;
	}
};

//enum Direction
void ManhattanPos(int input, int & i, int & j){

/*
	17  16  15  14  13
	18   5   4   3  12
	19   6   1   2  11
	20   7   8   9  10
	21  22  23---> ...
*/
	//input = 7;

	//1^2 3^2 5^2
	// 1,9,25,
	int squareSize = (int)sqrt((double)input);
	if((squareSize & 0x1) == 0){
		squareSize--;
	}
	int itemsInSquare = squareSize * squareSize;
	int indexInNewSquare = input - itemsInSquare;
	int blockSize = squareSize + 1;

	if(indexInNewSquare == 0){
		i = squareSize / 2;
		j = - squareSize / 2;
	}
	
	else if(indexInNewSquare <= blockSize){
		i = squareSize / 2 + 1;
		j = indexInNewSquare - (blockSize / 2);
	}
	else if(indexInNewSquare <= 2 * blockSize){
		i = -(indexInNewSquare - blockSize - 1) + (blockSize / 2 - 1);
		j = squareSize / 2 + 1;
	}
	else if(indexInNewSquare <= 3 * blockSize){
		i = -(squareSize / 2 + 1);
		j = -(indexInNewSquare - 2 * blockSize - 1) + (blockSize / 2 - 1);
	}
	else{
		i = (indexInNewSquare % blockSize) - (blockSize / 2);
		j = -(squareSize / 2 + 1);
	}
}

int ManhattanDist(int address){
	int x, y;
	ManhattanPos(address, x, y);
	return abs(x) + abs(y);
}

int main(){

	std::map<SPoint, int> valueGrid;
	SPoint firstValue(0, 0);
	valueGrid[firstValue] = 1;
	int i, j, x = 2;

	while(true){
		
		ManhattanPos(x, i, j);
		int newVal = 0;
		newVal += valueGrid[SPoint(i+1, j)];
		newVal += valueGrid[SPoint(i+1, j+1)];
		newVal += valueGrid[SPoint(i, j+1)];
		newVal += valueGrid[SPoint(i-1, j+1)];
		newVal += valueGrid[SPoint(i-1, j)];
		newVal += valueGrid[SPoint(i-1, j-1)];
		newVal += valueGrid[SPoint(i, j-1)];
		newVal += valueGrid[SPoint(i+1, j-1)];
		valueGrid[SPoint(i, j)] = newVal;
		if(newVal > 289326){
			printf("and the winner is: %d\n", newVal);
			break;		
		}
		x++;
	}
	
	
	getchar();
    return 0;
}
