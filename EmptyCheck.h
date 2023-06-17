#pragma once

#include "SingleCommand.h"

class EmptyCheck : public SingleCommand {
public:
	EmptyCheck(NDFA* a) : SingleCommand(a) {}

	void execute(std::ostream& os) override {
		if (_a->isEmptyLanguage()) {
			std::cout << "The language of the automaton is empty\n";
		}
		else {
			std::cout << "The language of the automaton isn't empty\n";
		}
	}
};