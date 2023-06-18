#pragma once

#include "DoubleCommand.h"
#include "AddCommand.h"

// Create a concatenation automaton and add it to an array 
class ConcatenationCommand : public DoubleCommand, AddCommand {
public:
	ConcatenationCommand(NDFA* a1, NDFA* a2, DynamicArray<NDFA>* arr) : DoubleCommand(a1, a2), AddCommand(arr) {}

	void execute(std::istream& is, std::ostream& os) override {
		_arr->pushBack(concatenation(*_a1, *_a2));

		os << "Concatenation automaton:\n";
		_arr->operator[](_arr->getSize() - 1).print(os);
		os << '\n';
	}
};