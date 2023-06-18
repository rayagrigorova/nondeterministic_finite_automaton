#include "Program.h"

#include "Command.h"
#include "CommandFactory.h"

// Program is a singleton class 
Program& Program::getInstance(){
	static Program p;
	return p;
}

void Program::run() {
	while (1) {
		Command* toExecute = commandFactory(_arr);
		toExecute->execute(std::cout);
	}
}