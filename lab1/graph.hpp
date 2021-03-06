#ifndef GRAPH_H
#define GRAPH_H

#include "fact.hpp"
#include "rule.hpp"
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Graph {
	vector<Fact*> facts;
	vector<Rule*> rules;
	vector<Fact*> mem;
public:
	Graph(vector<Fact*>, vector<Rule*>);
	bool dataToTargetDFS(vector<Fact*> trueFacts, Fact *target);
	bool targetToData(vector<Fact*> trueFacts, Fact *target);
	void addRulesToQueue(queue<Rule*> &rulesQueue);
	bool canUseRule(Rule *rule);
	vector<Rule*> findRulesWithTargetConsequent(Fact *target);
	bool handleFact(vector<Fact*> trueFacts, Fact *target);
	bool handleRule(vector<Fact*> trueFacts, Rule *rule);
};

#endif