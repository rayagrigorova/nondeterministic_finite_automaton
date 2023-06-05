#pragma once

#include "RegEx.h"

// A base class for letters, epsilon and the null set 
// This is an abstract class 
class Symbol : public RegEx{
protected:
	char _ch;

public: 
	Symbol(char ch) : _ch(ch){}
};
