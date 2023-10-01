#pragma once

// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

// namespace SKet or not?
#include <string>
#include <vector>
#include <set>
// #include "../Parser/token.h"
#include "parser.tab.h"
#include "../Parser/token.h"


class Type;

class Symbol {
public:
	std::string name;
	Type *type = nullptr;
	SKet::Parser::token_type ttype = SKet::Parser::token_type::UNKNOWN;
	// bool is_const = false;
	// std::vector<int> line_numbers;

	Symbol() {};
	Symbol(const std::string &name) { this->name = name; }
	Symbol(const std::string& name, Type* type) { this->name = name; this->type = type; }
	Symbol(const std::string& name, SKet::Parser::token_type type) { this->name = name; this->ttype = type; }
	// Symbol(const std::string& name, Type* type, bool is_const) { this->name = name; this->type = type; this->is_const = is_const; }
	// Symbol(const std::string& name, Type* type, bool is_const, int line);
	std::string getName() { return name; }
	virtual std::string to_string();
	virtual void appendLine(int line) {};  // Looks like we need this here in Symbol
};

class Type : public Symbol {
public:
	Type() {};
	Type(const std::string &name) : Symbol(name) {};
};

class BuiltInType : public Type {
public:
	BuiltInType(const std::string& name) : Type(name) {}
};

class VariableSymbol : public Symbol {
public:
	bool is_const = false;
	std::set<int> line_numbers;

	VariableSymbol(const std::string& name) : Symbol(name) {};

	// version 1 types:
	VariableSymbol(const std::string& name, Type *type) : Symbol(name, type) {};
	VariableSymbol(const std::string& name, Type* type, bool is_const) : Symbol(name, type) { this->is_const = is_const; };
	VariableSymbol(const std::string& name, Type* type, bool is_const, int line) : Symbol(name, type) { this->is_const = is_const; this->line_numbers.insert(line); };

	// version 2 types:
	VariableSymbol(const std::string& name, SKet::Parser::token_type type) : Symbol(name, type) {};
	VariableSymbol(const std::string& name, SKet::Parser::token_type type, bool is_const) : Symbol(name, type) { this->is_const = is_const; };
	VariableSymbol(const std::string& name, SKet::Parser::token_type type, bool is_const, int line) : Symbol(name, type) { this->is_const = is_const; this->line_numbers.insert(line); };

	// token version:
	VariableSymbol(SKet::yyTOKEN tok) : Symbol(tok.text, tok.code) { line_numbers.insert(tok.line); }

	void appendLine(int line) { line_numbers.insert(line); }  // do we need this method in Symbol too?

	std::string to_string() override;
};
