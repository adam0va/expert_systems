#include <string>
#include <vector>
#include <cstdio>
#include "argument.hpp"
#include "predicate.hpp"
#include "rule.hpp"
#include "readInfo.hpp"

using namespace std;
bool findTarget(Predicate *&target, vector<Predicate*> &mem) {
	for (int i = 0; i < mem.size(); i++) {
		if (mem[i]->isEqual(target))
			return true;
	}
	return false;
}

bool forwardChaining(Predicate *&target, vector<Rule*> &rules, vector<Predicate*> &mem) {
	for (int i = 0; i < rules.size(); i++) {
		printf("Mem:");
		for (int j = 0; j < mem.size(); j++) {
			mem[j]->printPredicate();
			printf(" ");
		}
		printf("\n\n");

		rules[i]->printRule();
		printf("\n\n");
		if (rules[i]->isProper(mem)) {
			if (findTarget(target, mem)) 
				return true;
			rules.erase(rules.begin() + i);
			i = -1;
		}
	}
	return false;
}

int main() {
	vector<Rule*> rules;
	Predicate *target;
	vector<Predicate*> mem;

	readData(target, mem, rules, "test1.txt");

	printf("Facts: ");
	for (auto m : mem) {
		m->printPredicate();
		printf(" ");
	}
	printf("\nTarget: ");
	target->printPredicate();
	printf("\nRules:\n");

	for (auto rule : rules) {
		rule->printRule();
		printf("\n");
	}

	bool res = forwardChaining(target, rules, mem);
	printf("%s\n", res ? "true" : "false");

	return 0;
}