#pragma once

#include "SingleCommand.h"

class DeterminizeCommand : public SingleCommand {
public:
	DeterminizeCommand(NDFA* a) : SingleCommand(a){}

	void execute(std::ostream& os) override {
		try {
			_a->determinize();
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			return;
		}

		std::cout << "Determinized automaton:\n";
		_a->print();
		std::cout << std::endl;
	}
};