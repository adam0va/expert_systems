#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>
#include "fact.hpp"

using namespace std;

class Rule {
	std::vector<Fact*> antecedent;
	Fact *consequent;
	bool watched;
	string ruleType;
public:
	Rule();
	Rule(vector<Fact*> antecedent, Fact *consequent, string ruleType);
	vector<Fact*> getAntecedent();
	void addToAntecedent(Fact*);
	Fact *getConsequent();
	void setConsequent(Fact*);
	string getRuleType();
	void setRuleType(string s);
	bool isWatched();
	void setWatched(bool watched);
};

#endif