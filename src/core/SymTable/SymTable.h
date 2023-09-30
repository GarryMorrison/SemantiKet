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
	Scope* parent_scope;
	std::map<std::string, Symbol*> symbols;
	SymbolTable() { initTypeSystem(); }
	SymbolTable(const std::string& name) { this->name = name; }
	SymbolTable(const std::string& name, Scope* scope) { this->name = name; this->parent_scope = scope; }
	void initTypeSystem() {
		define(new BuiltInType("ket"));
		define(new BuiltInType("sp"));
		define(new BuiltInType("seq"));
	}

	// satisfy scope interface:
	std::string getScopeName() { 
		if (name.empty())
		{
			return "global"; // default scope name is "global"
		}
		else
		{
			return name;
		}
	}
	Scope* getEnclosingScope() { return parent_scope; }
	void define(Symbol *sym) { 
		if (sym)
		{
			if (!sym->name.empty())
			{
				symbols[sym->name] = sym;
			}
		}
	}
	Symbol* resolve(const std::string& name)
	{
		if (symbols.find(name) == symbols.end())  // look in parent scope too!
		{
			return nullptr;
		}
		else
		{
			return symbols[name];
		}
	}

	std::string to_string() { return this->to_string(1); }

	std::string to_string(int level) {
		std::string s;
		s = indent(2 * level) + getScopeName() + ":\n";
		for (const auto& elt : symbols)
		{
			if (elt.second)
			{
				s += indent(2 * level + 2) + elt.second->to_string() + "\n";
			}
		}
		Scope *parent = getEnclosingScope();
		if (parent)
		{
			s += parent->to_string(level + 1);
		}
		return s;
	}
};