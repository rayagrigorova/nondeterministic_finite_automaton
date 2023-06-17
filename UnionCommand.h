#pragma once

#include "DoubleCommand.h"
#include "AddCommand.h"

class UnionCommand : public DoubleCommand, AddCommand {
public:
	UnionCommand(NDFA* a1, NDFA* a2, DynamicArray<NDFA>& arr) : DoubleCommand(a1, a2), AddCommand(arr){}

	void execute(std::ostream& os) override {
		_arr.pushBack(Union(*_a1, *_a2));
	}
};

