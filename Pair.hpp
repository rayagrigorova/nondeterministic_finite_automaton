#pragma once

template <typename T, typename S>
class Pair {
	T _first;
	S _second;

public:
	Pair(const T& first, const S& second);

	void setFirst(const T& first);
	void setSecond(const S& second);

	const T& getFirst() const;
	const S& getSecond() const;
};

template <typename T, typename S>
Pair<T, S>::Pair(const T& first, const S& second) : _first(first), _second(second){

}

template <typename T, typename S>
void Pair<T, S>::setFirst(const T& first) {
	_first = first;
}

template <typename T, typename S>
void Pair<T, S>::setSecond(const S& second) {
	_second = second;
}

template <typename T, typename S>
const T& Pair<T, S>::getFirst() const {
	return _first;
}

template <typename T, typename S>
const S& Pair<T, S>::getSecond() const {
	return _second;
}