#pragma once

#include "SingleCommand.h"

class ToRegex : public SingleCommand {
public:
	ToRegex(NDFA* a) : SingleCommand(a){}

	virtual void execute(std::istream& is, std::ostream& os) override {
		os << "Regex for automaton:\n\n";
		os << _a->getRegEx() << std::endl;
	}
};