#include "../Commands/DeterminizeCommand.h"
#include "../Commands/MinimizeCommand.h"
#include "../Commands/TotalizeCommand.h"
#include "../Commands/AcceptWord.h"
#include "../Commands/EmptyCheck.h"

#include "../Commands/UnionCommand.h"
#include "../Commands/ConcatenationCommand.h"
#include "../Commands/KleeneStarCommand.h"

#include "../Commands/ToAutomaton.h"
#include "../Commands/ToRegex.h"

#include "../Commands/SaveToFile.h"
#include "../Commands/LoadFromFile.h"

const char* SINGLE_INDEX = "dmtaekxs\0"; // Commands that require entering an index of an automaton 
const char* DOUBLE_INDEX = "uc\0"; // Commands that require entering two indices 

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
	std::cout << "\'e\' - empty language\n";

	std::cout << "\n";

	std::cout << "\'u\' - union\n";
	std::cout << "\'c\' - concatenation\n";
	std::cout << "\'k\' - Kleene star\n";

	std::cout << "\'h\' - get automaton from regex\n";
	std::cout << "\'x\' - get regex from automaton\n";

	std::cout << "\n";

	std::cout << "\'s\' - save automaton to file\n";
	std::cout << "\'l\' - load automaton from file\n";

	std::cin >> ch;

	if (foundInStr(SINGLE_INDEX, ch)) {
		std::cout << "Enter an automaton index:" << std::endl;
		int i;
		std::cin >> i;
		std::cout << '\n';

		switch (ch) {
		case 'd': return new DeterminizeCommand(&arr[i]); 
		case 'm': return new MinimizeCommand(&arr[i]);
		case 't': return new TotalizeCommand(&arr[i]);
		case 'a': return new AcceptWord(&arr[i]);
		case 'e': return new EmptyCheck(&arr[i]);
		case 'k': return new KleeneStarCommand(&arr[i], &arr);
		case 'x': return new ToRegex(&arr[i]); 
		case 's': return new SaveToFile(&arr[i]);
		}

	}
	else if (foundInStr(DOUBLE_INDEX, ch)) {
		std::cout << "Enter two indices:\n";
		int i1, i2;
		std::cin >> i1 >> i2;
		std::cout << "\n";

		switch (ch) {
		case 'u': return new UnionCommand(&arr[i1], &arr[i2], &arr);
		case 'c': return new ConcatenationCommand(&arr[i1], &arr[i2], &arr);
		}
	}

	// Get automaton from regex
	else if (ch == 'h') {
		return new ToAutomaton(&arr);
	}

	// Load from file and push to the array of automata 
	else if (ch == 'l') {
		return new LoadFromFile(&arr);
	}

	// Invalid command
	else {
		std::cout << "Error char: " << ch << std::endl; 
		throw std::invalid_argument("Invalid command!\n");
	}
}
