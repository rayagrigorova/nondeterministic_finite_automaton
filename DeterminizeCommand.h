#pragma once

#include "SingleCommand.h"

class DeterminizeCommand : public SingleCommand {
public:
	DeterminizeCommand(NDFA* a) : SingleCommand(a){}

	void execute(std::istream& is, std::ostream& os) override {
		try {
			_a->determinize();
		}
		catch (std::exception& e) {
			os << e.what() << std::endl;
			return;
		}

		os << "Determinized automaton:\n\n";
		_a->print(os);
		os << std::endl;
	}
};