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


class BaseScope {
public:
	virtual std::string getScopeName() = 0;
	virtual BaseScope* getEnclosingScope() = 0;
	virtual void addChild(BaseScope*) = 0;
	virtual std::vector<BaseScope*> getChildScopes() = 0;
	virtual void define(BaseSymbol *sym) = 0;
	virtual BaseSymbol* resolve(const std::string& name) = 0;
	virtual std::string to_string() = 0;
	virtual std::string to_string(int level) = 0;
};

class SymbolTable : public BaseScope { // derive more classes from this!
public:
	std::string name;
	BaseScope* parent_scope = nullptr;
	size_t nkids = 0;
	std::vector<BaseScope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	SymbolTable() { initTypeSystem(); }
	SymbolTable(BaseScope* scope) : SymbolTable("local", scope) {}; // only empty constructor initiates the type system
	SymbolTable(const std::string& name) { this->name = name; } // ditto
	SymbolTable(const std::string& name, BaseScope* scope); // ditto
	void initTypeSystem();

	// satisfy scope interface:
	std::string getScopeName(); 
	BaseScope* getEnclosingScope() { return parent_scope; }
	void addChild(BaseScope* sc);
	std::vector<BaseScope*> getChildScopes() { return kids; }
	void define(BaseSymbol* sym);
	BaseSymbol* resolve(const std::string& name);
	std::string to_string() { return this->to_string(1); }
	std::string to_string(int level);

};