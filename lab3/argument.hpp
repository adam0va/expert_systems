#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <string>

using namespace std;

class Argument {
	int type; // 0 - var, 1 - const
	string name;
public:
	Argument(int, string);
	void setName(string);
	string getName();
	void setType(int);
	int getType();
	void printArgument();
};

#endif