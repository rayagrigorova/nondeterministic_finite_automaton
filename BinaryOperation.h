#pragma once

#include "RegEx.h"

// Binary operations: '+' and '.' 
class BinaryOperation : public RegEx {
	RegEx* _lhs;
	RegEx* _rhs; 

	char _op; 
public: 
	BinaryOperation(RegEx* lhs, RegEx* rhs, char op);

	NDFA buildAutomatonForLanguage() const override;

	RegEx* clone() const override;

	~BinaryOperation(); 

	virtual void print() const override;
};