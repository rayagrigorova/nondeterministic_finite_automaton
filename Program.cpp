#include "Program.h"

#include "Command.h"
#include "CommandFactory.h"

Program& Program::getInstance() const {
	static Program p;
	return p;
}

void Program::run() {
	while (1) {
		Command* toExecute = commandFactory(_arr);
		toExecute->execute(std::cout);
	}
}