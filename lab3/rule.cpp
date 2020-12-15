#include <string>
#include <vector>
#include "argument.hpp"
#include "predicate.hpp"
#include "rule.hpp"

using namespace std;


Rule::Rule(vector<Predicate*> antecedent, Predicate* consequent) {
	this->antecedent = antecedent;
	this->consequent = consequent;
	return;
}

void Rule::setAntecedent(vector<Predicate*> antecedent) {
	this->antecedent = antecedent;
	return;
}

vector<Predicate*> Rule::getAntecedent() {
	return this->antecedent;
}

void Rule::addToAntecedent(Predicate* predicate) {
	this->antecedent.push_back(predicate);
	return;
}

void Rule::setConsequent(Predicate* consequent) {
	this->consequent = consequent;
	return;
}

Predicate* Rule::getConsequent() {
	return this->consequent;
}

bool Rule::isProper(vector<Predicate*> &mem) {
	int memSize = mem.size();
	vector<int> usedFacts;
	bool breakFlag = true, repeat = false;

	while (breakFlag) {
		map<string, string> vars;
		for (int i = 0; i < this->antecedent.size(); i++) {
			
			breakFlag = false;
			
			for (int j = 0; j < mem.size(); j++) {
				
				if (find(usedFacts.begin(), usedFacts.end(), j) != usedFacts.end())
					continue;
				
				if (this->antecedent[i]->canUnificate(mem[j], vars)) {
					usedFacts.push_back(j);
					breakFlag = true;

					break;
				}
			}
			if (!breakFlag) {
					repeat = vars.size() > 0;
					break;
				}
		}

		if (!breakFlag && repeat) {
			repeat = true;
			continue;
		}

		if (breakFlag) {
			Predicate *unificated = NULL;
			bool wasUnificated = unificate(vars, unificated);
			mem.push_back(unificated);
			if (!wasUnificated)
				breakFlag = false;
		}
	}
	return memSize != mem.size();
}

bool Rule::unificate(map<string, string> vars, Predicate *&unificated) {
	bool wasUnificated = false;
	unificated = new Predicate();
	unificated->setName(this->consequent->getName());

	for (auto arg : this->consequent->getArguments()) {
		if (arg->getType() == 1) {
			unificated->addToArguments(arg);
		} else {
			Argument *newArg = new Argument(1, vars.find(arg->getName())->second);
			unificated->addToArguments(newArg);
			wasUnificated = true;
		}
	}
	return wasUnificated;
}

void Rule::printRule() {
	for (int i = 0; i < this->antecedent.size(); i++) {
		antecedent[i]->printPredicate();
		printf(" ");
	}
	printf("> ");
	consequent->printPredicate();
}

