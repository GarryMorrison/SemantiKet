#pragma once

// Author: Garry Morrison
// Added: 2023-10-11
// Updated: 2023-10-11

#include "Symbol.h"
#include "BaseSymbol.h"
// class BaseSymbol;

class VariableSymbol : public BaseSymbol {
public:
	Symbol::SType stype = Symbol::SType::Variable;
	bool is_const = false;
	std::set<int> line_numbers;

	VariableSymbol(const std::string& name) : BaseSymbol(name) {};

	// version 1 types:
	VariableSymbol(const std::string& name, Type* type) : BaseSymbol(name, type) {};
	VariableSymbol(const std::string& name, Type* type, bool is_const) : BaseSymbol(name, type) { this->is_const = is_const; };
	VariableSymbol(const std::string& name, Type* type, bool is_const, int line) : BaseSymbol(name, type) { this->is_const = is_const; this->line_numbers.insert(line); };

	// version 2 types:
	VariableSymbol(const std::string& name, SKet::Parser::token_type type) : BaseSymbol(name, type) {};
	VariableSymbol(const std::string& name, SKet::Parser::token_type type, bool is_const) : BaseSymbol(name, type) { this->is_const = is_const; };
	VariableSymbol(const std::string& name, SKet::Parser::token_type type, bool is_const, int line) : BaseSymbol(name, type) { this->is_const = is_const; this->line_numbers.insert(line); };

	// token version:
	// VariableSymbol(SKet::yyTOKEN tok) : Symbol(tok.text, tok.code) { line_numbers.insert(tok.line); }
	VariableSymbol(SKet::yyTOKEN tok);

	void appendLine(int line) { line_numbers.insert(line); }  // do we need this method in Symbol too?
	std::set<int> getLines() { return line_numbers; }

	std::string to_string() override;
};
