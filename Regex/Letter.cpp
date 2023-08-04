#include "Letter.h"
#include "../State/State.h"

Letter::Letter(char ch) : Symbol(ch){

}

NDFA Letter::buildAutomatonForLanguage() const {
	// The automaton for a single letter is an initial state and
	// a transition with the given letter to a final state. 
	DynamicArray<size_t> initial, final;
	DynamicArray<State> all; 
	DynamicArray<char> alphabet;

	State s1, s2;

	// add a transition to the second state 
	s1.addTransition(_ch, 1);

	initial.pushBack(0);
	final.pushBack(1);

	all.pushBack(std::move(s1));
	all.pushBack(std::move(s2));

	alphabet.pushBack(_ch);

	NDFA res(std::move(final), std::move(initial), std::move(all), std::move(alphabet));

	return res; 
}

RegEx* Letter::clone() const {
	return new Letter(*this);
}

