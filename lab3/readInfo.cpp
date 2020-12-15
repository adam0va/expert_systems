#include "argument.hpp"
#include "predicate.hpp"
#include "rule.hpp"
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>

using namespace std;


void onError(const char* message) {
    printf("%s\n", message);
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// Функция, которая занимается парсингом предиката
Predicate* parsePredicate(string input) {
	int i = 0;
	size_t pos1, pos2;
	vector<Argument*> args; // Аргументы предиката

	pos1 = distance(input.begin(), find(input.begin(), input.end(), '(')); // Индекс, по которому расположена (
	pos2 = distance(input.begin(), find(input.begin(), input.end(), ')')); // Индекс, по которому расположена )

	string name = input.substr(0, pos1); // Имя предиката
	i = pos1 + 1; // Первым аргументом будет следующий символ после скобки

	bool breakFlag = false;

	while (true) {
		pos1 = distance(input.begin(), find(input.begin() + i, input.begin() + pos2, ',')); // Индекс, по которому расположена запятая
		if (pos1 >= pos2) { // Когда запятых не осталось, устанавливаем флаг, чтобы выйти из цикла
			pos1 = pos2;
			breakFlag = true;
		}

		string nameArg = input.substr(i, pos1 - i); // Сохраняем имя аргумента
		i = pos1 + 1;
		Argument *newArg;
		if (nameArg[0] >= 'a' && nameArg[0] <= 'z') // Название в нижнем регистре - переменная
			newArg = new Argument(0, nameArg);
		else
			newArg = new Argument(1, nameArg); // Название в верхнем регистре - константа
		args.push_back(newArg);
		if (breakFlag) break;
	}
	Predicate *newFact = new Predicate(name, args);
	return newFact;
}

// Функция, которая занимается парсингом строки с фактами
void parsePredicateLine(string input, vector<Predicate*> &trueFacts) {
	int i = 0;
	size_t pos;
	while ((pos = distance(input.begin(), find(input.begin() + i, input.end(), ')'))) < input.length()) {
		//printf("%zu %lu\n", pos, input.length());
		Predicate *newPredicate = parsePredicate(input.substr(i, pos - i + 1));
		trueFacts.push_back(newPredicate);
		i = pos + 2;
	}
}

// Функция, которая занимается парсингом цели
void parseTarget(string input, Predicate *&target) {
	target = parsePredicate(input);
}

// Функция, которая занимается парсингом правила
void parseRule(string input, vector<Rule*> &rules) {
	vector<Predicate*> preds;
	size_t limit = distance(input.begin(), find(input.begin(), input.end(), '>'));
	int i = 0;
	size_t pos;
	while ((pos = distance(input.begin(), find(input.begin() + i, input.end(), ')'))) < limit) {
		Predicate *newPredicate = parsePredicate(input.substr(i, pos - i + 1));
		preds.push_back(newPredicate);
		i = pos + 2;
	}
	i += 2;
	pos = distance(input.begin(), find(input.begin() + i, input.end(), ')'));
	Predicate *newPredicate = parsePredicate(input.substr(i, pos));
	Rule *newRule = new Rule(preds, newPredicate);
	rules.push_back(newRule);
}

// Функция, которая читает информацию из файла
void readData(Predicate *&target, vector<Predicate*> &trueFacts, vector<Rule*> &rules, char *filename) {
	ifstream fin(filename, std::ios_base::in);
	if (!fin.is_open()) {
		onError("File error");
	}
	string input = "";

	getline(fin, input); // Читаем факты
	parsePredicateLine(input, trueFacts);

	getline(fin, input); // Читаем цель
	parseTarget(input, target);

	getline(fin, input); // Пропускаем строку

	while (getline(fin, input)) { // Читаем правила построчно
		parseRule(input, rules);
	}
}