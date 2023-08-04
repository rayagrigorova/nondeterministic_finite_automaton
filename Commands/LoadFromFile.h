#pragma once

#include "SingleCommand.h"

// Load an automaton from a file and add it to an array 
class LoadFromFile : public AddCommand {
public:
	LoadFromFile(DynamicArray<NDFA>* arr) : AddCommand(arr) {}

	void execute(std::istream& is, std::ostream& os) override {
		std::cout << "Enter the name of the file:\n";

		char buff[250];
		std::cin >> buff;

		NDFA a;
		a.loadFromFile(buff); // This line could throw an exception (handled in Program)

		_arr->pushBack(std::move(a));

		os << "\nFile loaded successfully\n\n";

	}
};
