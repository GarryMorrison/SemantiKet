#include "LocalScope.h"

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15


void LocalScope::addChild(BaseScope* sc)
{
	if (sc)
	{
		kids.push_back(sc);
		nkids++;
	}
}

void LocalScope::define(BaseSymbol* sym)
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
					symbols[sym->name]->appendLine(line); // use it->second->appendLine(line) instead?
				}
			}
		}
	}
}

BaseSymbol* LocalScope::resolve(const std::string& name)
{
	auto it = symbols.find(name);
	if (it == symbols.end())
	{
		BaseScope* parent = getEnclosingScope(); // look in parent scope too! More complex implementation later
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
		return it->second;
	}
}

std::string LocalScope::to_string(int level) {
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
	for (BaseScope* child : kids)
	{
		if (child)
		{
			s += child->to_string(level + 1);
		}
	}
	return s;
}
