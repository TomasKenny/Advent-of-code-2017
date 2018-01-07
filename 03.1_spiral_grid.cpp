#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <math.h>

const char* results[] = {
	"", "(0,0)", "(1,0)", "(1,1)", "(0,1)",
	"(-1,1)", "(-1,0)", "(-1,-1)", "(0,-1)", "(1,-1)",
	"(2,-1)", "(2,0)", "(2,1)", "(2,2)", "(1,2)",
	"(0,2)", "(-1,2)", "(-2,2)", "(-2,1)", "(-2,0)",
	"(-2,-1)", "(-2,-2)", "(-1,-2)", "(0,-2)", "(1,-2)", "(2,-2)"
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
	/*int i = 0, j = 0;
	for(int x = 1; x <= 25; x++){
		ManhattanDist(x, i, j);
		printf("manhattan dist for %d is: (%d,%d), should be %s\n", x, i, j, results[x]);
	}
	*/
	
	printf("manhattan distance is: %d\n", ManhattanDist(289326));
	getchar();

    return 0;
}
