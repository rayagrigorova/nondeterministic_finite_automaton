#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(RegEx* expr, char op) : _expr(expr), _op(op){

}

// Valid unary operation: '*' 
NDFA UnaryOperation::buildAutomatonForLanguage() const {
	if (_op == '*') {
		NDFA res = kleeneStar(_expr->buildAutomatonForLanguage()); 
		return res;
	}
	else {
		throw std::invalid_argument("Error\n"); 
	}
}

RegEx* UnaryOperation::clone() const {
	return new UnaryOperation(*this); 
}

UnaryOperation::~UnaryOperation() {
	delete _expr;
	_expr = nullptr;
}

void UnaryOperation::print() const {
	std::cout << "Operation: " << _op << std::endl; 
	_expr->print(); 
}

MyString UnaryOperation::toString() const {
	return _expr->toString() + " " + &_op; 
}
