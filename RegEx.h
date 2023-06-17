#pragma once

#include "NDFA.h"

class RegEx {
	// Each regex knows how to construct an automaton for itself 
public:
	virtual NDFA buildAutomatonForLanguage() const = 0;
	virtual ~RegEx() = default; 
	virtual RegEx* clone() const = 0;

	virtual void print() const = 0;

	virtual MyString toString() const = 0;
};