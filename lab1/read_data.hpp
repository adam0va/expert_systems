#ifndef READDATA
#define READDATA

#include "fact.hpp"
#include "rule.hpp"
#include <vector>
#include <string>

void onError(const char* message);

void parseFactsLine(vector<Fact*> &facts, string &input);

Fact *findFact(std::vector<Fact*> &facts, string name);

void parseTrueFactsLine(vector<Fact*> &trueFacts, vector<Fact*> &facts, string &input);

void parseRuleLine(vector<Rule*> &rules, string &input, vector<Fact*> &facts);	

void readData(vector<Fact*> &facts, vector<Fact*> &trueFacts, Fact *&target, vector<Rule*> &rules, char *filename);

#endif