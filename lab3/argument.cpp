#include <string>
#include "argument.hpp"
#include <cstdio>

using namespace std;


Argument::Argument(int type, string name) {
	this->type = type;
	this->name = name;
	return;
}

void Argument::setName(string name) {
	this->name = name;
	return;
}

string Argument::getName() {
	return this->name;
}

void Argument::setType(int type) {
	if (type != 0 && type != 1)
		this->type = 1;
	this->type = type;
	return;
}

int Argument::getType() {
	return this->type >= 1 ? 1 : 0;
}

void Argument::printArgument() {
	printf("%s of type %s\n", this->name.c_str(), this->type ? "const" : "var");
}