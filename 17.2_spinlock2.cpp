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
		m_stepCount(stepCount),
		m_listSize(1)
	{
	}
	
	void Insert(int val){
		m_currentPos = (m_currentPos + m_stepCount) % m_listSize++;
		if(m_currentPos++ == 0){
			m_valueOnIndex1 = val;
		}
	}

	int GetValueOnIndex1(){ return m_valueOnIndex1; }
	
private:
	int m_currentPos;
	const int m_stepCount;
	int m_listSize;
	int m_valueOnIndex1;
};


int main(){
	Spinlock s(376);
	for(int i = 1; i <= 50000000; i++){
		s.Insert(i);
	}
	
	printf("GetValueOnIndex1: %d", s.GetValueOnIndex1());
	getchar();

    return 0;
}
