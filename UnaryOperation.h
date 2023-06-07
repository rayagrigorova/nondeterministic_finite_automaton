#pragma once

#include "RegEx.h"

class UnaryOperation : public RegEx{
	RegEx* _expr;
	char _op;
public:
	UnaryOperation(RegEx* expr, char op);

	NDFA buildAutomatonForLanguage() const override;

	RegEx* clone() const override;

	~UnaryOperation();
};