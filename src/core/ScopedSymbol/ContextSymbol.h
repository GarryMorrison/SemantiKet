#pragma once

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

#include <string>
#include <vector>
#include <map>
#include "BaseScopedSymbol.h"
#include "../Parser/Serial.h"

extern Serial scope_serial;

class ContextSymbol : public BaseScopedSymbol {
public:
	int scope_id = -1;
	std::string name;
	std::string label; // more ContextSymbol specific variables later! Eg, supported-ops, terminals, and non-terminals.
	BaseScope* parentScope = nullptr;
	size_t nkids = 0;
	std::vector<BaseScope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	std::map<std::string, ContextSymbol*> context_symbols;

	ContextSymbol(const std::string& name1, const std::string& label1, BaseScope* scope) { 
		scope_id = scope_serial.get_id();
		name = name1;
		label = label1;
		if (scope)  // Probably an Error if nullptr.
		{
			parentScope = scope;
		}
	}

	std::string getContextLabel() { return label; }

	// satisfy our Scope interface:
	int getScopeID() { return scope_id; }
	std::string getScopeName() { return name; }
	BaseScope* getEnclosingScope() { return parentScope; }
	void addChild(BaseScope*);
	std::vector<BaseScope*> getChildScopes() { return kids; }
	void define(BaseSymbol* sym);
	BaseSymbol* resolve(const std::string& name);
	void defineContext(ContextSymbol* context);
	ContextSymbol* resolveContext(const std::string& name);
	std::string to_string() { return to_string(1); }
	std::string to_string(int level);
};