#pragma once

#include "SingleCommand.h"
#include "AddCommand.h"

// Create a Kleene star automaton and add it to an array
class KleeneStarCommand : public SingleCommand, AddCommand {
public:
	KleeneStarCommand(NDFA* a, DynamicArray<NDFA>* arr) : SingleCommand(a), AddCommand(arr) {}

	void execute(std::istream& is, std::ostream& os) override {
		_arr->pushBack(kleeneStar(*_a));

		os << "Kleene star automaton:\n\n";
		_arr->operator[](_arr->getSize() - 1).print(os);
		os << '\n';
	}
};