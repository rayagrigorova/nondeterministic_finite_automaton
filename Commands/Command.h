#pragma once

#include <iostream>
#include "../NDFA/NDFA.h"

// Base class for all commands 
class Command {
public:
	~Command() = default;

	virtual void execute(std::istream& is, std::ostream& os) = 0;
};
