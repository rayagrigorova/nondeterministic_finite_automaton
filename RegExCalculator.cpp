#include "RegExCalculator.h"
#include "ValidOperations.h"

#include "SymbolConstants.h"

#include "NullSet.h"
#include "Epsilon.h"
#include "Letter.h"
#include "BinaryOperation.h"
#include "UnaryOperation.h"

bool RegExCalculator::isOperation(char ch) const {
	return ch == KLEENE_STAR || ch == CONCATENATION || ch == UNION; 
}

void  RegExCalculator::copyFrom(const RegExCalculator& other) {
	_expr = other._expr->clone();
}

void  RegExCalculator::free() {
	delete _expr;
	_expr = nullptr;
}

void  RegExCalculator::moveFrom(RegExCalculator&& other) {
	_expr = other._expr;
	other._expr = nullptr;
}

RegExCalculator::RegExCalculator(const RegExCalculator& other) {
	copyFrom(other);
}

RegExCalculator::RegExCalculator(RegExCalculator&& other) noexcept{
	moveFrom(std::move(other)); 
}

RegExCalculator& RegExCalculator::operator=(const RegExCalculator& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this; 
}

RegExCalculator& RegExCalculator::operator=(RegExCalculator&& other) noexcept{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

RegExCalculator::~RegExCalculator() {
	free();
}

RegExCalculator::RegExCalculator(const MyString& str) {
	_expr = parseExpr(str); 
}

NDFA RegExCalculator::buildAutomaton() {
	return _expr->buildAutomatonForLanguage(); 
}

RegEx* RegExCalculator::parseExpr(const StringView& str) {
	if (str.length() == 0) {
		switch (str[0]) {
		case NULL_SET:
			return new NullSet(); 
		case EPSILON:
			return new Epsilon(); 
		default:
			return new Letter(str[0]);
		}
	}

	int count = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			count++;
		}
		else if (str[i] == '(') {
			count--;
		}

		else if (count == 0 && isOperation(str[i])) {
			if (str[i] == KLEENE_STAR) {
				return new UnaryOperation(parseExpr(str.substr(0, i - 1)), KLEENE_STAR); 
			}
			else {
				return new BinaryOperation(parseExpr(str.substr(0, i - 1)), parseExpr(str.substr(i + 1, str.length() - i - 1)), str[i]); 
			}
		}
	}
}
