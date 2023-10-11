#pragma once

// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

// namespace SKet or not?

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "BaseSymbol.h"
#include "../misc/misc.h"


class Scope {
public:
	virtual std::string getScopeName() = 0;
	virtual Scope* getEnclosingScope() = 0;
	virtual void addChild(Scope*) = 0;
	virtual std::vector<Scope*> getChildScopes() = 0;
	virtual void define(BaseSymbol *sym) = 0;
	virtual BaseSymbol* resolve(const std::string& name) = 0;
	virtual std::string to_string() = 0;
	virtual std::string to_string(int level) = 0;
};

class SymbolTable : public Scope { // derive more classes from this!
public:
	std::string name;
	Scope* parent_scope = nullptr;
	size_t nkids = 0;
	std::vector<Scope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	SymbolTable() { initTypeSystem(); }
	SymbolTable(Scope* scope) : SymbolTable("local", scope) {}; // only empty constructor initiates the type system
	SymbolTable(const std::string& name) { this->name = name; } // ditto
	SymbolTable(const std::string& name, Scope* scope); // ditto
	void initTypeSystem();

	// satisfy scope interface:
	std::string getScopeName(); 
	Scope* getEnclosingScope() { return parent_scope; }
	void addChild(Scope* sc);
	std::vector<Scope*> getChildScopes() { return kids; }
	void define(BaseSymbol* sym);
	BaseSymbol* resolve(const std::string& name);
	std::string to_string() { return this->to_string(1); }
	std::string to_string(int level);

};