#pragma once

#include "SingleCommand.h"

// Make a given automaton total 
class TotalizeCommand : public SingleCommand {
public:
	TotalizeCommand(NDFA* a) : SingleCommand(a) {}

	void execute(std::istream& is, std::ostream& os) override {
		_a->makeTotal();

		os << "Total automaton:" << "\n\n";
		_a->print(os);
		os << '\n';
	}
};