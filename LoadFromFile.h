#pragma once

#include "SingleCommand.h"

class LoadFromFile : public AddCommand {
public:
	LoadFromFile(DynamicArray<NDFA>* arr) : AddCommand(arr) {}

	void execute(std::istream& is, std::ostream& os) override {
		std::cout << "Enter the name of the file:\n";

		char buff[250];
		std::cin >> buff;

		std::ifstream file(buff, std::ios::binary);

		if (!file.is_open()) {
			throw std::logic_error("Error opening file\n");
		}

		//NDFA res;
		//res.readFromBinaryFile(file);
		//_arr->pushBack(std::move(res));

	}
};
