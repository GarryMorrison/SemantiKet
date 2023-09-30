#pragma once

// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

// namespace SKet or not?

#include <iostream>
#include <string>
#include <map>
#include "Symbol.h"
#include "../misc/misc.h"


class Scope {
public:
	virtual std::string getScopeName() = 0;
	virtual Scope* getEnclosingScope() = 0;
	virtual void define(Symbol *sym) = 0;
	virtual Symbol* resolve(const std::string& name) = 0;
	virtual std::string to_string() = 0;
	virtual std::string to_string(int level) = 0;
};

class SymbolTable : public Scope { // move the below code to SymTable.cpp
public:
	std::string name;
	Scope* parent_scope = nullptr;
	std::map<std::string, Symbol*> symbols;
	SymbolTable() { initTypeSystem(); }
	SymbolTable(Scope* scope) : SymbolTable("local", scope) {}; // only empty constructor initiates the type system
	SymbolTable(const std::string& name) { this->name = name; } // ditto
	SymbolTable(const std::string& name, Scope* scope) { this->name = name; this->parent_scope = scope; } // ditto
	void initTypeSystem();

	// satisfy scope interface:
	std::string getScopeName(); 
	Scope* getEnclosingScope() { return parent_scope; }
	void define(Symbol* sym); 
	Symbol* resolve(const std::string& name);
	std::string to_string() { return this->to_string(1); }
	std::string to_string(int level);

};