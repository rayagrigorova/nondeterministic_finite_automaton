#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(RegEx* lhs, RegEx* rhs, char op)
	: _lhs(lhs), _rhs(rhs), _op(op) {

}

// Valid binary operations: '+', '.'
NDFA BinaryOperation::buildAutomatonForLanguage() const {
	if (_op == '+') {
		NDFA res = Union(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
		return res; 
	}
	else {
		NDFA res = concatenation(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
		return res;
	}
	//switch (_op) {
	//case '+':
	//	return Union(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
	//case '.':
	//	return concatenation(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
	//}
}

RegEx* BinaryOperation::clone() const {
	return new BinaryOperation(*this); 
}

BinaryOperation::~BinaryOperation() {
	delete _lhs;
	delete _rhs; 
}

void BinaryOperation::print() const {
	std::cout << "Operation: " << _op << std::endl;
	_rhs->print();
	_lhs->print();
}
