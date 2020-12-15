#include <string>
#include <vector>
#include "argument.hpp"
#include "predicate.hpp"
#include <map>
#include <cstring>

using namespace std;

Predicate::Predicate() {

}

Predicate::Predicate(string name, vector<Argument*> args) {
	this->name = name;
	this->arguments = args;
	return;
}

void Predicate::setName(string name) {
	this->name = name;
	return;
}

string Predicate::getName() {
	return this->name;
}

void Predicate::setArguments(vector<Argument*> args) {
	this->arguments = args;
	return;
}

vector<Argument*> Predicate::getArguments() {
	return arguments;
}

void Predicate::addAgrument(Argument* arg) {
	this->arguments.push_back(arg);
	return;
}

bool Predicate::canUnificate(Predicate *pred, map<string, string> &vars) {
	if (strcmp(this->name.c_str(), pred->name.c_str())) // Совпадает ли имя
		return false;

	if (this->arguments.size() != pred->arguments.size()) // Совпадает ли число аргументов
		return false;
	
	for (int i = 0; i < this->arguments.size(); i++) {
		if (arguments[i]->getType() == 1) { // Если аргумент - константа
			if (strcmp(this->arguments[i]->getName().c_str(), pred->arguments[i]->getName().c_str())) // Сравним имя
				return false;
		} else {
			auto itr = vars.find(this->arguments[i]->getName());
			if (itr != vars.end()) {
				if (strcmp(pred->arguments[i]->getName().c_str(), itr->second.c_str()))
					return false;
			}
			else 
				vars.insert(make_pair(this->arguments[i]->getName(), pred->arguments[i]->getName()));
		}
	} 
	return true;
}

void Predicate::addToArguments(Argument* arg) {
	this->arguments.push_back(arg);
}

bool Predicate::isEqual(Predicate *pred) {
	if (strcmp(this->name.c_str(), pred->name.c_str())) // Совпадает ли имя
		return false;

	if (this->arguments.size() != pred->arguments.size()) // Совпадает ли число аргументов
		return false;

	for (int i = 0; i < this->arguments.size(); i++) {
		if (this->arguments[i]->getType() != pred->arguments[i]->getType())
			return false; 
		if (strcmp(this->arguments[i]->getName().c_str(), pred->arguments[i]->getName().c_str()))
			return false;
			
	} 
	return true;	

}

void Predicate::printPredicate() {
	printf("%s(%s", this->name.c_str(), this->arguments[0]->getName().c_str());
	if (arguments.size() > 1) {
		for (int i = 1; i <  arguments.size(); i++) {
			printf(", %s", arguments[i]->getName().c_str());
		}
	}
	printf(")"); 
}
