#pragma once

// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

// namespace SKet or not?
#include <string>

class Type;

class Symbol {
public:
	std::string name;
	Type *type;

	Symbol() {};
	Symbol(const std::string &name) { this->name = name; }
	Symbol(const std::string& name, Type* type) { this->name = name; this->type = type; }
	std::string getName() { return name; }
	std::string to_string();
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
	VariableSymbol(const std::string& name) : Symbol(name) {};
	VariableSymbol(const std::string& name, Type *type) : Symbol(name, type) {};
};
