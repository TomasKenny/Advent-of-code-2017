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


int main(){
	unsigned __int64 valA = 591;
	unsigned __int64 valB = 393;
	
	const unsigned __int64 factorA = 16807;
	const unsigned __int64 factorB = 48271;

	int matches = 0;
	for(int i = 0; i < 40000000; i++){
		valA = (valA * factorA) % 2147483647;
		valB = (valB * factorB) % 2147483647;
		if((valA & 0xFFFF) == (valB & 0xFFFF)){
			matches++;
		}
	}

	printf("how many matches: %d", matches);
	getchar();

    return 0;
}
