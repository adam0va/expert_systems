#include "read_data.hpp"
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

// Функция, создающая факты из информации в файле
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

// Функция, осуществляющая поиск факта по имени в векторе фактов
Fact *findFact(std::vector<Fact*> &facts, string name) {
	for (int i = 0; i < facts.size(); i++) 
		if (strcmp(facts[i]->getName().c_str(), name.c_str()) == 0)
			return facts[i];
	return NULL;
}

// Функция, создающая вектор истинных фактов. 
void parseTrueFactsLine(vector<Fact*> &trueFacts, vector<Fact*> &facts, string &input) {
	int i = 0, j = 0;
	while (j <= input.length()) {
		if (input[j] == ' ' || j == input.length()) {
			Fact *f = findFact(facts, input.substr(i, j-i));
			if (!f)
				onError("Fact wasn't mentioned");
			trueFacts.push_back(f);
			i = ++j;
		} else
			j++;
	}
	return;
}

// Функция, создающая правила по строке входного файла о правиле
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

// Функция, которая парсит содержимое файла с фактами, правилами и т.д.
void readData(vector<Fact*> &facts, vector<Fact*> &trueFacts, Fact *&target, vector<Rule*> &rules, char *filename) {
	ifstream fin(filename, std::ios_base::in);
	if (!fin.is_open()) {
		onError("File error");
	}
	string input = "";

	getline(fin, input);
	parseFactsLine(facts, input);

	getline(fin, input);
	parseTrueFactsLine(trueFacts, facts, input);

	getline(fin, input);
	target = findFact(facts, input);
	if (!target)
		onError("Can't find target in facts\n");

	while (getline(fin, input)) {
		parseRuleLine(rules, input, facts);
	}
	
}