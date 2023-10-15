#pragma once

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

#include "BaseScope.h"
#include "../Parser/Serial.h"
// #include "../ScopedSymbol/ContextSymbol.h"

extern Serial scope_serial;

class LocalScope : public BaseScope {
public:
	int scope_id = -1;
	BaseScope* parentScope = nullptr;
	size_t nkids = 0;
	std::vector<BaseScope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	std::map<std::string, ContextSymbol*> context_symbols;
	LocalScope() { scope_id = scope_serial.get_id(); }

	// satisfy our interface:
	int getScopeID() { return scope_id; }
	std::string getScopeName() { return "Local Scope"; }
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