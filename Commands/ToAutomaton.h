#pragma once

#include "AddCommand.h"

const char* SYNTAX_RULE_1 = "1. Each operation should be surrounded by brackets\nExample: (a.b), (a+b) \n";
const char* SYNTAX_RULE_2 = "2. The Kleene star operation requires brackets both around the original expression and the Kleene star expression\nExample: ((a)*)\n";
const char* SYNTAX_RULE_3 = "3. The whole regex should be surrounded by brackets\nExample: (a.b)+(b.a) -> ((a.b)+(b.a))\n"; 

// Create an automaton from a regex and add it to an array 
class ToAutomaton : public AddCommand {
public:
	ToAutomaton(DynamicArray<NDFA>* arr) : AddCommand(arr) {}

	virtual void execute(std::istream& is, std::ostream& os) override {
		os << "Enter a regular expression:\n";

		char buff[250];
		is >> buff;

		try {
			_arr->pushBack(getAutomatonForRegEx(buff));

			os << "\nResult automaton:\n\n";
			_arr->operator[](_arr->getSize() - 1).print(os);
			os << std::endl;

		}
		catch (std::exception& e) {
			os << "Incorrect syntax!\n\n";
			os << SYNTAX_RULE_1 << SYNTAX_RULE_2 << SYNTAX_RULE_3 << "\n";
		}
	}
};