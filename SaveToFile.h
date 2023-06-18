#pragma once

#include "SingleCommand.h"

class SaveToFile : public SingleCommand {
public:
	SaveToFile(NDFA* a) : SingleCommand(a){}

	void execute(std::istream& is, std::ostream& os) override {
		std::cout << "Enter the name of the file:\n";

		char buff[250];
		std::cin >> buff;

		std::ofstream file(buff, std::ios::binary);

		if (!file.is_open()) {
			throw std::logic_error("Error opening file\n");
		}

		//_a->saveToBinaryFile(file);

	}
};