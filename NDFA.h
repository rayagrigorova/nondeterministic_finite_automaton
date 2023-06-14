#pragma once

#include "State.h"
#include "DynamicArray.hpp"
#include "MyString.h"
#include "StringView.h"

class NDFA {
	DynamicArray<size_t> _finalStates;
	DynamicArray<size_t> _initialStates;

	DynamicArray<State> _allStates;

	DynamicArray<char> _alphabet; 

	bool accept(const StringView& word, int currentState) const; 

	bool isReachable(size_t stateInd) const;
	bool isReachable(size_t fromInd, size_t destInd) const; // check if a state is reachable through some initial state

	void setAlphabet();

	// Check if a state is final/initial 
	bool isFinal(size_t ind) const;
	bool isInitial(size_t ind) const;

	void removeUnreachableStates();

public:
	NDFA() = default; 
	NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates); 
	NDFA(const DynamicArray<size_t>& finalStates, const DynamicArray<size_t>& initialStates, const DynamicArray<State>& allStates);

	NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates, DynamicArray<char>&& alphabet);
	NDFA(const DynamicArray<size_t>& finalStates, const DynamicArray<size_t>& initialStates, const DynamicArray<State>& allStates, const DynamicArray<char>& alphabet);

	NDFA(const MyString& str); 

	void determinize();
	void minimize();
	void makeTotal();

	bool accept(const StringView& word) const; 

	bool isEmptyLanguage() const;
	
	friend NDFA Union(const NDFA& a1, const NDFA& a2);
	friend NDFA Union(NDFA&& a1, NDFA&& a2);

	friend NDFA concatenation(const NDFA& a1, const NDFA& a2);
	friend NDFA concatenation(NDFA&& a1, NDFA&& a2);

	friend NDFA kleeneStar(const NDFA& a);
	//friend NDFA kleeneStar(NDFA& a);

	MyString getRegEx() const; 

	friend NDFA getAutomatonForRegEx(MyString regEx); 

	void print() const; 

	friend bool isDeterminisitic(const NDFA& a); 
	friend NDFA generateMinimalAutomaton(const DynamicArray<DynamicArray<size_t>>& newStates, size_t numberOfStates, const NDFA& originalAutomaton); 
};

NDFA Union(const NDFA& a1, const NDFA& a2);
NDFA concatenation(const NDFA& a1, const NDFA& a2);
NDFA kleeneStar(const NDFA& a);

NDFA Union(NDFA&& a1, NDFA&& a2);
NDFA concatenation(NDFA&& a1, NDFA&& a2);
//NDFA kleeneStar(NDFA& a);

NDFA getAutomatonForRegEx(MyString regEx);