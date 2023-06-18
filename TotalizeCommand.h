#pragma once

#include "SingleCommand.h"

class TotalizeCommand : public SingleCommand {
public:
	TotalizeCommand(NDFA* a) : SingleCommand(a) {}

	void execute(std::ostream& os) override {
		_a->makeTotal();

		std::cout << "Total automaton:" << std::endl;
		_a->print();
		std::cout << std::endl;
	}
};