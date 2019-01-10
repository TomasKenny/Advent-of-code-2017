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

struct Coord {
	__int64 x;
	__int64 y;
	__int64 z;

	Coord operator+(const Coord & other) const {
		Coord c;
		c.x = x + other.x;
		c.y = y + other.y;
		c.z = z + other.z;
		return c;
	}
	
	bool operator==(const Coord & other) const {
		return (x == other.x) && (y == other.y) && (z == other.z);
	}
};

struct Particle {
	int index;
	Coord pos;
	Coord velocity;
	Coord acceleration;

	void Move() {
		velocity = velocity + acceleration;
		pos = pos + velocity;
	}

	bool operator<(const Particle & other) const {
		if (pos.x == other.pos.x) {
			if (pos.y == other.pos.y) {
				return pos.z < other.pos.z;
			}
			return pos.y < other.pos.y;
		}
		return pos.x < other.pos.x;
	}
};

__int64 ManhattanDist(Coord a, Coord b) {
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int main() {
	std::ifstream myfile;
	myfile.open("c:\\Users\\naplava\\Desktop\\input.txt");
	std::string line;

	std::regex myRegex("p=<(-?\\d+),(-?\\d+),(-?\\d+)>, v=<(-?\\d+),(-?\\d+),(-?\\d+)>, a=<(-?\\d+),(-?\\d+),(-?\\d+)>");
	std::smatch matches;
	std::list<Particle> allParticles;

	int i = 0;
	while (std::getline(myfile, line)) {
		if (std::regex_match(line, matches, myRegex)) {
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

	for (int i = 0; i < 100000; i++) {
		for (auto & particle: allParticles) {
			particle.Move();
		}

		//detect collisions
		allParticles.sort();

		auto it = allParticles.begin();
		decltype(it) it2;

		while(it != allParticles.end()){
			it2 = it;
			it2++;
			if(it2 == allParticles.end()){
				break;
			}
			bool deleteParticles = it->pos == it2->pos;
			while((it2 != allParticles.end()) && (it->pos == it2->pos)){
				it2++;
			}
			if(deleteParticles){
				it = allParticles.erase(it, it2);
			}
			else{
				it++;
			}
		}
	}

	printf("particles left: %d\n", allParticles.size());

	return 0;
}
