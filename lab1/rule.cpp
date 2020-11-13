#include "rule.hpp"
#include "fact.hpp"
#include <string>
#include <vector>

using namespace std;

Rule::Rule() {
	this->watched = false;
}

Rule::Rule(vector<Fact*> antecedent, Fact *consequent, string ruleType) {
	this->antecedent = antecedent;
	this->consequent = consequent;
	this->ruleType = ruleType;
	this->watched = false;
	return;
}

vector<Fact*> Rule::getAntecedent() {
	return this->antecedent;
}

void Rule::addToAntecedent(Fact* f) {
	this->antecedent.push_back(f);
	return;
}

Fact* Rule::getConsequent() {
	return this->consequent;
}

void Rule::setConsequent(Fact* f) {
	this->consequent = f;
	return;
}

void Rule::setRuleType(string s) {
	this->ruleType = s;
	return;
}

string Rule::getRuleType() {
	return this->ruleType;
}

bool Rule::isWatched() {
	return this->watched;
}

void Rule::setWatched(bool watched) {
	this->watched = watched;
	return;
}