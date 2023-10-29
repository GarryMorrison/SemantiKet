#include "ContextSymbol.h"

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

void ContextSymbol::addChild(BaseScope* sc)
{
	if (sc)
	{
		kids.push_back(sc);
		nkids++;
	}
}

void ContextSymbol::define(BaseSymbol* sym)
{
	if (sym)
	{
		std::string name = sym->getName();
		if (!name.empty())
		{
			if (symbols.find(name) == symbols.end()) // name is not in set, so insert it
			{
				std::cout << "ContextSymbol just stored symbol: " << name << "\n";
				symbols[name] = sym;
			}
			else
			{
				std::set<int> lines = sym->getLines(); // Do more stuff here later. Eg, check types match, and so on.
				for (int line : lines)
				{
					symbols[name]->appendLine(line); // use it->second->appendLine(line) instead?
				}
			}
		}
	}
}

BaseSymbol* ContextSymbol::resolve(const std::string& name)
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

void ContextSymbol::defineContext(ContextSymbol* context)
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

ContextSymbol* ContextSymbol::resolveContext(const std::string& name)
{
	if (name == "#previous")
	{
		ContextSymbol* tmp = previousContext;
		previousContext = currentContext;
		currentContext = tmp;
		return tmp;
	}
	auto it = context_symbols.find(name);
	if (it == context_symbols.end())
	{
		// Error::RefUnknownContext // wire this in!
		return nullptr;
	}
	else
	{
		ContextSymbol* tmp = it->second;
		previousContext = currentContext;
		currentContext = tmp;
		return tmp;
	}
}

std::string ContextSymbol::to_string(int level) {  // do something better here later?
	std::string s;
	s = indent(2 * level) + std::to_string(getScopeID()) + " " + getScopeName() + " " + getContextLabel() + ":\n";
	for (const auto& elt : symbols)
	{
		if (elt.second != nullptr)
		{
			s += indent(2 * level + 6) + elt.second->to_string() + "\n";
		}
	}
	for (const auto& elt : context_symbols)
	{
		if (elt.second != nullptr)
		{
			s += indent(2 * level + 6) + elt.second->to_string() + "\n";
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