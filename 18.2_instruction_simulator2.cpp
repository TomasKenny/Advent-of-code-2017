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

int sendInstructionCounter = 0;

class CProcessor{
public:
	CProcessor(){
		m_queueNotEmpty[0] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
		m_queueNotEmpty[1] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	}
	~CProcessor(){
		m_threads[0].join();
		m_threads[1].join();
		CloseHandle(m_queueNotEmpty[0]);
		CloseHandle(m_queueNotEmpty[1]);
	}

	std::vector<std::string> m_instructions;
	void ThreadFunc(int procId);

	std::mutex m_mutex;
	std::vector<int64_t> m_messageQueue[2];
	HANDLE m_queueNotEmpty[2]; 

	std::thread m_threads[2];
};

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;

	// rcv a
	// jgz a -1

	std::vector<std::string> instructions;

	while (std::getline(myfile, line)) {
		instructions.push_back(line);

	}

	{
		CProcessor proc;
		proc.m_instructions = instructions;
		proc.m_threads[0] = std::thread(&CProcessor::ThreadFunc, &proc, 0);
		proc.m_threads[1] = std::thread(&CProcessor::ThreadFunc, &proc, 1);
	}

	printf("send inst counter: %d\n", sendInstructionCounter);
	getchar();

	return 0;
}

void CProcessor::ThreadFunc(int procId){
	char operation[10], op1[10], op2[10];
	int64_t instrPtr = 0;
	std::map<std::string, int64_t> registers;
	registers["p"] = procId;

	std::vector<std::string> instructions;
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		instructions = m_instructions;
	}

	while ((instrPtr >= 0) && (instrPtr < instructions.size())) {
		std::string instruction = instructions[instrPtr];
		sscanf(instruction.c_str(), "%s %s %s", operation, op1, op2);

		if (strcmp(operation, "snd") == 0) {
			int64_t val;
			if (isalpha(op1[0])) {
				val = registers[op1];
			}
			else {
				val = atoi(op1);
			}

			{
				std::lock_guard<std::mutex> lock(m_mutex);
				m_messageQueue[procId ^ 0x1].push_back(val);
				SetEvent(m_queueNotEmpty[procId ^ 0x1]);
			}
			if(procId == 1){
				sendInstructionCounter++;
			}
			instrPtr++;
		}
		else if (strcmp(operation, "rcv") == 0) {
			if (!isalpha(op1[0])) {
				assert(false && "toto jsem necekal");
			}

			int64_t val;
			WaitForSingleObject(m_queueNotEmpty[procId], -1);
			{
				std::lock_guard<std::mutex> lock(m_mutex);
				val = m_messageQueue[procId][0];
				m_messageQueue[procId].erase(m_messageQueue[procId].begin());
				if(m_messageQueue[procId].size() == 0){
					ResetEvent(m_queueNotEmpty[procId]);
				}
			}
			registers[op1] = val;

			instrPtr++;
		}
		else if (strcmp(operation, "set") == 0) {
			if (isalpha(op2[0])) {
				registers[op1] = registers[op2];
			}
			else {
				registers[op1] = atoi(op2);
			}
			instrPtr++;
		}
		else if (strcmp(operation, "add") == 0) {
			if (isalpha(op2[0])) {
				registers[op1] += registers[op2];
			}
			else {
				registers[op1] += atoi(op2);
			}
			instrPtr++;
		}
		else if (strcmp(operation, "mul") == 0) {
			if (isalpha(op2[0])) {
				registers[op1] *= registers[op2];
			}
			else {
				registers[op1] *= atoi(op2);
			}
			instrPtr++;
		}
		else if (strcmp(operation, "mod") == 0) {
			if (isalpha(op2[0])) {
				registers[op1] %= registers[op2];
			}
			else {
				registers[op1] %= atoi(op2);
			}
			instrPtr++;
		}
		else if (strcmp(operation, "jgz") == 0) {
			int64_t jump;
			int64_t cond;
			if (isalpha(op2[0])) {
				jump = registers[op2];
			}
			else {
				jump = atoi(op2);
			}

			if (isalpha(op1[0])) {
				cond = registers[op1];
			}
			else {
				cond = atoi(op1);
			}
			if (cond > 0) {
				instrPtr += jump;
			}
			else {
				instrPtr++;
			}
		}
		
	}
}

