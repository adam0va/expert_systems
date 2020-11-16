#include "graph.hpp"
#include "fact.hpp"
#include "rule.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

void onError(const char* message) {
    printf("%s\n", message);
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void parseFactsLine(vector<Fact*> &facts, string &input) {
	int i = 0, j = 0;
	while (j <= input.length()) {
		if (input[j] == ' ' || j == input.length()) {
			Fact *newFact = new Fact(input.substr(i, j-i));
			facts.push_back(newFact);
			i = ++j;
		} else
			j++;
	}
	return;
}

Fact *findFact(std::vector<Fact*> &facts, string name) {
	for (int i = 0; i < facts.size(); i++) 
		if (strcmp(facts[i]->getName().c_str(), name.c_str()) == 0)
			return facts[i];
	return NULL;
}

void parseRuleLine(vector<Rule*> &rules, string &input, vector<Fact*> &facts) {
	int i = 0, j = 0;
	Rule *newRule = new Rule();
	while (j < input.length() && input[j] != ' ')
		j++;
	Fact *ant = findFact(facts, input.substr(i, j-i));
	if (!ant)
		onError("Can't find fact");
	newRule->addToAntecedent(ant);
	j++;
	if (input[j] != '|' && input[j] != '&') {
		delete(newRule);
		onError("Wrong format in rules\n");
	}
	newRule->setRuleType(input.substr(j, 1));
	j += 2;
	i = j;
	while (j < input.length() && input[j] != ' ')
		j++;
	ant = findFact(facts, input.substr(i, j-i));
	if (!ant)
		onError("Can't find fact");
	newRule->addToAntecedent(ant);
	j++;
	if (input[j] != '>') {
		delete(newRule);
		onError("Wrong format in rules\n");
	}
	j += 2;
	i = j;
	while (j < input.length()) 
		j++;
	ant = findFact(facts, input.substr(i, j-i));
	if (!ant)
		onError("Can't find fact");
	newRule->setConsequent(ant);
	rules.push_back(newRule);
	return;
}

void readData(vector<Fact*> &facts, vector<Rule*> &rules, char *filename) {
	ifstream fin(filename, std::ios_base::in);
	if (!fin.is_open()) {
		onError("File error");
	}
	string input = "";
	getline(fin, input);
	parseFactsLine(facts, input);
	while (getline(fin, input)) {
		parseRuleLine(rules, input, facts);
	}
	printf("Facts: ");
	for (int i = 0; i < facts.size(); i++) {
		printf("%s ", facts[i]->getName().c_str());
	}
	printf("\nRules: \n");
	for (int i = 0; i < rules.size(); i++) {
		printf("%s %s %s => %s\n", rules[i]->getAntecedent()[0]->getName().c_str(), rules[i]->getRuleType().c_str(), 
			rules[i]->getAntecedent()[1]->getName().c_str(), rules[i]->getConsequent()->getName().c_str());
	}
	printf("\n");
}

int main() {
	vector<Fact*> facts;
	vector<Rule*> rules;

	readData(facts, rules, "examples/data.txt");

	Graph *graph = new Graph(facts, rules);

	vector<Fact*> trueFacts(facts.begin(), facts.begin()+2);

	graph->dataToTargetDFS(trueFacts, facts[4]);

	return 0;
}



