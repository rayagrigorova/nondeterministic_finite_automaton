#pragma once

#include "SingleCommand.h"

class SaveToFile : public SingleCommand {
public:
	SaveToFile(NDFA* a) : SingleCommand(a){}

	void execute(std::istream& is, std::ostream& os) override {
		os << "Enter the name of the file:\n";

		char buff[250];
		is >> buff;

		_a->saveToFile(buff); // This line could throw an exception
		
		os << "\nFile saved successfully\n\n"; 
	}
};