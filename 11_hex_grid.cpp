#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <algorithm>

int CoordsToSteps(int x, int y){
	x = abs(x);
	y = abs(y);

	int steps = 0;
	while(x != 0 && y != 0){
		x -= 2;
		y -= 1;
		steps++;
	}
	return steps + (x >> 1) + (y >> 1);
}

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::stringstream stringStream;
	stringStream << myfile.rdbuf();
	std::string content = stringStream.str();
	myfile.close();
	
	int x = 0, y = 0, maxSteps = 0;
	char* direction, *ptr = &content[0];
	direction = strtok(ptr, ",\n");
	do{
		if(strcmp(direction, "n") == 0){
			y += 2;
		}
		else if(strcmp(direction, "s") == 0){
			y += -2;
		}
		else if(strcmp(direction, "nw") == 0){
			x += -2;
			y += 1;
		}
		else if(strcmp(direction, "ne") == 0){
			x += 2;
			y += 1;
		}
		else if(strcmp(direction, "sw") == 0){
			x += -2;
			y += -1;
		}
		else if(strcmp(direction, "se") == 0){
			x += 2;
			y += -1;
		}
		else{
			assert(false && "bad input");
		}
		maxSteps = std::max(maxSteps, CoordsToSteps(x, y));

	}while((direction = strtok(NULL, ",\n")) != NULL);

	
	printf("current position steps: %d, max steps away: %d\n", CoordsToSteps(x, y), maxSteps);
	getchar();

    return 0;
}