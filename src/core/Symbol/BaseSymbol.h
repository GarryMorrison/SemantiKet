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
#include "Symbol.h"


class Type;

class BaseSymbol {
public:
	std::string name;
	Type *type = nullptr;
	SKet::Parser::token_type ttype = SKet::Parser::token_type::UNKNOWN;
	Symbol::SType stype = Symbol::SType::Base;
	// bool is_const = false;
	// std::vector<int> line_numbers;

	BaseSymbol() {};
	BaseSymbol(const std::string &name) { this->name = name; }
	BaseSymbol(const std::string& name, Type* type) { this->name = name; this->type = type; }
	BaseSymbol(const std::string& name, SKet::Parser::token_type type) { this->name = name; this->ttype = type; }

	static BaseSymbol* Construct(SKet::yyTOKEN tok);

	// Symbol(const std::string& name, Type* type, bool is_const) { this->name = name; this->type = type; this->is_const = is_const; }
	// Symbol(const std::string& name, Type* type, bool is_const, int line);
	virtual std::string getName() { return name; }
	void setType(Type* type) { this->type = type; }
	Type* getType() { return type; }
	virtual std::string to_string();
	virtual void appendLine(int line) {};  // Looks like we need this here in Symbol
	virtual std::set<int> getLines() { std::set<int> empty_set; return empty_set; } // This too
};

class Type : public BaseSymbol {  // Need SType?
public:
	Type() {};
	Type(const std::string &name) : BaseSymbol(name) {};
};

class BuiltInType : public Type {  // Need SType?
public:
	BuiltInType(const std::string& name) : Type(name) {}
};


