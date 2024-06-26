#include "Epsilon.h"
#include  "../Constants/SymbolConstants.h"

Epsilon::Epsilon() : Symbol(EPSILON) {

}

NDFA Epsilon::buildAutomatonForLanguage() const {
	// An automaton for epsilon is a single state which is final and initial (no transitions)

	DynamicArray<size_t> initial, final;
	DynamicArray<State> all;

	State s1;

	initial.pushBack(0);
	final.pushBack(0);

	all.pushBack(std::move(s1));

	return NDFA(std::move(final), std::move(initial), std::move(all), DynamicArray<char>());
}

RegEx* Epsilon::clone() const {
	return new Epsilon(*this); 
}
