#include "NDFA.h"

NDFA::NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates) {
	_finalStates = std::move(finalStates);
	_initialStates = std::move(initialStates);
	_allStates = std::move(allStates);
}

NDFA::NDFA(const MyString& str) {

}

void NDFA::determinize() {

}

void minimize() {

}
void NDFA::makeTotal() {

}

bool NDFA::accept(const MyString& word) const {

}

bool NDFA::isEmptyLanguage() const {

}

MyString NDFA::getRegEx() const {

}

NDFA Union(const NDFA& a1, const NDFA& a2) {
	NDFA res(a1); 

	// Get the maximal index for a state in the second automaton 
	size_t size1 = a1._allStates.getSize(); 
	size_t size2 = a2._allStates.getSize();

	// Copy states 
	for (int i = 0; i < size2; i++) {
		res._allStates.pushBack(a2._allStates[i]);
	}

	// Copy initial 
	size_t initalCount = a2._initialStates.getSize();
	for (int i = 0; i < initalCount; i++) {
		res._initialStates.pushBack(a2._initialStates[i] + size1);
	}

	// Copy final
	size_t finalCount = a2._finalStates.getSize();
	for (int i = 0; i < finalCount; i++) {
		res._finalStates.pushBack(a2._finalStates[i] + size1);
	}

	return res;
}

NDFA concatenation(const NDFA& a1, const NDFA& a2) {

}

NDFA kleeneStar(const NDFA& a) {

}

NDFA getAutomatonForRegEx(MyString regEx){

}
