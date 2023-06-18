#pragma once

#include "SingleCommand.h"

class ToRegex : public SingleCommand {
public:
	ToRegex(NDFA* a) : SingleCommand(a){}

	virtual void execute(std::ostream& os) override {
		std::cout << "Regex for automaton:" << std::endl;
		std::cout << _a->getRegEx() << std::endl;
	}
};