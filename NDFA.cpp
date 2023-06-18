#include "NDFA.h"
#include "RegExCalculator.h"
#include "SymbolConstants.h"

#include "Letter.h"
#include "BinaryOperation.h"
#include "UnaryOperation.h"
#include "Epsilon.h"
#include "NullSet.h"

#include <iomanip> 

namespace {
	template <typename T>
	bool contains(const DynamicArray<T>& arr, const T& elem) {
		for (int i = 0; i < arr.getSize(); i++) {
			if (arr[i] == elem) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	// A function to compare the contents of two dynamic arrays 
	// The type used should have an operator != 
	bool arraysAreEqual(const DynamicArray<T>& arr1, const DynamicArray<T>& arr2) {
		size_t size = arr1.getSize();
		if (size != arr2.getSize()) {
			return false;
		}

		for (int i = 0; i < size; i++) {
			if (!contains<T>(arr2, arr1[i])) {
				return false;
			}
		}
		return true;
	}
}

NDFA::NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates)
	: _finalStates(std::move(finalStates)), _initialStates(std::move(initialStates)), _allStates(std::move(allStates)){
	setAlphabet();
}

NDFA::NDFA(const DynamicArray<size_t>& finalStates, const DynamicArray<size_t>& initialStates, const DynamicArray<State>& allStates)
	: _initialStates(initialStates), _finalStates(finalStates), _allStates(allStates){
	setAlphabet();
}

NDFA::NDFA(const MyString& str){
	RegExCalculator calc(str);
	NDFA res = calc.buildAutomaton(); 
	*this = res;
	setAlphabet();
}

NDFA::NDFA(DynamicArray<size_t>&& finalStates, DynamicArray<size_t>&& initialStates, DynamicArray<State>&& allStates, DynamicArray<char>&& alphabet) 
	: _finalStates(std::move(finalStates)), _initialStates(std::move(initialStates)), _allStates(std::move(allStates)), _alphabet(std::move(alphabet)) {

}

NDFA::NDFA(const DynamicArray<size_t>& finalStates, const DynamicArray<size_t>& initialStates, const DynamicArray<State>& allStates, const DynamicArray<char>& alphabet)
	: _initialStates(initialStates), _finalStates(finalStates), _allStates(allStates), _alphabet(alphabet){

}

void NDFA::setAlphabet() {
	for (int i = 0; i < _allStates.getSize(); i++) { // for each state
		for (int j = 0; j < _allStates[i].getNumberOfTransitions(); j++) { // for each transition 
			if (!contains<char>(_alphabet, _allStates[i][j].getFirst())) {
				_alphabet.pushBack(_allStates[i][j].getFirst());
			}
		}
	}
}

bool NDFA::isFinal(size_t ind) const {
	return contains<size_t>(_finalStates, ind);
}

bool NDFA::isInitial(size_t ind) const {
	return contains<size_t>(_initialStates, ind);
}

// A deterministic automaton contains no more than one initial state and a single (or no) transition with each letter 
bool isDeterminisitic(const NDFA& a) {
	// If the number of initial states is greater than 0, then the automaton isn't deterministic
	if (a._initialStates.getSize() > 1) {
		return false;
	}

	for (int i = 0; i < a._allStates.getSize(); i++) { // for each state

		// I assume that the alphabet only contains symbols a-z
		uint32_t transitionsMask = 0; // store the letters of the outgoing transitions 


		for (int j = 0; j < a._allStates[i].getNumberOfTransitions(); j++) { // for each transition 
			// Create a mask for the current transition 
			// The first bit will correspond to 'a', the second one - to 'b' and so on. 
			uint32_t currentMask = 1 << (32 - (a._allStates[i][j].getFirst() - 'a' + 1)); 

			// (transitionsMask & currentMask) will return true if there exists a transition with the same letter 
			if (transitionsMask & currentMask) {
				return false; 
			}

			// Add the transition
			transitionsMask |= currentMask; 
		}

		// Check if there are transitions with each letter from the alphabet 
		for (int k = 0; k < a._alphabet.getSize(); k++) {
			uint32_t currentMask = 1 << (32 - (a._alphabet[k] - 'a' + 1));

			// No transition with the current letter 
			if (!(transitionsMask & currentMask)) {
				return false;
			}
		}
	}

	return true;
}

void addToSubset(DynamicArray<DynamicArray<size_t>>& stateSubsets, size_t i, size_t currentSubset, DynamicArray<size_t>& newState, char ch, DynamicArray<State>& allStates) {
	for (int j = 0; j < stateSubsets[currentSubset].getSize(); j++) { // for each state from the current subset 

		// Get the position of the current state in the _allStates array 
		size_t currentStateIndex = stateSubsets[currentSubset][j];

		for (int k = 0; k < allStates[currentStateIndex].getNumberOfTransitions(); k++) { // For each transition of the current state 
			// Skip transitions with other letters 
			if (allStates[currentStateIndex][k].getFirst() != ch) {
				continue;
			}

			// If the destination state hasn't been added to the new state yet 
			if (!contains<size_t>(newState, allStates[currentStateIndex][k].getSecond())) {
				newState.pushBack(allStates[currentStateIndex][k].getSecond());
			}
		}
	}
}

void checkStateType(DynamicArray<DynamicArray<size_t>>& stateSubsets, DynamicArray<char>& _alphabet, DynamicArray<State>& allStates,
	size_t& newStateIndex, DynamicArray<size_t>& _finalStates, DynamicArray<size_t>& finalStates) {
	// Check if the null set was added - if it was, the respective state in the states array 
// should have a transition to itself with all letters from the alphabet
	if (stateSubsets[newStateIndex].getSize() == 0) {
		for (int h = 0; h < _alphabet.getSize(); h++) {
			allStates[newStateIndex].addTransition(_alphabet[h], newStateIndex);
		}
	}

	else {
		// Check if the new state contains final states 
		for (int l = 0; l < _finalStates.getSize(); l++) {
			// If the added subset contains at least one final state 
			if (contains<size_t>(stateSubsets[newStateIndex], _finalStates[l])) {

				// Add the newly added state as a final state 
				finalStates.pushBack(newStateIndex);
				break;
			}
		}
	}
}

void searchAndAdd(DynamicArray<DynamicArray<size_t>>& stateSubsets, DynamicArray<size_t>& newState, DynamicArray<State>& allStates,
	bool& stateAdded, size_t& newStateIndex, DynamicArray<char>& _alphabet, size_t currentSubset, size_t i,
	DynamicArray<size_t>& finalStates, DynamicArray<size_t>& _finalStates) {

	// Check if the newly created state already exists in the state subsets array 
	int foundInd = -1;
	for (int t = 0; t < stateSubsets.getSize(); t++) {
		if (arraysAreEqual<size_t>(stateSubsets[t], newState)) {
			foundInd = t;
			break;
		}
	}

	// If the state hasn't been added yet 
	if (foundInd < 0) {
		// Mark that a new state was added
		stateAdded = true;
		// Add to subsets array 
		stateSubsets.pushBack(std::move(newState));

		// Add to the actual array of states 
		allStates.pushBack(State());
		allStates[currentSubset].addTransition(_alphabet[i], newStateIndex);

		checkStateType(stateSubsets, _alphabet, allStates, newStateIndex, _finalStates, finalStates);

		newStateIndex++;
	}

	else {
		allStates[currentSubset].addTransition(_alphabet[i], foundInd);
	}
}

void NDFA::determinize() {
	if (isDeterminisitic(*this)) {
		return;
	}

	// The arrays to be used to create the new automaton 
	DynamicArray<size_t> finalStates;
	DynamicArray<size_t> initialStates;
	DynamicArray<State> allStates;

	allStates.pushBack(State()); 
	initialStates.pushBack(0);

	DynamicArray<DynamicArray<size_t>> stateSubsets; 
	DynamicArray<size_t> initial; 

	// Initialize the first state in the state subset - a state containing all initial states of the NDFA
	for (int i = 0; i < _initialStates.getSize(); i++) {
		initial.pushBack(_initialStates[i]); 
	}

	stateSubsets.pushBack(std::move(initial)); 

	size_t currentSubset = 0;
	size_t alphabetSize = _alphabet.getSize();
	size_t newStateIndex = 1; // Index the newly added states, starting from 1

	while (1) {
		// If the current set is the null set, don't add any transitions 
		if (stateSubsets[currentSubset].getSize() == 0) {
			currentSubset++;
			continue; 
		}

		// A flag to indicate whether new states were added 
		bool stateAdded = false;

		for (int i = 0; i < alphabetSize; i++) { // for each letter of the alphabet 
			// A set of states representing the combined result of all delta functions with the current letter
			DynamicArray<size_t> newState; 

			addToSubset(stateSubsets, i, currentSubset, newState, _alphabet[i], _allStates); 
			searchAndAdd(stateSubsets, newState, allStates, stateAdded, newStateIndex, _alphabet, currentSubset, i, finalStates, _finalStates);
		}
		
		// If no new states were added 
		if (!stateAdded) {
			break;
		}

		currentSubset++;
	}

	*this = NDFA(std::move(finalStates), std::move(initialStates), std::move(allStates), std::move(_alphabet)); 
}

namespace {
	// A helper function to find if a pair of states belongs to some existing equivalence class 
	// This is done because equivalence relations have the property of transitivity
	int getEquivalenceClassIndex(size_t first, size_t second, const DynamicArray<DynamicArray<size_t>>& newStates) {
		for (int i = 0; i < newStates.getSize(); i++) { // For all equivalence classes 
			for (int j = 0; j < newStates[i].getSize(); j++) { // for all states in the equivalence class 

				// First and second are in the same equivalence class and if either
				// of them is in another equivalence class, the two equivalence classes can be united 
				if (newStates[i][j] == first || newStates[i][j] == second) {
					return i; // return the index of the equivalence class 
				}
			}
		}
		// Equivalence class not found 
		return -1;
	}

