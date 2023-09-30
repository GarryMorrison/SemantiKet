#pragma once

// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

// namespace SKet or not?

#include <iostream>
#include <string>
#include <map>
#include "Symbol.h"


class Scope {
public:
	virtual std::string getScopeName() = 0;
	virtual Scope* getEnclosingScope() = 0;
	virtual void define(Symbol *sym) = 0;
	virtual Symbol* resolve(const std::string& name) = 0;
};

class SymbolTable : public Scope { // single scope symtab
public:
	std::map<std::string, Symbol*> symbols;
	SymbolTable() { initTypeSystem(); }
	void initTypeSystem() {
		define(new BuiltInType("ket"));
		define(new BuiltInType("sp"));
		define(new BuiltInType("seq"));
	}

	// satisfy scope interface:
	std::string getScopeName() { return "global"; }
	Scope* getEnclosingScope() { return nullptr; }
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
		if (symbols.find(name) == symbols.end())
		{
			return nullptr;
		}
		else
		{
			return symbols[name];
		}
	}

	std::string to_string() {
		std::string s;
		s = "  " + getScopeName() + ":\n";
		
		for (const auto& elt : symbols)
		{
			if (elt.second)
			{
				s += "    " + elt.second->to_string() + "\n";
			}
		}
		
		return s;
	}
};