// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

#include "SymTable.h"

void SymbolTable::initTypeSystem() {  // Add more types here later!
	define(new BuiltInType("ket"));
	define(new BuiltInType("sp"));
	define(new BuiltInType("seq"));
}

std::string SymbolTable::getScopeName() {
	if (name.empty())
	{
		return "global"; // default scope name is "global"
	}
	else
	{
		return name;
	}
}

void SymbolTable::define(Symbol* sym) {
	if (sym)
	{
		if (!sym->name.empty())
		{
			symbols[sym->name] = sym;
		}
	}
}
Symbol* SymbolTable::resolve(const std::string& name)
{
	if (symbols.find(name) == symbols.end())  
	{
		Scope* parent = getEnclosingScope(); // look in parent scope too! More complex implementation later
		if (parent)
		{
			return parent->resolve(name);
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		return symbols[name];
	}
}

std::string SymbolTable::to_string(int level) {
	std::string s;
	s = indent(2 * level) + getScopeName() + ":\n";
	for (const auto& elt : symbols)
	{
		if (elt.second)
		{
			s += indent(2 * level + 2) + elt.second->to_string() + "\n";
		}
	}
	Scope* parent = getEnclosingScope();
	if (parent)
	{
		s += parent->to_string(level + 1);
	}
	return s;
}