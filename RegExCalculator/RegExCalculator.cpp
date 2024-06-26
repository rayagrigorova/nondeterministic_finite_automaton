#include "RegExCalculator.h"

#include "../Constants/ValidOperations.h"
#include "../Constants/SymbolConstants.h"

#include "../Regex/NullSet.h"
#include "../Regex/Epsilon.h"
#include "../Regex/Letter.h"
#include "../Regex/BinaryOperation.h"
#include "../Regex/UnaryOperation.h"

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

const RegEx* RegExCalculator::getRegEx() const {
	return _expr;
}

RegEx* RegExCalculator::parseExpr(const StringView& str) {
	if (str.length() == 1) {
		switch (str[0]) {
		case NULL_SET:
			return new NullSet(); 
		case EPSILON:
			return new Epsilon(); 
		default:
			return new Letter(str[0]);
		}
	}
	
	// Remove the first and the last symbol of the string (brackets)
	StringView withoutBrackets = str.substr(1, str.length() - 2);

	int count = 0;

	for (int i = 0; i < withoutBrackets.length(); i++) {
		if (withoutBrackets[i] == '(') {
			count++;
		}
		else if (withoutBrackets[i] == ')') {
			count--;
		}

		else if (count == 0 && isOperation(withoutBrackets[i])) {
			if (withoutBrackets[i] == KLEENE_STAR) {
				return new UnaryOperation(parseExpr(withoutBrackets.substr(1, withoutBrackets.length() - 3)), KLEENE_STAR);
			}
			else {
				return new BinaryOperation(parseExpr(withoutBrackets.substr(0, i)), parseExpr(withoutBrackets.substr(i + 1, withoutBrackets.length() - i - 1)), withoutBrackets[i]);
			}
		}
	}
	throw std::invalid_argument("Invalid regex\n"); 
}
