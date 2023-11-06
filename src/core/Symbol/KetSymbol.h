#pragma once

// Author: Garry Morrison
// Added: 2023-10-14
// Updated: 2023-10-14

#include "Symbol.h"
#include "BaseSymbol.h"

class KetSymbol : public BaseSymbol {
public:
	Symbol::SType stype = Symbol::SType::Ket;
	bool is_const = true;
	std::set<int> line_numbers;

	KetSymbol(SKet::yyTOKEN tok);

	void appendLine(int line) { line_numbers.insert(line); }  // do we need this method in Symbol too?
	std::set<int> getLines() { return line_numbers; }

	std::string to_string() override { return to_string(0); }
	std::string to_string(int level);
};