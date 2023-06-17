#include "DeterminizeCommand.h"
#include "MinimizeCommand.h"
#include "TotalizeCommand.h"
#include "AcceptWord.h"
#include "EmptyCheck.h"

#include "UnionCommand.h"
#include "ConcatenationCommand.h"
#include "KleeneStarCommand.h"

#include "ToAutomaton.h"
#include "ToRegex.h"

const char* SINGLE_INDEX = "dmtaekx";
const char* DOUBLE_INDEX = "uc";

namespace {
	bool foundInStr(const char* str, char ch) {
		size_t len = strlen(str);
		for (int i = 0; i < len; i++) {
			if (str[i] == ch) {
				return true;
			}
		}
		return false;
	}
}

Command* commandFactory(DynamicArray<NDFA>& arr) {
	char ch;

	std::cout << "\'d\' - determinize\n"; 
	std::cout << "\'m\' - minimize\n";
	std::cout << "\'t\' - make total\n";
	std::cout << "\'a\' - accept word\n";
	std::cout << "\'e\' - empty language";

	std::cout << "\'u\' - union\n";
	std::cout << "\'c\' - concatenation\n";
	std::cout << "\'k\' - Kleene star\n";

	std::cout << "\'h\' - get automaton from regex\n";
	std::cout << "\'x\' - get regex from automaton\n";

	std::cin >> ch;

	if (foundInStr(SINGLE_INDEX, ch)) {
		std::cout << "Enter an automaton index:\n";
		int i;
		std::cin >> i;

		switch (ch) {
		case 'd': return new DeterminizeCommand(&arr[i]); 
		case 'm': return new MinimizeCommand(&arr[i]);
		case 't': return new TotalizeCommand(&arr[i]);
		case 'a': return new AcceptWord(&arr[i]);
		case 'e': return new EmptyCheck(&arr[i]);
		case 'k': return new KleeneStarCommand(&arr[i], arr);
		case 'x': return new ToRegex(&arr[i]); 
		}

	}
	else if (foundInStr(DOUBLE_INDEX, ch)) {
		std::cout << "Enter wto automaton indices:\n";
		int i1, i2;
		std::cin >> i1 >> i2;

		switch (ch) {
		case 'u': return new UnionCommand(&arr[i1], &arr[i2], arr);
		case 'c': return new ConcatenationCommand(&arr[i1], &arr[i2], arr);
		}
	}

	// get automaton from regex
	else if (ch == 'h') {
		return new ToAutomaton(arr);
	}

	else {
		throw std::invalid_argument("Invalid command!\n");
	}
}