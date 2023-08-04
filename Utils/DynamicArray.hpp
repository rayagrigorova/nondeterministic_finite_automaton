#pragma once

#include <iostream>
#include <fstream>

// Necessary because template friends cause linker errors otherwise
template<typename T> class DynamicArray;  
template<typename T> std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& a);
template<typename T> std::istream& operator>>(std::istream& is, DynamicArray<T>& a); 

// Source: https://github.com/Angeld55/Object-oriented_programming_FMI/tree/master/Week%2009/DynamicArrayOfA%20(with%20move)

template <typename T>
class DynamicArray {
	T* arr;
	size_t size;
	size_t capacity;
	void moveFrom(DynamicArray&& other);

	void copyFrom(const DynamicArray& other);
	void free();
	void resize(size_t newCap);

public:
	DynamicArray();
	DynamicArray(size_t capacity);
	DynamicArray(const DynamicArray& other);
	DynamicArray& operator=(const DynamicArray& other);
	~DynamicArray();

	DynamicArray(DynamicArray&& other) noexcept;
	DynamicArray& operator=(DynamicArray&& other) noexcept;

	void pushBack(const T& newElem); //add a new element in the end
	void pushBack(T&& newElem); //add a new element in the end

	void popBack(); //removes the last element

	void setAtIndex(const T& element, size_t index);
	void setAtIndex(T&& element, size_t index);

	size_t getSize() const;
	bool isEmpty() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	void erase(size_t pos);
	void clear(); // erase all elements from the vector and leave it with a size of 0 

	friend std::ostream& operator<< <>(std::ostream& os, const DynamicArray<T>& a);
	friend std::istream& operator>> <>(std::istream& is, DynamicArray<T>& a);

};

template <typename T>
DynamicArray<T>::DynamicArray() : DynamicArray(8) {}

static size_t closestPowerOfAwo(size_t n)
{
	n--;

	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	n |= n >> 32;

	return n + 1;
};

template <typename T>
DynamicArray<T>::DynamicArray(size_t capacity) : size(0)
{
	this->capacity = closestPowerOfAwo(capacity);
	arr = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
	copyFrom(other);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
	free();
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
{
	moveFrom(std::move(other));
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
void DynamicArray<T>::copyFrom(const DynamicArray& other)
{
	arr = new T[other.capacity];

	for (size_t i = 0; i < other.size; i++)
		arr[i] = other.arr[i];

	size = other.size;
	capacity = other.capacity;
}

template <typename T>
void DynamicArray<T>::moveFrom(DynamicArray&& other)
{
	arr = other.arr;
	other.arr = nullptr;

	capacity = other.capacity;
	size = other.size;

	other.capacity = other.size = 0;
}

template <typename T>
void DynamicArray<T>::free()
{
	delete[] arr;
	arr = nullptr;
}

template <typename T>
void DynamicArray<T>::resize(size_t newCap)
{
	T* temp = new T[newCap];

	for (size_t i = 0; i < size; i++)
		temp[i] = arr[i];

	capacity = newCap;
	delete[] arr;
	arr = temp;
}

template <typename T>
void  DynamicArray<T>::pushBack(const T& newElem)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = newElem;
}

template <typename T>
void  DynamicArray<T>::pushBack(T&& newElem)
{
	if (size >= capacity)
		resize(capacity * 2);

	arr[size++] = std::move(newElem); //move op =
}

template <typename T>
void  DynamicArray<T>::popBack()
{
	if (size)
		size--;
	else
		throw std::length_error("Already empty!");

	if (size * 4 <= capacity && capacity > 1)
		resize(capacity / 2);
}

template <typename T>
void DynamicArray<T>::setAtIndex(const T& element, size_t index)
{
	if (index >= size)
		throw std::length_error("No such index!");

	arr[index] = element;
}

template <typename T>
void DynamicArray<T>::setAtIndex(T&& element, size_t index)
{
	if (index >= size)
		throw std::length_error("No such index!");

	arr[index] = std::move(element); //move op =
}

template <typename T>
size_t DynamicArray<T>::getSize() const
{
	return size;
}

template <typename T>
bool DynamicArray<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
const T& DynamicArray<T>::operator[](size_t index) const
{
	if (index > size)
		throw std::out_of_range("Out of range!");
	return arr[index];
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index)
{
	if (index > size)
		throw std::out_of_range("Out of range!");
	return arr[index];
}

template <typename T>
void DynamicArray<T>::erase(size_t pos) {
	if (pos >= size) {
		return;
	}

	for (int i = pos; i < size - 1; i++) {
		arr[i] = arr[i + 1];
	}
	size--;
}

template <typename T>
void DynamicArray<T>::clear() {
	size = 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& a){
	os << a.size;

	for (int i = 0; i < a.size; i++) {
		os << ' ' << a.arr[i];
	}

	os << '\n';
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, DynamicArray<T>& a){
	a.clear(); // Remove the old contents of the array

	size_t newSize;
	is >> newSize;

	for (int i = 0; i < newSize; i++) {
		is.get(); // skip space

		T obj;
		is >> obj; 
		 
		a.pushBack(std::move(obj));
	}

	is.get(); // skip the new line symbol
	return is;
}

