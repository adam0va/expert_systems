#ifndef READDATA
#define READDATA

#include "argument.hpp"
#include "predicate.hpp"
#include "rule.hpp"
#include <vector>
#include <string>

using namespace std;

void onError(const char* message);

Predicate* parsePredicate(string input);

void parsePredicateLine(string input, vector<Predicate*> &trueFacts);

void parseTarget(string input, Predicate *&target);

void parseRule(string input, vector<Rule*> &rules);

void readData(Predicate *&target, vector<Predicate*> &trueFacts, vector<Rule*> &rules, char *filename);


#endif