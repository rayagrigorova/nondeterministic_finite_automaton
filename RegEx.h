#pragma once

#include "NDFA.h"

class RegEx {
	// Each regex knows how to construct an automaton for itself 
public:
	virtual NDFA buildAutomatonForLanguage() const = 0;
};