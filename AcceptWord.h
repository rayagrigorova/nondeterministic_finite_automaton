#pragma once

#include "SingleCommand.h"

class AcceptWord : public SingleCommand {
public:
	AcceptWord(NDFA* a) : SingleCommand(a) {}

	void execute(std::ostream& os) override {
		std::cout << "Enter a word:\n";

		char buff[250];
		std::cin >> buff;
		std::cout << "\n";

		if (_a->accept(buff)) {
			std::cout << "Accepted\n";
		}
		else {
			std::cout << "Not accepted\n";
		}
	}
};