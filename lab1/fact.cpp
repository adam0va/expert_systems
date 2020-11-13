#include "fact.hpp"
#include <string>

using namespace std;

Fact::Fact() {
	this->name = "";
	this->watched = false;
	return;
}

Fact::Fact(string name) {
	this->name = name;
	this->watched = false;
	return;
}

string Fact::getName() {
	return this->name;
}

void Fact::setName(string s) {
	this->name = s;
	return;
}

bool Fact::isWatched() {
	return this->watched;
}

void Fact::setWatched(bool watched) {
	this->watched = watched;
	return;
}