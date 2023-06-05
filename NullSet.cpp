#include "NullSet.h"
#include  "SymbolConstants.h"

NullSet::NullSet() : Symbol(NULL_SET){

}

NDFA NullSet::buildAutomatonForLanguage() const{
	// An automaton for the null set is a single state which is initial 

	DynamicArray<size_t> initial, final;
	DynamicArray<State> all;

	State s1;

	initial.pushBack(0);

	all.pushBack(std::move(s1));

	return NDFA(std::move(final), std::move(initial), std::move(all));
}

RegEx* NullSet::clone() const {
	return new NullSet(*this); 
}
