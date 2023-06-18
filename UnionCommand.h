#pragma once

#include "DoubleCommand.h"
#include "AddCommand.h"

class UnionCommand : public DoubleCommand, AddCommand {
public:
	UnionCommand(NDFA* a1, NDFA* a2, DynamicArray<NDFA>& arr) : DoubleCommand(a1, a2), AddCommand(arr){}

	void execute(std::ostream& os) override {
		_arr->pushBack(Union(*_a1, *_a2));

		std::cout << "Union automaton:" << std::endl;
		_arr->operator[](_arr->getSize() - 1).print();
		std::cout << std::endl;
	}
};

