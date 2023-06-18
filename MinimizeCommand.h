#pragma once

#include "SingleCommand.h"

// Minimize a given automaton 
class MinimizeCommand : public SingleCommand {
public:
	MinimizeCommand(NDFA* a) : SingleCommand(a) {}

	void execute(std::istream& is, std::ostream& os) override {
		_a->minimize();

		os << "Minimized automaton:\n";
		_a->print(os);
		os << std::endl;
	}
};