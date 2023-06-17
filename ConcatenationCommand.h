#pragma once

#include "DoubleCommand.h"
#include "AddCommand.h"

class ConcatenationCommand : public DoubleCommand, AddCommand {
public:
	ConcatenationCommand(NDFA* a1, NDFA* a2, DynamicArray<NDFA>& arr) : DoubleCommand(a1, a2), AddCommand(arr) {}

	void execute(std::ostream& os) override {
		_arr.pushBack(concatenation(*_a1, *_a2));
	}
};