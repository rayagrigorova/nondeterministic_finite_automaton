#pragma once

#include "Command.h"
#include "DynamicArray.hpp"

// A command that adds something to an array 
class AddCommand : public virtual Command {
protected:
	DynamicArray<NDFA>* _arr;

public:
	AddCommand(DynamicArray<NDFA>* arr) : _arr(arr){}

};