#pragma once

#include "SingleCommand.h"

class AcceptWord : public SingleCommand {
public:
	AcceptWord(NDFA* a) : SingleCommand(a) {}

	void execute(std::istream& is, std::ostream& os) override {
		os << "Enter a word:\n";

		char buff[250];
		is >> buff;
		os << "\n";

		if (_a->accept(buff)) {
			os << "Accepted\n\n";
		}
		else {
			os << "Not accepted\n\n";
		}
	}
};