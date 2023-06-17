#pragma once

#include "Command.h"

// A command that works on one automaton
class SingleCommand : public virtual Command {
protected:
	NDFA* _a;

public:
	SingleCommand(NDFA* a) : _a(a){}
};
