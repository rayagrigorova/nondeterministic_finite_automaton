#pragma once

#include "NDFA.h"

class Program {
	DynamicArray<NDFA> _arr;

	Program() = default;

public:
	Program(const Program& other) = delete;
	Program& operator=(const Program& other) = delete;

	static Program& getInstance();

	void run();
};