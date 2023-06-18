#pragma once

#include "AddCommand.h"

class ToAutomaton : public AddCommand {
public:
	ToAutomaton(DynamicArray<NDFA>* arr) : AddCommand(arr) {}

	virtual void execute(std::ostream& os) override {
		std::cout << "Enter a regular expression:\n";

		char buff[250];
		std::cin >> buff;

		_arr->pushBack(getAutomatonForRegEx(buff)); 

		std::cout << "\nResult automaton:\n\n";
		_arr->operator[](_arr->getSize() - 1).print();
		std::cout << std::endl;
	}
};