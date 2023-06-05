#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(RegEx* expr, char op) : _expr(expr), _op(op){

}

// Valid unary operation: '*' 
NDFA UnaryOperation::buildAutomatonForLanguage() const {
	switch (_op) {
	case '*':
		return kleeneStar(_expr->buildAutomatonForLanguage());
	}
}

RegEx* UnaryOperation::clone() const {
	return new UnaryOperation(*this); 
}

UnaryOperation::~UnaryOperation() {
	delete _expr;
}