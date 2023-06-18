#pragma once

#include <fstream>

// Necessary because template friends cause linker errors otherwise
template<typename T, typename S> class Pair;
template<typename T, typename S> std::ostream& operator<<(std::ostream& os, const Pair<T, S>& p);
template<typename T, typename S> std::istream& operator>>(std::istream& is, Pair<T, S>& p);

template <typename T, typename S>
class Pair {
	T _first;
	S _second;

public:
	Pair() = default;
	Pair(const T& first, const S& second);

	void setFirst(const T& first);
	void setSecond(const S& second);

	const T& getFirst() const;
	const S& getSecond() const;

	friend std::ostream& operator<< <>(std::ostream& os, const Pair<T, S>& p);
	friend std::istream& operator>> <>(std::istream& is, Pair<T, S>& p);
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

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const Pair<T, S>& p){
	return os << ' ' << p.getFirst() << ' ' << p.getSecond();
}

template <typename T, typename S>
std::istream& operator>>(std::istream& is, Pair<T, S>& p) {
	is.get(); // skip space 

	T obj;
	is >> obj; 
	p.setFirst(obj);

	is.get(); // skip space 

	S obj2;
	is >> obj2;
	p.setSecond(obj2);

	return is;
};

