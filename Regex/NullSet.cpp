#include "NullSet.h"
#include  "../Constants/SymbolConstants.h"

NullSet::NullSet() : Symbol(NULL_SET){

}

NDFA NullSet::buildAutomatonForLanguage() const{
	// An automaton for the null set is a single state which is initial (no final states or transitions)

	DynamicArray<size_t> initial, final;
	DynamicArray<State> all;

	State s1;

	initial.pushBack(0);

	all.pushBack(std::move(s1));

	return NDFA(std::move(final), std::move(initial), std::move(all), DynamicArray<char>());
}

RegEx* NullSet::clone() const {
	return new NullSet(*this); 
}
