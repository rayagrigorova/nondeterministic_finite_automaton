#pragma once

#include "RegEx.h"

// A base class for letters, epsilon and the null set 
class Symbol : public RegEx{
protected:
	char _ch;

public: 
	Symbol(char ch) : _ch(ch){}
};
