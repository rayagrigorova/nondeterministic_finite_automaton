#pragma once

#include "SingleCommand.h"

class TotalizeCommand : public SingleCommand {
public:
	TotalizeCommand(NDFA* a) : SingleCommand(a) {}

	void execute(std::istream& is, std::ostream& os) override {
		_a->makeTotal();

		os << "Total automaton:" << "\n\n";
		_a->print(os);
		os << std::endl;
	}
};