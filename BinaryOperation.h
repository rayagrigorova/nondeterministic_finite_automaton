#pragma once

#include "RegEx.h"

class BinaryOperation : public RegEx {
	RegEx* _lhs;
	RegEx* _rhs; 

	char _op; 
public: 
	BinaryOperation(RegEx* lhs, RegEx* rhs, char op);

	NDFA buildAutomatonForLanguage() const override;
};