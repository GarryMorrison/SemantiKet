#pragma once

// Author: Garry Morrison
// Added: 2023-10-29
// Updated: 2023-10-29

#include <string>
#include <vector>
#include <map>
#include "BaseScopedSymbol.h"
#include "ContextSymbol.h"
#include "../AST/FunctionDefinition.h"
#include "../Parser/Serial.h"

extern Serial scope_serial;

class FunctionSymbol : public BaseScopedSymbol {
public:
	int scope_id = -1;
	std::string name;
	std::string fn_name; // more FunctionSymbol specific variables later! Eg, arguments.
	std::vector<std::string> args;
	bool is_variadic = false;
	std::string fn_rule_type;
	BaseScope* parentScope = nullptr;
	ContextSymbol* currentContext = nullptr;
	ContextSymbol* previousContext = nullptr;
	size_t nkids = 0;
	std::vector<BaseScope*> kids;
	std::map<std::string, BaseSymbol*> symbols;
	std::map<std::string, ContextSymbol*> context_symbols;
	FunctionSymbol(SKet::FunctionDefinition& node);
	FunctionSymbol(SKet::FunctionDefinition& node, BaseScope* scope);

	std::string getFunctionName() { return fn_name; }
	ContextSymbol* getPreviousContext() { return previousContext; }

	// satisfy our Symbol interface:
	std::string getName() { return name; }

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