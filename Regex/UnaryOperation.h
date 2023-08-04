#pragma once

#include "RegEx.h"

// Unary operation: *
class UnaryOperation : public RegEx{
	RegEx* _expr;
	char _op;
public:
	UnaryOperation(RegEx* expr, char op);
	NDFA buildAutomatonForLanguage() const override;
	RegEx* clone() const override;

	virtual void print() const override; 
	virtual MyString toString() const override;

	~UnaryOperation();
};