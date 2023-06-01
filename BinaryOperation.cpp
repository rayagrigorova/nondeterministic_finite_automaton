#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(RegEx* lhs, RegEx* rhs, char op)
	: _lhs(lhs), _rhs(rhs), _op(op) {

}

// Valid binary operations: '+', '.'
NDFA BinaryOperation::buildAutomatonForLanguage() const {
	switch (_op) {
	case '+':
		return Union(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
	case '.':
		return concatenation(_lhs->buildAutomatonForLanguage(), _rhs->buildAutomatonForLanguage());
	}
}
