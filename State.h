#pragma once

#include "DynamicArray.hpp"
#include "Pair.hpp"

// A state is a dynamic array of pairs<char, int>
class State {
	// The character represents the letter of the transition and the number (starting from 0) is 
	// the number of the state to be transitioned to. 
	DynamicArray<Pair<char, int>> _arr;

public:
	State() = default;

	void addTransition(char ch, int state); // Add transition to a state with a given character
	void removeAllTransitionsTo(int state); // Used when removing a state. All transitions to it should be deleted. 

	size_t getNumberOfTransitions() const;
	
	const Pair<char, int>& operator[](size_t ind) const; // constant 
	Pair<char, int>& operator[](size_t ind); // non-constant 
};