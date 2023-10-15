#pragma once

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

#include "BaseScope.h"

class LocalScope : public BaseScope {
public:
	BaseScope* parent_scope = nullptr;
	size_t nkids = 0;
	std::vector<BaseScope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	LocalScope() {}

	// satisfy our interface:
	std::string getScopeName() { return "Local Scope"; }
	BaseScope* getEnclosingScope() { return parent_scope; }
	void addChild(BaseScope*);
	std::vector<BaseScope*> getChildScopes() { return kids; }
	void define(BaseSymbol* sym);
	BaseSymbol* resolve(const std::string& name);
	std::string to_string() { return to_string(1); }
	std::string to_string(int level);
};