	void generateEquivalenceClasses(const bool** arr, size_t numberOfStates, DynamicArray<DynamicArray<size_t>>& newStates) {
		// This is a flag to generate sets for states that aren't equivalent to any other state
		bool isSingleton;

		// I will only look at the elements below the main diagonal
		for (int i = 0; i < numberOfStates; i++) { // for each row

			// States that are not equivalent to any other state are represented by a row of 0's in the table 
			isSingleton = true;

			for (int j = 0; j < i; j++) { // for each column 
				// A pair that is a part of some equivalence class 
				if (arr[i][j]) {
					// The current state (i) can't be added by itself, it will be a part of some equivalence class 
					isSingleton = false;

					int ind = getEquivalenceClassIndex(i, j, newStates);
					
					// An equivalence class for the pair of states already exists 
					if (ind > 0) {
						newStates[ind].pushBack(i); 
						newStates[ind].pushBack(j);
					}
					// An equivalence class for the pair of states doesn't exist
					else {
						DynamicArray<size_t> pair;
						pair.pushBack(i);
						pair.pushBack(j);
						newStates.pushBack(std::move(pair));
					}
				}
			}
			if (isSingleton) {
				DynamicArray<size_t> singleton;
				singleton.pushBack(i);
				newStates.pushBack(std::move(singleton));
			}
		}
	}

