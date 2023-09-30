#pragma once

// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

// namespace SKet or not?
#include <string>
#include <vector>

class Type;

class Symbol {
public:
	std::string name;
	Type *type = nullptr;
	bool is_const = false;
	std::vector<int> line_numbers;

	Symbol() {};
	Symbol(const std::string &name) { this->name = name; }
	Symbol(const std::string& name, Type* type) { this->name = name; this->type = type; }
	Symbol(const std::string& name, Type* type, bool is_const) { this->name = name; this->type = type; this->is_const = is_const; }
	Symbol(const std::string& name, Type* type, bool is_const, int line);
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
	VariableSymbol(const std::string& name, Type* type, bool is_const) : Symbol(name, type, is_const) {};
	VariableSymbol(const std::string& name, Type* type, bool is_const, int line) : Symbol(name, type, is_const, line) {};
};
