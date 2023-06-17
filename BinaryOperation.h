#pragma once

#include "RegEx.h"

// Binary operations: '+' and '.' 
class BinaryOperation : public RegEx {
	RegEx* _lhs = nullptr;
	RegEx* _rhs = nullptr; 

	char _op; 
public: 
	BinaryOperation(RegEx* lhs, RegEx* rhs, char op);

	NDFA buildAutomatonForLanguage() const override;

	RegEx* clone() const override;

	~BinaryOperation(); 

	virtual void print() const override;

	void setRhs(RegEx* rhs);
	void setLhs(RegEx* lhs);

	const RegEx* getRhs() const;
	const RegEx* getLhs() const;

	virtual MyString toString() const override;
};