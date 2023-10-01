// Author: Garry Morrison
// Added: 2023-9-30
// Updated: 2023-9-30

#include "SymTable.h"

SymbolTable::SymbolTable(const std::string& name, Scope* scope)
{
	this->name = name; 
	this->parent_scope = scope; 
	if (this->parent_scope)
	{
		this->parent_scope->addChild(this);  // does this work?
	}
}

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

void SymbolTable::addChild(Scope* sc)
{
	if (sc)
	{
		kids.push_back(sc);
		nkids++;
	}
}

/*
void SymbolTable::define(Symbol* sym) {
	if (sym != nullptr)
	{
		if (!sym->name.empty())
		{
			symbols[sym->name] = sym;
		}
	}
}
*/
void SymbolTable::define(Symbol* sym)
{
	if (sym)
	{
		if (!sym->name.empty())
		{
			if (symbols.find(sym->name) == symbols.end()) // name is not in set, so insert it
			{
				symbols[sym->name] = sym;
			}
			else
			{
				std::set<int> lines = sym->getLines(); // Do more stuff here later. Eg, check types match, and so on.
				for (int line : lines)
				{
					symbols[sym->name]->appendLine(line);
				}
			}
		}
	}
}

Symbol* SymbolTable::resolve(const std::string& name)
{
	if (symbols.find(name) == symbols.end())  
	{
		Scope* parent = getEnclosingScope(); // look in parent scope too! More complex implementation later
		if (parent != nullptr)
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
		if (elt.second != nullptr)
		{
			s += indent(2 * level + 2) + elt.second->to_string() + "\n";
		}
	}
	/*
	Scope* parent = getEnclosingScope();
	if (parent != nullptr)
	{
		s += parent->to_string(level + 1);
	}
	*/
	for (Scope* child : kids)
	{
		if (child)
		{
			s += child->to_string(level + 1);
		}
	}
	return s;
}