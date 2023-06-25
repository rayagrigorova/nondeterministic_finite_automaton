#include "State.h"
#include <fstream>

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

void State::print(std::ostream& os) const {
	for (int i = 0; i < _arr.getSize(); i++) {
		os << "Letter: " << _arr[i].getFirst() << " Destination state: " << _arr[i].getSecond() << "\n";
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

bool State::hasTransition(char ch, size_t destInd) {
	for (int i = 0; i < _arr.getSize(); i++) {
		if (_arr[i].getFirst() == ch && _arr[i].getSecond() == destInd) {
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const State& s) {
	return os << s._arr;
}

std::istream& operator>>(std::istream& is, State& s) {
	return is >> s._arr;
}
