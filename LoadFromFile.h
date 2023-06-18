#pragma once

#include "SingleCommand.h"

class LoadFromFile : public AddCommand {
public:
	LoadFromFile(DynamicArray<NDFA>* arr) : AddCommand(arr) {}

	void execute(std::istream& is, std::ostream& os) override {
		std::cout << "Enter the name of the file:\n";

		char buff[250];
		std::cin >> buff;

		NDFA a;
		a.loadFromFile(buff);
		_arr->pushBack(std::move(a));

	}
};
