#include "fact.hpp"
#include "rule.hpp"
#include "graph.hpp"
#include <vector>
#include <string>
#include <queue>

using namespace std;

Graph::Graph(vector<Fact*> f, vector<Rule*> r) {
	this->facts = f;
	this->rules = r;
	return;
}

bool Graph::canUseRule(Rule *rule) {
	for (int i = 0; i < rule->getAntecedent().size(); i++) {
		if (count(this->mem.begin(), this->mem.end(), rule->getAntecedent()[i]) == 0 
			&& !strcmp(rule->getRuleType().c_str(), "&")) {
			return false;
		}
		else  {
			if (!strcmp(rule->getRuleType().c_str(), "|")) 
				return true;
		}
	}
	return true;
}

void Graph::addRulesToQueue(queue<Rule*> &rulesQueue) {
	for (int i = 0; i < this->rules.size(); i++) {
		if (!rules[i]->isWatched() && canUseRule(rules[i])) {
			rules[i]->setWatched(true);
			rulesQueue.push(rules[i]);
		}
	}
	return;
}

// Функция поиска от данных, использующая поиск в глубину
bool Graph::dataToTargetDFS(vector<Fact*> trueFacts, Fact *target) {
	queue<Rule*> rulesQueue;
	this->mem = trueFacts;
	bool ans = false;
	int iterCount = 0;
	this->addRulesToQueue(rulesQueue); // Добавляем правила в очередь правил

	while (!rulesQueue.empty() && !ans) { // Пока очередь не пуста или ответ не стал положительным
		Rule *curRule = rulesQueue.front(); // Рассмотрим первый элемент в очереди
		rulesQueue.pop();
		Fact *cons = curRule->getConsequent(); // Рассмотрим его консеквент

		printf("Iteration: %d\n", iterCount); // Вывыдем информацию о том, что на данной итерации рассматриваем
		printf("Memory: ");
		for (int i = 0; i < mem.size(); i++) {
			printf("%s ", mem[i]->getName().c_str());
		}
		printf("\nCurrent rule: %s %s %s -> %s\n\n", curRule->getAntecedent()[0]->getName().c_str(), curRule->getRuleType().c_str(), 
			curRule->getAntecedent()[1]->getName().c_str(), curRule->getConsequent()->getName().c_str());
		iterCount++;

		if (cons == target) // Если консеквент рассматриваемого правила совпадает с целью, ответ положительный
			ans = true;
		
		if (!cons->isWatched()) { // Если консеквент ранее не был рассмотрен
			cons->setWatched(true); // Помечаем его как рассмотренный
			mem.push_back(cons); // И добавляем в вектор истинных фактов
		}
		this->addRulesToQueue(rulesQueue); // Добавляем правила в очередь правил
	}
	ans ? printf("true\n") : printf("false\n");
	return ans;
}








