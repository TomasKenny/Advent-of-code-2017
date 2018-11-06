#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include "assert.h"

class Grid{
public:
	Grid(int size):
		m_size(size)
	{
		Init();
	}

	Grid(const std::string & strData){
		//#.#/#../...
		m_size = strData.find("/");
		std::string strCopy(strData);
		int pos;
		while((pos = strCopy.find("/")) != std::string::npos){
			strCopy.erase(pos, 1);
		}
		Init();
		SetData(strCopy, 0, 0, m_size);
	}

	void SetData(const std::string & data, int offsetX, int offsetY, int blockSize){
		std::string::const_iterator it = data.begin();
		for(int i = offsetY; i < offsetY + blockSize; i++){
			for(int j = offsetX; j < offsetX + blockSize; j++){
				m_grid[i][j] = *it++;
			}
		}
	}
	
	void Rotate(int rotateCount){
		rotateCount %= 4;
		for(int i = 0; i < rotateCount; i++){
		
			Grid rotatedGrid(m_size);
			for(int i = 0; i < m_size; i++){
				for(int j = 0; j < m_size; j++){
					rotatedGrid.m_grid[j][m_size - i - 1] = m_grid[i][j];
				}
			}
			this->m_grid = rotatedGrid.m_grid;
		}
	}

	void Flip(){
		for(int i = 0; i < m_size; i++){
			std::string reverse(m_grid[i].rbegin(), m_grid[i].rend());
			m_grid[i] = reverse;
		}
	}

	std::string BlockToString(int x, int y, int blockSize){
		std::string str;
		for(int i = y; i < y + blockSize; i++){
			for(int j = x; j < x + blockSize; j++){
				str += m_grid[i][j];
			}
		}
		return str;

	}

	int GetSize(){ return m_size; }
	
	int GetTurnedOnPixelsCount(){
		int ctr = 0;
		for(int i = 0; i < m_size; i++){
			for(int j = 0; j < m_size; j++){
				ctr += (m_grid[i][j] == '#') ? 1 : 0;
			}
		}
		return ctr;
	}

private:
	void Init(){
		std::string line;
		line.resize(m_size);
		for(int i = 0; i < m_size; i++){
			m_grid.push_back(line);
		}
	}

	int m_size;
	std::vector<std::string> m_grid;
};

	
typedef std::map<std::string, std::string> Rules;


class Fractal{
public:
	Fractal():
		m_grid(3)
	{
		m_grid.SetData(".#...####", 0, 0, 3);	
	}

	void AddRule(const std::string & before, const std::string & after){
		m_rules[before] = after;
	}

	void DoTheMagic();
	int GetTurnedOnPixelsCount(){ return m_grid.GetTurnedOnPixelsCount(); }

public:
	Grid m_grid;
	Rules m_rules;
};

void Fractal::DoTheMagic(){
	int blockSize, newGridSize;
	if((m_grid.GetSize() % 2) == 0){
		blockSize = 2;
		newGridSize = m_grid.GetSize() + (m_grid.GetSize() >> 1);
	}
	else{
		blockSize = 3;
		newGridSize = m_grid.GetSize() + (m_grid.GetSize() / 3);
	}

	Grid newGrid(newGridSize);

	for(int i = 0; i < m_grid.GetSize() / blockSize; i++){
		for(int j = 0; j < m_grid.GetSize() / blockSize; j++){
			std::string pattern = m_grid.BlockToString(j * blockSize, i * blockSize, blockSize);
			std::string newFractalData = m_rules[pattern];
			newGrid.SetData(newFractalData, j * (blockSize + 1), i * (blockSize + 1), blockSize + 1);
		}
	}

	m_grid = newGrid;
}

int main(){
	std::ifstream myfile;
	myfile.open("c:\\Users\\Tom\\Desktop\\input.txt");
	std::string line;
	
	
	Fractal f;
	while(std::getline(myfile, line)){
		//  .../.../... => ..../.#../##.#/#.#.		
		std::string leftSide = strtok(&line[0], " =>");
		std::string rightSide = strtok(NULL, " =>");

		int pos;
		while((pos = rightSide.find("/")) != std::string::npos){
			rightSide.erase(pos, 1);
		}

		Grid leftSideGrid(leftSide);
		Grid leftSideGridFlipped(leftSide);
		leftSideGridFlipped.Flip();

		for(int i = 0; i < 4; i++){
			leftSideGrid.Rotate(1); 
			leftSideGridFlipped.Rotate(1);

			std::string rotatedGridStr = leftSideGrid.BlockToString(0, 0, leftSideGrid.GetSize());
			f.AddRule(rotatedGridStr, rightSide);

			rotatedGridStr = leftSideGridFlipped.BlockToString(0, 0, leftSideGridFlipped.GetSize());
			f.AddRule(rotatedGridStr, rightSide);
		}
	}

	for(int i = 0; i < 18; i++){
		f.DoTheMagic();
	}

	printf("turned on pixels: %d\n", f.GetTurnedOnPixelsCount());
	getchar();

    return 0;
}



