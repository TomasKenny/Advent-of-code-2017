#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <mutex>
#include <thread>
#include <assert.h>
#include <windows.h>
#include <algorithm>


class Layer{
public:
	Layer(){}

	Layer(int layerIndex, int range):
		m_layerIndex(layerIndex), 
		m_range(range)
	{}
	
	void Advance(){
		if(m_scannerGoingDown){
			m_scannerPos++;
			if(m_scannerPos == m_range){
				m_scannerGoingDown = false;
				m_scannerPos = m_range - 2;
			}
		}
		else{
			m_scannerPos--;
			if (m_scannerPos == -1) {
				m_scannerGoingDown = true;
				m_scannerPos = 1;
			}
		}
	}

	void Skip(int steps){
		steps %= m_range * 2 - 2;
		if(steps < m_range){
			m_scannerGoingDown = true;
			m_scannerPos = steps;
		}
		else{
			m_scannerGoingDown = false;
			m_scannerPos = m_range - (steps - m_range + 1) - 1;
		}
	}

	bool IsInTopLayer(){ return m_scannerPos == 0; }
	int GetSeverity(){ return m_layerIndex * m_range; }

private:
	int m_range;
	int m_layerIndex;
	int m_scannerPos = 0;
	bool m_scannerGoingDown = true;
};

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;

	
	std::map<int, Layer> fireWall;
	std::map<int, Layer>::iterator it;
	int layerIndex, range, totalLayers = 0;

	while (std::getline(myfile, line)) {
		sscanf(line.c_str(), "%d: %d", &layerIndex, &range);
		fireWall[layerIndex] = Layer(layerIndex, range);
		totalLayers = max(totalLayers, layerIndex);
	}

	for(int delay = 0;;delay++){
		std::map<int, Layer> fireWallCopy(fireWall);
		
		//prepare delay
		for (it = fireWallCopy.begin(); it != fireWallCopy.end(); it++) {
			it->second.Skip(delay);
		}
		

		bool gotCaught = false;
		for(int i = 0; i <= totalLayers; i++){
			if(fireWallCopy.find(i) != fireWallCopy.end()){
				if(fireWallCopy[i].IsInTopLayer()){
					gotCaught = true;
					break;
				}
			}

			for(it = fireWallCopy.begin(); it != fireWallCopy.end(); it++){
				it->second.Advance();
			}
		}
		if(gotCaught){
			continue;
		}
		printf("escaped in time: %d\n", delay);
		getchar();
		return 0;
	}

	printf("too bad");
	getchar();

	return 0;
}


