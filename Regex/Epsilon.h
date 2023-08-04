#pragma once
#include "Symbol.h"
  
class Epsilon : public Symbol{
public:
	Epsilon();

	virtual NDFA buildAutomatonForLanguage() const override;
	virtual RegEx* clone() const override;
};