#pragma once

#include "SingleCommand.h"

// Convert an automaton to a regular expression 
class ToRegex : public SingleCommand {
public:
	ToRegex(NDFA* a) : SingleCommand(a){}

	virtual void execute(std::istream& is, std::ostream& os) override {
		os << "Regex for automaton:\n\n";
		os << _a->getRegEx() << std::endl;
	}
};