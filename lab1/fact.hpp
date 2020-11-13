#ifndef FACT_H
#define FACT_H

#include <string>

using namespace std;

class Fact {
	string name;
	bool watched;
public:
	Fact();
	Fact(string name);
	string getName();
	void setName(string);
	bool isWatched();
	void setWatched(bool watched);
};

#endif