#pragma once

// Author: Garry Morrison
// Added: 2023-10-15
// Updated: 2023-10-15

// namespace SKet or not?

#include <iostream>
#include <string>
#include <map>
#include <vector>

// #include "../ScopedSymbol/ContextSymbol.h"
#include "../Symbol/BaseSymbol.h"
#include "../misc/misc.h"

class ContextSymbol;

class BaseScope {
public:
	virtual int getScopeID() = 0;
	virtual std::string getScopeName() = 0;
	virtual BaseScope* getEnclosingScope() = 0;
	virtual void addChild(BaseScope*) = 0;
	virtual std::vector<BaseScope*> getChildScopes() = 0;
	virtual void define(BaseSymbol* sym) = 0;
	virtual BaseSymbol* resolve(const std::string& name) = 0;
	virtual void defineContext(ContextSymbol* context) = 0;
	virtual ContextSymbol* resolveContext(const std::string& name) = 0;
	virtual std::string to_string() = 0;
	virtual std::string to_string(int level) = 0;
};
