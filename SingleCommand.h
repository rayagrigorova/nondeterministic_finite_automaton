#pragma once

#include "Command.h"

// A command that works on one automaton
// Virtual inheritance to avoid the diamond problem
class SingleCommand : public virtual Command {
protected:
	// Non-owning pointer
	NDFA* _a;

public:
	SingleCommand(NDFA* a) : _a(a){}

	~SingleCommand() {
		_a = nullptr;
	}
};
