#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>
#include <stack>
#include <assert.h>
#include <numeric>

typedef std::pair<int,int> DominoPiece;

const std::vector<DominoPiece> dominoPieces = {
		/*{0, 2},
		{2, 2},
		{2, 3},
		{3, 4},
		{3, 5},
		{0, 1},
		{10, 1},
		{9, 10},
		*/
	{24, 14},{30, 24},{29, 44},{47, 37},{6, 14},{20, 37},{14, 45},{5, 5},
	{26, 44},{2, 31},{19, 40},{47, 11},{0, 45},{36, 31},{3, 32},{30, 35},
	{32, 41},{39, 30},{46, 50},{33, 33},{0, 39},{44, 30},{49, 4},{41, 50},
	{50, 36},{5, 31},{49, 41},{20, 24},{38, 23},{4, 30},{40, 44},{44, 5},
	{0, 43},{38, 20},{20, 16},{34, 38},{5, 37},{40, 24},{22, 17},{17, 3},
	{9, 11},{41, 35},{42, 7},{22, 48},{47, 45},{6, 28},{23, 40},{15, 15},
	{29, 12},{45, 11},{21, 31},{27, 8},{18, 44},{2, 17},{46, 17},{29, 29},
	{45, 50},
	
};

class DominoChain{
public:
	int GetStrength() const {
		int strength = 0;
		for(const auto & item: m_chain){
			strength += item.first + item.second;
		}
		return strength;
	}

	int GetLength() const { return m_chain.size(); }

	bool IsConnectable(const DominoPiece & domino) const {
		if (m_chain.empty()) {
			return (domino.first == 0) || (domino.second == 0);
		}
		return (m_freeEnd == domino.first) || (m_freeEnd == domino.second);
	}

	void Connect(const DominoPiece & domino){
		if(m_chain.empty()){
			m_freeEnd = std::max(domino.first, domino.second);
		}
		else{
			if(m_freeEnd == domino.first){
				m_freeEnd = domino.second;
			}
			else{
				m_freeEnd = domino.first;
			}
		}
		m_chain.push_back(domino);
	}

private:
	std::vector<DominoPiece> m_chain;
	int m_freeEnd;
};


struct DominoSolver{
	
	void DoTheMagic(){
		m_maxStrength = 0;
		m_maxLength = 0;

		for(int chainSize = 1; chainSize <= dominoPieces.size(); chainSize++){
			Solve(DominoChain(), dominoPieces, chainSize);
		}
	}

	void Solve(const DominoChain & chain, const std::vector<DominoPiece> & freeDominos, int connectCount) {
		int length = chain.GetLength();
		if (length > m_maxLength) {
			m_maxLength = length;
			m_maxStrength = chain.GetStrength();
		}
		else if (length == m_maxLength) {
			m_maxStrength = std::max(m_maxStrength, chain.GetStrength());
		}

		if (connectCount == 0) {
			return;
		}
		for (int i = 0; i < freeDominos.size(); i++) {
			if (chain.IsConnectable(freeDominos[i])) {
				DominoChain chainCopy(chain);
				chainCopy.Connect(freeDominos[i]);
				std::vector<DominoPiece> freeDominosCopy(freeDominos);
				freeDominosCopy.erase(freeDominosCopy.begin() + i);
				
				Solve(chainCopy, freeDominosCopy, connectCount - 1);
			}
		}
	}
	
	int m_maxStrength;
	int m_maxLength;
	DominoChain m_strongestChain;
};

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::stringstream stringStream;
	stringStream << myfile.rdbuf();
	std::string line = stringStream.str();

	/*while(std::getline(stringStream, line)){
		
	}*/

	DominoSolver solver;
	solver.DoTheMagic();

	printf("max strength: %d\n", solver.m_maxStrength);
	return 0;
}
