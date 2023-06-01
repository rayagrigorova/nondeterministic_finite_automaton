#pragma once

#include "State.h"
#include "DynamicArray.hpp"
#include "MyString.h"

class NDFA {
	DynamicArray<size_t> _finalStates;
	DynamicArray<size_t> _initialStates;

	DynamicArray<State> _allStates;

	// the following will be set to false each time the automaton
	// is changed or if it was newly constructed
	bool _total = false; 
	bool _minimal = false;
	bool _deterministic = false;

public:
	NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates); 
	NDFA(const MyString& str); 

	void determinize();
	void minimize();
	void makeTotal();

	bool accept(const MyString& word) const; 
	bool isEmptyLanguage() const;
	
	friend NDFA Union(const NDFA& a1, const NDFA& a2);
	friend NDFA concatenation(const NDFA& a1, const NDFA& a2);
	friend NDFA kleeneStar(const NDFA& a);

	MyString getRegEx() const; 

	friend NDFA getAutomatonForRegEx(MyString regEx); 
};

NDFA Union(const NDFA& a1, const NDFA& a2);
NDFA concatenation(const NDFA& a1, const NDFA& a2);
NDFA kleeneStar(const NDFA& a);

NDFA getAutomatonForRegEx(MyString regEx);