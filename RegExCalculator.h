#pragma once

#include "RegEx.h"
#include "StringView.h"

class RegExCalculator {
	RegEx* _expr = nullptr;

	bool isOperation(char ch) const; 

	void copyFrom(const RegExCalculator& other);
	void free();
	void moveFrom(RegExCalculator&& other);

	RegEx* parseExpr(const StringView& str); 

public:
	RegExCalculator() = default; 
 	RegExCalculator(const RegExCalculator& other);
	RegExCalculator(RegExCalculator&& other) noexcept;

	RegExCalculator& operator=(const RegExCalculator& other);
	RegExCalculator& operator=(RegExCalculator&& other) noexcept;

	~RegExCalculator(); 

	RegExCalculator(const MyString& str);
	NDFA buildAutomaton();
};