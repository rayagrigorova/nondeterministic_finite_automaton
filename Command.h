#pragma once

#include <iostream>
#include "NDFA.h"

// Base class for all commands 
class Command {
public:
	~Command() = default;
	virtual void execute(std::ostream& os) = 0;
};