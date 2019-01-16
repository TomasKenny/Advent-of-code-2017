#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <regex>
#include <assert.h>


int main(){
	__int64 a,b,c,d,e,f,g,h;
	int mulCount = 0;
	b = c = d = e = f = g = h = 0;
	a = 1;	/////////////////////////
	//a = 0;

	b = c = 93;

	if (a != 0){
		mulCount++;
		b = 109300;
		c = 126300;
	}
		
	do{
		f = 1;
		d = 2;

		do{
			e = 2;

			/*
			do{
				mulCount++;
				g = (d * e) - b;
				if (g == 0) {
					f = 0;
				}
				e++;
				g = e - b;

			}while(g != 0);
			*/
			if((b % d) == 0){
				f = 0;
			}


			d++;
			g = d - b;

		}while(g != 0);
			

		if (f == 0) {
			h++;
		}
		
		g = b - c;
		b += 17;
	}while(g != 0);

	//printf("mul count: %d", mulCount);
	printf("h value: %d", h);
	return 0;
}

