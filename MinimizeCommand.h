#pragma once

#include "SingleCommand.h"

class MinimizeCommand : public SingleCommand {
public:
	MinimizeCommand(NDFA* a) : SingleCommand(a) {}

	void execute(std::ostream& os) override {
		_a->minimize();

		std::cout << "Minimized automaton:\n";
		_a->print();
		std::cout << std::endl;
	}
};