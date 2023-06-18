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
		try {
			Command* toExecute = commandFactory(_arr);
			toExecute->execute(std::cin, std::cout);
		}
		catch (std::exception& e) {
			std::cout << e.what() << "\n"; 
			break;
		}

		//delete toExecute;
	}
}