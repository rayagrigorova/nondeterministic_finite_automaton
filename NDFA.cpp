#include "NDFA.h"
#include "RegExCalculator.h"

NDFA::NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates)
	: _finalStates(std::move(finalStates)), _initialStates(std::move(initialStates)), _allStates(std::move(allStates)){

}

NDFA::NDFA(const DynamicArray<size_t>& finalStates, const DynamicArray<size_t>& initialStates, const DynamicArray<State>& allStates)
	: _initialStates(initialStates), _finalStates(finalStates), _allStates(allStates){

}

NDFA::NDFA(const MyString& str) {
	// parse the string 
}

void NDFA::determinize() {

}

void minimize() {

}

void NDFA::makeTotal() {

}

bool NDFA::accept(const StringView& word) const{
	for (int i = 0; i < _initialStates.getSize(); i++) {
		if (accept(word, _initialStates[i])) {
			return true;
		}
	}
	return false;
}

bool NDFA::accept(const StringView& word, int currentState) const{
	if (word.length() == 0) {
		return true;
	}
	for (int i = 0; i < _allStates.getSize(); i++) {
		if (i == currentState) {
			continue;
		}
		
		for (int j = 0; j < _allStates[i].getNumberOfTransitions(); i++) {
			if (_allStates[i][j].getFirst() == word[0]) {
				return accept(word.substr(1, word.length() - 1), _allStates[i][j].getSecond());
			}
		}
	}
	return false;
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

NDFA Union(NDFA&& a1, NDFA&& a2) {
	NDFA res(std::move(a1));

	// Get the maximal index for a state in the second automaton 
	size_t size1 = a1._allStates.getSize();
	size_t size2 = a2._allStates.getSize();

	// Copy states 
	for (int i = 0; i < size2; i++) {
		res._allStates.pushBack(std::move(a2._allStates[i]));
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

NDFA concatenation(NDFA&& a1, NDFA&& a2) {

}

NDFA kleeneStar(NDFA&& a) {

}

NDFA concatenation(const NDFA& a1, const NDFA& a2) {

}

NDFA kleeneStar(const NDFA& a) {

}

NDFA getAutomatonForRegEx(MyString regEx){
	RegExCalculator calc(regEx);
	return calc.buildAutomaton(); 
}




