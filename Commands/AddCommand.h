#pragma once

#include "Command.h"
#include "../Utils/DynamicArray.hpp"

// A command that adds something to an array 
// Virtual inheritance to avoid the diamond problem
class AddCommand : public virtual Command {
protected:
	// Non-owning pointer
	DynamicArray<NDFA>* _arr;

public:
	AddCommand(DynamicArray<NDFA>* arr) : _arr(arr){}

	~AddCommand() {
		_arr = nullptr;
	}

};
