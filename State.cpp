#include "State.h"

void State::addTransition(char ch, int state) {
	_arr.pushBack(Pair<char, int>(ch, state));
}

void State::removeAllTransitionsTo(int state) {
	for (int i = 0; i < _arr.getSize(); i++) {
		if (_arr[i].getSecond() == state) {
			_arr.erase(i);
		}
	}
}

const Pair<char, int>& State::operator[](size_t ind) const {
	return _arr[ind];
}

Pair<char, int>& State::operator[](size_t ind) {
	return _arr[ind];
}

size_t State::getNumberOfTransitions() const {
	return _arr.getSize(); 
}

void State::print() const {
	for (int i = 0; i < _arr.getSize(); i++) {
		std::cout << "Letter: " << _arr[i].getFirst() << " Destination state: " << _arr[i].getSecond() << "\n";
	}
}

// This function is intended to work with DFAs
int State::getDestinationState(char ch) const {
	for (int i = 0; i < _arr.getSize(); i++) {
		if (_arr[i].getFirst() == ch) {
			return _arr[i].getSecond();
		}
	}
	return -1;
}