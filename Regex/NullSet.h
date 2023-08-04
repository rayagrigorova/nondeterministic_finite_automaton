#pragma once

#include "Symbol.h"

class NullSet : public Symbol {
public:
	NullSet();

	virtual NDFA buildAutomatonForLanguage() const override;
	virtual RegEx* clone() const override;
};