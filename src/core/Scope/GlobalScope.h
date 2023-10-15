#pragma once

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

#include "BaseScope.h"
#include "../Parser/Serial.h"

extern Serial scope_serial;

class GlobalScope : public BaseScope {
public:
	int scope_id = -1;
	BaseScope* parent_scope = nullptr;
	size_t nkids = 0;
	std::vector<BaseScope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	GlobalScope() { scope_id = scope_serial.get_id(); initTypeSystem(); }
	void initTypeSystem();

	// satisfy our interface:
	int getScopeID() { return scope_id; }
	std::string getScopeName() { return "Global Scope"; }
	BaseScope* getEnclosingScope() { return parent_scope; }
	void addChild(BaseScope*);
	std::vector<BaseScope*> getChildScopes() { return kids; }
	void define(BaseSymbol* sym);
	BaseSymbol* resolve(const std::string& name);
	std::string to_string() { return to_string(1); }
	std::string to_string(int level);
};