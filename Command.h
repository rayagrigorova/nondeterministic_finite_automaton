#pragma once

#include <iostream>
#include "NDFA.h"

class Command {
public:
	~Command() = default;
	virtual void execute(std::ostream& os) = 0;
};