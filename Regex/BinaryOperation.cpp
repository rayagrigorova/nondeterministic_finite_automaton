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

	else if(_op == '.'){
		NDFA res = concatenation(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
		return res;
	}

	else {
		throw std::invalid_argument("Error\n");
	}
}

RegEx* BinaryOperation::clone() const {
	return new BinaryOperation(*this); 
}

BinaryOperation::~BinaryOperation() {
	delete _lhs;
	delete _rhs; 

	_lhs = _rhs = nullptr;
}

void BinaryOperation::print() const {
	_rhs->print();
	std::cout << ' ' << _op << ' ';
	_lhs->print();
}

void BinaryOperation::setRhs(RegEx* rhs){
	delete _rhs;
	_rhs = rhs;
}

void BinaryOperation::setLhs(RegEx* lhs) {
	delete _lhs;
	_lhs = lhs;
}

const RegEx* BinaryOperation::getRhs() const {
	return _rhs;
}

const RegEx* BinaryOperation::getLhs() const {
	return _lhs;
}

MyString BinaryOperation::toString() const{
	return _lhs->toString() + " " + &_op + " " + _rhs->toString();
}
