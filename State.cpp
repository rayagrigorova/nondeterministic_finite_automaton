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

size_t State::getNumberOfTransitions() const
{
	return size_t();
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