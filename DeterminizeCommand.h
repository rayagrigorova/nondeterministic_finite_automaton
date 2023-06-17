#pragma once

#include "SingleCommand.h"

class DeterminizeCommand : public SingleCommand {
public:
	DeterminizeCommand(NDFA* a) : SingleCommand(a){}

	void execute(std::ostream& os) override {
		_a->determinize();
	}
};