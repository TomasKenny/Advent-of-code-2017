#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

void ManhattanDist(int input, int & i, int & j){

/*
	17  16  15  14  13
	18   5   4   3  12
	19   6   1   2  11
	20   7   8   9  10
	21  22  23---> ...
*/
	//input = 6;

	//1^2 3^2 5^2
	// 1,9,25,
	int squareSize = sqrt(input);
	if((squareSize & 0x1) == 0){
		squareSize--;
	}
	int itemsInSquare = squareSize * squareSize;
	int indexInNewSquare = input - itemsInSquare;
	int newSquareSize = squareSize + 2;
	if(indexInNewSquare == 0){
		i = squareSize / 2;
		j = - squareSize / 2;
		printf("centre\n");
	}
	
	else if(indexInNewSquare <= (squareSize + 1)){
		i = squareSize / 2 + 1;
		j = indexInNewSquare - (newSquareSize / 2);
		printf("right\n");
	}
	else if(indexInNewSquare <= 2 * (squareSize + 1)){
		i = -((indexInNewSquare % newSquareSize) - (newSquareSize / 2) + 1);
		j = squareSize / 2 + 1;
		printf("top\n");
	}
	else if(indexInNewSquare <= 3 * (squareSize + 1)){
		i = -(squareSize / 2 + 1);
		j = -((indexInNewSquare % newSquareSize) - (newSquareSize / 2) - 1);
		printf("left\n");
	}
	else{
		i = (indexInNewSquare % newSquareSize) - (newSquareSize / 2);
		j = -(squareSize / 2 + 1);
		printf("bottom\n");
	}
}

int main(){
	int i = 0, j = 0;
	for(int x = 1; x <= 25; x++){
		ManhattanDist(x, i, j);
		printf("manhattan dist for %d is: (%d,%d)\n", x, i, j);
	}
	
	printf("manhattan distance is: %d\n", i + j);
	getchar();

    return 0;
}

