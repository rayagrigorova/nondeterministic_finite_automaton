#include "Letter.h"
#include "State.h"

Letter::Letter(char ch) : Symbol(ch){

}

NDFA Letter::buildAutomatonForLanguage() const {
	// The automaton for a single letter is an initial state and
	// a transition with the given letter to a final state. 
	DynamicArray<size_t> initial, final;
	DynamicArray<State> all; 
	State s1, s2;

	// add a transition to s2 
	s1.addTransition(_ch, 1);

	initial.pushBack(0);
	final.pushBack(1);

	all.pushBack(std::move(s1));
	all.pushBack(std::move(s2));

	return NDFA(std::move(final), std::move(initial), std::move(all));
}

RegEx* Letter::clone() const {
	return new Letter(*this);
}

