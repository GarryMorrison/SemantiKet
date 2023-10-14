#pragma once

// Author: Garry Morrison
// Added: 2023-10-14
// Updated: 2023-10-14

#include "Symbol.h"
#include "BaseSymbol.h"

class ConstantSymbol : public BaseSymbol {
public:
	Symbol::SType stype = Symbol::SType::Constant;
	bool is_const = true;
	std::set<int> line_numbers;

	ConstantSymbol(SKet::yyTOKEN tok);

	void appendLine(int line) { line_numbers.insert(line); }  // do we need this method in Symbol too?
	std::set<int> getLines() { return line_numbers; }

	std::string to_string() override;
};