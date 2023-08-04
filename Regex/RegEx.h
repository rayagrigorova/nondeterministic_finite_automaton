#pragma once

#include "../NDFA/NDFA.h"

class RegEx {
public:
	// Each regex knows how to construct an automaton for itself 
	virtual NDFA buildAutomatonForLanguage() const = 0;

	virtual ~RegEx() = default; 
	virtual RegEx* clone() const = 0;

	virtual void print() const = 0;

	virtual MyString toString() const = 0;
};
