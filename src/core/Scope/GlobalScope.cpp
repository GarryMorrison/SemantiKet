#include "GlobalScope.h"
#include "../ScopedSymbol/ContextSymbol.h"

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

void GlobalScope::initTypeSystem() {  // Add more types here later!
	define(new BuiltInType("bool"));
	define(new BuiltInType("float"));
	define(new BuiltInType("ket"));
	define(new BuiltInType("bra"));
	define(new BuiltInType("sp"));
	define(new BuiltInType("seq"));
	define(new BuiltInType("string"));
}

void GlobalScope::addChild(BaseScope* sc)
{
	if (sc)
	{
		kids.push_back(sc);
		nkids++;
	}
}

void GlobalScope::define(BaseSymbol* sym)
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


BaseSymbol* GlobalScope::resolve(const std::string& name)
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

void GlobalScope::defineContext(ContextSymbol* context)
{
	if (context)
	{
		if (!context->name.empty())
		{
			auto it = context_symbols.find(context->name);
			if (it == context_symbols.end())
			{
				context_symbols[context->name] = context;
			}
			else
			{
				// Error::ContextRedefinition, probably.
			}
		}
	}
}

ContextSymbol* GlobalScope::resolveContext(const std::string& name)
{
	auto it = context_symbols.find(name);
	if (it == context_symbols.end())
	{
		// Error::RefUnknownContext // wire this in!
	}
	else
	{
		return it->second;
	}
}

std::string GlobalScope::to_string(int level) {
	std::string s;
	s = indent(2 * level) + std::to_string(getScopeID()) + " " + getScopeName() + ":\n";
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
