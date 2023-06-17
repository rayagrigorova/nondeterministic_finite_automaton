#pragma once

#include "SingleCommand.h"
#include "AddCommand.h"

class KleeneStarCommand : public SingleCommand, AddCommand {
public:
	KleeneStarCommand(NDFA* a, DynamicArray<NDFA>& arr) : SingleCommand(a), AddCommand(arr) {}

	void execute(std::ostream& os) override {
		_arr.pushBack(kleeneStar(*_a));
	}
};