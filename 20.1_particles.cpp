#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <regex>

struct Coord{
	__int64 x;
	__int64 y;
	__int64 z;

	Coord operator+(const Coord & other){
		Coord c;
		c.x = x + other.x;
		c.y = y + other.y;
		c.z = z + other.z;
		return c;
	}
};

struct Particle{
	int index;
	Coord pos;
	Coord velocity;
	Coord acceleration;

	void Move(){
		velocity = velocity + acceleration;
		pos = pos + velocity;
	}
};

__int64 ManhattanDist(Coord a, Coord b){
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;

	std::regex myRegex("p=<(-?\\d+),(-?\\d+),(-?\\d+)>, v=<(-?\\d+),(-?\\d+),(-?\\d+)>, a=<(-?\\d+),(-?\\d+),(-?\\d+)>");
	std::smatch matches;
	std::vector<Particle> allParticles;
	
	int i = 0;
	while (std::getline(myfile, line)) {
		if(std::regex_match(line, matches, myRegex)){
			Particle p;
			p.index = i++;
			p.pos.x = atoi(matches[1].str().c_str());
			p.pos.y = atoi(matches[2].str().c_str());
			p.pos.z = atoi(matches[3].str().c_str());

			p.velocity.x = atoi(matches[4].str().c_str());
			p.velocity.y = atoi(matches[5].str().c_str());
			p.velocity.z = atoi(matches[6].str().c_str());

			p.acceleration.x = atoi(matches[7].str().c_str());
			p.acceleration.y = atoi(matches[8].str().c_str());
			p.acceleration.z = atoi(matches[9].str().c_str());

			allParticles.push_back(p);
		} 
	}

	for(int i = 0; i < 100000; i++){
		for(int j = 0; j < allParticles.size(); j++){
			allParticles[j].Move();
		}
	}

	int index;
	__int64 minDistance = 0x7FFFFFFFFFFFFFFFll;
	for (i = 0; i < allParticles.size(); i++) {
		__int64 dist = ManhattanDist(Coord{0,0,0}, allParticles[i].pos);
		if(dist < minDistance){
			minDistance = dist;
			index = i;
		}
	}

	printf("closest node: %d\n", index);
	
	return 0;
}
