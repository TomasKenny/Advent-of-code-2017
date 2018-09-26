#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <ctype.h>
#include "windows.h"

const int LIST_LENGTH = 256;


std::string GetKnotHash(const std::string & data){
	std::vector<int> buffer(LIST_LENGTH);
	for(int i = 0; i < buffer.size(); i++){
		buffer[i] = i;
	}
	
	std::string input(data);
	std::string suffix = "\x11\x1F\x49\x2F\x17";
	input += suffix;
	int skipSize = 0, pos = 0;
	
	for(int rep = 0; rep < 64; rep++){
		for(int j = 0; j < input.size(); j++){
			char length = input[j];
			int steps = length / 2;
			for(int i = 0; i < steps; i++){
				int pos1 = (pos + i) % LIST_LENGTH;
				int pos2 = (pos + length - 1 - i) % LIST_LENGTH;
				std::swap(buffer[pos1], buffer[pos2]);
			}
			pos += length + skipSize++;
			pos %= LIST_LENGTH;

		}
	}

	for(int block = 0; block < 16; block++){
		int val = 0;
		for(int i = 0; i < 16; i++){
			val ^= buffer[block * 16 + i];
		}
		buffer[block] = val;
	}

	std::string result;
	char strBuf[5];
	for(int i = 0; i < 16; i++){
		sprintf(strBuf, "%02x", buffer[i]);
		result += strBuf;
	}
	return result;
}

bool FindSetBit(char grid[128][128], int & row, int & column){
	for(int i = 0; i < 128; i++){
		for(int j = 0; j < 128; j++){
			if(grid[i][j] != 0){
				row = i;
				column = j;
				return true;
			}
		}
	}
	return false;
}

bool IsGridPointSet(char grid[128][128], const int row, const int column){
	if(row < 0 || row >= 128 || column < 0 || column >= 128){
		return false;
	}
	return grid[row][column] != 0;
}

int main(){
	const std::string key = "hxtvlmkl";
	//const std::string key = "flqrgnkx";
	
	char grid[128][128];
	char buf[5];
	int squaresUsed = 0;
	for(int i = 0; i < 128; i++){
		std::string input(key);
		sprintf(buf, "-%d", i);
		input += buf;
		std::string hash = GetKnotHash(input);
		for(int s = 0; s < hash.size(); s++){
			std::string tempStr;
			tempStr += hash[s];
			unsigned val = strtol(tempStr.c_str(), NULL, 16);
			grid[i][s*4] = 0x1 & (val >> 3);
			grid[i][s*4 + 1] = 0x1 & (val >> 2);
			grid[i][s*4 + 2] = 0x1 & (val >> 1);
			grid[i][s*4 + 3] = 0x1 & val;
		}
	}

	int groupsCounter = 0, row, column;
	std::set<std::pair<int,int>> neighborsWithVal1;

	while(FindSetBit(grid, row, column)){
		groupsCounter++;
		std::pair<int,int> gridPoint;
		gridPoint.first = row;
		gridPoint.second = column;
		neighborsWithVal1.insert(gridPoint);

		while(!neighborsWithVal1.empty()){
			gridPoint = *(neighborsWithVal1.begin());
			neighborsWithVal1.erase(neighborsWithVal1.begin());
			int i = gridPoint.first, j = gridPoint.second; 
			grid[i][j] = 0;
			
			if(IsGridPointSet(grid, i + 1, j)){
				gridPoint.first = i + 1;
				gridPoint.second = j;
				neighborsWithVal1.insert(gridPoint);
			}
			if(IsGridPointSet(grid, i - 1, j)){
				gridPoint.first = i - 1;
				gridPoint.second = j;
				neighborsWithVal1.insert(gridPoint);
			}
			if(IsGridPointSet(grid, i, j + 1)){
				gridPoint.first = i;
				gridPoint.second = j + 1;
				neighborsWithVal1.insert(gridPoint);
			}
			if(IsGridPointSet(grid, i, j - 1)){
				gridPoint.first = i;
				gridPoint.second = j - 1;
				neighborsWithVal1.insert(gridPoint);
			}
		}
	}
	printf("how many groups: %d", groupsCounter);
	getchar();

    return 0;
}
