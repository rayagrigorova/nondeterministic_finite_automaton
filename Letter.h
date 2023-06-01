#pragma once

#include "Symbol.h"

class Letter : public Symbol {
public:
	Letter(char ch);
	virtual NDFA buildAutomatonForLanguage() const override;
};