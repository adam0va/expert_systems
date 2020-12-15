#ifndef RULE_HPP
#define RULE_HPP

#include <string>
#include <vector>
#include <map>
#include "argument.hpp"
#include "predicate.hpp"

using namespace std;


class Rule {
	vector<Predicate*> antecedent;
	Predicate *consequent;
public:
	Rule(vector<Predicate*>, Predicate*);
	void setAntecedent(vector<Predicate*>);
	vector<Predicate*> getAntecedent();
	void addToAntecedent(Predicate*);

	void setConsequent(Predicate*);
	Predicate *getConsequent();
	bool isProper(vector<Predicate*> &mem);
	bool unificate(map<string, string>, Predicate *&unificated);
	void printRule();
};

#endif