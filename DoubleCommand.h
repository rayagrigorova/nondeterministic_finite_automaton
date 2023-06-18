#pragma once

#include "Command.h"

// A command that works on two automata
class DoubleCommand : public virtual Command {
protected:
	NDFA* _a1;
	NDFA* _a2;

public:
	DoubleCommand(NDFA* a1, NDFA* a2) : _a1(a1), _a2(a2){}

	~DoubleCommand() {
		_a1 = nullptr;
		_a2 = nullptr;
	}
};