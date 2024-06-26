#pragma once

#include "RegEx.h"

// A base class for letters, epsilon and the null set 
// This is an abstract class 
class Symbol : public RegEx{
protected:
	char _ch;

public: 
	Symbol(char ch) : _ch(ch){}
	void print() const override { std::cout << "Character: " << _ch << std::endl; }

	MyString toString() const override {
		char arr[2];
		arr[0] = _ch;
		arr[1] = '\0';
		return MyString(arr);
	}
};
