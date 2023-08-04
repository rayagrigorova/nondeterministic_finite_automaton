#pragma once

#include "SingleCommand.h"

// Check if the language of a given automaton is empty 
class EmptyCheck : public SingleCommand {
public:
	EmptyCheck(NDFA* a) : SingleCommand(a) {}

	void execute(std::istream& is, std::ostream& os) override {
		if (_a->isEmptyLanguage()) {
			os << "The language of the automaton is empty\n\n";
		}
		else {
			os << "The language of the automaton isn't empty\n\n";
		}
	}
};