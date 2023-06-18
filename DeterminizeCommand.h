#pragma once

#include "SingleCommand.h"

// Determinize a given automaton 
class DeterminizeCommand : public SingleCommand {
public:
	DeterminizeCommand(NDFA* a) : SingleCommand(a){}

	void execute(std::istream& is, std::ostream& os) override {
		_a->determinize();

		os << "Determinized automaton:\n\n";
		_a->print(os);
		os << std::endl;
	}
};