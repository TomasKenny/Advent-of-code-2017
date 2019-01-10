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

struct MachineAction{
	char writeValue;
	int move;
	char nextState;
};

typedef std::pair<char,char> MachineState;

std::map<MachineState, MachineAction> turingProgram = {
	{{'A', 0}, {1, 1, 'B'}},
	{{'A', 1}, {0, -1, 'B'}},
	{{'B', 0}, {0, 1, 'C'}},
	{{'B', 1}, {1, -1, 'B'}},
	{{'C', 0}, {1, 1, 'D'}},
	{{'C', 1}, {0, -1, 'A'}},
	{{'D', 0}, {1, -1, 'E'}},
	{{'D', 1}, {1, -1, 'F'}},
	{{'E', 0}, {1, -1, 'A'}},
	{{'E', 1}, {0, -1, 'D'}},
	{{'F', 0}, {1, 1, 'A'}},
	{{'F', 1}, {1, -1, 'E'}},
};

class TuringMachine{
public:
	int Run(char startState, int stepCount){
		int tapePos = 0;
		tape.clear();
		char state = startState;

		for(int i = 0; i < stepCount; i++){
			MachineAction action = turingProgram[MachineState(state, tape[tapePos])];
			tape[tapePos] = action.writeValue;
			tapePos += action.move;
			state = action.nextState;
		}

		int checksum = 0;
		for(const auto & item: tape){
			checksum += item.second;
		}
		return checksum;
	}
private:
	std::map<int,char> tape;
};

int main() {
	
	TuringMachine m;
	printf("checksum: %d\n", m.Run('A', 12586542));
	return 0;
}
