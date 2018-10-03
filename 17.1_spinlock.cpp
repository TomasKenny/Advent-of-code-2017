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
#include <deque>

class Spinlock{
public:
	Spinlock(int stepCount):
		m_currentPos(0),
		m_stepCount(stepCount)
	{
		m_list.push_back(0);
	}
	
	void Insert(int val){
		m_currentPos = (m_currentPos + m_stepCount) % m_list.size();
		m_list.insert(m_list.begin() + m_currentPos + 1, val);
		m_currentPos++;
	}

	int GetCurrentItem(int offset = 0){
		return *(m_list.begin() + m_currentPos + offset);
	}

private:
	int m_currentPos;
	const int m_stepCount;
	std::deque<int> m_list;
};


int main(){
	Spinlock s(376);
	for(int i = 1; i <= 2017; i++){
		s.Insert(i);
	}
	
	printf("value following 2017: %d", s.GetCurrentItem(1));
	getchar();

    return 0;
}
