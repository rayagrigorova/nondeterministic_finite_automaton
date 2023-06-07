#include "NDFA.h"
#include "RegExCalculator.h"
#include "SymbolConstants.h"

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
	// There are no transitions involved when recognizing epsilon 
	// The condition under which a language contains epsilon is that for some state qi: 
	// qi is both initial and final 
	if (word.length() == 1 && word[0] == EPSILON) {
		for (int i = 0; i < _initialStates.getSize(); i++) {
			for (int j = 0; j < _finalStates.getSize(); j++) {
				if (_initialStates[i] == _finalStates[j]) {
					return true;
				}
			}
		}
		return false;
	}

	for (int i = 0; i < _initialStates.getSize(); i++) {
		// Use a private function accept to check if one of the initial states 
		// accepts the word - at least one initial state's right language should contain the word. 
		if (accept(word, _initialStates[i])) {
			return true;
		}
	}

	// No initial state's right language contains the word 
	return false;
}

bool NDFA::accept(const StringView& word, int currentState) const{
	// Base of the recursion 
	if (word.length() == 0) {
		return true;
	}

	// Go through all states 
	for (int i = 0; i < _allStates.getSize(); i++) {	

		// Go through all transitions of the current state 
		for (int j = 0; j < _allStates[i].getNumberOfTransitions(); j++) {
			// If there is a transition from state qi to qj with the first letter of the word, proceed to the
			// next state and remove the first letter of the word. 
			if (_allStates[i][j].getFirst() == word[0]) {
				// Recursive call 
				accept(word.substr(1, word.length() - 1), _allStates[i][j].getSecond());
			}
		}
	}

	// If we go through all possible qi and possible destination states qj without finding a transition (qi, x, qj) for 
	// some i,j and x = word[0], then the subtree can't possibly contain a valid path with a label w
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

// This function will only be used to call the overload isReachable(fromInd, stateInd) for all start states 
bool NDFA::isReachable(size_t stateInd) {
	for (int i = 0; i < _initialStates.getSize(); i++) {
		if (isReachable(i, stateInd)) {
			return true;
		}
	}
	return false;
}

bool NDFA::isReachable(size_t fromInd, size_t destInd) {
	// A state qj is reachable from a state qi if there exists a natural number n: 
	// qj is reachable from qi i n steps 

	// Make a list of all states reachable from the fromState 
	// Using a bool array isn't optimal in terms of memory because a bool only uses 1 bit out of 8 
	// However, for the sake of simplicity, I am going to use a bool array 
	size_t reachableCount = 0;
	bool* reachable = new bool[_allStates.getSize()];

	// The fromState is reachable from itself in 0 steps 
	reachable[fromInd] = 1; 

	// This loop will repeat n times 
	while(1){
		// This flag is used to indicate whether a new state was added to the reachable list 
		bool flag = 0; 

		// Go through all states in the reachable array 
		for (int i = 0; i < reachableCount; i++) {

			// For each states in the reachable array, add the destination states from all one step transitions 
			// to the array of reachable states. A destination state is qj in (qi, x) = qj 
			for (int j = 0; j < _allStates[i].getNumberOfTransitions(); i++) {

				// If we are about to add a state that wasn't in the array initially 
				// This check is necessary because of the flag 
				if (reachable[_allStates[i][j].getSecond()] == 0) {
					flag = 1;
					reachable[_allStates[i][j].getSecond()] = 1;
				}
			}
		}

		// If no new states were added in the reachable array 
		if (!flag) {
			break; 
		}
	}

	delete[] reachable;

	return reachable[destInd] == 1;
}




