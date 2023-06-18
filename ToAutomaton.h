#pragma once

#include "AddCommand.h"

const char* SYNTAX_RULE_1 = "Each operation should be surrounded by brackets ( example: (a.b), (a+b) )\n";
const char* SYNTAX_RULE_2 = "The Kleene star operation requires brackets both around the original expression and the Kleene star expression ( example: ((a)*) )\n";
const char* SYNTAX_RULE_3 = "The whole regex should be surrounded by brackets ( example: (a.b)+(b.a) -> ((a.b)+(b.a)) )\n"; 

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
			os << "Incorrect syntax!\n";
			os << SYNTAX_RULE_1 << SYNTAX_RULE_2 << SYNTAX_RULE_3; 
		}
	}
};