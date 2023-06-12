#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(RegEx* expr, char op) : _expr(expr), _op(op){

}

// Valid unary operation: '*' 
NDFA UnaryOperation::buildAutomatonForLanguage() const {
	//switch (_op) {
	//case '*':
	//	return kleeneStar(_expr->buildAutomatonForLanguage());
	//}

	if (_op == '*') {
		NDFA res = kleeneStar(_expr->buildAutomatonForLanguage()); 
		return res;
	}
}

RegEx* UnaryOperation::clone() const {
	return new UnaryOperation(*this); 
}

UnaryOperation::~UnaryOperation() {
	delete _expr;
}

void UnaryOperation::print() const {
	std::cout << "Operation: " << _op << std::endl; 
	_expr->print(); 
}