	int findStateEquivalenceClass(const DynamicArray<DynamicArray<size_t>>& equivalenceClasses, size_t stateName) {
		for (int i = 0; i < equivalenceClasses.getSize(); i++) { // for each class
			for (int j = 0; j < equivalenceClasses[i].getSize(); j++) { // for each state in the class 
				if (equivalenceClasses[i][j] == stateName) {
					// return the index of the equivalence class 
					return i;
				}
			}
		}
		// not found
		return -1;
	}
}

// Using the transitions of the old automaton and the created equivalence classes, generate a minimal NDFA 
NDFA generateMinimalAutomaton(const DynamicArray<DynamicArray<size_t>>& newStates, size_t numberOfStates, const NDFA& originalAutomaton) {
	DynamicArray<size_t> finalStates;
	DynamicArray<size_t> initialStates;
	DynamicArray<State> allStates;
	DynamicArray<char> alphabet = originalAutomaton._alphabet;

	for (int i = 0; i < newStates.getSize(); i++) { // for each equivalence class 
		allStates.pushBack(State()); // Add a new state for the current set of states 

		// If one of the states is final in the original automaton, then all other states are final too, so check for the first state
		if (originalAutomaton.isFinal(newStates[i][0])) {  
			finalStates.pushBack(i); 
		}

		// Find the initial state in the current equivalence class 
		// The equivalence class of the initial state is the initial state of the new automaton 
		for (int j = 0; j < newStates[i].getSize(); j++) {
			// The automaton has a single initial state since it's deterministic
			if (newStates[i][j] == originalAutomaton._initialStates[0]) {
				initialStates.pushBack(i);
			}
		}

		// Add transitions with all letters 
		for (int k = 0; k < alphabet.getSize(); k++) {
			size_t destClass = findStateEquivalenceClass(newStates, originalAutomaton._allStates[newStates[i][0]].getDestinationState(alphabet[k]));
			allStates[i].addTransition(alphabet[k], destClass);
		}
	}
	return NDFA(std::move(finalStates), std::move(initialStates), std::move(allStates), std::move(alphabet)); 
}

// Source used: https://store.fmi.uni-sofia.bg/fmi/logic/static/eai/eai.pdf
void NDFA::minimize() {
	removeUnreachableStates();
	determinize();

	size_t numberOfStates = _allStates.getSize();

	// Create a two dimensional bool array (an array of pointers)
	bool** arr = new bool*[numberOfStates];

	for (int i = 0; i < numberOfStates; i++) {
		// Create the sub-arrays 
		arr[i] = new bool[numberOfStates];

		for (int j = 0; j < numberOfStates; j++) {
			bool firstIsFinal = isFinal(i); 
			bool secondIsFinal = isFinal(j);

			// p is final <-> q isn't final 
			// Mark all pairs where the two states aren't of the same finality 
			if (firstIsFinal && !secondIsFinal ||
				!firstIsFinal && secondIsFinal) {
				arr[i][j] = 0;
			}
			else {
				arr[i][j] = 1;
			}
		}
	}

	bool ready; 

	do {
		ready = true;

		for (int i = 0; i < numberOfStates; i++) {
			for (int j = 0; j < numberOfStates; j++) {
				if (arr[i][j]) {
					for (int k = 0; k < _alphabet.getSize(); k++) {
						int deltaOne = _allStates[i].getDestinationState(_alphabet[k]);
						int deltaTwo = _allStates[j].getDestinationState(_alphabet[k]);

						// If arr[deltaOne][deltaTwo] is marked 
						if (!arr[deltaOne][deltaTwo]) {
							// Mark the current pair of states 
							arr[i][j] = false;
							ready = false;
						}
					}
				}
			}
		}
		
	} while (!ready);


	// The new states are sets of states (they can't be used in the actual automaton ôêø are necessary for its construction)
	DynamicArray<DynamicArray<size_t>> newStates; 

	generateEquivalenceClasses((const bool**)arr, numberOfStates, newStates); 
	*this = generateMinimalAutomaton(newStates, numberOfStates, *this);

	// Delete the bool array 
	// For each sub-array
	for (int i = 0; i < numberOfStates; i++) {
		delete[] arr[i];
	
	}
	// Free the array of pointers 
	delete[] arr; 
}

void NDFA::makeTotal() {
	// A total automaton is such that for each of its
	// states p and each letter of the alphabet x there exists at least one transition from p with x

	// I will simultaneously check if the automaton is total and if there is a transition with each letter
	bool isTotal = true;
	size_t newStateIndex = _allStates.getSize(); // The index of the new state

	for (int i = 0; i < _allStates.getSize(); i++) { // for each state 

		int32_t transitionsMask = 0; // store the letters of the outgoing transitions 

		for (int j = 0; j < _allStates[i].getNumberOfTransitions(); j++) { // for each transition 

			// This way, the first bit will correspond to 'a', the second one - to 'b' and so on. 
			int32_t currentMask = 1 << (32 - (_allStates[i][j].getFirst() - 'a' + 1));

			// Add the transition
			transitionsMask |= currentMask;
		}

		for (int l = 0; l < _alphabet.getSize(); l++) { // for all symbols in the alphabet 
			int32_t currentMask = 1 << (32 - (_alphabet[l] - 'a' + 1)); // Mask for the current letter of the alphabet

			if (!(transitionsMask & currentMask)) { // Check if the bit for the transition with the current letter is set to false 
				isTotal = false;
				// The current state doesn't have a transition with _alphabet[l]. Add a transition to the new state. 
				_allStates[i].addTransition(_alphabet[l], newStateIndex);
			}
		}

	}

	if (!isTotal) {
		// A new state should be added 
		_allStates.pushBack(State());

		for (int l = 0; l < _alphabet.getSize(); l++) {
			// For each letter of the alphabet, ad a self loop to the new state 
			_allStates[newStateIndex].addTransition(_alphabet[l], newStateIndex);
		}
	}

}

bool NDFA::accept(const StringView& word) const{
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

	// Go through all transitions of the current state 
	for (int i = 0; i < _allStates[currentState].getNumberOfTransitions(); i++) {
		// If there is a transition with the first letter of the word 
		if (_allStates[currentState][i].getFirst() == word[0]) {
			return accept(word.substr(1, word.length() - 1), _allStates[currentState][i].getSecond()); 
		}
	}

	// If we go through all possible qi and possible destination states qj without finding a transition (qi, x, qj) for 
	// some i,j and x = word[0], then the subtree can't possibly contain a valid path with a label w
	return false;
}

bool NDFA::isEmptyLanguage() const {
	for (int i = 0; i < _finalStates.getSize(); i++) {
		if (isReachable(_finalStates[i])) {
			return false;
		}
	}
	return true;
}

// Source used: https://www.fit.vut.cz/research/project-file/589/Presentations/PB05-Converting-FAs-To-REs.pdf
// Method: transitive closure 
MyString NDFA::getRegEx() const {
	if (!isDeterminisitic(*this)) {
		throw std::invalid_argument("For the transitive closure method to work, the automaton should be a DFA\n"); 
	}

	size_t Q = _allStates.getSize(); 

	// Rij(k)
	// A three dimensional array of pointers to regular expressions 
	// Three dimensions to access i, j, k
	RegEx**** R = new RegEx ***[Q]; 

	
	// Initialize Rij(0)
	for (int i = 0; i < Q; i++) { // For all states 
		R[i] = new RegEx **[Q];

		for (int j = 0; j < Q; j++) { // For each pair of states
			R[i][j] = new RegEx *[Q + 1]; // 0 to Q for k 

			if (i == j) {
				R[i][j][0] = new Epsilon();
			}
			else {
				R[i][j][0] = new NullSet();
			}

			for (int t = 0; t < _allStates[i].getNumberOfTransitions(); t++) { // for all transitions of i
				// If the current  transition is from qi to qj
				if (_allStates[i][t].getSecond() == j) {
					R[i][j][0] = new BinaryOperation(R[i][j][0]->clone(), new Letter(_allStates[i][t].getFirst()), '+');
				}
			}
		}
		
	}

	// Transitive closure
	// Computation for all Rij(k) where i, j, k are { 1, |Q| }
	for (int k = 1; k <= Q; k++) {
		for (int i = 0; i < Q; i++) { // For all states 
			for (int j = 0; j < Q; j++) { // For each pair of states
				// Rij(k) = Rij(k-1) + Rik(k-1) . Rkk(k-1))* . Rkj(k-1)

				RegEx* ex1 = new UnaryOperation(R[k - 1][k - 1][k - 1]->clone(), '*'); // (R[k,k,k-1])*
				RegEx* ex2 = new BinaryOperation(R[i][k - 1][k - 1]->clone(), ex1, '.'); // Rik(k-1)
				RegEx* ex3 = new BinaryOperation(ex2, R[k - 1][j][k - 1]->clone(), '.'); // Rkj(k-1)
				RegEx* ex4 = new BinaryOperation(R[i][j][k - 1]->clone(), ex3, '+'); // Rij(k-1) + Rik(k-1) . Rkk(k-1))* . Rkj(k-1)

				R[i][j][k] = ex4->clone();
			}
		}
	}
	 //Get the final expression
	 //Expr uses resources managed from R
	RegEx* expr = new NullSet();
	size_t initialInd = _initialStates[0];

	for (int i = 0; i < Q; i++) {
		if (isFinal(i)) {
			expr = new BinaryOperation(expr->clone(), R[initialInd][i][Q - 1]->clone(), '+');
		}
	}

	// Save result and delete R 
	MyString res = expr->toString();


	for (int i = 0; i < Q; i++) {
		for (int j = 0; j < Q; j++) {
			// for (int k = 0; k <= Q; k++) {

			//	 //Delete pointers RegEx* (created using new)
			//delete R[i][j][k]; 
			//	
			//}
			
			// Delete pointers to the regular expressions 
			delete[] R[i][j];
		}
		delete[] R[i];
	}
	delete[] R;

	return res;
}

// The result of creating an union automaton is like "putting the automata next to each other"
NDFA Union(const NDFA& a1, const NDFA& a2) {	
	NDFA res(a1);

	// Get the maximal index for a state in the second automaton 
	size_t size1 = a1._allStates.getSize();
	size_t size2 = a2._allStates.getSize();

	// Copy states 
	for (int i = 0; i < size2; i++) {
		res._allStates.pushBack(State());
		size_t newStateInd = res._allStates.getSize() - 1;
		for (int j = 0; j < a2._allStates[i].getNumberOfTransitions(); j++) {
			res._allStates[newStateInd].addTransition(a2._allStates[i][j].getFirst(), a2._allStates[i][j].getSecond() + size1);
		}
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

// The result of creating an union automaton is like "putting the automata next to each other"
NDFA Union(NDFA&& a1, NDFA&& a2) {
	size_t size1 = a1._allStates.getSize();

	NDFA res(std::move(a1));

	// Get the maximal index for a state in the second automaton 
	size_t size2 = a2._allStates.getSize();

	// Copy states 
	for (int i = 0; i < size2; i++) {
		res._allStates.pushBack(State());
		size_t newStateInd = res._allStates.getSize() - 1;

		for (int j = 0; j < a2._allStates[i].getNumberOfTransitions(); j++) {
			res._allStates[newStateInd].addTransition(a2._allStates[i][j].getFirst(), a2._allStates[i][j].getSecond() + size1);
		}
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
	bool acceptEpsilon = a2.accept(&EPSILON); 
	size_t indexingStart = a1._allStates.getSize(); // change the indices of the states of the second automaton 

	size_t secondAutomatonInitialCount = a2._initialStates.getSize(); // to remove the states of the second automaton as initial 
	size_t firstAutomatonFinalCount = a1._finalStates.getSize(); // to remove final states of the first automaton if necessary 

	// "Put the automata next to each other"
	NDFA res(Union(std::move(a1), std::move(a2)));

	// Add all outgoing transitions from start states of the second automaton to the end states of the first automaton 

	for (int i = 0; i < a2._initialStates.getSize(); i++) { // For all initial states of the second automaton 
		// The index of the current initial state in the array of states 
		int initialStateInd = a2._initialStates[i]; 

		// All outgoing transitions of the current state 
		for (int j = 0; j < a2._allStates[initialStateInd].getNumberOfTransitions(); j++) {

			// All final states of the first automaton 
			for (int k = 0; k < firstAutomatonFinalCount; k++) {

				// The index of the current final state in the array of states 
				int finalInd = res._finalStates[k];
				
				res._allStates[finalInd].addTransition(a2._allStates[initialStateInd][j].getFirst(), a2._allStates[initialStateInd][j].getSecond() + indexingStart);
			}
		}
	}

	// Remove the states of the second automaton as initial 
	for (int i = 0; i < secondAutomatonInitialCount; i++) {
		res._initialStates.popBack();
	}
	
	// Remove the states of the first automaton as final if needed 
	if (!acceptEpsilon) {
		for (int i = 0; i < firstAutomatonFinalCount; i++) {
			res._finalStates.erase(i);
		}
	}

	return res;
}

NDFA concatenation(const NDFA& a1, const NDFA& a2) {
	size_t indexingStart = a1._allStates.getSize();
	size_t secondAutomatonInitialCount = a2._initialStates.getSize(); // to remove the states of the second automaton as initial 
	size_t firstAutomatonFinalCount = a1._finalStates.getSize(); // to remove the states of the second automaton as initial 

	// "Put the automata next to each other"
	NDFA res(Union(a1, a2));

	// Add all outgoing transitions from start states of the second automatons to the end states of the first automaton 

	// All initial states of the second automaton 
	for (int i = 0; i < a2._initialStates.getSize(); i++) {
		// The index of the current initial state in the array of states 
		int initialStateInd = a2._initialStates[i];

		// All outgoing transitions of the current state 
		for (int j = 0; j < a2._allStates[initialStateInd].getNumberOfTransitions(); j++) {

			// All final states of the first automaton 
			for (int k = 0; k < firstAutomatonFinalCount; k++) {

				// The index of the current final state in the array of states 
				int finalInd = res._finalStates[k];

				res._allStates[finalInd].addTransition(a2._allStates[initialStateInd][j].getFirst(), a2._allStates[initialStateInd][j].getSecond() + indexingStart);
			}
		}
	}

	// Remove the states of the second automaton as initial
	for (int i = 0; i < secondAutomatonInitialCount; i++) {
		res._initialStates.popBack();
	}

	// Remove the states of the first automaton as final if needed 
	if (!a2.accept(&EPSILON)) {
		for (int i = 0; i < firstAutomatonFinalCount; i++) {
			res._finalStates.popBack();
		}
	}

	return res;
}

NDFA kleeneStar(const NDFA& a) {
	NDFA copyA(a);
	// Add a new state
	copyA._allStates.pushBack(State());
	size_t indexInArr = copyA._allStates.getSize() - 1; // index of the new state 

	copyA._finalStates.pushBack(indexInArr); // add the new state as final 

	// Copy all outgoing transitions of initial states from the old automaton for the final states. 
	for (int i = 0; i < copyA._initialStates.getSize(); i++) { // for all initial states 
		size_t initialInd = copyA._initialStates[i]; 

		for (int j = 0; j < copyA._allStates[initialInd].getNumberOfTransitions(); j++) { // for each transition of the current initial state
			for (int k = 0; k < copyA._finalStates.getSize(); k++) { // for all final states 
				size_t finalInd = copyA._finalStates[k];

				// Copy the current transition of the current intial state for the current final state 
				copyA._allStates[finalInd].addTransition(copyA._allStates[initialInd][j].getFirst(), copyA._allStates[initialInd][j].getSecond());
			}
		}
	}

	// Remove all other initial states as initial states 
	copyA._initialStates.clear();

	// Add the new state as copyA final and initial state 
	copyA._initialStates.pushBack(indexInArr);

	return copyA;
}

NDFA getAutomatonForRegEx(MyString regEx){
	RegExCalculator calc(regEx);
	return calc.buildAutomaton(); 
}

// This function will only be used to call the overload isReachable(fromInd, stateInd) for all start states 
bool NDFA::isReachable(size_t stateInd) const{
	for (int i = 0; i < _initialStates.getSize(); i++) {
		// Initial states are reachable in 0 steps 
		if (_initialStates[i] == stateInd || isReachable(_initialStates[i], stateInd)) {
			return true;
		}
	}
	return false;
}

bool NDFA::isReachable(size_t fromInd, size_t destInd) const{
	// A state qj is reachable from a state qi if there exists a natural number n: 
	// qj is reachable from qi in n steps 

	// Make a list of all states reachable from the fromState 
	// Using a bool array isn't optimal in terms of memory because a bool only uses 1 bit out of 8 
	// However, for the sake of simplicity, I am going to use a bool array 
	size_t reachableCount = 1;
	size_t arrSize = _allStates.getSize();
	bool* reachable = new bool[arrSize] { false };

	// The fromState is reachable from itself in 0 steps 
	reachable[fromInd] = 1; 

	// This loop will repeat n times 
	while(1){
		// This flag is used to indicate whether a new state was added to the reachable list 
		bool flag = 0; 

		// Go through all states in the reachable array 
		for (int i = 0; i < arrSize; i++) {
			// Skip the states that are still unreachable 
			if (!reachable[i]) {
				continue;
			}
			// For each states that is reachable, add the destination states from all one step transitions as reachable. A destination state is qj in (qi, x) = qj 
			for (int j = 0; j < _allStates[i].getNumberOfTransitions(); j++) {

				// If we are about to add a state that wasn't in the array initially 
				if (!reachable[_allStates[i][j].getSecond()]) {
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

	bool isReachable = reachable[destInd];

	delete[] reachable;

	return isReachable;
}

void NDFA::print() const {
	std::cout << "Indices of all states:" << std::endl;
	for (int i = 0; i < _allStates.getSize(); i++) {
		std::cout << i << " "; 
	}
	std::cout << std::endl; 

	std::cout << "Indices of initial states:" << std::endl;
	for (int i = 0; i < _initialStates.getSize(); i++) {
		std::cout << _initialStates[i] << " "; 
	}
	std::cout << std::endl << std::endl; 

	std::cout << "Indices of final states:" << std::endl;
	for (int i = 0; i < _finalStates.getSize(); i++) {
		std::cout << _finalStates[i] << " ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Transitions:\n";

	for (int i = 0; i < _allStates.getSize(); i++) {
		std::cout << "Current state: " << i << " "; 
		_allStates[i].print();
		std::cout << "\n";
	}
	std::cout << std::endl << std::endl;
}

void NDFA::removeUnreachableStates() {
	for (int i = 0; i < _allStates.getSize(); i++) {
		if (!isReachable(i)) {
			// Remove the unreachable state from the array of states 
			_allStates.erase(i);

			// Erase the unreachable state from the list of final states if it's in it 
			for (int j = 0; j < _finalStates.getSize(); j++) {
				if (_finalStates[j] == i) {
					_finalStates.erase(j);
				}
				// Decrement the indices of states with an index greater than the unreachable state's 
				else if (_finalStates[j] > i) {
					_finalStates[j]--;
				}
			}

			for (int j = 0; j < _initialStates.getSize(); j++) {
				// Decrement the indices of states with an index greater than the unreachable state's 
				if (_initialStates[j] > i) {
					_initialStates[j]--;
				}
			}

			// For all remaining states 
			for (int j = 0; j < _allStates.getSize(); j++) {

				for (int k = 0; k < _allStates[j].getNumberOfTransitions(); k++) { // for all transitions
					// Decrement destination indices that are higher than the unreachable state's 
					if (_allStates[j][k].getSecond() > i) {
						_allStates[j][k].setSecond(_allStates[j][k].getSecond() - 1);
					}
					// Remove transitions to the removed state 
					else if (_allStates[j][k].getSecond() == i) {
						_allStates[j]._arr.erase(k);
					}
				}
				
			}
		}
	}
}




