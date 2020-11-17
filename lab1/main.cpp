#include "graph.hpp"
#include "fact.hpp"
#include "rule.hpp"
#include "read_data.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

int main() {
	vector<Fact*> facts, trueFacts;
	vector<Rule*> rules;
	Fact *target = NULL;

	readData(facts, trueFacts, target, rules, "examples/data.txt"); // Вызываем функцию для чтения информации из заданного файла

	printf("Facts: "); // Выводим все прочитанные данные
	for (int i = 0; i < facts.size(); i++) {
		printf("%s ", facts[i]->getName().c_str());
	}
	printf("\nTrue facts: ");
	for (int i = 0; i < trueFacts.size(); i++) {
		printf("%s ", trueFacts[i]->getName().c_str());
	}
	printf("\nRules: \n");
	for (int i = 0; i < rules.size(); i++) {
		printf("%s %s %s => %s\n", rules[i]->getAntecedent()[0]->getName().c_str(), rules[i]->getRuleType().c_str(), 
			rules[i]->getAntecedent()[1]->getName().c_str(), rules[i]->getConsequent()->getName().c_str());
	}
	printf("Target: %s\n", target->getName().c_str());
	printf("\n");

	Graph *graph = new Graph(facts, rules); // Строим граф по прочитанным данным

	graph->dataToTargetDFS(trueFacts, target); // Выолняем поиск от данных

	return 0;
}



