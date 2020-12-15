#ifndef PREDICATE_HPP
#define PREDICATE_HPP

#include <string>
#include <vector>
#include <map>
#include "argument.hpp"

using namespace std;


class Predicate {
	string name;
	vector<Argument*> arguments;
public:
	Predicate(string, vector<Argument*>);
	Predicate();
	void setName(string);
	string getName();
	void setArguments(vector<Argument*>);
	void addToArguments(Argument*);
	vector<Argument*> getArguments();
	void addAgrument(Argument*);
	void printPredicate();
	bool canUnificate(Predicate *pred, map<string, string> &vars);
	bool isEqual(Predicate *pred);
};

#endif